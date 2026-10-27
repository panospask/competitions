#include <bits/stdc++.h>
using namespace std; 
 
typedef long long ll;
typedef long double ld;
#define pb push_back
#define F first
#define S second
#define enter cout<<'\n';
#define INF 99999999999999
#define MOD 1000000007
#define all(x) x.begin(),x.end()

using namespace std;

typedef pair<int, int> pi;

const int DEGREES = 360;
const int RADIUS = 20;

// vertical walls by theta
vector<pi> verticals;

// circular walls by radius
vector<pi> circular;

ll n;
vector<vector<int>> grid;
vector<vector<bool>> dir[4];

// DEGREE THETA + 0.5 --> POS THETA
// RADIUS R + 0.5 --> POS R

int dx[4] ={ 1 , - 1 , 0 , 0};
int dy[4] = { 0 , 0 , 1 , -1};


void floodfill(int r , int th)
{
	grid[r][th] = true;
    for(int i = 0 ; i < 4 ; i++)
        if(dir[i][r][th] && !grid[r + dx[i]][(th + dy[i] + DEGREES) % DEGREES])
            floodfill(r + dx[i] , (th + dy[i] + DEGREES) % DEGREES);
         
}

void solve(void) {
    cin>>n;
    
	for (int d = 0 ;d < 4; d++) {
		dir[d].assign(RADIUS + 1, vector<bool>(DEGREES, 1));
	}
    grid.assign(RADIUS + 1 , vector<int>(DEGREES, 0));
	for (int t = 0; t < DEGREES; t++) {
		dir[0][RADIUS][t] = false;
		dir[1][0][t] = false;
	}

    for(int i = 0 ; i < n ; i++)
    {
        char a;
        cin>>a;

        if(a == 'C')
        {
            int r, th1 , th2;

            cin>>r>>th1>>th2;
            
			// From r - 0.5 (pos r - 1) to r + 0.5 (pos r )
			
			// From th1 + 0.5(pos th1) to th2 - 0.5(pos th2 - 1)
			for (int t = th1; t != th2; t = (t + 1) % (DEGREES)) {
				dir[0][r - 1][t] = false;
				dir[1][r][t] = false;
			}
        }
        else
        {
            int r1, r2 , th;
            cin>>r1>>r2>>th;

			int t1 = (th - 1 + DEGREES) % DEGREES;
			int t2 = th;

			for (int r = r1; r != r2; r++) {
				dir[2][r][t1] = false;
				dir[3][r][t2] = false;
			}
        }
    }

    grid[0][0] = true;
	floodfill(0, 0);

	if (grid[RADIUS][0]) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}

