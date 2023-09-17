#include "robot.h"
#include <vector>
#define pb push_back

using namespace std;

int DIRS = 4;

int WALL = -2;
int BLOCK = -1;
int EMPTY = 0;
int PATH = 1;
int MX = 14;

// If the parent of current node is neighbour i, it will be marked fresh[i - 1]
int fresh[4] = {2, 3, 4, 5};
int used[4] = {6, 7, 8, 9};
int ending[4] = {10, 11, 12, 13};
char dir[4] = {'W', 'S', 'E', 'N'};

vector<int> s;

int par, pathtile, endtile;
vector<int> avail;
// Fresh and used kids
vector<int> kids[2];

void precalc(void)
{
    avail.clear();
    kids[0].clear();
    kids[1].clear();
    par = 0;
    pathtile = -1;
    endtile = -1;

    for (int i = 0; i < 4; i++) {
        // Check if s[i] indicates that the kid has this as parent
        int p = (i + 2) % 4;
        if (s[i + 1] == fresh[p]) {
            kids[0].pb(i);
        }
        else if (s[i + 1] == used[p]) {
            kids[1].pb(i);
        }
        else if (s[0] == fresh[i] || s[0] == used[i] || s[0] == ending[i]) {
            par = i;
        }

        if (s[i + 1] == PATH)
            pathtile = i;
    }
}

bool isfresh(int v)
{
    for (int i = 0; i < DIRS; i++)
        if (fresh[i] == v)
            return true;

    return false;
}

bool startcell()
{
    return s[1] == WALL && s[4] == WALL;
}
bool endcell()
{
    return s[2] == WALL && s[3] == WALL;
}

bool explore_neighbours(bool m)
{
    if (kids[m].size()) {
        set_instruction(s, s[0], dir[kids[m].front()]);
        return true;
    }
    else {
        return false;
    }
}

void empty_cell()
{
    if (s[0] != EMPTY)
        return;

    if (startcell()) {
        set_instruction(s, fresh[0], 'H');

        return;
    }


    // Find the parent which is fresh
    for (int i = 0; i < DIRS; i++)
        if (isfresh(s[i + 1])) {
            // Mark the best path and go back

            if (endcell()) {
                set_instruction(s, PATH, dir[i]);
                return;
            }
            set_instruction(s, used[i], dir[i]);
            break;
        }
}

void invert_state()
{
    if (startcell()) {
        if (s[0] == fresh[0])
            set_instruction(s, used[0], 'H');
        else
            set_instruction(s, fresh[0], 'H');
        return;
    }

    if (s[0] == fresh[par])
        set_instruction(s, used[par], dir[par]);
    else
        set_instruction(s, fresh[par], dir[par]);
}

void kill_paths(bool b)
{
    for (int b = 0; b < 2; b++)
        for (auto k : kids[b]) {
            set_instruction(s, ending[par], dir[k]);
            return;
        }

    // Everything is killed
    if (startcell()) {
        set_instruction(s, PATH, 'T');
        return;
    }

    set_instruction(s, b ? PATH : EMPTY, dir[par]);
}

void traversed_cell()
{
    precalc();

    if (!startcell() && (s[par + 1] >= ending[0] || s[par + 1] == PATH)) {
        kill_paths(false);
        return;
    }

    if (pathtile != -1) {
        kill_paths(true);
        return;
    }

    if (explore_neighbours(!isfresh(s[0])))
        return;

    if (isfresh(s[0]) && kids[0].size() == 0) {
        // Find empty cells
        for (int i = 0; i < DIRS; i++)
            if (s[i + 1] == 0) {
                set_instruction(s, s[0], dir[i]);
                return;
            }
    }

    invert_state();
}

void program_pulibot()
{
    s.resize(5);

    for (s[0] = -2; s[0] < MX; s[0]++)
        for (s[1] = -2; s[1] < MX; s[1]++)
            for (s[2] = -2; s[2] < MX; s[2]++)
                for (s[3] = -2; s[3] < MX; s[3]++)
                    for (s[4] = -2; s[4] < MX; s[4]++) {
                        if (s[0] < 0)
                            continue;

                        if (s[0] == EMPTY) {
                            empty_cell();
                        }
                        else {
                            traversed_cell();
                        }
                    }
}
