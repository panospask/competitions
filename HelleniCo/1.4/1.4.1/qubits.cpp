#include <bits/stdc++.h>

using namespace std;

void move_n_from_to(int n, char from, char to)
{
    if (n == 1) {
        printf("%c %c\n", from, to);
        return;
    }

    char middle;
    if (from + to == 'A' + 'C')
        middle = 'B';
    else if (from + to == 'A' + 'B')
        middle = 'C';
    else 
        middle = 'A';

    move_n_from_to(n - 1, from, middle);
    
    printf("%c %c\n", from, to);

    move_n_from_to(n - 1, middle, to);
}


int main(void)
{
    freopen("qubits.in", "r", stdin);
    freopen("qubits.out", "w", stdout);

    int n;
    cin >> n;

    move_n_from_to(n, 'A', 'C');
}