#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int degree[MAXN];
bool visited[MAXN];
int color[MAXN];
bool can_be_invited[MAXN];

bool dfs_check_bipartite(int u) {
    visited[u] = true;
    can_be_invited[u] = true; // Assume can be invited initially
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            color[v] = color[u] ^ 1;
            if (!dfs_check_bipartite(v)) {
                return false;
            }
        } else if (color[v] == color[u]) {
            // Found odd cycle - all nodes in this component can be invited
            return false;
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
        degree[x]++;
        degree[y]++;
    }
    
    memset(visited, false, sizeof(visited));
    memset(color, -1, sizeof(color));
    memset(can_be_invited, false, sizeof(can_be_invited));
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && degree[i] >= 2) {
            color[i] = 0;
            if (!dfs_check_bipartite(i)) {
                // Component has odd cycle, all nodes with degree >= 2 can be invited
                for (int j = 1; j <= n; j++) {
                    if (visited[j] && degree[j] >= 2) {
                        can_be_invited[j] = true;
                    }
                }
            }
            // If component is bipartite, can_be_invited remains false for these nodes
        }
    }
    
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (!can_be_invited[i]) {
            answer++;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}