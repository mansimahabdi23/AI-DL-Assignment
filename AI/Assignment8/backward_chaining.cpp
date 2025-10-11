#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Structure to store rules
struct Rule
{
    vector<string> conditions;
    string conclusion;
};

// Recursive backward chaining function
bool backwardChain(const string &goal,
                   const vector<Rule> &rules,
                   const unordered_set<string> &facts,
                   unordered_set<string> &visited)
{

    // If goal already known
    if (facts.find(goal) != facts.end())
        return true;

    // Prevent infinite recursion
    if (visited.find(goal) != visited.end())
        return false;
    visited.insert(goal);

    // Search for rules that can conclude the goal
    for (const auto &rule : rules)
    {
        if (rule.conclusion == goal)
        {
            bool allTrue = true;
            for (const auto &cond : rule.conditions)
            {
                if (!backwardChain(cond, rules, facts, visited))
                {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue)
                return true;
        }
    }
    return false;
}

int main()
{
    // Define rules
    vector<Rule> rules = {
        {{"it is raining"}, "ground is wet"},
        {{"ground is wet"}, "road is slippery"},
        {{"road is slippery"}, "drive carefully"}};

    // Known facts
    unordered_set<string> facts = {"it is raining"};

    // Goal
    string goal = "drive carefully";

    unordered_set<string> visited;

    cout << "Goal: " << goal << endl;

    if (backwardChain(goal, rules, facts, visited))
        cout << "Goal can be proven from the known facts.\n";
    else
        cout << "Goal cannot be proven from the known facts.\n";

    return 0;
}
