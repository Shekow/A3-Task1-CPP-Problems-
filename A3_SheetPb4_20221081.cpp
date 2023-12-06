// File name: A3_SheetPb4_20221081.cpp
// Purpose: Solving problem 4 in the sheet (Set Template)
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

template<typename T> class Set
{
    vector<T> values;
    public:
    void insert(T newvalue)
    {
        // checking if the value is already in the set (using binary search since the vector is sorted).
        // If so, do nothing. Otherwise, add it to the set.
        if (!binary_search(all(values), newvalue))
        {
            // Insert the new value in the right position using binary search to keep the set sorted.
            values.insert(lower_bound(all(values), newvalue), newvalue);
        }
    }
    void erase(T value)
    {
        // checking if the value is already in the set (using binary search since the vector is sorted).
        // If so, erase it using binary search
        if (binary_search(all(values), value))
        {
            values.erase(lower_bound(all(values), value));
        }
    }
    size_t size() const
    {
        return values.size();
    }
    bool exists(T value) const
    {
        return binary_search(all(values), value);
    }
    T *getElements() const
    {
        T *ptr = new T[size()];
        for (size_t i{}; i < size(); i++)
        {
            ptr[i] = values[i];
        }
        return ptr;
    }
    bool operator=(const Set<T> &rhs) const
    {
        return values == rhs.values;
    }
    bool operator!=(const Set<T> &rhs) const
    {
        return values != rhs.values;
    }
    bool operator>(const Set<T> &rhs) const
    {
        return values > rhs.values;
    }
    bool operator<(const Set<T> &rhs) const
    {
        return values < rhs.values;
    }
    bool operator>=(const Set<T> &rhs) const
    {
        return values >= rhs.values;
    }
    bool operator<=(const Set<T> &rhs) const
    {
        return values <= rhs.values;
    }
};




int main()
{
    Set<string> st;
    st.insert("foo");
    st.insert("2nd string");
    st.insert("3nd string");
    st.erase("2nd string");
    st.erase("unknown string");
    cout << st.exists("bar") << endl;
    cout << st.exists("foo") << endl;
    cout << st.size() << endl;
    auto ptr = st.getElements();
    for (size_t i{}; i < st.size(); i++) cout << ptr[i] << endl;
    delete [] ptr;
}

