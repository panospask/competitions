#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N;
vector<pi> movies;

int main(void)
{
    scanf("%d", &N);

    movies.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &movies[i].second, &movies[i].first);
    }
    sort(movies.begin(), movies.end());

    int watched = 0;
    int time = 0;
    for (int i = 0; i < N; i++) {
        if (time <= movies[i].second) {
            watched++;
            time = movies[i].first;
        }
    }

    printf("%d\n", watched);

    return 0;
}