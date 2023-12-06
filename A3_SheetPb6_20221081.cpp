// File name: A3_SheetPb6_20221081.cpp
// Purpose: Solving problem 6 in the sheet (Game of Life)
// Author(s): Sherif Youssef Mahmoud
// ID(s): 20221081
// Section: 21
// Date: Dec 6th, 2023
// Version: 1

#include <iostream>
#include <stdlib.h>
#include <time.h>
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


class Universe
{
    size_t rows, cols;
    bool **grid;
    char mark;
    // Bounds checking
    bool inbounds(size_t x, size_t y)
    {
        return (x >= 0 && x < rows && y >= 0 && y < cols);
    }
    // This function returns a 2d array of type bool
    bool** newGrid()
    {
        bool **ptr = new bool*[rows];
        for (int i = 0; i < rows; i++) 
        {
            ptr[i] = new bool[cols]{};
        }
        return ptr;
    }
    public:
    Universe(size_t rows = 30, size_t cols = 30, char mark = '#') : rows(rows), cols(cols), mark(mark)
    {
        grid = newGrid();
    }
    // This function copies the content from the input array to the grid array
    void intialize(bool **layout)
    {
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < cols; j++)
            {
                grid[i][j] = layout[i][j];
            }
        }
    }
    // This function resert all cells in the grid to be dead
    void reset()
    {
        memset(grid, 0, sizeof grid);
    }
    void reverseCell(size_t row, size_t col)
    {
        if (inbounds(row, col))
            grid[row][col] = !grid[row][col];
    }
    void editMark(char newMark)
    {
        mark = newMark;
    }
    // This function creates a new random grid
    void randomizeGrid()
    {
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < cols; j++)
            {
                grid[i][j] = rand() % 2;
            }
        }
    }
    // This function counts the number of alive cells that are adjacent to a specific cell
    int countNeighbors(size_t x, size_t y)
    {
        int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
        int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};

        int ctr{};
        for (size_t i{}; i < 8; i++)
        {
            size_t nx = x + dx[i], ny = y + dy[i];
            if (inbounds(nx, ny) && grid[nx][ny]) ctr++;
        }
        return ctr;
    }
    // This function generated the next state of the game
    void nextGeneration()
    {
        bool **tmp = newGrid();
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < cols; j++)
            {
                if ((grid[i][j] && (countNeighbors(i, j) == 2 || countNeighbors(i, j) == 3)) 
                || (!grid[i][j] && countNeighbors(i, j) == 3))
                {
                    tmp[i][j] = 1;
                }
            }
        }
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < cols; j++)
            {
                grid[i][j] = tmp[i][j];
            }
        }
        delete [] tmp;
    }
    // This function outputs the grid to a specfied ouput stream
    void display(ostream &os)
    {
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < cols; j++)
            {
                if (grid[i][j]) 
                    os << mark;
                else 
                    os << ".";
            }
            os << endl;
        }
    }
    void run(size_t runs)
    {
        for (size_t i{}; i < runs; i++)
        {
            nextGeneration();
        }
    }
    // This function runs the game for a number of times while displaying 
    // each new state and waiting for some time after generating each new state
    void runAndDisplay(size_t runs, double delay = 1, string fileName = "") 
    {
        bool fs{!fileName.empty()};
        for (size_t i{}; i < runs + 1; i++)
        {
            if (fs) 
            {
                ofstream ofs(fileName, ofstream::out | ofstream::trunc);
                display(ofs);
                ofs.close();
            }
            else 
            {
                system("cls");
                display(cout);
            }
            Sleep(1000 * delay);
            if (i < runs) nextGeneration();
        }
    }
    ~Universe()
    {
        delete [] grid;
    }
};





int main()
{
    srand(time(0));
    size_t rows, cols;
    cout << "Dimensions of the grid: \n";
    cout << "Rows: ";
    cin >> rows;
    cout << "Columns: ";
    cin >> cols;
    Universe uni(rows, cols);
    string fileName;
    double delay{1};
    while (true)
    {
        int op;
        cout << "======================================\n";
        cout << "1-Edit the grid/game\n";
        cout << "2-Edit the output destination\n";
        cout << "3-Run the game\n";
        cout << "0-Exit\n";
        cout << "======================================\n";
        cout << "Response: ";
        cin >> op;
        if (op == 0) 
        {
            cout << "Hope you enjoyed ^^\n";
            return 0;
        }
        else if (op == 1)
        {
            while (true)
            {
                cout << "======================================\n";
                cout << "1-Load a new layout (" << rows << "x" << cols << ")\n";
                cout << "2-Reverse a cell with index\n";
                cout << "3-Randomize the grid\n";
                cout << "4-Change the \'ON\' symbol\n";
                cout << "5-change the delay\n";
                cout << "0-Back\n";
                cout << "======================================\n";
                cout << "Response: ";
                cin >> op;
                if (op == 0) break;
                else if (op == 1)
                {
                    string fileName, line;
                    size_t lineIndex{};
                    bool ** layout = new bool*[rows];
                    for (size_t i{}; i < rows; i++)
                        layout[i] = new bool[cols]{};
                    cout << "File name: ";
                    cin >> fileName;
                    ifstream ifs(fileName);
                    while (getline(ifs, line))
                    {
                        for (size_t charIndex{}; charIndex < line.size(); charIndex++)
                        {
                            layout[lineIndex][charIndex] = line[charIndex] != '.';
                        }
                        lineIndex++;
                    }
                    uni.intialize(layout);
                }
                else if (op == 2)
                {
                    size_t x, y;
                    cout << "Index: ";
                    cin >> x >> y;
                    uni.reverseCell(x, y);
                }
                else if (op == 3)
                {
                    uni.randomizeGrid();
                }
                else if (op == 4)
                {
                    char ns;
                    cout << "New Symbol: ";
                    cin >> ns;
                    uni.editMark(ns);
                }
                else if (op == 5)
                {
                    cout << "New delay(seconds): ";
                    cin >> delay;
                }
            }
        }
        else if (op == 2)
        {
            cout << "======================================\n";
            cout << "1-Terminal\n";
            cout << "2-Text file\n";
            cout << "======================================\n";
            cout << "Response: ";
            cin >> op;
            if (op == 1)
            {
                fileName.clear();
            }
            else if (op == 2)
            {
                cout << "file name: ";
                cin >> fileName;
            }
        }
        else if (op == 3)
        {
            size_t runs;
            cout << "No. of runs: ";
            cin >> runs;
            uni.runAndDisplay(runs, delay, fileName);
        }
    }
}

