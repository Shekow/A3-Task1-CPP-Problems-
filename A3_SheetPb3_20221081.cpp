// File name: A3_SheetPb3_20221081.cpp
// Purpose: Solving problem 3 in the sheet (Frequency Table)
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


int main()
{
    map<string, int> freq;
    string fileName;
    cout << "Input File: ";
    cin >> fileName;
    ifstream fs(fileName);
    ostringstream oss;
    oss << fs.rdbuf();
    fs.close();
    string content(oss.str()), word;
    for (char c: content)
    {
        if (isalnum(c) || c == '-') word.push_back(tolower(c));
        else if (!word.empty())
        {
            freq[word]++;
            word.clear();
        }
    }
    if (!word.empty())
    {
        freq[word]++;
    }
    cout << "=============================================" << endl;
    for (auto &e: freq)
    {
        cout << setw(10) << e.first << setw(10) << e.second << endl;
    }
    cout << "=============================================" << endl;
}

