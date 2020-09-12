#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pii pair<int,int>
#define F first
#define S second

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;

const int MX = 200005;

int n,q;

pair<pii,pii> a[MX],quer[MX];
int ans[MX];

indexed_set seg[2*MX];

int SZ = 0;

void upd(int pos,int val){
    pos += SZ;
    while(pos){
        seg[pos].insert(val);
        pos /= 2;
    }
}

int query(int l,int val){
    l += SZ;
    int r = 2*SZ;
    int res = 0;
    while(l < r){
        if(l%2){
            res += seg[l].size()-seg[l].order_of_key(val);
            l++;
        }
        if(r%2){
            --r;
            res += seg[r].size()-seg[r].order_of_key(val);
        }
        l /= 2;
        r /= 2;
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    
    set<int> s;
    map<int,int> m;

    REP(i,n){
        cin >> a[i].S.F >> a[i].S.S;
        a[i].F.F = a[i].S.F+a[i].S.S;
        a[i].F.S = i;
        s.insert(a[i].S.F);
    }
    sort(a,a+n);
    REP(i,q){
        cin >> quer[i].S.F >> quer[i].S.S >> quer[i].F.F;
        quer[i].F.F = max(quer[i].F.F,quer[i].S.F+quer[i].S.S);
        s.insert(quer[i].S.F);
        quer[i].F.S = i;
    }
    sort(quer,quer+q);
    
    for(auto x:s){
        m[x] = SZ++;
    }
    REP(i,n) a[i].S.F = m[a[i].S.F];
    REP(i,q) quer[i].S.F = m[quer[i].S.F];
    int ind = n-1;
    for(int i = q-1; i >= 0; i --){
        while(ind >= 0 and a[ind].F.F >= quer[i].F.F){
            upd(a[ind].S.F,a[ind].S.S);
            ind--;
        }
        ans[quer[i].F.S] = query(quer[i].S.F,quer[i].S.S);
    }
    REP(i,q) cout << ans[i] << "\n";
}