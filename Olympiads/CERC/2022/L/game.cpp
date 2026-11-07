#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int REGULAR = 98;
const int NUMROWS = 4;

const int INF = 101;

int A[REGULAR];

// Positions of cards in hand
set<int> hand;

vector<int> stacks[NUMROWS];
// s is 1 for increasing rows, -1 for decreasing rows. It's a modifier
int mod[NUMROWS] = {1, 1, -1, -1};

// I define the loss of a certain value to be 0 if the reverse trick can be done
// otherwise its min(abs(vprev - v)) for all usable stacks
// Target is for actually playing the card, which value of res we're targeting
int loss(int v, int target = -1) {
    int res = INF;
    for (int r = 0; r < NUMROWS; r++) {
        // Check for the -10 trick
        if ((v - stacks[r].back()) * mod[r] == -10) {
            res = 0;
        }
        else if ((v - stacks[r].back()) * mod[r] > 0) {
            // This card can be used here
            res = min(res, abs(v - stacks[r].back()));
        }

        if (res == target) {
            // Play the card (don't care about return value)
            stacks[r].push_back(v);
            return 0;
        }
    }

    return res;
}

int main(void) {
    for (int i = 0; i < REGULAR; i++) {
        cin >> A[i];
    }

    // Build rows
    stacks[0].push_back(1);
    stacks[1].push_back(1);
    stacks[2].push_back(100);
    stacks[3].push_back(100);

    for (int i = 0; i < 8; i++) {
        hand.insert(i);
    }
    // Next insert cards
    int nxt = 8;

    while (!hand.empty()) {
        int res = INF;
        int idx = -1;
        for (auto pos : hand) {
            int cur = loss(A[pos]);
            if (cur < res) {
                res = cur;
                idx = pos;
            }
        }

        if (res == INF) {
            // We cannot play a move
            break;
        }

        // Play the card
        loss(A[idx], res);
        hand.erase(idx);

        if (nxt != REGULAR) {
            nxt++;
            if (nxt % 2 == 0) {
                hand.insert(nxt - 2);
                hand.insert(nxt - 1);
            }
        }
    }

    // Print the final game state
    // Stacks
    for (int j = 0; j < 4; j++) {
        for (auto v : stacks[j]) {
            cout << v << ' ';
        }
        cout << endl;
    }
    // Hand
    for (auto pos : hand) {
        cout << A[pos] << ' ';
    }
    cout << endl;
    // Remaining
    for (int i = (nxt % 2 == 0 ? nxt : nxt - 1); i < REGULAR; i++) {
        cout << A[i] << ' ';
    }
    cout << endl;
}