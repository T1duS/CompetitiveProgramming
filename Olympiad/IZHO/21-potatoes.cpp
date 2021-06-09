#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define REP(i,n) for(int  i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
#define vi vector<int>
#define pb push_back
#define remin(a,b) a = min(a,b)
#define pii pair<int,int>
#define F first
#define S second
#define mii unordered_map<int,int>
#define remax(a,b) a = max(a,b)
#define vpii vector<pii>

const int MX = 200005;

ll x,y;
int n,q; 
int a[MX];
vpii queries[MX];
int seg[2*MX];
int last[MX][21];
int gg[21][MX];
int ans[MX];

void upd(int l,int r){
    l += n-1;
    r += n;
    while(l < r){
        if(l%2) seg[l++] ++;
        if(r%2) seg[--r] ++;
        l /= 2;
        r /= 2;
    }
}

int query(int pos){
    pos += n-1;
    int res = 0;
    while(pos){
        res += seg[pos];
        pos /= 2;
    }
    return res;
}

void comp(vpii v,int p,int md){
    if(v.size() == 1) return;
    REP(i,v.size()-1){
        if(v[i].F == v[i+1].F){
            last[v[i+1].S][p] = v[i].S;
        }
    }
    vpii v1,v2;
    REP(i,v.size()){
        if(v[i].S%(1<<(p+1)) == md) v1.pb(v[i]);
        else v2.pb(v[i]);
    }
    comp(v1,p+1,md);
    comp(v2,p+1,md+(1<<p));
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> x >> y;
    vpii bruh;
    FOR(i,1,n+1){
        cin >> a[i];
        bruh.pb({a[i],i});
    }
    sort(bruh.begin(),bruh.end());
    comp(bruh,0,0);
    cin >> q;
    REP(i,q){
        int l,r; cin >> l >> r;
        queries[r].pb({l,i});
    }
    FOR(i,1,n+1){
        REP(j,18){
            int md = i%(1<<j);
            if(last[i][j] > gg[j][md]){
                upd(gg[j][md]+1,last[i][j]);
                gg[j][md] = last[i][j];
            }
        }
        for(auto x:queries[i]){
            ans[x.S] = query(x.F);
        }
    }
    REP(i,q) cout << x*(ans[i]+1)+y*ans[i] << "\n";
}