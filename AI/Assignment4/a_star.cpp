#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

// Node class
class Node
{
public:
    // f(n)=g(n)+h(n)
    string name; // name of node
    double g;    // cost from start
    double h;    // heuristic cost
    double f;    // g + h
    Node *parent;

    Node(string n) : name(n), g(0), h(0), f(0), parent(nullptr) {}
};

// Comparator for priority_queue (min-heap based on f)
struct CompareNode
{
    bool operator()(Node *a, Node *b)
    {
        return a->f > b->f; // min-heap
    }
};

// Edge class
class Edge
{
public:
    Node *from;
    Node *to;
    double cost;

    Edge(Node *f, Node *t, double c) : from(f), to(t), cost(c) {}
};

// A* Graph class
class AStarExample
{
private:
    map<string, Node *> nodes;
    vector<Edge> edges;
    map<string, double> heuristic;

public:
    Node *getNode(const string &name)
    {
        if (nodes.find(name) == nodes.end())
            nodes[name] = new Node(name);
        return nodes[name];
    }

    void addEdge(const string &from, const string &to, double cost)
    {
        Node *n1 = getNode(from);
        Node *n2 = getNode(to);
        edges.push_back(Edge(n1, n2, cost));
        edges.push_back(Edge(n2, n1, cost)); // undirected
    }

    void setHeuristic(const string &node, double hValue)
    {
        heuristic[node] = hValue;
    }

    vector<string> aStarSearch(const string &start, const string &goal)
    {
        Node *startNode = getNode(start);
        Node *goalNode = getNode(goal);

        priority_queue<Node *, vector<Node *>, CompareNode> openList;
        set<Node *> closedList;

        startNode->g = 0;
        startNode->h = heuristic[start];
        startNode->f = startNode->g + startNode->h;

        openList.push(startNode);

        while (!openList.empty())
        {
            Node *current = openList.top();
            openList.pop();

            if (current->name == goal)
            {
                return reconstructPath(current);
            }

            closedList.insert(current);

            for (Edge &edge : edges)
            {
                // FOR ALL EDGES WHERE CURRENT -> NEIGHBOR
                if (edge.from == current)
                {
                    Node *neighbor = edge.to;

                    if (closedList.count(neighbor))
                        continue;

                    double tentativeG = current->g + edge.cost;

                    // Check if neighbor is already in openList with higher g
                    bool inOpen = false;
                    priority_queue<Node *, vector<Node *>, CompareNode> temp = openList;
                    while (!temp.empty())
                    {
                        if (temp.top() == neighbor)
                        {
                            inOpen = true;
                            break;
                        }
                        temp.pop();
                    }

                    if (!inOpen || tentativeG < neighbor->g) // if the neighbour is not already in the open list we will add it up
                    {
                        neighbor->parent = current;
                        neighbor->g = tentativeG;
                        neighbor->h = heuristic[neighbor->name];
                        neighbor->f = neighbor->g + neighbor->h;

                        if (!inOpen)
                        {
                            openList.push(neighbor);
                        }
                    }
                }
            }
        }
        // When all possible nodes have been explored and goal is not found, we return:
        return {}; // No path found
    }
    // when goal is found this function runs
    vector<string> reconstructPath(Node *goal)
    {
        vector<string> path;
        for (Node *n = goal; n != nullptr; n = n->parent)
            path.push_back(n->name);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main()
{
    AStarExample graph;

    // Graph edges
    graph.addEdge("A", "B", 1);
    graph.addEdge("A", "C", 3);
    graph.addEdge("B", "D", 1);
    graph.addEdge("C", "D", 1);
    graph.addEdge("D", "E", 5);

    // Heuristics
    graph.setHeuristic("A", 7);
    graph.setHeuristic("B", 6);
    graph.setHeuristic("C", 4);
    graph.setHeuristic("D", 2);
    graph.setHeuristic("E", 0);

    // Run A*
    vector<string> path = graph.aStarSearch("A", "E");

    if (!path.empty())
    {
        cout << "Shortest Path: [";
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
                cout << ", ";
        }
        cout << "]\n";
    }
    else
    {
        cout << "No path found!\n";
    }

    return 0;
}
