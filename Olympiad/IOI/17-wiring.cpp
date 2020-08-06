#include "wiring.h"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define all(v) v.begin(),v.end()

vector<pii> a;
int n;
int comp[200005];
pii range[200005];
ll dp[200005],pref[200005],suff[200005],gg1[200005],gg2[200005];
ll seg[2][400005];

const ll INF = 1e14;

void upd(int type,int ind,ll val){
	ind += n;
	while(ind){
		seg[type][ind] = min(seg[type][ind],val);
		ind /= 2;
	}
}

ll quer(int type,int l,int r){
	l += n;
	r += n;
	ll res = INF;
	while(l < r){
		if(l&1) res = min(res,seg[type][l++]);
		if(r&1) res = min(res,seg[type][--r]);
		l /= 2;
		r /= 2;
	}
	return res;
}

ll min_total_length(vi r, vi b) {
	for(auto x:r) a.pb({x,0});
	for(auto x:b) a.pb({x,1});
	sort(all(a));
	n = a.size();
	int last = 0,cmp = 0;
	FOR(i,1,n){
		if(a[i].S != a[last].S){
			range[cmp] = {last,i-1};
			last = i;
			cmp++;
		}
		comp[i] = cmp;
	}
	REP(i,2*n+5) seg[0][i] = seg[1][i] = INF;

	range[cmp] = {last,n-1};
	pref[0] = 0;
	FOR(i,1,n){
		if(comp[i] == comp[i-1]){
			pref[i] = pref[i-1]+(a[i].F-a[range[comp[i]].F].F);
		}
	}
	suff[n-1] = 0;
	for(int i = n-2; i >= 0; i--){
		if(comp[i] == comp[i+1]){
			suff[i] = suff[i+1]+(a[range[comp[i]].S].F-a[i].F);
		}
	}
	REP(i,n){
		if(comp[i]){
			int st = range[comp[i]].F;
			int l1 = range[comp[st-1]].F,r2 = range[comp[st-1]].S;
			ll diff = a[st].F-a[r2].F;
			dp[i] = INF;
			int r1 = max(2*st-i-1,l1-1);
			int l2 = r1+1;
			/*
			FOR(j,l1,r1+1){
				// pref[i]+suff[j]+diff*(st-j)+(j?min(dp[j-1],dp[j]):0)
				// [  pref[i]+diff*st  ]+[  suff[j]-diff*j+(j?min(dp[j-1],dp[j]):0)  ]
				// [  pref[i]+diff*st  ]+[  gg1[j]  ]
				dp[i] = min(dp[i],pref[i]+diff*st+gg1[j]);
			}
			FOR(j,l2,r2+1){
				// pref[i]+suff[j]+diff*(i-st+1)+(j?min(dp[j-1],dp[j]):0)
				// [  pref[i]+diff*(i-st+1)  ]+[  suff[j]+(j?min(dp[j-1],dp[j]):0)  ]
				// [  pref[i]+diff*(i-st+1)  ]+[  gg2[j]  ]
				dp[i] = min(dp[i],pref[i]+diff*(i-st+1)+gg2[j]);
			}
			*/
			dp[i] = min(pref[i]+diff*st+quer(0,l1,r1+1),pref[i]+diff*(i-st+1)+quer(1,l2,r2+1));
		}
		else dp[i] = INF;

		if(comp[i] == comp[n-1]) continue;
		ll diff2 = a[range[comp[i]+1].F].F-a[range[comp[i]].S].F;
		gg1[i] = suff[i]-diff2*i+(i?min(dp[i],dp[i-1]):0);
		gg2[i] = suff[i]+(i?min(dp[i],dp[i-1]):0);
		upd(0,i,gg1[i]);
		upd(1,i,gg2[i]);
	}
	return dp[n-1];
}
