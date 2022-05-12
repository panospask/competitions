#include <bits/stdc++.h>

using namespace std;

bool check_digit(bool array[], int m, int m1)
{
    int m2 = m * m1;
    bool new_array[10];
    for (int i = 0; i < 10; i++) 
        new_array[i] = array[i];

    for (; m1 > 0; m1 /= 10) {
        int digit = m1 % 10;
        if (!new_array[digit])
            return false;
        else 
            new_array[digit] = false;
    }

    for(; m2 > 0; m2 /= 10) {
        int digit = m2 % 10;
        if (!new_array[digit])
            return false;
        else 
            new_array[digit] = false;
    }

    for (int i = 0; i < 10; i++)
        if (new_array[i] == true)
            return false;

    return true;
}

int main(void)
{
    freopen("digits.in", "r", stdin);
    freopen("digits.out", "w", stdout);

    int n;
    cin >> n;
    bool digits[10] = {false, true, true, true, true, true, true, true, true, true};
   
    if (n >= 5000) {
        cout << 0 << endl;
        return 0;
    }

    for (int num = n; num > 0; num /= 10) {
        int dig = num % 10;
        if (digits[dig] != false)
            digits[dig] = false;
        else {
            cout << 0 << endl;
            return 0;
        }
    }

    for (int i = 1; i < 5000; i++) {
        if (check_digit(digits, n, i)) {
            cout << i << ' ' << i * n << endl;
            return 0;
        }
    }

    cout << 0 << endl;
}