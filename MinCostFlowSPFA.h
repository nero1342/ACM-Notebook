struct Edge {
	int u, v;
	long long flow, cap, cost;

	Edge() {}
	Edge(int u, int v, long long flow, long long cap, long long cost):u(u), v(v), flow(flow), cap(cap), cost(cost) {}
};

struct MinCostFlow {
	vector<long long> d;
	vector<int> visited;
	vector<vector<int> > g;
	vector<Edge> e;
	int n, s, t;
	long long totalCost, totalFlow;

	const long long INF = 1e18;

	MinCostFlow() {}
	MinCostFlow(int n):n(n), d(n), visited(n), g(n) {}

	void addEdge(int u, int v, int cap, int cost) {
		g[u].push_back(e.size());
		e.push_back(Edge(u, v, 0, cap, cost));
		g[v].push_back(e.size());
		e.push_back(Edge(v, u, 0, 0, -cost));
	}

	pair<long long, long long> getMCF(int _s, int _t) { // Flow, cost
		s = _s, t = _t;
		totalCost = 0, totalFlow = 0;
		SPFA();
		while (1) {
			while (1) {
				REP(i, n) visited[i] = 0;
				if (!findFlow(s, INF)) break;
			}
			if (!modifyLabel()) break;
		}
		return make_pair(totalFlow, totalCost);
	}
private:
	void SPFA() {
		priority_queue<pp> heap;
		REP(i, n) d[i] = INF;
		d[s] = 0;
		heap.push(pp(0, s));
		while (!heap.empty()) {
			int u = heap.top().second;
			long long dist = -heap.top().first;
			heap.pop();
			if (dist != d[u]) continue;
			for (int id : g[u]) if (e[id].flow < e[id].cap) {
				int v = e[id].v;
				long long c = e[id].cost;
				if (d[v] > d[u] + c) {
					d[v] = d[u] + c;
					heap.push(pp(-d[v], v));
				}
			}
		}
		long long dT = d[t];
		REP(i, n) d[i] = dT - d[i];
	}

	long long findFlow(int u, long long flow) {
		if (u == t) {
			totalCost += flow * d[s];
			totalFlow += flow;
			return flow;
		}
		visited[u] = 1;
		long long now = flow;
		for (int id : g[u]) if (e[id].flow < e[id].cap) {
			int v = e[id].v;
			long long c = e[id].cost;
			if (d[u] == d[v] + c && !visited[v]) {
				long long pushed = findFlow(v, min(now, e[id].cap - e[id].flow));
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				now -= pushed;
				if (now == 0) break;
			}
		}
		return flow - now;
	}

	bool modifyLabel() {
		long long dist = INF;
		REP(u, n) if (visited[u]) {
			for (int id : g[u]) if (e[id].flow < e[id].cap) {
				int v = e[id].v;
				long long c = e[id].cost;
				if (!visited[v]) dist = min(dist, d[v] + c - d[u]);
			}
		}
		if (dist == INF) return 0;
		REP(i, n) if (visited[i]) d[i] += dist;
		return 1;
	}
};