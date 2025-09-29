import java.util.*;

class Node implements Comparable<Node> {
    String name;
    double g; // cost from start node
    double h; // heuristic cost to goal
    double f; // f = g + h
    Node parent;
    
    Node(String name) {
        this.name = name;
        this.g = 0;
        this.h = 0;
        this.f = 0;
        this.parent = null;
    }

    @Override
    public int compareTo(Node other) {
        return Double.compare(this.f, other.f);
    }
}

class Edge {
    Node from, to;
    double cost;

    Edge(Node from, Node to, double cost) {
        this.from = from;
        this.to = to;
        this.cost = cost;
    }
}

public class AStarExample {
    private Map<String, Node> nodes = new HashMap<>();
    private List<Edge> edges = new ArrayList<>();
    private Map<String, Double> heuristic = new HashMap<>();

    public Node getNode(String name) {
        return nodes.computeIfAbsent(name, Node::new);
    }

    public void addEdge(String from, String to, double cost) {
        Node n1 = getNode(from);
        Node n2 = getNode(to);
        edges.add(new Edge(n1, n2, cost));
        edges.add(new Edge(n2, n1, cost)); // undirected
    }

    public void setHeuristic(String node, double hValue) {
        heuristic.put(node, hValue);
    }

    public List<String> aStarSearch(String start, String goal) {
        Node startNode = getNode(start);
        Node goalNode = getNode(goal);

        PriorityQueue<Node> openList = new PriorityQueue<>();
        Set<Node> closedList = new HashSet<>();

        startNode.g = 0;
        startNode.h = heuristic.getOrDefault(start, 0.0);
        startNode.f = startNode.g + startNode.h;

        openList.add(startNode);

        while (!openList.isEmpty()) {
            Node current = openList.poll();

            if (current.name.equals(goal)) {
                return reconstructPath(current);
            }

            closedList.add(current);

            for (Edge edge : edges) {
                if (edge.from.equals(current)) {
                    Node neighbor = edge.to;

                    if (closedList.contains(neighbor)) continue;

                    double tentativeG = current.g + edge.cost;

                    if (!openList.contains(neighbor) || tentativeG < neighbor.g) {
                        neighbor.parent = current;
                        neighbor.g = tentativeG;
                        neighbor.h = heuristic.getOrDefault(neighbor.name, 0.0);
                        neighbor.f = neighbor.g + neighbor.h;

                        if (!openList.contains(neighbor)) {
                            openList.add(neighbor);
                        }
                    }
                }
            }
        }

        return Collections.emptyList(); // no path found
    }

    private List<String> reconstructPath(Node goal) {
        List<String> path = new ArrayList<>();
        for (Node n = goal; n != null; n = n.parent) {
            path.add(n.name);
        }
        Collections.reverse(path);
        return path;
    }

    public static void main(String[] args) {
        AStarExample graph = new AStarExample();

        // Graph structure
        graph.addEdge("A", "B", 1);
        graph.addEdge("A", "C", 3);
        graph.addEdge("B", "D", 1);
        graph.addEdge("C", "D", 1);
        graph.addEdge("D", "E", 5);

        // Heuristics (straight-line distance estimate to goal "E")
        graph.setHeuristic("A", 7);
        graph.setHeuristic("B", 6);
        graph.setHeuristic("C", 4);
        graph.setHeuristic("D", 2);
        graph.setHeuristic("E", 0);

        // Run A* from A to E
        List<String> path = graph.aStarSearch("A", "E");

        if (!path.isEmpty()) {
            System.out.println("Shortest Path: " + path);
        } else {
            System.out.println("No path found!");
        }
    }
}
