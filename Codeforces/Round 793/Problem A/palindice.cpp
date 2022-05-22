#include <bits/stdc++.h>

using namespace std;

bool check_pal(char* c, int length)
{
    int i = 0;
    int j = length - 1;

    while (i <= j) {
        if (c[i] == '\0')
            i++;
        else if (c[j] == '\0')
            j--;
        else {
            if (c[i] != c[j])
                return false;
        
            i++;
            j--;
        }
    }

    return true;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d ", &n);
        char s[n];
        for (int i = 0; i < n; i++) 
            scanf("%c", &s[i]);

        int count = 0;
        for (int i = 0; i < n; i++) {
            char temp = s[i];
            s[i] = '\0';
            count += check_pal(s, n);
            s[i] = temp;
        }

        printf("%d\n", count);
    }

    return 0;
}