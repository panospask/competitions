#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

vector<ii> sections;

void make_rotation(int start, int* a, int* new_arr, int n)
{
    int j = start;
    for (int i = 0; i < n; i++) {
        new_arr[i] = a[j];
        j++;
        j %= n;
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        sections.clear();
        int n;
        scanf("%d", &n);

        int a[n], new_a[n];
        int odd_num = 0;
        for (int i = 0; i < n; i++) {
            scanf("%1d", &a[i]);
            if (a[i] == 1)
                odd_num++;
        }

        bool isgood = true;
        if (odd_num == 0 || odd_num % 2 == 1) 
            isgood = false;

        int shift_by = 0;
        for (int i = 1; i < n && isgood; i++) {
            if (a[i - 1] == 1) {
                make_rotation(i, a, new_a, n);
                shift_by = i;
                break;
            }
        }
        int starting = 1;
        for (int i = 1; i < n && isgood; i++) {
            if (new_a[i] == 1) {
                sections.pb(mp(starting, i));
                starting = i + 1;
            }
        }

        if (isgood) {
            printf("YES\n");
            for (auto& rng : sections) {
                for (int i = rng.first; i < rng.second; i++)
                    printf("%d %d\n", ( i + shift_by) % n + 1, ((i + shift_by + 1) % n + 1));

                printf("%d %d\n", (shift_by) % n + 1,(rng.first + shift_by) % n + 1);
            }
        }
        else 
            printf("NO\n");
    }

    return 0;
}