/*
ID: panos.p1
LANG: C++11
TASK: packrec
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(i, n) (i & (1 << (n-1)))

#define MAXL 50

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> ansstruct;

int minans = INT_MAX;
set<ii> coords;

struct rect {
    int x_side;
    int y_side;

    void read_rect(void) {
        scanf("%d %d", &this->x_side, &this->y_side);
    }

    void rotate_rect(void) {
        swap(x_side, y_side);
    }
};
typedef struct rect Rect;

int subcase2(Rect first, Rect a, Rect b, Rect c);
int subcase3(Rect down1, Rect down2, Rect up1, Rect up2);
int subcase4(Rect down, Rect up, Rect side1, Rect side2);
int subcase5(Rect down1, Rect down2, Rect up1, Rect up2);

void enter_ans(int a, int b)
{
    if (a * b < minans) {
        minans = a * b;
        coords.clear();
        coords.insert(mp(min(a, b), max(a, b)));
    }
    else if (a * b == minans) {
        coords.insert(mp(min(a, b), max(a, b)));
    }
}

int case1(Rect a, Rect b, Rect c, Rect d) 
{
    int width = a.x_side + b.x_side + c.x_side + d.x_side;
    int heigth = max(a.y_side, max(b.y_side, max(c.y_side, d.y_side)));

    enter_ans(width, heigth);
    return width * heigth;
}

int case2(Rect a, Rect b, Rect c, Rect d)
{
    // Try every possible case 2 combination

    int ans = subcase2(a, b, c, d);
    ans = min(ans, subcase2(b, a, c, d));
    ans = min(ans, subcase2(c, a, b, d));
    ans = min(ans, subcase2(d, a, b, c));

    return ans;
}

int subcase2(Rect down, Rect a, Rect b, Rect c)
{
    int width = max(down.x_side, a.x_side + b.x_side + c.x_side);
    int heigth = down.y_side + max(a.y_side, max(b.y_side, c.y_side));

    enter_ans(width, heigth);
    return width * heigth;
}

int case3(Rect a, Rect b, Rect c, Rect d)
{
    // Try every possible case 3 combination

    // For a as main base
    int ans = subcase3(a, b, c, d);
    ans = min(ans, subcase3(a, c, b, d));
    ans = min(ans, subcase3(a, d, b, c));
    
    // For b as main base
    ans = min(ans, subcase3(b, a, c, d));
    ans = min(ans, subcase3(b, c, a, d));
    ans = min(ans, subcase3(b, d, a, c));

    // For c as main base
    ans = min(ans, subcase3(c, a, b, d));
    ans = min(ans, subcase3(c, b, a, d));
    ans = min(ans, subcase3(c, d, a, b));

    // For d as main base
    ans = min(ans, subcase3(d, a, b, c));
    ans = min(ans, subcase3(d, b, a, c));
    ans = min(ans, subcase3(d, c, a, b));

    return ans; 
}

int subcase3(Rect down1, Rect down2, Rect up1, Rect up2)
{
    int width = max(down1.x_side, up1.x_side + up2.x_side) + down2.x_side;
    if (down1.y_side >= down2.y_side) {
        width = down1.x_side + down2.x_side;
        if (up1.x_side + up2.x_side > width)
            width = up1.x_side + up2.x_side;
    }
    int height = max(down2.y_side, down1.y_side + max(up1.y_side, up2.y_side));

    enter_ans(width, height);
    return width * height;
}

int case4(Rect a, Rect b, Rect c, Rect d)
{
    // Try every possible case 4 combination

    // For a as main base
    int ans = subcase4(a, b, c, d);
    ans = min(ans, subcase4(a, c, b, d));
    ans = min(ans, subcase4(a, d, b, c));
    
    // For b as main base
    ans = min(ans, subcase4(b, a, c, d));
    ans = min(ans, subcase4(b, c, a, d));
    ans = min(ans, subcase4(b, d, a, c));

    // For c as main base
    ans = min(ans, subcase4(c, a, b, d));
    ans = min(ans, subcase4(c, b, a, d));
    ans = min(ans, subcase4(c, d, a, b));

    // For d as main base
    ans = min(ans, subcase4(d, a, b, c));
    ans = min(ans, subcase4(d, b, a, c));
    ans = min(ans, subcase4(d, c, a, b));

    return ans; 
}

int subcase4(Rect down, Rect up, Rect side1, Rect side2)
{
    int width = max(down.x_side, up.x_side) + side1.x_side + side2.x_side;
    int heigth = max(down.y_side + up.y_side, max(side1.y_side, side2.y_side));

    enter_ans(width, heigth);
    return width * heigth;
}

int case5(Rect a, Rect b, Rect c, Rect d)
{
    // Try every possible case 5 combination

    // For a as main base
    int ans = subcase5(a, b, c, d);
    ans = min(ans, subcase5(a, c, b, d));
    ans = min(ans, subcase5(a, d, b, c));
    
    // For b as main base
    ans = min(ans, subcase5(b, a, c, d));
    ans = min(ans, subcase5(b, c, a, d));
    ans = min(ans, subcase5(b, d, a, c));

    // For c as main base
    ans = min(ans, subcase5(c, a, b, d));
    ans = min(ans, subcase5(c, b, a, d));
    ans = min(ans, subcase5(c, d, a, b));

    // For d as main base
    ans = min(ans, subcase5(d, a, b, c));
    ans = min(ans, subcase5(d, b, a, c));
    ans = min(ans, subcase5(d, c, a, b));

    return ans;
}

int subcase5(Rect down1, Rect down2, Rect up1, Rect up2)
{
    int width = max(down1.x_side + down2.x_side, up1.x_side + up2.x_side);
    if (down1.y_side > down2.y_side) {
        width = max(width, down1.x_side + up2.x_side);
        if (down1.y_side - down2.y_side < up2.y_side) 
            width = max(width, up1.x_side + up2.x_side);
    }
    else {
        width = max(width, down2.x_side + up1.x_side);
        if (down2.y_side - down1.y_side < up1.y_side)
            width = max(width, up1.x_side + up2.x_side);
    }

    int heigth = max(down1.y_side + up1.y_side, down2.y_side + up2.y_side);

    enter_ans(width, heigth);
    return width * heigth;
}

void test_cases(Rect a, Rect b, Rect c, Rect d)
{
    case1(a, b, c, d);
    case2(a, b, c, d);
    case3(a, b, c, d);
    case4(a, b, c, d);
    case5(a, b, c, d);
}

int main(void)
{
    freopen("packrec.in", "r", stdin);
    freopen("packrec.out", "w", stdout);

    Rect a, b, c, d;
    a.read_rect();
    b.read_rect();
    c.read_rect();
    d.read_rect();

    for (int i = 0; i < 16; i++) {
        if (CHECK_BIT(i, 1))
            a.rotate_rect();
        if (CHECK_BIT(i, 2))
            b.rotate_rect();
        if (CHECK_BIT(i, 3))
            c.rotate_rect();
        if (CHECK_BIT(i, 4))
            d.rotate_rect();
        test_cases(a, b, c, d);
        if (CHECK_BIT(i, 1))
            a.rotate_rect();
        if (CHECK_BIT(i, 2))
            b.rotate_rect();
        if (CHECK_BIT(i, 3))
            c.rotate_rect();
        if (CHECK_BIT(i, 4))
            d.rotate_rect();
    }

    printf("%d\n", minans);
    for (auto p : coords)
        printf("%d %d\n", p.first, p.second);
    
    return 0;
}