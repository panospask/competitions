#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

long long int muffintime = 7, cookietime = 9;
long long int a[10] = {4}, b[10] = {3}, c[10] = {18};

pair<int, int> find_cookie_points(long long int z, int cow)
{
    long long int min_x = max(1ll, z - muffintime);
    long long int max_x = min(cookietime, z-1);

    if (a[cow] > b[cow]) {
        max_x = min(max_x, (c[cow] - z * b[cow]) / (a[cow] - b[cow]));
    }
    else if (a[cow] < b[cow]) {
        min_x = max(min_x, (c[cow] - z * b[cow]) / (a[cow] - b[cow]));
    }
    else {
        if (c[cow] < z * b[cow])
            return mp(-1, -1);
    }


    if (min_x > max_x)
        return mp(-1, -1);
    return mp(min_x, max_x);
}

void print_pair(pair<int, int> p) 
{
    cout << p.first << ' ' << p.second;
}

int main(void)
{
    print_pair(find_cookie_points(6, 0));
}