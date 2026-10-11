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
int parent[MAXN];
int depth[MAXN];

void mark_nodes_in_odd_cycle(int u, int v) {
    // u and v are in the same color and form an odd cycle
    // Find the path from u to v and mark all nodes on that path
    vector<int> path_u, path_v;
    
    int curr = u;
    while (curr != -1) {
        path_u.push_back(curr);
        curr = parent[curr];
    }
    
    curr = v;
    while (curr != -1) {
        path_v.push_back(curr);
        curr = parent[curr];
    }
    
    // Find LCA
    int lca = -1;
    for (int i = 0; i < path_u.size() && i < path_v.size(); i++) {
        if (path_u[path_u.size() - 1 - i] == path_v[path_v.size() - 1 - i]) {
            lca = path_u[path_u.size() - 1 - i];
        } else {
            break;
        }
    }
    
    // Mark path from u to lca
    curr = u;
    while (curr != lca) {
        can_be_invited[curr] = true;
        curr = parent[curr];
    }
    
    // Mark path from v to lca
    curr = v;
    while (curr != lca) {
        can_be_invited[curr] = true;
        curr = parent[curr];
    }
    can_be_invited[lca] = true;
}

void dfs_find_odd_cycles(int u, int p) {
    visited[u] = true;
    parent[u] = p;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            depth[v] = depth[u] + 1;
            color[v] = color[u] ^ 1;
            dfs_find_odd_cycles(v, u);
        } else if (v != p && color[v] == color[u]) {
            // Found odd cycle
            mark_nodes_in_odd_cycle(u, v);
        }
    }
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
    memset(parent, -1, sizeof(parent));
    memset(depth, 0, sizeof(depth));
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && degree[i] >= 2) {
            color[i] = 0;
            depth[i] = 0;
            dfs_find_odd_cycles(i, -1);
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