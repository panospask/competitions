#include <bits/stdc++.h>

using namespace std;

const int MAXV = 30;
vector<int> H;

int calculate(int x, int y, int iteration)
{
    if (iteration == 0) {
        return 0;
    }

    int cut = H[iteration - 1];
    if (x <= cut) {
        return calculate(x, y, iteration - 1);
    }
    if (x - y < cut) {
        return calculate(x - cut, y, iteration - 1);
    }
    if (y >= cut + 1) {
        return calculate(x - cut, y - cut, iteration - 1);
    }

    return 1;
}

int main(void)
{
    H.resize(MAXV + 1);
    H[0] = 2;

    for (int i = 0; i < MAXV; i++) {
        H[i] = H[i - 1] * 2 + 1;
    }

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int x, y;
        scanf("%d %d", &x, &y);

        printf("%d\n",(int) !calculate(x, y, MAXV - 1));
    }
}