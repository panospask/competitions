#include <bits/stdc++.h>

using namespace std;

int n;
string s, t;

bool find_if_pos(int i)
{
    int c1 = s[i], c2 = t[i];
    if (c1 == 'a' && c2 == 'b') {
        bool can_go = true;
        for (int j = i + 1; j < n && can_go; j++) {
            if (s[j] == 'b') {
                swap(s[i], s[j]);
                return true;
            }
            else if (s[j] == 'c')
                return false;
        }
        return false;
    }
    else if (c1 == 'b' && c2 == 'c') {
        bool can_go = true;
        for (int j = i + 1; j < n && can_go; j++) {
            if (s[j] == 'c') {
                swap(s[i], s[j]);
                return true;
            }
            else if (s[j] == 'a')
                return false;
        }
        return false;
    }

    return false;
}

int main(void)
{
    int m;
    scanf("%d", &m);

    for (int x = 0; x < m; x++) {
        scanf("%d", &n);
        s.resize(n); t.resize(n);

        getchar();
        for (int i = 0; i < n; i++)
            s[i] = getchar();
        
        getchar();
        for (int i = 0; i < n; i++)
            t[i] = getchar();

        bool can_go = true;
        for (int i = 0; i < n && can_go; i++) {
            if (s[i] != t[i])
                can_go = find_if_pos(i);
        }

        if (can_go)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}