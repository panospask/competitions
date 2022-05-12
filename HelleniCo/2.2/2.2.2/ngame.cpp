#include <bits/stdc++.h>  
  
using namespace std;  
  
int recursion_with_memoization(int array[], int start, int end, int** checked, int sum)  
{  
    if (start == end)  
        return array[start];  
  
    if (checked[start][end] != 0)  
        return checked[start][end];  
  
  
    checked[start + 1][end] = recursion_with_memoization(array, start + 1, end, checked, sum - array[start]);  
    checked[start][end - 1] = recursion_with_memoization(array, start, end - 1, checked, sum - array[end]);  
    int remove_front = checked[start + 1][end];  
    int remove_back = checked[start][end - 1];  
  
    if (sum - checked[start + 1][end] > sum - checked[start][end - 1]) {  
        return sum - checked[start + 1][end];  
    }  
    else {  
        return sum - checked[start][end - 1];  
    }  
}  
  
int main(void)  
{  
    freopen("ngame.in", "r", stdin);  
    freopen("ngame.out", "w", stdout);  
  
    int n;  
    cin >> n;  
    int array[n];  
    int** checked = (int**) malloc(sizeof(int*) * n);  
    for (int i = 0; i < n; i++) {  
        checked[i] = (int*) malloc(sizeof(int) * n);  
        for  (int j = 0; j < n; j++)  
            checked[i][j] = 0;  
    }  
  
    int sum = 0;  
    for (int i = 0; i < n; i++) {  
        cin >> array[i];  
        sum += array[i];  
    }  
  
    int first = recursion_with_memoization(array, 0, n - 1, checked, sum);  
  
    cout << first << ' '<< sum - first << endl;  
} 