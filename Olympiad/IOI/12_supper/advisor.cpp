#include<bits/stdc++.h>
using namespace std;
#include "advisor.h"

#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define all(v) v.begin(),v.end()

const int MAXN = 200005;

int ans[MAXN],last[MAXN];

vi gg[MAXN];

void ComputeAdvice(int *C, int N, int K, int M) {

	priority_queue<pii> pq;

	REP(i,K) gg[i].pb(i);
	REP(i,N){
		last[i] = -1;
		gg[C[i]].pb(i+K);
	}
	REP(i,N) gg[i].pb(N+K);
	REP(i,K){
		pq.push({*upper_bound(all(gg[i]),i),i});
		last[i] = i;
	}
	REP(i,N){
		if(last[C[i]] != -1) ans[last[C[i]]] = 1;
		else{
			int x = pq.top().S;
			pq.pop();
			last[x] = -1;
		}
		last[C[i]] = i+K;
		pq.push({*upper_bound(all(gg[C[i]]),i+K),C[i]});
	}

	REP(i,N+K) WriteAdvice(ans[i]);

}