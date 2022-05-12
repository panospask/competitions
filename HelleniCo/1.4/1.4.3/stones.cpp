#include <bits/stdc++.h>

using namespace std;

struct stone {
    int mass;
    int volume;
    double density;

    void init(int v, int m) {
        mass = m;
        volume = v;
        density = (double) m / v;
    }
};

int sort_rocks(const void* a, const void* b)
{
    const struct stone sa = *(stone*)a;
    const struct stone sb = *(stone*)b;

    if (sa.density > sb.density)
        return -1;
    else if (sa.density == sb.density)
        return 0;
    else 
        return 1;
}

int main(void)
{
    freopen("stones.in", "r", stdin);
    freopen("stones.out", "w", stdout);

    int n, z;
    cin >> n >> z;

    stone rocks[n];

    for (int i = 0; i < n; i++) {
        int vol, mass;
        cin >> vol >> mass;

        rocks[i].init(vol, mass);
    }

    qsort(rocks, n, sizeof(stone), sort_rocks);

    int remaining_vol = z;
    double total_mass = 0;
    for (int i = 0; i < n && remaining_vol > 0; i++) {
        if (rocks[i].volume < remaining_vol) {
            total_mass += rocks[i].mass;
            remaining_vol -= rocks[i].volume;
        }
        else {
            total_mass += remaining_vol * rocks[i].density;
            remaining_vol = 0;
        }
    }

    printf("%.3f\n", total_mass);
}