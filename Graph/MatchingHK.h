struct HopcroftKarp {
	vector<int> d, match;
	int n, nil = 0;
	HopcroftKarp() {}
	HopcroftKarp(int n, int m) : n(n), d(n + 1), match(m + 1, 0), e(n + 1) {}
	vector< vector<int> > e;

	void addEdge(int u, int v) {
		e[u].push_back(v);
	}

	int MaxMatching() {
		int matching = 0;
		while (bfs()) {
			FOR(i, 1, n) if (match[i] == nil && dfs(i)) {
				matching++;
			} 
		}
		return matching;
	}
private:
	bool bfs() {
		queue<int> q;
		FOR(i, 1, n) if (match[i] == nil) {
			q.push(i);
			d[i] = 0;
		} else d[i] = -1;
		d[nil] = -1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : e[u]) {
				if (d[match[v]] == -1) {
					d[match[v]] = d[u] + 1;
					q.push(match[v]);
				}
			}
		}
		return d[nil] != -1;
	}

	bool dfs(int u) {
		if (u == nil) return 1;
		for (int v : e[u]) {
			if (d[match[v]] == d[u] + 1 && dfs(match[v])) {
				match[v] = u;
				return 1;
			}
		}
		d[u] = -1;
		return 0;
	}
};