#include <bits/stdc++.h>
#define MAXN 10000
#define MINN 1
#define MAXM 10
#define MINM 1
#define MAXLENGTH (int)(1e9)
#define MINLENGTH 1
#define MAXCOST 10000
#define MINCOST 1

using namespace std;

// Generates a random number in the range [start, end]
int generate_random_number(int start, int end)
{
    long int diff = end - start + 1;
    return (rand() % diff) + start;
}

int main(void)
{
    srand((unsigned)time(NULL));

    // Generate offers
    int n = generate_random_number(MINN, MAXN);
    int q = generate_random_number(MINM, MAXM);

    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int start_offer = generate_random_number(MINLENGTH, MAXLENGTH - 1);
        int end_offer = generate_random_number(start_offer + 1, MAXLENGTH);

        int travel = end_offer - start_offer;

        int cost = generate_random_number(MINCOST, MAXCOST);

        printf("%d %d %d\n", start_offer, travel, cost);
    }

    // Generate queries
    for (int i = 0; i < q; i++) {
        int start_query = generate_random_number(MINLENGTH, MAXLENGTH - 1);
        int end_query = generate_random_number(start_query + 1, MAXLENGTH);

        int travel = end_query - start_query;

        printf("%d %d\n", start_query, travel);
    }

    return 0;
}