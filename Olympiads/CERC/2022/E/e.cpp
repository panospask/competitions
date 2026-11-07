//Trumling ©
//Αφόδευε υψηλά και ηγνάντει 
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

int main()
{
ios_base::sync_with_stdio(0);
cin.tie(0);
ll n;
cin>>n;


ld arr[n];
for(int i = 0 ; i < n; i++)
    cin>>arr[i];

int pos = 0;
for (int i = 0; i < n; i++) {
    if (arr[i] < arr[pos]) {
        pos = i;
    }
}
// Play the smaller one
swap(arr[pos], arr[0]);

ld coef[n];
coef[0] = 1;

for(int i = 1 ; i < n; i++)
    coef[i] = arr[i]/arr[0];


vector<int>x(n);
for(int i = 1; i <= 10000; i++)
{
    ll sum = 0;
    x[0] = i;
    sum += i*i;


    for(int j = 1; j < n; j++)
    {
       // if(i==5)
      //      cout<<((((ll)i*coef[j])) * (((ll)i*coef[j])))<<'-';
        x[j] = round((i*coef[j]));
        sum += x[j] * x[j];

        // if(i==5)
        //  cout<<x[j]<<'-';
    
    }
    ld sqsum = sqrt((ld)sum);
        

    bool tf = 1;
    for(int j = 0; j < n; j++)
        {
            if(abs( (x[j]) / sqsum   -  arr[j] ) > 0.000001)
            {
                tf = 0 ;
               break;
            }
        }
    if(tf)
    {
        swap(x[pos], x[0]);
        for(int j = 0; j < n; j++)
            cout<<x[j]<<'\n';

        break;
    }
    
}

}