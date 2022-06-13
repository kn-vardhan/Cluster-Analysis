//
//  distance.cpp
//  DSA_Lab
//
//  Created by Kethari Narasimha Vardhan on 01/12/21.
//

#include <iostream>
#include <cmath>
#include <list>
#include <limits.h>
using namespace std;

class Graph {
    int V;
    list<int> *adj;
    int isCyclicUtil (int v, bool visited[], int parent);
//    int mst[];
public:
    Graph(int V);
    void addEdge(int v, int w);
    int isCyclic();
//    void mst_points[];
};

Graph::Graph (int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

int Graph::isCyclicUtil(int v, bool visited[], int parent) {
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); i++) {
        if (!visited[*i]) {
            if (isCyclicUtil(*i, visited, v)) {
                return 1;
            }
        }
        else if  (*i != parent) {
            return 1;
        }
    }
    return 0;
}

int Graph::isCyclic() {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i, visited, -1)) {
                return 1;
            }
        }
    }
    return 0;
}

struct vertex {
    int vertex_no;
    int x;
    int y;
};

struct points {
    struct vertex vertex1;
    struct vertex vertex2;
    double weight;
};

struct vertex node_list[4];
struct points edges[6];

void swap (struct points *p1, struct points *p2) {
    struct points temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

double euclid (struct vertex node1, struct vertex node2) {
    int temp_x;
    int temp_y;
    double dist;
    temp_x = pow(abs(node1.x - node2.x), 2);
    temp_y = pow(abs(node1.y - node2.y), 2);
    dist = sqrt(temp_x + temp_y);
    return dist;
}

int main() {
    
    int vertex1[4] = {0, 2, 1, 0};
    int vertex2[4] = {0, 0, 1, 1};
    int len = sizeof(vertex1)/sizeof(vertex1[0]);
    
    for (int i = 0; i < len; i++) {
        node_list[i].vertex_no = i;
        node_list[i].x = vertex1[i];
        node_list[i].y = vertex2[i];
    }
    
    int no_edges = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i+1; j < len; j++) {
            edges[no_edges].vertex1.x = node_list[i].x;
            edges[no_edges].vertex1.y = node_list[i].y;
            edges[no_edges].vertex2.x = node_list[j].x;
            edges[no_edges].vertex2.y = node_list[j].y;
            edges[no_edges].weight = euclid(node_list[i], node_list[j]);
            no_edges++;
        }
    }
    
    for (int i = 0; i < no_edges; i++) {
        for (int j = i-1; j >= 0; j--) {
            if (edges[j].weight >= edges[j+1].weight) {
                swap(&edges[j], &edges[j+1]);
            }
        }
    }
    
    for (int i = 0; i < no_edges; i++) {
        printf("Edge[%d] - (%d, %d) - (%d, %d) - %.3lf\n",
               i, edges[i].vertex1.x, edges[i].vertex1.y,
               edges[i].vertex2.x, edges[i].vertex2.y, edges[i].weight);
    }
    
    Graph mst(len - 1);
    for (int i = 0; i < no_edges; i++) {
        while (mst.isCyclic() == 0) {
            mst.addEdge(edges[i].vertex1.vertex_no, edges[i].vertex2.vertex_no);
        }
    }
    
    cout<<mst.isCyclic();
    
    cout<<endl;
    return 0;
}
