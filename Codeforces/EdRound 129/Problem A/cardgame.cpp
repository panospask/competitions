#include <bits/stdc++.h>

using namespace std;

int alice[50];
int bob[50];

int main(void)
{
    // freopen("inputfile.in", "r", stdin);

    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n, m;
        scanf("%d", &n);
        int max_A = 0, max_B = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &alice[i]);
            if (alice[i] > max_A)
                max_A = alice[i];
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &bob[i]);
            if (bob[i] > max_B)
                max_B = bob[i];
        }

        if (max_B > max_A)
            printf("Bob\nBob\n");
        else {
            printf("Alice\n");
            if (max_B == max_A)
                printf("Bob\n");
            else   
                printf("Alice\n");
        }
    }

    return 0;
}