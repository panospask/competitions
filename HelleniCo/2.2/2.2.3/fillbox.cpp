#include <bits/stdc++.h>

using namespace std;


long long int cubes(long long int l, long long int w, long long int h)
{
    int smallest = min(l, min(w, h));

    if (smallest == 0)
        return 0;
    else if (smallest == 1)
        return l * w * h;

    long long int big = 1;
    while (big <= smallest)
        big *= 2;
    big /= 2;

    long long int fit = (l / big) * (w / big) * (h / big);

    long long int c1 = cubes(l % big, w, h);
    long long int c2 = cubes(l - (l % big), w % big, h);
    long long int c3 = cubes(l - (l % big), w - (w % big), h % big);

    return fit + c1 + c2 + c3;
}

int main(void)
{
    freopen("fillbox.in", "r", stdin);
    freopen("fillbox.out", "w", stdout);

    long long int l, w, h;
    cin >> l >> w >> h;

    cout << cubes(l, w, h) << endl;
    return 0;
}