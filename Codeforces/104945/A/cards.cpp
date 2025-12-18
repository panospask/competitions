#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define INF 99999999999
#define all(x) x.begin(),x.end()

int main()
{
    ll n;
    cin>>n;
    vector<vector<pair<ll,ll>>>v(5,vector<pair<ll,ll>>());
    for(int i=0;i<n;i++)
        {
            char a;
            int x;
            cin>>a>>x;
            if(a=='S')
                {
                    v[0].pb({x,i});
                    continue;
                }

            if(a=='W')
                {
                    v[1].pb({x,i});
                    continue;
                }
                
            if(a=='E')
                {
                    v[2].pb({x,i});
                    continue;
                }

            if(a=='R')
                {
                    v[3].pb({x,i});
                    continue;
                }

            if(a=='C')
                {
                    v[4].pb({x,i});
                    continue;
                }
        }

    vector<ll>temp;
    temp.pb(0);
    temp.pb(1);
    temp.pb(2);
    temp.pb(3);

    ll ans=n;
    
    do
    {

        vector<ll>arr(n);
        for(int i=0;i<4;i++)
            for(int j=0;j<v[temp[i]].size();j++)
                arr[v[temp[i]][j].S]= v[temp[i]][j].F + i*n;
        
        for(int i=0;i<v[4].size();i++)
            arr[v[4][i].S]= v[4][i].F + 4*n;
        
        vector<ll>lis;
        for(int i=0;i<n;i++)
            {
                ll pos=lower_bound(all(lis),arr[i]) - lis.begin();
                if(pos==lis.size())
                    lis.pb(arr[i]);
                else
                    lis[pos]=arr[i];
            }
        
        ans=min(ans,n - (ll)lis.size());

    } while (next_permutation(all(temp)));
    cout<<ans;
}