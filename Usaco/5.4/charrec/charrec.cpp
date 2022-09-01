/*
ID: panos.p1
LANG: C++11
TASK: charrec
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAX_FONTS 27
#define MAX_LINES 1200
#define N 20

using namespace std;

const char symbols[] = " abcdefghijklmnopqrstuvwxyz";
char font[MAX_FONTS][N][N];
char image[MAX_LINES][N];
int diff[MAX_LINES][MAX_FONTS][N];

// cost: How many switches must one make to make the lines[i, i + j + 19(0 <= j <= 2)] a font
int cost[MAX_LINES][3];
// represent: The character the above minimal conversion would be assigned to
int represent[MAX_LINES][3];
int linecount;
int anssize;
// dp: Conversion cost of the optimal symbol sequence ending at i
int dp[MAX_LINES];
int opt[MAX_LINES];
void read_font(void)
{
    ifstream fontfile;
    fontfile.open("font.in");

    int lns;
    fontfile >> lns;

    string ln;
    for (int a = 0; a < MAX_FONTS; a++)
        for (int b = 0; b < N; b++) {
            fontfile >> ln;
            for (int c = 0; c < N; c++)
                font[a][b][c] = ln[c];
        }
}

void read_image(void)
{
    for (int i = 0; i < linecount; i++) {
        getchar();
        for (int j = 0; j < N; j++)
            image[i][j] = getchar();
    }
}

void find_diff(void)
{
    for (int i = 0; i < MAX_LINES; i++)
        for (int a = 0; a < MAX_FONTS; a++)
            for (int b = 0; b < N; b++)
                for (int j = 0; j < N; j++)
                    if (image[i][j] != font[a][b][j])
                        diff[i][a][b]++;
}  

void calculate_conversion_cost(void)
{
    // Mistake here

    for (int i = 0; i + N - 2 < MAX_LINES; i++) {
        cost[i][0] = cost[i][1] = cost[i][2] = INT_MAX;

        // Check matching to every possible font with no duplicate or delete
        if (i + N - 1 < linecount) {
            for (int a = 0; a < MAX_FONTS; a++) {
                int curcost = 0;

                for (int b = 0; b < N; b++)
                    curcost += diff[i + b][a][b];

                if (curcost < cost[i][1]) {
                    cost[i][1] = curcost;
                    represent[i][1] = a;
                }
            }
        }

        // Check matching to every possible font with a deleted line
        for (int a = 0; a < MAX_FONTS; a++) {
            int curcost = 0;

            // If the last line is deleted
            for (int b = 0; b < N - 1; b++)
                curcost += diff[i + b][a][b];

            if (cost[i][0] > curcost) {
                cost[i][0] = curcost;
                represent[i][0] = a;
            }

            for (int b = N - 2; b >= 0; b--) {
                // If any other line is deleted
                curcost -= diff[i + b][a][b];
                curcost += diff[i + b][a][b + 1];
                if (cost[i][0] > curcost) {
                    cost[i][0] = curcost;
                    represent[i][0] = a;
                }
            }
        }

        // Check for matching with duplicate line
        if (i + N < linecount) {
            for (int a = 0; a < MAX_FONTS; a++) {
                int curcost = 0;

                // If the last line is duplicated
                for (int b = 0; b < N; b++)
                    curcost += diff[i + b][a][b];
                if (cost[i][2] > curcost) {
                    cost[i][2] = curcost;
                    represent[i][2] = a;
                }

                // If any other line is duplicated
                for (int b = N - 1; b >= 0; b--) {
                    curcost -= diff[i + b][a][b];
                    curcost += diff[i + b + 1][a][b];

                    if (cost[i][2] > curcost) {
                        cost[i][2] = curcost;
                        represent[i][2] = a;
                    }
                }
            }
        }    
    }
}

void find_optimal(void)
{
    for (int i = 0; i < linecount; i++)
        dp[i] = 10e7;
    dp[-1] = 0;

    for (int i = N - 2; i < linecount; i++) {
        int val;
        
        // With a deleted line(N - 1 lines)
        if (i == N - 2)
            val = cost[i - (N - 2)][0];
        else
            val = dp[i - (N - 1)] + cost[i - (N - 2)][0];
        if (val < dp[i]) {
            dp[i] = val;
            opt[i] = N - 1;
        }

        // With no added/removed lines
        if (i >= N - 1) {
            if (i == N - 1)
                val = cost[i - (N - 1)][1];
            else
                val = dp[i - N] + cost[i - (N - 1)][1];
            if (val < dp[i]) {
                dp[i] = val;
                opt[i] = N;
            }
        }

        // With a duplicated line
        if (i >= N) {
            if (i == N)
                val = cost[i - N][2];
            else
                val = dp[i - (N + 1)] + cost[i - N][2];
            if (val < dp[i]) {
                dp[i] = val;
                opt[i] = N + 1;
            }
        }
    }
}

void translate_and_print_answers(void)
{
    vector<char> ans;

    for (int i = linecount - 1; i >= 0; i -= opt[i])
        ans.pb(symbols[represent[i - opt[i] + 1][opt[i] - N + 1]]);

    reverse(ans.begin(), ans.end());
    for (auto c : ans)
        putchar(c);
    putchar('\n');
}

int main(void)
{
    freopen("charrec.in", "r", stdin);
    freopen("charrec.out", "w", stdout);

    scanf("%d", &linecount);
    read_font();
    read_image();
    find_diff();
    calculate_conversion_cost();
    find_optimal();
    translate_and_print_answers();

    return 0;
}