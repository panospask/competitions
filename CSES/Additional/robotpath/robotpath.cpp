#include <bits/stdc++.h>

using namespace std;

struct HorizontalPoint {
    int x, y;
    int id;
    bool is_end;
};

bool operator < (const HorizontalPoint& a, const HorizontalPoint& b)
{
    if (a.x == b.x) {
        return a.is_end < b.is_end;
    }

    return a.x < b.x;
}

struct VerticalSegment {
    int x;
    int y1, y2;

    int id;
};

bool operator < (const VerticalSegment& a, const VerticalSegment& b)
{
    return a.x < b.x;
}

int N;
vector<int> starts;

vector<HorizontalPoint> points;
vector<VerticalSegment> segments;

int main(void)
{
    scanf("%d", &N);

    int x = 0, y = 0;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        char dir;
        int dist;

        scanf(" %c %d", &dir, &dist);
        
    }
}