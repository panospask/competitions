#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

int n;
vector<int> active_circles;
vector<long double> radius;
vector<int> maxradius;
vector<int> position;

long double find_r2(int x1, long double r1, int x2)
{
    return ((ll)(x1 - x2) * (x1 - x2)) / (4 * r1);
}

long double allowed_radius(int i, int j)
{
    return find_r2(position[i], radius[i], position[j]);
}

int main(void)
{
    scanf("%d", &n);

    position.resize(n);
    maxradius.resize(n);
    radius.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &position[i], &maxradius[i]);
    }

    for (int i = 0; i < n; i++) {
        bool foundbreak = false;

        radius[i] = maxradius[i];
        while (!active_circles.empty()) {
            radius[i] = min(radius[i], allowed_radius(active_circles.back(), i));

            if (radius[i] >= radius[active_circles.back()])
                active_circles.pop_back();
            else
                break;
        }

        active_circles.push_back(i);

        printf("%.3Lf\n", radius[i]);
    }

    return 0;
}