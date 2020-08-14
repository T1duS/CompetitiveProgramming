/*
Soln:
https://github.com/stefdasca/CompetitiveProgramming/blob/master/POI/POI%2014-Supercomputer.cpp
Used li chao tree instead of CHT
*/
#pragma GCC optimize("Ofast,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define pb push_back
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
 
const int MAXN = 1000005;
const int K = 1000000;
 
int n,m;
int a[MAXN];
int par[MAXN],dep[MAXN],suf[MAXN];
vi adj[MAXN];
int mxd;

void dfs(int u,int d){
	remax(mxd,d);
	dep[d] ++;
	for(auto v:adj[u]) dfs(v,d+1);
}

int f(pii line,int x){
	return line.F*x+line.S;
}

pii seg[4*K];

void upd(int ind,int l,int r,pii line){
	int mid = (l+r)/2;
	bool chm = (f(line,mid) > f(seg[ind],mid));
	bool chr = (f(line,r) > f(seg[ind],r));
	if(chm) swap(seg[ind],line);
	if(l == r) return;

	if(chm == chr) upd(2*ind,l,mid,line);
	else upd(2*ind+1,mid+1,r,line);
}

int quer(int ind,int l,int r,int x){
	int mid = (l+r)/2;
	if(l == r) return f(seg[ind],x);
	if(x <= mid) return max(f(seg[ind],x),quer(2*ind,l,mid,x));
	else return max(f(seg[ind],x),quer(2*ind+1,mid+1,r,x));
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    FOR(i,1,m+1) cin >> a[i];
    FOR(i,2,n+1){
    	cin >> par[i];
    	adj[par[i]].pb(i);
    }
    dfs(1,0);
    FORD(i,mxd+1,0){
    	suf[i] = dep[i]+suf[i+1];
    	upd(1,0,K,{i,suf[i]});
    }
    FOR(i,1,m+1){
    	int ans = quer(1,0,K,a[i]);
    	ans = (ans+a[i]-1)/a[i];
    	cout << ans << " ";
    }
    cout << "\n";
}
