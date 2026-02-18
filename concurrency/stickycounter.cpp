struct badConcurrentCounter
{
    bool increment_if_not_zero()
    {
        if (counter > 0)
        {
            ++counter;
            return true;
        }
        return false;
    }

    bool decrement()
    {
        return (--counter == 0);
    }

    uint64_t read()
    {
        return counter;
    }

    uint64_t counter{1};
}

// above is not thread-safe
// increment_if_not_zero is not atomic
// so if one thread enters the yes-block at line 6, then (real-time) another thread decrements, then the first thread resumes, we get incorrect behavior

struct lockedConcurrentCounter
{
    std::lock_guard g_{m};
    bool increment_if_not_zero()
    {
        if (counter > 0)
        {
            ++counter;
            return true;
        }
        return false;
    }

    bool decrement()
    {
        std::lock_guard g_{m};
        return (--counter == 0);
    }

    uint64_t read()
    {
        return counter;
    }

    std::mutex m;
    uint64_t counter{1};
}

// locks get rid of concurrency!
// blocking

struct lockFreeConcurrentCounter
{
    bool increment_if_not_zero()
    {
        auto current = counter.load();
        while (current > 0 && !counter.compare_exchange_weak(current, current + 1))
        {
        }
        // counter.compare_exchange(current, current + 1):
        // if counter == current, increment counter to current + 1 and return true
        // else set current = counter and return false
        return current > 0;
    }

    bool decrement()
    {
        return counter.fetch_sub(1) == 1;
        // return original value of counter after subtracting 1
    }

    uint64_t read()
    {
        return counter.load();
    }

    std::atomic<uint64_t> counter{1};
}


struct lockFreeConcurrentCounter
{
	static constexpr unsigned uint64_t is_zero = 1ull << 63;
	static constexpr unsigned uint64_t helped = 1ull << 62;

    bool increment_if_not_zero()
    {
		return (counter.fetch_add(1) & is_zero) == 0;
    }

    bool decrement()
    {
		if (counter.fetch_sub(1) == 1)
		{
			uint64_t e = 0;
			if (counter.compare_exchange_strong(e, is_zero))
			{
				return true;
			}
			else if ((e & helped) && (counter.exchange(is_zero) & helped)) 
			{
				return true;
			}
		}
		return false;
    }

    uint64_t read()
    {
        return counter.load();
		if (val == 0 && counter.compare_exchange_string(val, is_zero | helped)) // possible only if another thread is doing CAS in decrement --- help them!
																	   // but be careful, because the decrement's CAS will always fail --- so use another bit
		{
			return 0;
		}
		return (val & is_zero) ? 0 : val;
    }

	std::atomic<uint64_t> counter{1};
}

// if CAS decrement return false (counter wasn't actually zero):
// this is because we entered the if block (by setting counter to zero)
// and then we noticed that the value was no longer zero (e != counter)
// so we say that the decrement linearizes after that increment (even though at the time of the if statement the decrement had happened and the bits were actually zero)
// But! Then allowing a read operation exposes real-time incorrect behavior
