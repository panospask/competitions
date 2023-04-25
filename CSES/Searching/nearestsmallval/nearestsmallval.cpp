#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int n;
vector<int> vals;
stack<ii> smaller_values;

int main(void)
{
    int n;
    scanf("%d", &n);
    vals.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i]);

    for (int i = 0; i < n; i++) {
        while (!smaller_values.empty()) {
            ii cur = smaller_values.top();
            if (cur.first >= vals[i])
                smaller_values.pop();
            else
                break;
        }

        if (smaller_values.empty())
            printf("0 ");
        else
            printf("%d ", smaller_values.top().second + 1);

        smaller_values.push(make_pair(vals[i], i));
    }

    return 0;
}