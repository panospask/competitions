#include "message.h"
#include <stack>
#define pb push_back
#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

using namespace std;

const int N = 31;
const int GOOD = 16;

vector<bool> visited(N, false);
vector<bool> on_stack(N, false);
stack<int> s;

void dfs(int node, vector<bool>& C, vector<int>& dest) {
	if (visited[node]) {
		if (!on_stack[node]) {
			return;
		}
		// Found cycle, time to count length
		int len = 1;
		vector<int> cycle;
		cycle.pb(node);
		while (s.top() != node) {
			cycle.pb(s.top());
			s.pop();
			len++;
		}

		if (cycle.size() == GOOD) {
			// Found it!
			for (auto u : cycle) {
				C[u] = false;
			}
		}

		return;
	}

	visited[node] = on_stack[node] = true;
	s.push(node);
	dfs(dest[node], C, dest);
	on_stack[node] = false;

	if (!s.empty()) {
		s.pop();
	}
}

void send_message(vector<bool> M, vector<bool> C) {
	// Augment the message
	M.pb(1);

	// Find the good positions
	vector<int> positions;
	for (int i = 0; i < N; i++) {
		if (!C[i]) {
			positions.pb(i);
		}
	}
	positions.pb(positions[0] + N);

	int idx = 0;
	for (int p = 1; p <= 32 || idx < M.size(); p++) {
		vector<bool> packet(N, false);

		for (int i = 0; i < GOOD; i++) {
			int a = positions[i];
			int b = positions[i + 1];

			if (b - a > p) {
				packet[a] = 0;
			}
			else if (b - a == p) {
				packet[a] = 1;
			}
			else {
				// Send message info
				if (idx < M.size()) {
					packet[a] = M[idx];
					idx++;
				}
				else {
					packet[a] = 0;
				}
			}
		}

		send_packet(packet);
	}
}

vector<bool> receive_message(vector<vector<bool>> R) {
	vector<bool> C(N, true);

	vector<int> dest(N);
	// Retrieve destination of each position
	for (int i = 0; i < N; i++) {
		int p = 0;
		while (p < R.size() && R[p][i] == 0) {
			p++;
		}

		dest[i] = (i + p + 1) % N;
	}

	// Find cycle of length GOOD
	visited.assign(N, false);
	on_stack.assign(N, false);
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			dfs(i, C, dest);
		}
	}

	// Retrieve message
	vector<bool> message;
	vector<bool> done(N, false);
	for (int p = 0; p < R.size(); p++) {
		for (int i = 0; i < N; i++) {
			if (C[i]) {
				continue;
			}
			else if (!done[i]) {
				done[i] = R[p][i];
			}
			else {
				message.pb(R[p][i]);
			}
		}
	}

	while (message.back() == 0) {
		message.pop_back();
	}
	message.pop_back();

	return message;
}
