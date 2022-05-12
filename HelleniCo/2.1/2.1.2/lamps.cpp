#include <bits/stdc++.h>

using namespace std;

int size;

void swap(int& i)
{
    if (i == 1)
        i = 0;
    else 
        i = 1;
}

int compare_ints(int* a, int* b)
{
    for (int i = 0; i < size; i++) {
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i]) {
            return 0;
        }
    }

    return 0;

}

bool test(int lamps[], int test, bool cond)
{
    if (test == -1)
        return true;
    
    if (lamps[--test] == cond)
        return true;
    
    return false;
}

void test_case(int n, bool l1, bool l2, bool l3, bool l4, int on1, int on2, int off1, int off2, list<int*>& accepted)
{
    int* lamps = (int*) malloc(sizeof(*lamps) * n);
    for (int i = 0; i < n; i++)
        lamps[i] = 1;

    if (l1) {
        for (int i = 0; i < n; i++)
            swap(lamps[i]);
    }
    if (l2) {
        for (int i = 0; i < n; i += 2)
            swap(lamps[i]);
    }
    if (l3) {
        for (int i = 1; i < n; i += 2)
            swap(lamps[i]);
    }
    if (l4) {
        for (int i = 0; i < n; i += 3)
            swap(lamps[i]);
    }

    if (test(lamps, off1, false))
        if (test(lamps, off2, false))
            if (test(lamps, on1, true))
                if (test(lamps, on2, true)) {
                    accepted.push_back(lamps);
                }
                    
}


int main(void)
{

    freopen("lamps.in", "r", stdin);
    freopen("lamps.out", "w", stdout);

    int n;
    int c;
    cin >> size >> c;
    n = size;
    int on = c % 4;

    list<int*> accepted;

    int on1 = -1, on2 = -1, off1 = -1, off2 = -1;
    cin >> on1;
    if (on1 != -1) {
        cin >> on2;
        if (on2 != -1) {
            int i;
            cin >> i;
        }
    }

    cin >> off1;
    if (off1 != 0)
        cin >> off2;
    
    if (c % 2 == 0) {
        test_case(n, false, false, false, false, on1, on2, off1, off2, accepted);
        test_case(n, true, true, false, false, on1, on2, off1, off2, accepted);
        test_case(n, true, false, true, false, on1, on2, off1, off2, accepted);
        test_case(n, true, false, false, true, on1, on2, off1, off2, accepted);
        test_case(n, false, true, true, false, on1, on2, off1, off2, accepted);
        test_case(n, false, true, false, true, on1, on2, off1, off2, accepted);
        test_case(n, false, false, true, true, on1, on2, off1, off2, accepted);
        if (c > 2)
            test_case(n, true, true, true, true, on1, on2, off1, off2, accepted);
    }
    else {
        test_case(n, true, false, false, false, on1, on2, off1, off2, accepted);
        test_case(n, false, true, false, false, on1, on2, off1, off2, accepted);
        test_case(n, false, false, true, false, on1, on2, off1, off2, accepted);
        test_case(n, false, false, false, true, on1, on2, off1, off2, accepted);
        if (c > 1) {
            test_case(n, true, true, true, false, on1, on2, off1, off2, accepted);
            test_case(n, true, true, false, true, on1, on2, off1, off2, accepted);
            test_case(n, true, false, true, true, on1, on2, off1, off2, accepted);
            test_case(n, false, true, true, true, on1, on2, off1, off2, accepted);
        }
    }


    accepted.sort(compare_ints);

    while (accepted.size() > 0) {
        int* array = accepted.back();
        for (int i = 0; i < n; i++)
            cout << array[i];
        cout << '\n';
        accepted.pop_back();
    }
}