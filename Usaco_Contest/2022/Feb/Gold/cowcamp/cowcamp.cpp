#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXT 1000

using namespace std;

// prob[i][j] is the probability of getting j test cases correct from a total of i
double prob[MAXT + 1][MAXT + 1];

// pref_prob[i] is the probability of getting i or less test cases correct from a total of t
double pref_prob[MAXT + 1];

// exp_val[t] - exp_val[i-1] is the expected value you would get by getting i or more test_cases correct 
double exp_val[MAXT + 1];

int t, k;

double skip_submissions(double a, double b, double E, long long int num)
{
    double a_k = pow(a, num);

    return E * a_k + b * (a_k - 1) / (a - 1);
}

int main(void)
{
    // freopen("cowcamp.in", "r", stdin);
    // freopen("cowcamp.out", "w", stdout);

    scanf("%d %d", &t, &k);
    t--;

    prob[0][0] = 1;
    for (int i = 1; i <= t; i++) {
        prob[i][0] = prob[i-1][0] / 2;
        for ( int j = 1; j <= t; j++)
            prob[i][j] = (prob[i-1][j-1] + prob[i-1][j]) / 2;
    }
    pref_prob[0] = prob[t][0];
    for (int i = 1; i <= t; i++)
        pref_prob[i] = pref_prob[i-1] + prob[t][i];

    exp_val[0] = 0;
    for (int i = 1; i <= t; i++)
        exp_val[i] = exp_val[i-1] + prob[t][i] * i;

    double cur_exp = 0;
    int cur_k = 0;

    while (cur_k < k) {
        long long int lbound = (long long int)floor(cur_exp);

        double c_a = pref_prob[lbound];
        double c_b = exp_val[t] - exp_val[lbound];

        // Implement binary search on k
        long long int l = 1; 
        long long int r = k + 1; 

        while (r > l + 1) {
            auto mid = (l + r) / 2;
            if (floor(skip_submissions(c_a, c_b, cur_exp, mid)) == lbound)
                l = mid;
            else 
                r = mid;
        }

        auto cur_skip = min(l, (long long int) k - cur_k);
        cur_k += cur_skip;
        cur_exp = skip_submissions(c_a, c_b, cur_exp, cur_skip);
    }

    printf("%.20lf\n", cur_exp + 1);
    return 0;
}