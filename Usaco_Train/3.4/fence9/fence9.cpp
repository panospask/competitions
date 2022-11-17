/*
ID: panos.p1
LANG: C++11
TASK: fence9
*/

#include <bits/stdc++.h>
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;

ii p1, p2, p3;
ii c;
long long int ans;

int gcd(int a,int b){
    if(b==0)return a;
    else return gcd(b,a%b);
}

int abval(int a)
{
    if (a < 0)
        return -a;

    return a;
}

int find_points(ii a, ii b)
{
    return gcd(abval(a.first - b.first), abval(a.second - b.second)) + 1;
}

int main(void)
{
    freopen("fence9.in", "r", stdin);
    freopen("fence9.out", "w", stdout);

    scanf("%d %d", &p2.first, &p2.second);
    c = mp(p2.first, 0);
    p1 = mp(0 , 0);
    scanf("%d", &p3.first);
    p3.second = 0;

    //Triangle p1-p2-c
    int ttl_points = find_points(c, p1);
    ttl_points += find_points(c, p2);
    ttl_points += find_points(p1, p2); 
    ttl_points -= 3;
    ans += (c.first * p2.second + ttl_points) / 2 + 1;
    //Triangle p2-p3-c
    ttl_points = find_points(c, p3) + find_points(c, p2) + find_points(p3, p2) - 3;
    int val = (abval(p3.first - c.first) * p2.second + ttl_points) / 2 + 1;
    if (p3.first < c.first)
        val = -val;

    ans += val;

    ans -= find_points(p1, p2) + find_points(p2, p3) + find_points(p3, p1) - 3;
    if (val >= 0)
        ans -= find_points(c, p2);
    else 
        ans += find_points(p2, p3);

    printf("%lld\n", ans);
    return 0;
}