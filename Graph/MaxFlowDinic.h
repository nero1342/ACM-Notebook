struct Edge {
    int u, v, cap, flow;
    Edge() {}
    Edge(int u, int v, int cap, int flow):u(u), v(v), cap(cap), flow(flow) {}
};

struct Dinic {
    vector<int> d, ptr;
    vector<vector<int> > g;
    vector<Edge> e;
    int n, s, t;
    Dinic() {}
    Dinic(int n):n(n), d(n), ptr(n), g(n) {}
    
    void addEdge(int u, int v, int cap) {
        g[u].push_back(e.size());
        e.push_back(Edge(u, v, cap, 0));
        g[v].push_back(e.size());
        e.push_back(Edge(v, u, cap, 0));
    }

    int MaxFlow(int s, int t) {
        this -> s = s;
        this -> t = t;
        int flow = 0;
        while (bfs()) {
            while (int x = dfs(s, 1e9)) {
                flow += x;
            }
        }
        return flow;
    }
private:
    bool bfs() {
        queue<int> q;
        REP(i, n) ptr[i] = 0, d[i] = -1;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u]) if (e[id].flow < e[id].cap) {
                int v = e[id].v;
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }

    int dfs(int u, int flow) {
        if (u == t) return flow;
        for (; ptr[u] < (int)g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] == d[u] + 1 && e[id].cap > e[id].flow) {
                if (int x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
                    e[id].flow += x;
                    e[id ^ 1].flow -= x;
                    return x;
                }
            }
        }
        return 0;
    }
};