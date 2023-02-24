#include <bits/stdc++.h>

using namespace std;

double c;

bool f(double a)
{
    return a * a + sqrt(a) <= c;
}

int main(void)
{
    scanf("%lf", &c);

    double l = 0; // f(l) = true
    double r = c; // f(r) = false
    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2;
        if (f(mid))
            l = mid;
        else 
            r = mid;
    }
    printf("%.10lf\n", l);
    return 0;
}