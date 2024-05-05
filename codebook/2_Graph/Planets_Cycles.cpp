vector<int> dis, v;
vector<bool> vis;
int step;
queue<int> path;
void dfs(int x) {
    path.push(x);
    if (vis[x]) {
        step += dis[x];
        return;
    }
    vis[x] = true;
    step++;
    dfs(v[x]);
}
// count path_dis to rep
int main() {
    int n; cin >> n;
    v.assign(n + 1, 0);
    dis.assign(n + 1, 0);
    vis.assign(n + 1, false);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        step = 0;
        int is_outof_cycle = 1;
        dfs(i);
        while (!path.empty()) {
            if (path.front() == path.back()) {
                is_outof_cycle = 0;
            }
            dis[path.front()] = step;
            step -= is_outof_cycle;
            path.pop();
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << ' ';
    }
    cout << '\n';
}