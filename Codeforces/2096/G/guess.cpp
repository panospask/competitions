#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int BASE = 3;

struct Query {
    vector<vector<int>> numbers;
    int left, right, out;

    Query(vector<vector<int>> n) : numbers(n) {
        if (numbers[0].size() == numbers[1].size()) {
            left = 0;
            right = 1;
            out = 2;
        }
        else if (numbers[1].size() == numbers[2].size()) {
            left = 1;
            right = 2;
            out = 0;
        }
        else if (numbers[0].size() == numbers[2].size()) {
            left = 2;
            right = 0;
            out = 1;
        }
        else {
            left = -1;
        }
    }

    void ask_query(void);
    void answer(char a);
};

int N;
int total_digits = 0;
vector<int> pwr;

vector<Query> queries;
vector<char> results;

vector<bool> alive;

// In base 3, what is the digit d of v
int check_digit(int v, int d) {
    v /= pwr[d];
    v %= BASE;

    return v;
}

int digitsum(int v) {
    int sum = 0;

    for (int d = 0; d < total_digits; d++) {
        sum += v % BASE;
        v /= BASE;
    }

    return sum % BASE;
}

void Query::ask_query(void) {
    printf("%d", 2 * (int)numbers[left].size());

    if (numbers[left].size() != numbers[right].size()) {
        exit(EXIT_FAILURE);
    }

    for (auto i : numbers[left]) {
        printf(" %d", i + 1);
    }
    for (auto i : numbers[right]) {
        printf(" %d", i + 1);
    }
    printf("\n");
}

void Query::answer(char a) {
    if (a == '?') {
        return;
    }

    if (a != 'L') {
        for (auto i : numbers[left]) {
            alive[i] = false;
        }
    }
    if (a != 'R') {
        for (auto i : numbers[right]) {
            alive[i] = false;
        }
    }
    if (a != 'N') {
        for (auto i : numbers[out]) {
            alive[i] = false;
        }
    }
}

void solve(void) {
    scanf("%d", &N);

    pwr.clear();
    queries.clear();
    alive.clear();
    results.clear();

    pwr.pb(1);
    while (pwr.back() * BASE < N) {
        pwr.pb(pwr.back() * 3);
    }
    total_digits = pwr.size();

    vector<vector<int>> numbers;
    for (int d = 0; d < total_digits; d++) {
        // Create new query

        // numbers categorized by their d-th digit
        numbers.clear();
        numbers.resize(BASE);
        for (int i = 0; i < N; i++) {
            numbers[check_digit(i, d)].pb(i);
        }

        Query cur(numbers);
    
        if (cur.left == -1) {
        int s = cur.numbers[1].size();
            cur.numbers[2].insert(cur.numbers[2].end(), cur.numbers[0].begin() + s, cur.numbers[0].end());
            cur.numbers[0].erase(cur.numbers[0].begin() + s, cur.numbers[0].end());

            cur.left = 0;
            cur.right = 1;
            cur.out = 2;
        }
        queries.pb(cur);
    }

    // Create "special" query using digsum
    numbers.clear();
    numbers.resize(BASE);
    for (int i = 0; i < N; i++) {
        numbers[digitsum(i)].pb(i);
    }
    queries.pb(Query(numbers));

    // Ask queries
    int Q = queries.size();
    printf("%d\n", Q);
    for (auto& q : queries) {
        q.ask_query();
    }
    fflush(stdout);
    
    // Read answers
    results.resize(queries.size());
    for (int i = 0; i < Q; i++) {
        scanf(" %c", &results[i]);
    }

    // Process answers
    alive.assign(N, true);
    for (int i = 0; i < Q; i++) {
        queries[i].answer(results[i]);
    }

    int remaining = -1;
    for (int i = 0; i < N; i++) {
        if (alive[i]) {
            remaining = i;
            break;
        }
    }

    printf("%d\n", remaining + 1);
    fflush(stdout);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}