#include <bits/stdc++.h>

#define MIN_YEAR -100000

using namespace std;

int compare_ints(const void* a, const void* b)
{
    return *(int*) a - *(int*) b;
}

int main(void)
{
    freopen("crocodiles.in", "r", stdin);
    freopen("crocodiles.out", "w", stdout);

    int n;
    cin >> n;

    int births[n];
    int deaths[n];

    for (int i = 0; i < n; i++) {
        int born, dead;
        cin >> born >> dead;

        births[i] = born - MIN_YEAR;
        deaths[i] = dead - MIN_YEAR;
    }

    qsort(births, n, sizeof(int), compare_ints);
    qsort(deaths, n, sizeof(int), compare_ints);

    int year;
    int cur_death = 0;
    int max_crocs = 0;
    int cur_crocs = 0;

    for (int i = 0; i < n; i++) {
        year = births[i];
        cur_crocs++;
        for (; deaths[cur_death] <= year; cur_death++)
            cur_crocs--;
        
        if (cur_crocs > max_crocs)
            max_crocs = cur_crocs;
    }


    cout << max_crocs << endl;
}