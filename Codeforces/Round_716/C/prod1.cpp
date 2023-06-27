#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
int coprimes = 0;

vector<int> ans;

int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);

    while (b != 0)
        swap(b, a %= b);

    return a;
}

int main(void)
{
    scanf("%d", &n);

    ll res = 1;
    for (int i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            ans.push_back(i);
            res = res * i % n;
        }
    }

    int exclude = -1;
    if (res != 1)
        exclude = res;


    printf("%d\n", (int)ans.size() - (exclude != -1));
    for (auto a : ans) {
        if (a != exclude)
            printf("%d ", a);
    }
    printf("\n");
    return 0;
}