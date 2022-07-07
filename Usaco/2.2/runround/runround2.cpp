/*
ID: panos.p1
LANG: C++
TASK: runround
*/


#include <bits/stdc++.h>
#define FIND_DEST(pos, val, si) (((pos + val) % si) + si) % si
#define pb push_back

using namespace std;

vector<int> num;
int dignum = 0;
int digits[10];
int points_to[10];
bool visited[10];
bool found = false;
int more_than_1_cnt = 0;

void count_digits(void)
{
    more_than_1_cnt = 0;
    dignum = 0;
    for (int i = 0; i < 10; i++)   
        digits[i] = 0;

    for (auto d : num) {
        digits[d]++;
        if (digits[d] == 1)
            dignum++;
        if (digits[d] == 2)
            more_than_1_cnt++;
    }
}

void create_new_spot(void)
{
    num.pb(1);

    for (int i = num.size() - 1; i > 0; i--)
        num[i] = num[i - 1];

    num[0] = 1;

    int sz = num.size();

    for (int i = 0; i < sz; i++)
        points_to[i] = FIND_DEST(i, num[i], sz);

    count_digits();
}

void modify_spot(int spot)
{
    if (spot < 0) {
        create_new_spot();
        return;
    }

    digits[num[spot]]--;
    if (digits[num[spot]] == 0) dignum--;
    if (digits[num[spot]] == 1) more_than_1_cnt--;

    num[spot]++;
    num[spot] %= 10;

    digits[num[spot]]++;
    if (digits[num[spot]] == 1) dignum++;
    if (digits[num[spot]] == 2) more_than_1_cnt++;

    points_to[spot] = FIND_DEST(spot, num[spot], num.size());
    
    
    if (num[spot] == 0)
        modify_spot(spot - 1);
}

bool check_num(void)
{
    memset(visited, false, sizeof(visited));

    int start = 0;
    int cnt = 0;
    int max_cnt = dignum;

    int cur = 0;

    while(true) {
        if (cnt == max_cnt) {
            if (cur == start)
                return true;
            else 
                return false;
        }

        if (visited[num[cur]])
            return false;

        visited[num[cur]] = true;
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

    count_digits();

    while (!found) {
        n++;
        modify_spot(num.size() - 1);
        if (more_than_1_cnt == 0)
            found = check_num();
    }

    for (auto i : num)
        printf("%d", i);

    printf("\n");

    return 0;
}