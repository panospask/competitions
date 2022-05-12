#include <bits/stdc++.h>

using namespace std;

struct client {
    int s;
    int f;
};


typedef struct client Client;

int compare_client(const void* a, const void* b)
{
    const Client* ca;
    const Client* cb;
    ca = (Client*)a;
    cb = (Client*)b;

    return ca->f - cb->f;

}

int main(void)
{
    freopen("rentacar.in", "r", stdin);
    freopen("rentacar.out", "w", stdout);

    int n;
    cin >> n;
    
    Client lists[n];
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        cin >> lists[i].s >> lists[i].f;
    }

    qsort(lists, n, sizeof(Client), compare_client);

    int max = 0;
    int cur_fin = 0;
    for (int i = 0; i < n; i++) {
        if (lists[i].s >= cur_fin) {
            cur_fin = lists[i].f;
            max++;
        }       
    }

    cout << max << endl;
}