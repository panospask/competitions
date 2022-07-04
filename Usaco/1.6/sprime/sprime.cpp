/*
ID: panos.p1
LANG: C++
TASK: sprime
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<int> sprimes;
int n;

bool isprime(int num)
{
    if (num == 2)
        return true;

    if (num % 2 == 0)
        return false;
    
    for (int i = 3; i * i <= num; i+= 2)
        if (num % i == 0)
            return false;

    return true;
}

void sprime_dfs(int num, int l)
{
    if (!isprime(num))
        return;

    if (l == n) {
        sprimes.pb(num);
        return;
    }

    for (int i = 1; i < 10; i += 2)
        sprime_dfs(10 * num + i, l + 1);
}

int main(void)
{
    freopen("sprime.in", "r", stdin);
    freopen("sprime.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 2; i < 10; i++)
        sprime_dfs(i, 1);

    for (auto& num : sprimes)
        printf("%d\n", num);

    return 0;
}