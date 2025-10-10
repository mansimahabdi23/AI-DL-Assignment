#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

string goal = "123456780"; // goal state

// Print 3x3 puzzle
void printState(string s)
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << "\n";
        cout << s[i] << " ";
    }
    cout << "\n";
}

vector<int> moves = {-3, 3, -1, 1};

// Check if move is valid
bool isValid(int pos, int move)
{
    if (pos % 3 == 0 && move == -1)
        return false;
    if (pos % 3 == 2 && move == 1)
        return false;
    int newPos = pos + move;
    return (newPos >= 0 && newPos < 9);
}

bool DFSUtil(string state, set<string> &visited, map<string, string> &parent, int depth, int limit)
{
    if (state == goal)
        return true;
    if (depth >= limit)
        return false;

    visited.insert(state);
    int pos = state.find('0');

    for (int m : moves)
    {
        if (isValid(pos, m))
        {
            string next = state;
            swap(next[pos], next[pos + m]);
            if (!visited.count(next))
            {
                parent[next] = state;
                if (DFSUtil(next, visited, parent, depth + 1, limit))
                    return true;
            }
        }
    }
    return false;
}

void DFS(string start, int limit = 20)
{
    set<string> visited;
    map<string, string> parent;

    if (DFSUtil(start, visited, parent, 0, limit))
    {
        cout << "\nDFS Solution Path:\n";
        vector<string> path;
        string state = goal;
        while (state != "")
        {
            path.push_back(state);
            state = parent[state];
        }
        reverse(path.begin(), path.end());
        for (auto &s : path)
        {
            printState(s);
            cout << "-----\n";
        }
    }
    else
    {
        cout << "No solution found with DFS (limit = " << limit << ").\n";
    }
}

int main()
{
    string start = "103425786"; // Change start state
    cout << "Start State:";
    printState(start);
    DFS(start, 20);
    return 0;
}
