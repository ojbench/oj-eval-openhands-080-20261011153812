#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
bool visited[MAXN];
int color[MAXN];

bool is_bipartite_component(int start) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    visited[start] = true;
    int component_size = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        component_size++;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                color[v] = color[u] ^ 1;
                q.push(v);
            } else if (color[v] == color[u]) {
                return false; // Not bipartite
            }
        }
    }
    return true; // Bipartite
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    memset(visited, false, sizeof(visited));
    memset(color, -1, sizeof(color));
    
    int answer = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // Count component size
            queue<int> q;
            q.push(i);
            visited[i] = true;
            int component_size = 0;
            vector<int> component_nodes;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                component_size++;
                component_nodes.push_back(u);
                
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            
            // Reset visited for bipartite check
            for (int node : component_nodes) {
                visited[node] = false;
            }
            
            // Check if component is bipartite
            if (is_bipartite_component(i)) {
                answer += component_size;
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}