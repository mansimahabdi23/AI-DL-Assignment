#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

// Structure for a rule with multiple conditions
struct Rule
{
    vector<string> conditions;
    string conclusion;
};

// Helper function to check if all conditions are satisfied
bool allConditionsMet(const vector<string> &conditions, const unordered_set<string> &facts)
{
    for (const auto &cond : conditions)
    {
        if (facts.find(cond) == facts.end())
            return false;
    }
    return true;
}

int main()
{
    // Step 1: Define rules
    vector<Rule> rules = {
        {{"it is raining", "it is cold"}, "take an umbrella"},
        {{"take an umbrella"}, "stay dry"},
        {{"stay dry", "road is slippery"}, "drive carefully"}};

    // Step 2: Initial known facts
    unordered_set<string> facts = {"it is raining", "it is cold", "road is slippery"};

    cout << "Initial Facts:\n";
    for (const auto &f : facts)
        cout << "- " << f << endl;

    // Step 3: Forward chaining
    bool newFactAdded = true;
    while (newFactAdded)
    {
        newFactAdded = false;

        for (auto &rule : rules)
        {
            if (allConditionsMet(rule.conditions, facts) &&
                facts.find(rule.conclusion) == facts.end())
            {

                facts.insert(rule.conclusion);
                cout << "Derived new fact: " << rule.conclusion << endl;
                newFactAdded = true;
            }
        }
    }

    // Step 4: Final results
    cout << "\nFinal set of facts:\n";
    for (const auto &f : facts)
        cout << "- " << f << endl;

    return 0;
}
