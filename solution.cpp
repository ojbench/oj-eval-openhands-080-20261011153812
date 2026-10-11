#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int degree[MAXN];

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
    
    int answer = 0;
    
    for (int i = 1; i <= n; i++) {
        if (degree[i] < 2) {
            answer++;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}