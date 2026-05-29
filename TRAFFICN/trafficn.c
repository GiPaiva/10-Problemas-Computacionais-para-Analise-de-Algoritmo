#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10001
#define INF 1000000000

typedef struct Edge {
    int to;
    int cost;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
Edge* reverse_graph[MAX_N];
int dist_from_s[MAX_N];
int dist_to_t[MAX_N];
int n, m, k, s, t;

typedef struct {
    int u, v, q;
} Proposal;

Proposal proposals[300];

void addEdge(Edge* adj[], int from, int to, int cost) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->cost = cost;
    e->next = adj[from];
    adj[from] = e;
}

void freeGraph(Edge* adj[]) {
    for (int i = 1; i <= n; i++) {
        Edge* e = adj[i];
        while (e != NULL) {
            Edge* temp = e;
            e = e->next;
            free(temp);
        }
        adj[i] = NULL;
    }
}

void dijkstra(Edge* adj[], int start, int dist[]) {
    int visited[MAX_N];
    memset(visited, 0, sizeof(visited));
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    
    for (int count = 0; count < n; count++) {
        int u = -1;
        int minDist = INF;
        
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        
        if (u == -1 || minDist == INF) break;
        
        visited[u] = 1;
        
        for (Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            int cost = e->cost;
            
            if (!visited[v] && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
            }
        }
    }
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d %d %d", &n, &m, &k, &s, &t);
        
        // Initialize graphs
        for (int i = 1; i <= n; i++) {
            graph[i] = NULL;
            reverse_graph[i] = NULL;
        }
        
        // Read existing one-way roads
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addEdge(graph, u, v, w);
            addEdge(reverse_graph, v, u, w);
        }
        
        // Read proposed two-way roads
        for (int i = 0; i < k; i++) {
            scanf("%d %d %d", &proposals[i].u, &proposals[i].v, &proposals[i].q);
        }
        
        // Run Dijkstra from s
        dijkstra(graph, s, dist_from_s);
        
        // Run Dijkstra from t on reverse graph
        dijkstra(reverse_graph, t, dist_to_t);
        
        // Current shortest path
        int best = dist_from_s[t];
        
        // Try each proposed two-way road
        for (int i = 0; i < k; i++) {
            int u = proposals[i].u;
            int v = proposals[i].v;
            int q = proposals[i].q;
            
            // s -> u -> v -> t
            int path1 = dist_from_s[u] + q + dist_to_t[v];
            // s -> v -> u -> t
            int path2 = dist_from_s[v] + q + dist_to_t[u];
            
            best = min(best, min(path1, path2));
        }
        
        if (best >= INF) {
            printf("-1\n");
        } else {
            printf("%d\n", best);
        }
        
        // Free memory
        freeGraph(graph);
        freeGraph(reverse_graph);
    }
    
    return 0;
}