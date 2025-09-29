import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

public class NQueensCSP {

    private final int N;
    // The assignment maps the column (variable) to the row (value)
    // Key: Column index (0 to N-1), Value: Row index (0 to N-1)
    private Map<Integer, Integer> assignment;

    public NQueensCSP(int n) {
        this.N = n;
        this.assignment = new HashMap<>();
    }

    /**
     * Checks if placing a queen in the current column and row is consistent
     * with all previously placed queens (in columns 0 to currentColumn - 1).
     * @param currentColumn The column to place the new queen.
     * @param currentRow The row to place the new queen.
     * @return true if consistent (safe), false otherwise.
     */
    private boolean isConsistent(int currentColumn, int currentRow) {
        // Check conflicts with every previously assigned queen (columns < currentColumn)
        for (Map.Entry<Integer, Integer> entry : assignment.entrySet()) {
            int previousColumn = entry.getKey();
            int previousRow = entry.getValue();

            // 1. Check for Row conflict (Same row)
            if (previousRow == currentRow) {
                return false;
            }

            // 2. Check for Diagonal conflict (Same diagonal)
            // The absolute difference between column indices must equal
            // the absolute difference between row indices for a diagonal.
            if (Math.abs(previousColumn - currentColumn) == Math.abs(previousRow - currentRow)) {
                return false;
            }
        }
        return true;
    }

    /**
     * The recursive backtracking search method.
     * @param column The current column we are trying to assign a queen to.
     * @return true if a complete solution is found starting from this column, false otherwise.
     */
    public boolean backtrack(int column) {
        // Base Case: If all columns are assigned (column index equals N), a solution is found.
        if (column == N) {
            return true;
        }

        // Try every row (domain value) for the current column (variable)
        for (int row = 0; row < N; row++) {
            // Check if assigning this value is consistent with the current partial assignment
            if (isConsistent(column, row)) {
                
                // 1. Tentatively assign the value
                assignment.put(column, row);

                // 2. Recurse to the next variable (column + 1)
                if (backtrack(column + 1)) {
                    return true; // Solution found! Stop and return up the call stack.
                }

                // 3. Backtrack (Unassign the value)
                // If recursion returned false, the current path failed. Remove the assignment.
                assignment.remove(column); 
            }
        }

        // If no row works for this column, return false to trigger backtracking in the previous column
        return false;
    }

    public Map<Integer, Integer> solve() {
        if (backtrack(0)) {
            return assignment;
        } else {
            return null; // No solution found
        }
    }

    public void printSolution() {
        if (assignment.isEmpty() && !backtrack(0)) {
            System.out.println("No solution exists for N = " + N);
            return;
        }
        
        System.out.println("\nSolution for " + N + "-Queens:");
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                // Check if the queen is at (r, c)
                if (assignment.containsKey(c) && assignment.get(c) == r) {
                    System.out.print(" Q ");
                } else {
                    System.out.print(" - ");
                }
            }
            System.out.println();
        }
    }
}