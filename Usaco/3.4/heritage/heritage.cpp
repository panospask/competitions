/*
ID: panos.p1
LANG: C++11
TASK: heritage
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

string inorder;
string preorder;
string postorder;

int create_post(int prenum, int innum_from, int innum_cur ,int innum_to)
{
    int curmax = prenum;
    int t_prenum = prenum;
    char next = preorder[curmax + 1];
    for (int i = innum_from; i < innum_cur; i++)
        if (inorder[i] == next) {
            curmax = create_post(curmax + 1, innum_from, i, innum_cur - 1);
            break;
        }
    next = preorder[curmax + 1];
    for (int i = innum_cur + 1; i <= innum_to; i++)
        if (inorder[i] == next) {
            curmax = max(curmax, create_post(curmax + 1, innum_cur + 1, i, innum_to));
        }

    postorder.pb(preorder[t_prenum]);
    return curmax;
}

int main(void)
{
    freopen("heritage.in", "r", stdin);
    freopen("heritage.out", "w", stdout);

    cin >> inorder;
    cin >> preorder;
    postorder.clear();

    char c = preorder[0];
    int cur = -1;
    for (int i = 0; i < preorder.size(); i++)
        if (inorder[i] == c) {
            cur = i;
            break;
        }

    create_post(0, 0, cur, preorder.size() -1);
    cout << postorder << '\n';
    return 0;
}