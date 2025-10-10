#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

string goal = "123456780"; // goal state (0 = blank)

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

// Moves for blank (up, down, left, right)
vector<int> moves = {-3, 3, -1, 1};

// Check if move is valid
bool isValid(int pos, int move)
{
    if (pos % 3 == 0 && move == -1)
        return false; // left edge
    if (pos % 3 == 2 && move == 1)
        return false; // right edge
    int newPos = pos + move;
    return (newPos >= 0 && newPos < 9);
}

void BFS(string start)
{
    queue<string> q;
    set<string> visited;
    map<string, string> parent;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    while (!q.empty())
    {
        string state = q.front();
        q.pop();

        if (state == goal)
        {
            cout << "\nBFS Solution Path:\n";
            vector<string> path;
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
            return;
        }

        int pos = state.find('0');
        for (int m : moves)
        {
            if (isValid(pos, m))
            {
                string next = state;
                swap(next[pos], next[pos + m]);
                if (!visited.count(next))
                {
                    visited.insert(next);
                    parent[next] = state;
                    q.push(next);
                }
            }
        }
    }

    cout << "No solution found using BFS.\n";
}

int main()
{
    string start = "103425786"; // Change start state
    cout << "Start State:";
    printState(start);
    BFS(start);
    return 0;
}
