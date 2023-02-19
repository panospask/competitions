#include <bits/stdc++.h>

using namespace std;

struct segment {
    int start;
    int end;
    int length;

    segment(int s, int e) {
        start = s;
        end = e;
        length = end - start;
    }
};
typedef struct segment Segment;

int n, x;

bool lengthsort(Segment a, Segment b)
{
    if (a.length == b.length)
        return a.end < b.end;

    return a.length < b.length;
}

bool endsort(Segment a, Segment b)
{
    return a.end < b.end;
}

int main(void)
{
    set<Segment, decltype(lengthsort)*> by_length(lengthsort);
    set<Segment, decltype(endsort)*> by_endpoint(endsort);


    scanf("%d %d", &x, &n);
    Segment starting(0, x);
    by_length.insert(starting);
    by_endpoint.insert(starting);

    for (int i = 0; i < n; i++) {
        int next_add;
        scanf("%d", &next_add);

        Segment to_remove = *(by_endpoint.upper_bound(Segment(0, next_add)));
        by_endpoint.erase(to_remove);
        by_length.erase(to_remove);
        

        Segment new1(to_remove.start, next_add), new2(next_add, to_remove.end);
        by_endpoint.insert(new1);
        by_endpoint.insert(new2);
        by_length.insert(new1);
        by_length.insert(new2);

        Segment longest = *by_length.rbegin();

        printf("%d ", longest.length);
    }

    printf("\n");
    return 0;
}