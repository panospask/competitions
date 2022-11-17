/*
ID: panos.p1
LANG: C++
TASK: runround
*/

#include <bits/stdc++.h>
#define FIND_DEST(pos, val, si) (((pos - val) % si) + si) % si
#define pb push_back

using namespace std;

bool found = false;
int points_to[10];
bool visited[10];

int digcount[10];

vector<int> num;

void create_new_spot(void)
{
    num.pb(1);

    for (int i = num.size() - 1; i > 0; i--)
        num[i] = num[i - 1];

    num[0] = 1;

    int sz = num.size();

    for (int i = 0; i < num.size(); i++)
        points_to[i] = ((i - num[i]) % sz + sz) % sz;
}

void modify_spot(int spot)
{
    if (spot < 0) {
        create_new_spot();
        return;
    }

    num[spot]++;
    if (num[spot] == 10) {
        num[spot] = 0;
    }

    points_to[spot] = FIND_DEST(spot, num[spot], num.size());
    
    
    if (num[spot] == 0)
        modify_spot(spot - 1);
}

bool check_num(void)
{
    memset(visited, false, sizeof(visited));

    int start = 0;
    int cnt = 0;
    int max_cnt = num.size();

    int cur = start;

    while(true) {
        if (cnt == max_cnt) {
            if (cur == start)
                return true;
            else 
                return false;
        }

        if (visited[cur])
            return false;

        visited[cur] = true;
        cnt++;
        cur = points_to[cur];
    }
}

int main(void)
{
    freopen("runround.in", "r", stdin);
    freopen("runround.out", "w", stdout);

    long long int n;
    scanf("%lld", &n);

    for (long long int i = n; i > 0; i /= 10)
        num.pb(i % 10);

    reverse(num.begin(), num.end());

    int size = num.size();
    for (int i = 0; i < num.size(); i++)
        points_to[i] = FIND_DEST(i, num[i], num.size());

    while (!found) {
        modify_spot(num.size() - 1);
        found = check_num();
    }

    for (auto i : num)
        printf("%d", i);

    printf("\n");

    return 0;
}