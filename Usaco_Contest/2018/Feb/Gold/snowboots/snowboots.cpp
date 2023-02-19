#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1e5
#define MAXB 100000

using namespace std;

typedef pair<int, int> ii;

// The continuous segments of tiles that have more than x snow on them
struct segment {
    int start;
    int end;
    
    int length(void) 
    {
        return end - start + 1;
    }
};
typedef struct segment Segment;

struct boot {
    int snow_tollerant;
    int jump_length;
    int original_pos;

    void read_boot(int op) {
        original_pos = op;
        scanf("%d %d", &snow_tollerant, &jump_length);
    }
};
typedef struct boot Boot;

Segment make_seg(int s, int e)
{
    Segment a;
    a.start = s;
    a.end = e;

    return a;
}

bool lengthsort(Segment a, Segment b) 
{
    if (a.length() == b.length())
        return a.start < b.start;
    return a.length() > b.length();
}

bool endsort(Segment a, Segment b)
{
    return a.end < b.end;
}

bool operator < (Boot a, Boot b)
{
    if (a.snow_tollerant == b.snow_tollerant)
        return a.original_pos < b.original_pos;
    return a.snow_tollerant < b.snow_tollerant;
}

int n, b;
set<Segment, decltype(lengthsort)*> by_length(lengthsort);
set<Segment, decltype(endsort)*> by_end(endsort);
vector<ii> tiles;
vector<Boot> boots;
bool can_pass[MAXB + 5];

void split_segment_at(Segment a, int pos)
{
    Segment b = make_seg(a.start, pos - 1);
    by_length.erase(a);
    by_end.erase(a);

    if (b.length() >= 0) {
        by_length.insert(b);
        by_end.insert(b);
    }
    Segment c = make_seg(pos + 1, a.end);
    if (c.length() >= 0) {
        by_length.insert(c);
        by_end.insert(c);
    }
}

int main(void)
{
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    scanf("%d %d", &n, &b);

    int snowval;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &snowval);
        tiles.pb(mp(snowval, i));
    }
    Boot curboot;
    for (int j = 0; j < b; j++) {
        curboot.read_boot(j);
        boots.pb(curboot);
    }
    sort(tiles.begin(), tiles.end());
    sort(boots.begin(), boots.end());

    int curtile = 0;
    Segment initial = make_seg(1, n);
    by_length.insert(initial);
    by_end.insert(initial);
    int prevtol = -1;
    for (auto& curboot : boots) {
        // if (curboot.original_pos == 0)
            // cerr << "here";
    
        if (curboot.snow_tollerant > prevtol) {
            // Must update the segments with the new snow tolerance
            bool still_lower = true;
            while (curtile < n) {
                if (tiles[curtile].first <= curboot.snow_tollerant) {
                    // Add the current tile --> Split the segment
                    Segment to_rm = *(by_end.lower_bound(make_seg(0, tiles[curtile].second)));
                    split_segment_at(to_rm, tiles[curtile].second);
                    curtile++;
                }
                else 
                    break;
            }

            prevtol = curboot.snow_tollerant;
        }

        Segment longest_seg = *(by_length.begin());
        if (curboot.jump_length > longest_seg.length())
            can_pass[curboot.original_pos] = true;
        else
            can_pass[curboot.original_pos] = false;
    }

    for (int i = 0; i < b; i++)
        printf("%d\n", can_pass[i]);
    return 0;
}