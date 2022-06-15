/*
ID: panos.p1
LANG: C++
TASK: ride
*/

#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);

    string a;
    string b;

    cin >> a >> b;
    long long int a_val = 1;
    for (int i = 0; i < a.size(); i++) {
        a_val *= a[i] - 'A' + 1;
    }
    long long int b_val = 1;
    for (int i = 0; i < b.size(); i++) {
        b_val *= b[i] - 'A' + 1;
    }

    if (a_val % 47 == b_val % 47)
        printf("GO");
    else 
        printf("STAY");

    printf("\n");
    
    return 0;
}