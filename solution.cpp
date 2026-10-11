#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int color[MAXN];
bool visited[MAXN];

bool is_bipartite(int start, int& component_size) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    visited[start] = true;
    component_size = 0;
    
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
                return false;
            }
        }
    }
    return true;
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
            int component_size = 0;
            if (is_bipartite(i, component_size)) {
                answer += component_size;
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}