#include <bits/stdc++.h>

using namespace std;

#define pb push_back

unordered_map<long long int, int> dist;

int main(void)
{
    int n;
    long long int x;

    scanf("%d %lld", &n, &x);

    queue<long long int> resulting;
    dist[x] = 0;
    resulting.push(x);

    while(!resulting.empty()) {
        long long int cur = resulting.front();
        resulting.pop();
        int curdist = dist[cur];

        string num = to_string(cur);
        if (num.length() == n) {
            printf("%d\n", curdist);
            return 0;
        }

        for (auto z : num) {
            long long int new_num = cur * (int)(z - '0');
            if (!dist[new_num]) {
                dist[new_num] = curdist + 1;
                resulting.push(new_num);
            }
        }
    }

    printf("-1\n");
    return 0;
}