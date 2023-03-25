#include <bits/stdc++.h>
#define MAXM 200000
#define MAXN 200000

using namespace std;

bool greatersort(int a, int b)
{
    return a > b;
}

int n, m;
int customers[MAXM];
multiset<int, decltype(greatersort)*> tickets(greatersort);

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        int curticket;
        scanf("%d", &curticket);
        tickets.insert(curticket);
    }

    for (int c = 0; c < m; c++) {
        scanf("%d", &customers[c]);

        auto ticketpoint = (tickets.lower_bound(customers[c]));
        int ticket;
        if (ticketpoint == tickets.end())
            ticket = -1;
        else {
            tickets.erase(ticketpoint);
            ticket = *(ticketpoint);
        }

        printf("%d\n", ticket);
    }

    
    return 0;
}