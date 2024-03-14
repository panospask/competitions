#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int teams[10];

void read_input(void)
{
    int total_teams;
    scanf("%d", &total_teams);
    getchar();

    for (int i = 0; i < total_teams; i++) {

        char c;
        c = getchar();

        while (c != ' ' && c != '\0' && c != '\n') {
            teams[c - '0'] = i;
            c = getchar();
        }
    }   
}

void move_players(vector<int>& players)
{
    printf("next");
    for (auto player : players)
        printf(" %d", player);
    printf("\n");

    fflush(stdout);
    cout.flush();
}

int main(void)
{
    // Implementing tortoise and hare algorithm

    // Step 1
    bool noteq = true;
    vector<int> to_move;
    to_move.pb(0); // P0 is the hare
    to_move.pb(1); // P1 is the tortoise
    while (noteq) {
        move_players(to_move);
        read_input(); // Ignore this, we want to move P0 once more
        to_move.pop_back();
        move_players(to_move);
        to_move.pb(1);
        read_input();

        if (teams[0] == teams[1]) {
            // We have found a cycle
            noteq = false;
        }
    }

    for (int i = 2; i < 10; i++)
        to_move.pb(i);
    
    // Move everyone together, as they will first up joining at the finish
    bool joined = false;
    while (!joined) {
        move_players(to_move);
        read_input();

        if (teams[0] == teams[3])
            joined = true;
    }

    printf("done\n");

    return 0;
}
