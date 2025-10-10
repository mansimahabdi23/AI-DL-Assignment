#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class KnowledgeBase
{
private:
    // Store parent -> children relationships
    unordered_map<string, vector<string>> parentMap;
    // Store gender info
    unordered_map<string, string> genderMap;

public:
    // Add parent-child relationship
    void addParent(const string &parent, const string &child)
    {
        parentMap[parent].push_back(child);
    }

    // Add gender info
    void addGender(const string &person, const string &gender)
    {
        genderMap[person] = gender;
    }

    // Get children of a person
    vector<string> getChildren(const string &person)
    {
        if (parentMap.find(person) != parentMap.end())
            return parentMap[person];
        else
            return {};
    }

    // Get parents of a person
    vector<string> getParents(const string &person)
    {
        vector<string> parents;
        for (auto &entry : parentMap)
        {
            if (find(entry.second.begin(), entry.second.end(), person) != entry.second.end())
            {
                parents.push_back(entry.first);
            }
        }
        return parents;
    }

    // Get grandparents of a person
    vector<string> getGrandparents(const string &person)
    {
        vector<string> grandparents;
        for (const string &parent : getParents(person))
        {
            vector<string> gp = getParents(parent);
            grandparents.insert(grandparents.end(), gp.begin(), gp.end());
        }
        return grandparents;
    }

    // Get siblings of a person
    vector<string> getSiblings(const string &person)
    {
        vector<string> siblings;
        for (const string &parent : getParents(person))
        {
            for (const string &child : getChildren(parent))
            {
                if (child != person && find(siblings.begin(), siblings.end(), child) == siblings.end())
                {
                    siblings.push_back(child);
                }
            }
        }
        return siblings;
    }
    vector<string> getUnclesAunts(const string &person)
    {
        vector<string> unclesAunts;

        // Step 1: Find the person's parents
        vector<string> parents = getParents(person);

        // Step 2: For each parent, find their siblings
        for (const string &parent : parents)
        {
            vector<string> siblings = getSiblings(parent);

            // Step 3: Add them as uncles/aunts (avoid duplicates)
            for (const string &s : siblings)
            {
                if (find(unclesAunts.begin(), unclesAunts.end(), s) == unclesAunts.end())
                    unclesAunts.push_back(s);
            }
        }
        return unclesAunts;
    }
    vector<string> getNephewsNieces(const string &person)
    {
        vector<string> nephewsNieces;

        // Step 1: Find siblings of the person
        vector<string> siblings = getSiblings(person);

        // Step 2: For each sibling, get their children
        for (const string &sibling : siblings)
        {
            vector<string> children = getChildren(sibling);

            // Step 3: Add those children as nephews/nieces (avoid duplicates)
            for (const string &child : children)
            {
                if (find(nephewsNieces.begin(), nephewsNieces.end(), child) == nephewsNieces.end())
                    nephewsNieces.push_back(child);
            }
        }
        return nephewsNieces;
    }

    // Get gender of a person
    string getGender(const string &person)
    {
        if (genderMap.find(person) != genderMap.end())
            return genderMap[person];
        else
            return "Unknown";
    }
};

// Helper function to print vectors
void printVector(const vector<string> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i != vec.size() - 1)
            cout << ", ";
    }
    cout << "]";
}

int main()
{
    KnowledgeBase kb;

    // Add relationships
    kb.addParent("John", "Alice");
    kb.addParent("Mary", "Alice");
    kb.addParent("John", "Bob");
    kb.addParent("Mary", "Bob");
    kb.addParent("Alice", "Charlie");
    kb.addParent("David", "Charlie");

    // Add genders
    kb.addGender("John", "Male");
    kb.addGender("Mary", "Female");
    kb.addGender("Alice", "Female");
    kb.addGender("Bob", "Male");
    kb.addGender("Charlie", "Male");
    kb.addGender("David", "Male");

    // Queries
    cout << "Children of John: ";
    printVector(kb.getChildren("John"));
    cout << "\n";
    cout << "Parents of Alice: ";
    printVector(kb.getParents("Alice"));
    cout << "\n";
    cout << "Siblings of Alice: ";
    printVector(kb.getSiblings("Alice"));
    cout << "\n";
    cout << "Grandparents of Charlie: ";
    printVector(kb.getGrandparents("Charlie"));
    cout << "\n";

    cout << "Uncles/Aunts of Charlie: ";
    printVector(kb.getUnclesAunts("Charlie"));
    cout << "\n";

    cout << "Nephews/Nieces of Alice: ";
    printVector(kb.getNephewsNieces("Alice"));
    cout << "\n";
    return 0;
}

/*
for uncle/aunt function
vector<string> getUnclesAunts(const string &person)
{
    vector<string> unclesAunts;

    // Step 1: Find the person's parents
    vector<string> parents = getParents(person);

    // Step 2: For each parent, find their siblings
    for (const string &parent : parents)
    {
        vector<string> siblings = getSiblings(parent);

        // Step 3: Add them as uncles/aunts (avoid duplicates)
        for (const string &s : siblings)
        {
            if (find(unclesAunts.begin(), unclesAunts.end(), s) == unclesAunts.end())
                unclesAunts.push_back(s);
        }
    }
    return unclesAunts;
}
/*🧠 Explanation in simple words:

First, find the person’s parents.

Then, find who are the parents’ siblings (they are uncle/aunt).

Add them to the list (no duplicates).

📍Example:
If John & Mary are Alice’s parents,
and John’s sibling is David → then David is Alice’s uncle.
*/

/*
Nephew/Niece Function
vector<string> getNephewsNieces(const string &person)
{
    vector<string> nephewsNieces;

    // Step 1: Find siblings of the person
    vector<string> siblings = getSiblings(person);

    // Step 2: For each sibling, get their children
    for (const string &sibling : siblings)
    {
        vector<string> children = getChildren(sibling);

        // Step 3: Add those children as nephews/nieces (avoid duplicates)
        for (const string &child : children)
        {
            if (find(nephewsNieces.begin(), nephewsNieces.end(), child) == nephewsNieces.end())
                nephewsNieces.push_back(child);
        }
    }
    return nephewsNieces;
}

*/