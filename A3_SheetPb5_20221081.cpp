// File name: A3_SheetPb5_20221081.cpp
// Purpose: Solving problem 5 in the sheet (Task Manager)
// Author(s): Sherif Youssef Mahmoud
// ID(s): 20221081
// Section: 21
// Date: Dec 6th, 2023
// Version: 1

#include <iostream>
#include <windows.h>
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define ld long double
#define each auto &
#define endl '\n'
#define pll pair<ll, ll>
#define all(v) v.begin(), v.end()
using namespace std;

class Process
{
    string name, sessionName;
    size_t ID, sessionID, memUsage;
    public:
    Process(string name, size_t ID, size_t memUsage = 0, string sessionName = "", size_t sessionID = 0) 
    : name(name), ID(ID), memUsage(memUsage), sessionName(sessionName), sessionID(sessionID)
    {

    }
    string getName() const
    {
        return name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    size_t getID() const
    {
        return ID;
    }
    void setID(size_t ID)
    {
        this->ID = ID;
    }
    size_t getMemUsage() const
    {
        return memUsage;
    }
    void setMemUsage(size_t memUsage)
    {
        this->memUsage = memUsage;
    }
    string getSessionName() const
    {
        return sessionName;
    }
    void setSessionName(string sessionName)
    {
        this->sessionName = sessionName;
    }
    size_t getSessionID() const
    {
        return sessionID;
    }
    void setSessionID(size_t sessionID)
    {
        this->sessionID = sessionID;
    }
};


class RunningPrccesses
{
    vector<Process> pList;
    // This function checks if the given string is an integer or nor
    bool isInt(string s)
    {
        for (char c: s) 
        {
            if (!isdigit(c)) return false;
        }
        return true;
    }
    // this function unformated numbers like (13,45 -> 1345)
    string unFormat(string s)
    {
        string ns;
        for (char c: s) 
        {
            if (isdigit(c)) ns.push_back(c);
        }
        return ns;
    }
    // this function prints the contents of a vector of Process
    void display(const vector<Process> &vec)
    {
        size_t w = 15;
        cout << setw(2 * w) << "Process Name" << setw(w) << "PID" << setw(w) << "Session Name" << setw(w) << "Session ID" << setw(w) << "Mem Usage(KB)" << endl;
        cout << "==============================================================================================" << endl;
        for (auto &p: vec)
        {
            cout << setw(2 * w) << p.getName();
            cout << setw(w) << p.getID();
            cout << setw(w) << p.getSessionName();
            cout << setw(w) << p.getSessionID();
            cout << setw(w) << p.getMemUsage();
            cout << endl;
        }
        cout << "==============================================================================================" << endl;
    }
    public:
    // This function loads the info of the running tasks from the OS liks so:
    // redirects the result of the tasklist command to a temporary file
    // read each line (starting from the third one) in the file and splits it into 5 variables
    // close the file stream and delete the temporary file
    bool loadFromOS()
    {
        system("tasklist > tlout.txt");
        ifstream fs("tlout.txt");
        if (!fs.is_open()) return false;
        string line;
        size_t lineCtr{1};
        while (getline(fs, line))
        {
            if (lineCtr > 3)
            {
                deque<string> words;
                string word, name, PID, sName, sID, mUsage;
                for (char c: line)
                {
                    if (c == ' ')
                    {
                        if (!word.empty())
                        {
                            words.push_back(word);
                            word.clear();
                        }
                    }
                    else word.push_back(c);
                }
                // last word is always "K"

                while (!isInt(words.front()))
                {
                    name += words.front() + " ";
                    words.pop_front();
                }
                PID = words.front();
                words.pop_front();
                while (!isInt(words.front()))
                {
                    sName += words.front() + " ";
                    words.pop_front();
                }
                sID = words[0], mUsage = words[1];
                pList.push_back(Process(name, stoull(PID), stoull(unFormat(mUsage)), sName, stoull(sID)));
            }
            lineCtr++;
        }
        fs.close();
        remove("tlout.txt");
        return true;
    }
    void clear()
    {
        pList.clear();
    }
    size_t size()
    {
        return pList.size();
    }
    Process operator[](size_t index)
    {
        return pList[index];
    }
    
    void displaySortedByName()
    {
        vector<Process> tmp = pList;
        sort(all(tmp), [](const Process p1, const Process p2)
        {
            return p1.getName() < p2.getName();
        });
        display(tmp);
    }
    void displaySortedByID()
    {
        vector<Process> tmp = pList;
        sort(all(tmp), [](const Process p1, const Process p2)
        {
            return p1.getID() < p2.getID();
        });
        display(tmp);
    }
    void displaySortedByMemUsage()
    {
        vector<Process> tmp = pList;
        sort(all(tmp), [](const Process p1, const Process p2)
        {
            return p1.getMemUsage() < p2.getMemUsage();
        });
        display(tmp);
    }
};






int main()
{
    RunningPrccesses rps;
    size_t delay = 3;
    while (1)
    {
        cout << "=================================================\n";
        cout << "1-Display the current list of running processes\n";
        cout << "2-Display the list of processes live\n";
        cout << "0-Exit\n";
        cout << "=================================================\n";
        int res, op, timer;
        cin >> res;
        if (res == 0) return 0;
        else if (res < 0 || res > 2) continue;
        cout << "=================================================\n";
        cout << "Sorted by:\n";
        cout << "1-Name\n";
        cout << "2-ID\n";
        cout << "3-Memory Usage\n";
        cout << "=================================================\n";
        cin >> op;
        if (op < 1 || op > 3) continue;
        if (res == 2)
        {
            cout << "=================================================\n";
            cout << "For how many seconds?\n";
            cout << "=================================================\n";
            cin >> timer;
        }
        else timer = 1;
        while (timer > 0)
        {
            system("cls");
            rps.loadFromOS();
            if (op == 1) rps.displaySortedByName();
            else if (op == 2) rps.displaySortedByID();
            else rps.displaySortedByMemUsage();
            rps.clear();
            Sleep(delay * 1000);
            timer -= delay;
        }
    }
}

