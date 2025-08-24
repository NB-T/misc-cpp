#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Normalize input: lowercase and remove non-alpha
string normalize(const string& s)
{
    string result;
    for (char c : s)
        if (isalpha(c)) result += tolower(c);
    return result;
}

unordered_map<char, int> count_letters(const string& s)
{
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    return count;
}

bool can_form(const string& word, const unordered_map<char, int>& letters)
{
    unordered_map<char, int> temp;
    for (char c : word) temp[c]++;
    for (auto& [c, n] : temp)
        if (n > letters.at(c)) return false;
    return true;
}

bool subtract_letters(unordered_map<char, int>& from, const string& word)
{
    for (char c : word)
    {
        if (--from[c] < 0) return false;
    }
    return true;
}

void add_letters(unordered_map<char, int>& to, const string& word)
{
    for (char c : word) ++to[c];
}

bool letters_empty(const unordered_map<char, int>& m)
{
    for (auto& [c, n] : m)
        if (n > 0) return false;
    return true;
}

bool has_vowel(const string& word)
{
    static const string vowels = "aeiou";
    for (char c : word)
        if (vowels.find(c) != string::npos) return true;
    return false;
}

// Output multiple valid anagrams
void solve(vector<string>& result, vector<string>& candidates,
           unordered_map<char, int>& remaining,
           int idx,
           int& count,
           const int max_results)
{
    if (letters_empty(remaining))
    {
        for (size_t i = 0; i < result.size(); ++i)
        {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
        count++;
        return;
    }
    if (count >= max_results) return;

    for (int i = idx; i < candidates.size(); ++i)
    {
        const string& word = candidates[i];
        unordered_map<char, int> backup = remaining;
        if (!subtract_letters(remaining, word))
        {
            remaining = backup;
            continue;
        }
        result.push_back(word);
        solve(result, candidates, remaining, i, count, max_results);
        result.pop_back();
        remaining = backup;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " \"your input string\"" << endl;
        return 1;
    }
    string input = argv[1];

    string normalized = normalize(input);
    auto letter_count = count_letters(normalized);

    // Load dictionary
    ifstream dict("words_alpha.txt");  // Replace with your dictionary path
    if (!dict.is_open())
    {
        cerr << "Failed to open dictionary file." << endl;
        return 1;
    }

    unordered_set<string> dict_words;
    string word;
    while (dict >> word)
    {
        word = normalize(word);

        // Skip empty or non-lowercase-only words
        if (word.empty() || !all_of(word.begin(), word.end(), ::islower))
            continue;

        // Only allow 1-letter words "a" or "i"
        if (word.length() == 1 && word != "a" && word != "i")
            continue;

        // Disallow words with no vowels
        if (!has_vowel(word))
            continue;

        // Must only contain letters from input
        bool valid = true;
        for (char c : word)
            if (letter_count.find(c) == letter_count.end())
            {
                valid = false;
                break;
            }

        if (valid) dict_words.insert(word);
    }

    // Filter candidates
    vector<string> candidates;
    for (const auto& w : dict_words)
        if (can_form(w, letter_count)) candidates.push_back(w);

    sort(candidates.begin(), candidates.end());  // Optional: for stable output

    // Solve and print multiple anagrams
    vector<string> result;
    unordered_map<char, int> rem = letter_count;
    int found = 0;
    const int max_results = 1000;
    solve(result, candidates, rem, 0, found, max_results);

    if (found == 0)
        cout << "No anagrams found." << endl;
}
