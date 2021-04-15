#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 10000000;
 
int n,q;
int a[100005];
int lp[MAXN+5];
int dp[MAXN+5];
 
signed main(){
    cin >> n >> q;
    for(int i = 0; i < n; i ++){
        cin >> a[i];
    }
    sort(a,a+n);
    for(int i = n-1; i >= 0; i --){
        if(lp[a[i]]) continue;
        for(int j = 0; j <= 10000000; j += a[i]){
            if(!lp[j]) lp[j] = a[i];
        }
    }
    int ptr = 0;
    dp[0] = 0;
    deque<int> dq;
    dq.push_back(0);
    // cout << "gg\n";
    for(int i = 1; i <= MAXN; i ++){
        while(ptr+lp[ptr] <= i) ptr++;
        // cout << i << " " << ptr << endl;
        while((!dq.empty()) and dq.front() < ptr) dq.pop_front();
        if(dq.empty()) dp[i] = MAXN*100;
        else dp[i] = 1+dp[dq.front()];
        
        while((!dq.empty()) and dp[dq.back()] > dp[i]){
            dq.pop_back();
            // cout << i << " ";
        }
        dq.push_back(i);
    }
    for(int i = 0; i < q; i ++){
        int x; cin >> x;
        if(dp[x] <= MAXN) cout << dp[x] << "\n";
        else cout << "oo\n";
    }
}