import java.util.*;
import java.io.*;

class Node{
    String state;
    List<String> path;
    Node(String state, List<String> path){
        this.state = state;
        this.path = path;
        this.path.add(state);
    }
}

public class DFS{
    //goal state
    static final String goal = "123456780";
    //moves
    static int[][] moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    static final int MAX_DEPTH = 20;
    public static void dfs(String start){
        Set<String> visited = new HashSet<>();
        boolean found = dfsRecursive(new Node(start, new ArrayList<>()), visited, 0);
        if(!found){
            System.out.println("No solution found");
        }
    }
    private static boolean dfsRecursive(Node current, Set<String> visited, int depth){
        if(depth > MAX_DEPTH) return false;

        visited.add(current.state);
        if (current.state.equals(goal)) {
            System.out.println("Goal reached at depth " + depth + "!");
            printPath(current.path);
            return true;
        }
        int zeroIndex = current.state.indexOf('0');
        int x = zeroIndex / 3;
        int y = zeroIndex % 3;

        //exploring in DFS irder
        for(int[] move : moves){
            int newX = x + move[0];
            int newY = y + move[1];
            
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {

                String newState = swap(current.state, zeroIndexm newX * 3 + newY);
                if(!visited.contains(newState)){
                    Node nextNode = new Node(newState, current.path);
                    if(dfsRecursive(nextNode, visited, depth + 1)){
                        return true;
                    }
       }
        }
    }
    return false;

}

//swapping two character in state string
public static String swap(String state, int i, int j){
    char[] arr = state.toCharArray();
    char temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return new String(arr);
}

private static void printState(String state){
    for (int i = 0; i < 9; i++) {
            if (i % 3 == 0) System.out.println();
            System.out.print(state.charAt(i) + " ");
        }
        System.out.println("\n---------");
}

private static void printPath(List<String> path) {
        int step = 0;
        for (String state : path) {
            System.out.println("Step " + step + ":");
            printState(state);
            step++;
        }
    }   

public static void main(String[] args) {
    String start = "123405678";
    System.out.println("Starting DFS...");
    printState(start);
    dfs(start);
}

