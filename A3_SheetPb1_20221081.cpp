// File name: A3_SheetPb1_20221081.cpp
// Purpose: Solving problem 1 in the sheet (Label generation)
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

class LabelGenerator
{
    protected:
    string prefix;
    int index;
    public:
    LabelGenerator(string prefix, int initialIndex): prefix(prefix), index(initialIndex)
    {

    }
    virtual string nextLabel()
    {
        string label = prefix + to_string(index);
        index++;
        return label;
    }
};

class FileLabelGenerator: public LabelGenerator
{
    vector<string> fileLabels;
    size_t vIndex;
    public:
    FileLabelGenerator(string prefix, int initialIndex, string fileName): LabelGenerator(prefix, initialIndex)
    {
        // Setting the vector index to zero
        vIndex = 0;
        // Initializing an input file stream for fileName
        ifstream fs(fileName);
        string label;
        // Reading the file contents into the vector (as lines)
        while (getline(fs, label))
        {
            fileLabels.push_back(label);
        }
        // Closing the file stream
        fs.close();
    }
    string nextLabel() override
    {
        // Returns a basic label if we have reached the end of the file. 
        // Otherwise, returns the basic label concatenated sith a specific line from the file
        string label = LabelGenerator::nextLabel() + " " + (vIndex < fileLabels.size() ? fileLabels[vIndex] : ""s);
        vIndex++;
        return label;
    }
};


int main()
{
    cout << "==========================\n";
    cout << "1-LabelGenerator\n";
    cout << "2-FileLabelGenerator\n";
    cout << "==========================\n";
    int op;
    LabelGenerator *LG{};
    string prefix, fileName;
    int index;
    cin >> op;
    if (op == 1 || op == 2)
    {
        cout << "Prefix: ";
        cin >> prefix;
        cout << "Initial Index: ";
        cin >> index;
        if (op == 1) LG = new LabelGenerator(prefix, index);
        else
        {
            cout << "File name: ";
            cin >> fileName;
            LG = new FileLabelGenerator(prefix, index, fileName);
        }
        while (1)
        {
            cout << "==========================\n";
            cout << "1-Next Label\n";
            cout << "0-Exit\n";
            cout << "==========================\n";
            cin >> op;
            if (!op) return 0;
            else if (op == 1)
            {
                cout << LG->nextLabel() << endl;
            }
        }
    }
}

