// File name: A3_SheetPb2_20221081.cpp
// Purpose: Solving problem 2 in the sheet (StringSet)
// Author(s): Sherif Youssef Mahmoud
// ID(s): 20221081
// Section: 21
// Date: Dec 6th, 2023
// Version: 1

#include <iostream>
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define ld long double
#define each auto &
#define endl '\n'
#define pll pair<ll, ll>
#define all(v) v.begin(), v.end()
using namespace std;

class StringSet
{
    vector<string> words;
    // This function loads the vector of string with the words in the input string.
    void load(string content)
    {
        string word;
        content.push_back(' ');
        for (char c: content)
        {
            if (isalnum(c) || c == '-') 
            {
                word.push_back(tolower(c));
            }
            else if (!word.empty())
            {
                push(word);
                word.clear();
            }
        }
    }
    public:
    StringSet(string s = ""s)
    {
        // Checks if a file is a text file or not. 
        // IF it is, load the contents of the file using an input file stream and an output file stream into the set
        // Otherwise, load the words of the input string immmediately
        if (s.find(".txt") != string::npos && s.find(".txt") == s.size() - 4)
        {
            ifstream fs(s);
            ostringstream oss;
            oss << fs.rdbuf();
            load(oss.str());
        }
        else 
        {
            load(s);
        }
    }
    void push(string newWord)
    {
        // checking if the word is already in the set (using binary search since the vector is sorted).
        // If so, do nothing. Otherwise, add it to the set.
        if (!binary_search(all(words), newWord))
        {
            // Insert the new word in the right position using binary search to keep the set sorted.
            words.insert(lower_bound(all(words), newWord), newWord);
        }
    }
    void erase(string word)
    {
        // checking if the word is already in the set (using binary search since the vector is sorted).
        // If so, erase it using binary search
        if (binary_search(all(words), word))
        {
            words.erase(lower_bound(all(words), word));
        }
    }
    void clear()
    {
        words.clear();
    }
    size_t size() const
    {
        return words.size();
    }
    void display() const
    {
        cout << "{";
        for (const string &s: words)
        {
            cout << s << ", ";
        }
        cout << "}\n";
    }
    
    // Calculates the union of two StringSets
    StringSet operator+(StringSet &rhs) const
    {
        StringSet result;
        set_union(all(words), all(rhs.words), back_inserter(result.words));
        return result;
    }

    // Calculates the intersection of two StringSets
    StringSet operator*(StringSet &rhs) const
    {
        StringSet result;
        set_intersection(all(words), all(rhs.words), back_inserter(result.words));
        return result;
    }

    // Calculating the binary cosine coefficient
    double CommputeSimilarity(StringSet &another) const
    {
        if (this->size() == 0 || another.size() == 0) return 0;
        return (*this * another).size() / (sqrt(this->size()) * sqrt(another.size()));
    }
};




int main()
{
    StringSet ss[2];
    while (1)
    {
        cout << "===============================\n";
        cout << "1-Load a StringSet\n";
        cout << "2-Add a new word to a StringSet\n";
        cout << "3-Remove a word from a StringSet\n";
        cout << "4-Clear a StringSet\n";
        cout << "5-Display the size of a StringSet\n";
        cout << "6-Display a StringSet\n";
        cout << "7-Union of both StringSets\n";
        cout << "8-Intersection of both StringSets\n";
        cout << "9-Similarity of both StringSets\n";
        cout << "0-Exit\n";
        cout << "===============================\n";
        int op;
        cin >> op;
        if (op == 0) return 0;
        else if (op > 0 && op < 7)
        {
            int idx;
            cout << "Which one? ";
            cin >> idx;
            idx--;
            if (op == 1)
            {
                string s;
                cout << "===============================\n";
                cout << "1-Load using a text file\n";
                cout << "2-Load using a string\n";
                cout << "===============================\n";
                cin >> op;
                
                if (op == 1)
                {
                    cout << "File name: ";
                    cin >> s;
                }
                else
                {
                    cout << "Text: ";
                    getline(cin, s);
                    getline(cin, s);
                }
                ss[idx] = StringSet(s);
            }
            else if (op == 2 || op == 3)
            {
                string word;
                cout << "Word: ";
                cin >> word;
                if (op == 2) ss[idx].push(word);
                else ss[idx].erase(word);
            }
            else if (op == 4)
            {
                ss[idx].clear();
            }
            else if (op == 5)
            {
                cout << ss[idx].size() << endl;
            }
            else 
            {
                ss[idx].display();
            }
        }
        else if (op == 7)
        {
            (ss[0] + ss[1]).display();
        }
        else if (op == 8)
        {
            (ss[0] * ss[1]).display();
        }
        else if (op == 9)
        {
            cout << ss[0].CommputeSimilarity(ss[1]) << endl;
        }
    }
}

