#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <map> // Although unordered_map is used, std::map is included here for completeness if you prefer an ordered map.

class NQueensCSP
{
private:
    const int N;
    // The assignment maps the column (variable) to the row (value)
    // std::unordered_map<KeyType, ValueType> is the C++ equivalent of Java's HashMap.
    // Key: Column index (0 to N-1), Value: Row index (0 to N-1)
    std::unordered_map<int, int> assignment;

    /**
     * Checks if placing a queen in the current column and row is consistent
     * with all previously placed queens (in columns 0 to currentColumn - 1).
     * * @param currentColumn The column to place the new queen.
     * @param currentRow    The row to place the new queen.
     * @return true if consistent (safe), false otherwise.
     */
    bool isConsistent(int currentColumn, int currentRow)
    {
        // Check conflicts with every previously assigned queen (columns < currentColumn)
        // C++ uses a range-based for loop for iterating over the map entries
        for (const auto &pair : assignment)
        {
            int previousColumn = pair.first;
            int previousRow = pair.second;

            // 1. Check for Row conflict (Same row)
            if (previousRow == currentRow)
            {
                return false;
            }

            // 2. Check for Diagonal conflict (Same diagonal)
            // C++ uses std::abs from <cmath> for absolute value.
            // Note: For int, <cstdlib> is often sufficient, but <cmath> is safer.
            if (std::abs(previousColumn - currentColumn) == std::abs(previousRow - currentRow))
            {
                return false;
            }
        }
        return true;
    }

public:
    // Constructor
    NQueensCSP(int n) : N(n)
    {
        // N is initialized in the initializer list.
        // assignment is automatically initialized as an empty map.
    }

    /**
     * The recursive backtracking search method.
     * * @param column The current column we are trying to assign a queen to.
     * @return true if a complete solution is found starting from this column, false
     * otherwise.
     */
    bool backtrack(int column)
    {
        // Base Case: If all columns are assigned (column index equals N), a solution is found.
        if (column == N)
        {
            return true;
        }

        // Try every row (domain value) for the current column (variable)
        for (int row = 0; row < N; row++)
        {
            // Check if assigning this value is consistent with the current partial assignment
            if (isConsistent(column, row))
            {

                // 1. Tentatively assign the value
                // In C++, map/unordered_map uses the subscript operator [] for insertion/update.
                assignment[column] = row;

                // 2. Recurse to the next variable (column + 1)
                if (backtrack(column + 1))
                {
                    return true; // Solution found! Stop and return up the call stack.
                }

                // 3. Backtrack (Unassign the value)
                // If recursion returned false, the current path failed. Remove the assignment.
                // In C++, std::map::erase or std::unordered_map::erase is used to remove a key.
                assignment.erase(column);
            }
        }

        // If no row works for this column, return false to trigger backtracking in the
        // previous column
        return false;
    }

    // Public method to start the search and return the result map
    const std::unordered_map<int, int> &solve()
    {
        if (backtrack(0))
        {
            // Return a const reference to the internal assignment map
            return assignment;
        }
        else
        {
            // If no solution, clear the map and return a const reference to the cleared map.
            // In a real application, you might use a more robust way to signal no solution,
            // or return a copy/smart pointer, but for a direct conversion, this is simplest.
            assignment.clear();
            return assignment; // Returns an empty map to signify no solution, similar to Java's 'null'
        }
    }

    void printSolution()
    {
        // Note: The original Java code re-runs backtrack(0) if assignment is empty.
        // It's cleaner to ensure solve() is called first, but following the logic:
        bool solved = true;
        if (assignment.empty())
        {
            solved = backtrack(0); // Attempt to solve if not already solved
        }

        if (!solved)
        {
            std::cout << "No solution exists for N = " << N << std::endl;
            return;
        }

        std::cout << "\nSolution for " << N << "-Queens:" << std::endl;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                // Check if the queen is at (r, c)
                // C++ map::count(key) checks if a key exists (returns 1 or 0).
                // C++ map::at(key) or map[key] accesses the value.
                // map.count(c) ensures column 'c' is in the assignment.
                // assignment.at(c) safely retrieves the row value.
                if (assignment.count(c) && assignment.at(c) == r)
                {
                    std::cout << " Q ";
                }
                else
                {
                    std::cout << " - ";
                }
            }
            std::cout << std::endl;
        }
    }
};

// --- Example Usage (main function) ---
int main()
{
    // Solve 8-Queens problem
    NQueensCSP csp(8);

    // Call printSolution, which internally calls backtrack if needed
    csp.printSolution();

    // Example 2: 4-Queens
    NQueensCSP csp2(4);
    csp2.printSolution();

    // Example 3: N=2 (No solution)
    NQueensCSP csp3(2);
    csp3.printSolution();

    return 0;
}