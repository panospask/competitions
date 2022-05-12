#include <bits/stdc++.h>

using namespace std;

long long int calc_min_cubes(int n, int k)
{
    long long int m = n % k;
    long long int y = n - m;
    long long int x = y/k;

    int b = m *(x + 1);
    long long int t = k * (x * (x + 1)) / 2;

    long long int total = b + t;
    return total;
}

int binary_search(int min, int max, int number, int k) {
    if (min >= max - 1) {
        return min;
    }
    
    int middle = (min + max) / 2;
    long long int calculated = calc_min_cubes(middle, k);
    if (calculated == number)
        return middle;
    else if (calculated > number) {
        return binary_search(min, middle, number, k);
    }
    else {
        return binary_search(middle, max, number, k);
    }
    
}

int main(void)
{
    freopen("cubes.in", "r", stdin);
    freopen("cubes.out", "w", stdout);

    int n, k;
    cin >> n >> k;

    cout << binary_search(1, 100000, n, k) << endl;
}