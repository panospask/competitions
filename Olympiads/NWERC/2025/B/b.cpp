#include<bits/stdc++.h>
using namespace std;

int coins[] = {1 , 2 , 5 , 10 , 20 , 50, 100 , 200, 500};

void fill_rest(vector<int> &v, int n) {
    int coinind = 8;
    while(n > 0){
        if(n < coins[coinind]){
            coinind--;
        }
        else {
            n -= coins[coinind];
            v.push_back(coins[coinind]);
        }
    }
}

void print_ans(vector<int> &v){
    cout << v.size() << endl;
    for(auto &x : v){
        cout << x << " ";
    }
    cout << endl;
}

bool no_good(int n){
    // true if I can't fix it
    while(n > 0) {
        int cur = n % 10;
        if(cur != 0 && cur != 4){
            return false;
        }
        n /= 10;
    }
    return true;
}

int main(){
    int n;
    cin >> n;

    vector<int> ans;


    if(n / 1000 == 1 && no_good(n % 1000)){
        //10xy or 14xy, all have an odd number of 200
        while(n >= 200){
            n -= 200;
            ans.push_back(200);
        }
        fill_rest(ans, n);
        print_ans(ans);
        return 0;
    }
    
    while(n >=1000){
        ans.push_back(500);
        ans.push_back(500);
        n-=1000;
    }
 
 
    int mult = 1;
    bool valid = false;
    while(n > 0 && mult <= 100){
        int dig = (n / mult)% 10;
        if(dig >= 5) {
            valid = true;
            while(n >= 5 * mult){
                ans.push_back(5 * mult);
                n -= 5 * mult;
            }
            break;
        }
        else if(dig % 2 == 1){
            //dig = 1 or 3
            valid = true;
            while(n >= mult){
                ans.push_back(mult);
                n -= mult;
            }
            break;
        }
        else if(dig == 2){
            valid = true;
            while(n >= 10 * mult){
                ans.push_back(10 * mult);
                n -= 10 * mult;
            }
            ans.push_back(2 * mult);
            n -= 2 * mult;
            break;
        }
        mult *= 10;
    }
 
    if(!valid){
        cout << "splittable" << endl;
        return 0;
    }
 
    fill_rest(ans, n);
 
    cout << ans.size() << endl;
 
    for(auto &x : ans) {
        cout << x << " ";
    }
    cout << endl;
}