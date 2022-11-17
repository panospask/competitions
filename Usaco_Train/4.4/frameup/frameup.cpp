/*
ID: panos.p1
LANG: C++11
TASK: frameup
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXH 30
#define MAXW 30
#define MAXC 26

using namespace std;

typedef pair<int, int> ii;

char image[MAXH][MAXW];
int h, w;
unordered_map<char, ii> minsquare;
unordered_map<char, ii> maxsquare;
unordered_map<char, int> maxspot;
unordered_map<char, int> minspot;
set<char> allcs;
unordered_map<char, vector<char>> place_before;
unordered_map<char, bool> placed;
string curplaced;
set<string> answers;

int cmpr[MAXC][MAXC];
bool found[MAXC];

int compare_frames(char a, char b)
{
    return cmpr[a - 'A'][b - 'A'];
}

bool can_place(char a)
{
    for (auto c : place_before[a])
        if (!placed[c])
            return false;
    return true;
}

void place_letter(void)
{
    if (curplaced.size() == allcs.size()) {
        string ptr = curplaced;
        reverse(ptr.begin(), ptr.end());
        answers.insert(ptr);
        return;
    }

    for (auto let : allcs) {
        if (!placed[let] && can_place(let)) {
            placed[let] = true;
            curplaced.pb(let);
            place_letter();
            placed[let] = false;
            curplaced.pop_back();
        }
    }
}

int main(void)
{
    freopen("frameup.in", "r", stdin);
    freopen("frameup.out", "w", stdout);

    scanf("%d %d", &h, &w);
    char c;
    for (int i = 0; i < h; i++) {
        getchar();
        for (int j = 0; j < w; j++) {
            c = getchar();
            image[i][j] = c;

            if (c != '.') {
                if (!found[c - 'A']) {
                    found[c - 'A'] = true;
                    minsquare[c] = mp(i, j);
                    maxsquare[c] = mp(i, j);
                    allcs.insert(c);
                }
                else {
                    minsquare[c].first = min(minsquare[c].first, i);
                    minsquare[c].second = min(minsquare[c].second, j);
                    maxsquare[c].first = max(maxsquare[c].first, i);
                    maxsquare[c].second = max(maxsquare[c].second, j);
                }
            }
        }
    }


    ii topleft, botright;
    for (auto letter : allcs) {
        topleft = minsquare[letter];
        botright = maxsquare[letter];

        // Walk through the perimeter(right -> down -> left -> up)
        int i = topleft.first, j = topleft.second;
        
        char cur;
        while (j <= botright.second) {
            cur = image[i][j];
            if (cur != letter) {
                cmpr[cur - 'A'][letter - 'A'] = 1;
                cmpr[letter - 'A'][cur - 'A'] = -1;
                place_before[letter].pb(cur);
            }
            j++;
        }
        j--;
        while (i <= botright.first) {
            cur = image[i][j];
            if (cur != letter) {
                cmpr[cur - 'A'][letter - 'A'] = 1;
                cmpr[letter - 'A'][cur - 'A'] = -1;
                place_before[letter].pb(cur);
            }
            i++;
        }
        i--;
        while (j >= topleft.second) {
            cur = image[i][j];
            if (cur != letter) {
                cmpr[cur - 'A'][letter - 'A'] = 1;
                cmpr[letter - 'A'][cur - 'A'] = -1;
                place_before[letter].pb(cur);
            }
            j--;
        }
        j++;
        while (i >= topleft.first) {
            cur = image[i][j];
            if (cur != letter) {
                cmpr[cur - 'A'][letter - 'A'] = 1;
                cmpr[letter - 'A'][cur - 'A'] = -1;
                place_before[letter].pb(cur);
            }
            i--;
        }
        i++;

        maxspot[letter] = 1;
        minspot[letter] = allcs.size();
    }


    place_letter();
    for (auto ans : answers)
        cout << ans << '\n';
    return 0;
}