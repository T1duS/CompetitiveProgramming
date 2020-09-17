#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define all(v) v.begin(),v.end()
 
const int MX = 1505;
const ll INF = 1e16;
 
int n,m,k;
vvi a;
int plow[MX],phigh[MX];
ll val[MX][MX];
ll pref[MX][MX];
 
ll find_maximum(int k, vvi x) {
	n = x.size();
	m = x[0].size();
	::k = k;
	vvi ans(n,vi(m,-1));
	a.resize(n);
	vector<pair<int,pii> > everything;
	ll res = 0;
	priority_queue<pair<ll,int> > pq;
	REP(i,n){
		pref[i][0] = 0;
		REP(j,m){
			a[i].pb(x[i][j]);
			pref[i][j+1] = a[i][j]+pref[i][j];
		}
		REP(j,k+1){
			val[i][j] = pref[i][m]-pref[i][m-(k-j)]-pref[i][j]; 
		}
		plow[i] = -1;
		phigh[i] = m-1; 
		res += val[i][0];
		pq.push({val[i][1]-val[i][0],i});
	}
	REP(i,(n*k)/2){
		pair<ll,int> bruh = pq.top();
		pq.pop();
		res += bruh.F;
		plow[bruh.S]++;
		if(plow[bruh.S] != k-1){
			pq.push({val[bruh.S][plow[bruh.S]+2]-val[bruh.S][plow[bruh.S]+1],bruh.S});
		}
	}
	REP(turn,k){
		vector<pii> v;
		REP(i,n){
			if(plow[i] >= 0){
				v.pb({-plow[i],i});
			}
			else v.pb({1,i});
		}
		sort(all(v));
		REP(i,n/2){
			int ind = v[i].S;
			ans[ind][plow[ind]] = turn;
			plow[ind]--;
		}
		FOR(i,n/2,n){
			int ind = v[i].S;
			ans[ind][phigh[ind]] = turn;
			phigh[ind]--;
		}
	}
	allocate_tickets(ans);
	return res;
}