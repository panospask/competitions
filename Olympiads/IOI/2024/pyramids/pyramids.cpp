#include "pyramids.h"
#include <vector>

using namespace std;

int N;

typedef long long ll;

vector<ll> p1, p2;

ll sum(vector<ll>& p, int l, int r)
{
    return p[r + 1] - p[l];
}

void makepref(vector<ll>& p, vector<int>& v)
{
    p.resize(N + 1);
    p[0] = 0;

    for (int i = 1; i <= N; i++) {
        p[i] = p[i - 1] + v[i - 1];
    }
}

void init(std::vector<int> A, std::vector<int> B) {
    N = A.size();

    makepref(p1, A);
    makepref(p2, B);
}

bool can_transform(int L, int R, int X, int Y) {
  return sum(p1, L, R) == sum(p2, X, Y);
}
