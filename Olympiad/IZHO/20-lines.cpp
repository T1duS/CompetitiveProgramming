#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)

const int MX = 1000005;

int n;
int a[MX],b[MX];
int seg[4*MX];

void update(int node,int l,int r,int pos,int val){
    if(pos < l or pos > r) return;
    if(l == r){
        seg[node] += val;
        return;
    }
    int mid = (l+r)/2;
    update(2*node,l,mid,pos,val);
    update(2*node+1,mid+1,r,pos,val);
    seg[node] = seg[node*2]+seg[node*2+1];
}

int query(int node,int l,int r,int ind){
    if(l == r) return l;
    int mid = (l+r)/2;
    if(seg[2*node] >= ind) return query(node*2,l,mid,ind);
    else return query(node*2+1,mid+1,r,ind-seg[2*node]);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    FOR(i,1,n+1) cin >> a[i];
    FOR(i,1,n+1){
        cin >> b[i];
        update(1,1,n,b[i],1);
    }
    int ans = 0;
    FOR(i,1,n+1){
        int bi = query(1,1,n,i);
        if(a[i] > bi){
            update(1,1,n,bi,-1);
            update(1,1,n,a[i],1);
            ans++;
        }
    }
    cout << ans << "\n";
}