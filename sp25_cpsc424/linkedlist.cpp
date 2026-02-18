void insert(int val)
{
    Node* pred = head;
    std::unique_lock<std::mutex> pred_lock(pred->m);

    Node* curr = pred->next;
    std::unique_lock<std::mutex> curr_lock;
    if (curr)
    {
        curr_lock = std::unique_lock<std::mutex>(curr->m);
    }

    while (curr && curr->value < val)
    {
        pred_lock.unlock();
        pred = curr;
        pred_lock = std::move(curr_lock);

        Node* next = pred->next;

        if (next)
        {
            curr_lock = std::unique_lock<std::mutex>(next->m);
        }
        else
        {
            curr_lock = std::unique_lock<std::mutex>();
        }
        curr = next;
    }

    Node* new_node = new Node(val, curr);
    pred->next = new_node;
}
