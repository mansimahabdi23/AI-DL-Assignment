#include <iostream>
#include <cstring> // For strcmp (string comparison) and strncpy

// --- Global Constants (Variables and Domain) ---
const int NUM_REGIONS = 7;
const char *REGIONS[NUM_REGIONS] = {
    "WA", "NT", "SA", "Q", "NSW", "V", "T"};

const int NUM_COLORS = 3;
const char *COLORS[NUM_COLORS] = {
    "Red", "Green", "Blue"};

// --- Constraints (Adjacency Matrix/List) ---
// Simplified constraint representation: A list of adjacent pairs (indices)
// WA(0), NT(1), SA(2), Q(3), NSW(4), V(5), T(6)
const int ADJACENCIES[][2] = {
    {0, 1}, // WA - NT
    {0, 2}, // WA - SA
    {1, 2}, // NT - SA
    {1, 3}, // NT - Q
    {2, 3}, // SA - Q
    {2, 4}, // SA - NSW
    {2, 5}, // SA - V
    {3, 4}, // Q - NSW
    {4, 5}, // NSW - V
    // T (6) has no connections
};
const int NUM_CONSTRAINTS = sizeof(ADJACENCIES) / sizeof(ADJACENCIES[0]);

// --- Assignment Storage ---
// Use a C-style array to store the color assigned to each region index.
// Index 0 stores the color for REGIONS[0] ("WA"), etc.
// The maximum length of a color string is 5 ("Green"), plus 1 for the null terminator.
const int MAX_COLOR_LEN = 6;
char assignment[NUM_REGIONS][MAX_COLOR_LEN];

// --- Function Prototypes ---
bool isConsistent(int regionIndex, const char *color);
bool backtrack(int regionIndex);
void solveAndPrint();

// -----------------------------------------------------------------
// --- Constraint Checking Logic ---
// -----------------------------------------------------------------

/**
 * Checks if the two given regions (by index) are adjacent.
 */
bool isAdjacent(int r1, int r2)
{
    for (int i = 0; i < NUM_CONSTRAINTS; ++i)
    {
        // Constraints are unordered, check both directions
        if ((ADJACENCIES[i][0] == r1 && ADJACENCIES[i][1] == r2) ||
            (ADJACENCIES[i][0] == r2 && ADJACENCIES[i][1] == r1))
        {
            return true;
        }
    }
    return false;
}

/**
 * Checks if assigning a color to a region is consistent with previous assignments.
 * This is the simplified equivalent of the Map Coloring CSP constraint.
 */
bool isConsistent(int regionIndex, const char *color)
{
    // Only check against regions that have ALREADY been assigned (index < regionIndex)
    for (int previousIndex = 0; previousIndex < regionIndex; ++previousIndex)
    {

        // 1. Check Adjacency
        if (isAdjacent(regionIndex, previousIndex))
        {

            // 2. Check Color Conflict
            const char *previousColor = assignment[previousIndex];

            // strcmp returns 0 if strings are equal
            if (strcmp(previousColor, color) == 0)
            {
                return false; // Conflict: adjacent regions have the same color
            }
        }
    }
    return true;
}

// -----------------------------------------------------------------
// --- Backtracking Search Logic ---
// -----------------------------------------------------------------

bool backtrack(int regionIndex)
{
    // Base Case: If all regions are assigned (regionIndex equals NUM_REGIONS)
    if (regionIndex == NUM_REGIONS)
    {
        return true;
    }

    // Try every color (domain value) for the current region (variable)
    for (int colorIndex = 0; colorIndex < NUM_COLORS; ++colorIndex)
    {
        const char *color = COLORS[colorIndex];

        // Check consistency BEFORE making a permanent assignment
        if (isConsistent(regionIndex, color))
        {

            // 1. Tentatively assign the value (C-style string copy)
            // strncpy is used for safety to prevent buffer overflow
            strncpy(assignment[regionIndex], color, MAX_COLOR_LEN - 1);
            assignment[regionIndex][MAX_COLOR_LEN - 1] = '\0'; // Ensure null termination

            // 2. Recurse to the next region
            if (backtrack(regionIndex + 1))
            {
                return true; // Solution found!
            }

            // 3. Backtrack (Unassigning is implicitly handled by overwriting
            // or by not needing to clear for this specific implementation,
            // since only forward indices are checked. We can set to empty
            // for clarity, but it's not strictly necessary here.)
            // For a formal un-assignment:
            assignment[regionIndex][0] = '\0';
        }
    }

    // If no color works for this region, return false
    return false;
}

// -----------------------------------------------------------------
// --- Main Execution and Print ---
// -----------------------------------------------------------------

void solveAndPrint()
{
    std::cout << "Starting Simple C++ Backtracking Search for Australia Map Coloring..." << std::endl;
    std::cout << "Colors(Domains) : Red Green Blue";
    // Initialize assignment array to empty strings
    for (int i = 0; i < NUM_REGIONS; ++i)
    {
        assignment[i][0] = '\0';
    }

    if (backtrack(0))
    {
        std::cout << "\n--- Solution Found ---" << std::endl;
        for (int i = 0; i < NUM_REGIONS; ++i)
        {
            std::cout << REGIONS[i] << ": " << assignment[i] << std::endl;
        }
        std::cout << "----------------------" << std::endl;
    }
    else
    {
        std::cout << "\nNo solution exists with the given constraints and domains." << std::endl;
    }
}

int main()
{
    solveAndPrint();
    return 0;
}