#include<bits/stdc++.h>
using namespace std;

#define int long long
#define REP(i,n) for(int  i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
#define vi vector<int>
#define pb push_back
#define remin(a,b) a = min(a,b)
#define pii pair<int,int>
#define F first
#define S second

const int MX = 1000005;
const int INF = (int)1e17;

int n,s,t;
int a[MX],dp[MX];
pii seg[2][4*MX];
int mn[MX];

int f(pii line,int x){
    return line.F*x+line.S;
}

void update(int idx,int node,int l,int r,pii line){
    int m = (l+r)/2;
    bool lef = f(line,l) < f(seg[idx][node],l);
    bool mid = f(line,m) < f(seg[idx][node],m);
    if(mid) swap(line,seg[idx][node]);
    if(l+1 == r) return;
    if(lef != mid) update(idx,2*node,l,m,line);
    else update(idx,2*node+1,m,r,line);
}

int query(int idx,int node,int l,int r,int x){
    int m  = (l+r)/2;
    if(l+1 == r) return f(seg[idx][node],x);
    if(x < m) return min(f(seg[idx][node],x),query(idx,2*node,l,m,x));
    else return min(f(seg[idx][node],x),query(idx,2*node+1,m,r,x));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s >> t;
    REP(i,4*n+1) REP(j,2) seg[j][i] = {0,INF};
    if(s == t){
        cout << "0\n";
        return 0;
    }
    FOR(i,1,n+1){
        cin >> a[i];
    }
    if(s > t){
        FOR(i,1,n+1){
            if(i < n+1-i){
                swap(a[i],a[n+1-i]);
            }
        }
        s = n+1-s;
        t = n+1-t;
    }
    mn[s] = a[s];
    FOR(i,s+1,n+1) mn[i] = min(mn[i-1],a[i]);
    FORD(i,s-1,1) mn[i] = min(mn[i+1],a[i]);
    vector<pii> gg;
    FOR(i,1,n+1) gg.pb({a[i],i});
    sort(gg.begin(),gg.end());
    REP(i,n+1) dp[i] = INF;
    dp[s] = 0;
    int p1 = s,p2 = s;
    FORD(i,n-1,0){
        if(gg[i].F >= a[s]) continue;
        int ind = gg[i].S;
        if(ind < s){
            if(mn[ind+1] <= a[ind]) continue;
            remin(dp[ind],dp[p1]+a[p1]*(p1-ind));
            remin(dp[ind],query(0,1,1,n+1,ind));
            p1 = ind;
            update(1,1,1,n+1,{a[ind],dp[ind]-ind*a[ind]});
        }
        else{
            if(mn[ind-1] <= a[ind]) continue;  
            remin(dp[ind],dp[p2]+a[p2]*(ind-p2));
            remin(dp[ind],query(1,1,1,n+1,ind));
            p2 = ind;
            update(0,1,1,n+1,{-a[ind],dp[ind]+ind*a[ind]});
        }
        // cout << ind << " " << a[ind] << " " << dp[ind] << "\n";
    }
    int ans = INF;
    FOR(i,1,n+1){
        remin(ans,dp[i]+a[i]*abs(t-i));
    }
    cout << ans << "\n";
}