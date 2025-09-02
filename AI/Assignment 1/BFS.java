import java.util.*;
import java.io.*;

class Node{
    String state, path;

    Node(String state, String path){
        this.state = state;
        this.path = path;
    }
}

public class BFS{
    //goal state
    static final Strinf goal = "123456780";
    //moves
    static int[][] moves = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    //bfs algorithm
    public static void bfs(String start){
        Queue<Node> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        queue.add(new Node(start, ""));
        visited.add(start);

        while(!queue.isEmpty()){
            Node current = queue.poll();
            if(current.state.equals(goal)){
                System.out.println("Goal reached");
                System.out.println("Path: "+current.path);
                printState(current.state);
                return;
            }
            int zeroIndex = current.state.indexOf('0');
            int x = zeroIndex / 3;
            int y = zeroIndex % 3;

            for(int[] move : moves){
                int newX = x + move[0];
                int newY = y + move[1];
                if(newX >= 0 && newX < 3 && newY >= 0 && newY < 3){
                    String newState = swap(current.state, zeroIndex, newX * 3 + newY);
                    if(!visited.contains(newState)){
                        visited.add(newState);
                        queue.add(new Node(newState, current.path + " -> " + newState));
                    }
                }
            }
        }
        System.out.println("No solution found");
    }
    //swap function to generate new state
    public static String swap(String state, int i, int j){
        char[] arr = state.toCharArray();
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        return new String(arr);
    }
    //print state in 3x3 format
    public static void printState(String state){
        for(int i = 0; i < 9; i++){
            if(i % 3 == 0) System.out.println();
            System.out.print(state.charAt(i) + " ");
        }
        System.out.println();
    }

public static void main(String[] args) {
    String start = "123405678"; // Example start state
    System.out.println("Starting BFS...");
    printState(start);
    bfs(start);
}

}