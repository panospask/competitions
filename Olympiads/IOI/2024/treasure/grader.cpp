#include "treasure.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <random>

namespace {

const int MIN_VAL = 0;
const int MAX_VAL = 2'000'000'000;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}

void run_scenario() {
  int n;
  assert(1 == scanf("%d", &n));

  std::vector<std::pair<int, int>> P(n);
  for (int i = 0; i < n; i++)
    assert(2 == scanf("%d%d", &P[i].first, &P[i].second));

  std::vector<int> E = encode(P);
  int L = E.size();

  for (int i = 0; i < L; i++)
    if (E[i] < MIN_VAL || E[i] > MAX_VAL)
      quit("Invalid element in the returned array");

  std::vector<int> S = E;
  std::shuffle(S.begin(), S.end(), std::mt19937(0));

  std::vector<std::pair<int, int>> D = decode(S);
  int M = D.size();

  printf("%d\n%d\n", L, M);
  for (int i = 0; i < M; i++)
    printf("%d %d\n", D[i].first, D[i].second);
}

} // namespace

int main() {
  int T;
  assert(1 == scanf("%d", &T));
  for (int i = 1; i <= T; i++)
    run_scenario();

  return 0;
}
