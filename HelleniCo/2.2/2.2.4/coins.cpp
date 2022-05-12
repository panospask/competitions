#include <bits/stdc++.h>

using namespace std;

bool decide_win(int n, int k, int l, int array[])
{
    if (array[n] != 2)
        return array[n];
    
    if (n == 0)
        return false;
    
    if (n < k) {
        array[n] = n % 2;
        return n % 2;
    }

    int remove_k = false;
    int remove_l = false;
    int remove_one = false;


    remove_k = !decide_win(n - k, k, l, array);
    if (n >= l) {
        remove_l = !decide_win(n - l, k, l, array);
    }

    remove_one = !decide_win(n - 1, k, l, array);

    if (remove_k || remove_l || remove_one) {
        array[n] = true;
        return true;
    }
    else {
        array[n] = false;
        return false;
    }
}

int main(void)
{
    freopen("coins.in", "r", stdin);  
    freopen("coins.out", "w", stdout); 

    int array[1000000];

    fill(array, array + 1000000, 2);

    int k, l;
    cin >> k >> l;
    int m;
    cin >> m;

    
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;

        bool asen_win = decide_win(n, k, l, array);
        if (asen_win)
            cout << 'A';
        else 
            cout << 'B';
    }

    cout << endl;
}