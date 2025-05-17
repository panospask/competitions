#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> elsie;
vector<int> bessie;

// found[v]: Does elsie have card with value v?
vector<bool> found;

// We assume bigger cards always win
int solve_game(vector<int> mine, vector<int> opponent) {
    sort(mine.begin(), mine.end());
    reverse(mine.begin(), mine.end());
    sort(opponent.begin(), opponent.end());
    reverse(opponent.begin(), opponent.end());

    int won = 0;
    int lost = 0;
    for (int i = 0; i < mine.size(); i++) {
        // Our biggest card is the one in position: won (0 based)

        if (mine[won] > opponent[i]) {
            won++;
        }
        else {
            lost++;
        }
    }

    return won;
}

int main(void) {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    scanf("%d", &N);

    elsie.resize(N);
    found.assign(2 * N + 1, false);

    for (int i = 0; i < N; i++) {
        scanf("%d", &elsie[i]);

        found[elsie[i]] = true;
    }

    for (int v = 1; v <= 2 * N; v++) {
        if (found[v] == false) {
            // Elsie does not have this card => Bessie has this card
            bessie.push_back(v);
        }
    }

    sort(bessie.begin(), bessie.end());
    reverse(bessie.begin(), bessie.end());

    // N/2 for the first half
    // vector<int> first_elsie(elsie.begin(), elsie.begin() + N / 2);

    vector<int> first_elsie;
    vector<int> first_bessie;
    for (int i = 0; i < N / 2; i++) {
        first_elsie.push_back(elsie[i]);
        first_bessie.push_back(bessie[i]);
    }

    int total_wins = solve_game(first_bessie, first_elsie);
    
    // For second half, we want to modify (somehow) the cards such that big cards lose (are smaller than) small cards
    vector<int> second_elsie;
    vector<int> second_bessie;
    for (int i = N / 2; i < N; i++) {
        second_bessie.push_back(-bessie[i]);
        second_elsie.push_back(-elsie[i]);
    }

    total_wins += solve_game(second_bessie, second_elsie);

    printf("%d\n", total_wins);
}