#include<bits/stdc++.h>
#include "garden.h"
#include "gardenlib.h"
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define pb push_back

const int MX = 300005;
const int INF = 1e9+1;

int edge[MX][2];
pii nxt[MX][2];
vector<pii> rev[MX][2];
int dist[2][MX][2];
vector<int> gg0,gg1;
vector<pii> queries;
int ans[MX];
int cnt0[MX],cnt1[MX];

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]){
	P++;
	for(int i = 0; i < M; i ++){
		int u = R[i][0]+1;
		int v = R[i][1]+1;
		if(!edge[u][0]) edge[u][0] = v;
		else if(!edge[u][1]) edge[u][1] = v;
		swap(u,v);
		if(!edge[u][0]) edge[u][0] = v;
		else if(!edge[u][1]) edge[u][1] = v;
	}
	for(int i = 1; i <= N; i ++){
		if(!edge[i][1]) edge[i][1] = edge[i][0];

		if(edge[edge[i][0]][0] == i){
			nxt[i][1] = {edge[i][0],0};
		}
		else nxt[i][1] = {edge[i][0],1};

		if(edge[edge[i][1]][0] == i){
			nxt[i][0] = {edge[i][1],0};
		}
		else nxt[i][0] = {edge[i][1],1};
	}
	for(int i = 1; i <= N; i ++){
		rev[nxt[i][0].F][nxt[i][0].S].pb({i,0});
		rev[nxt[i][1].F][nxt[i][1].S].pb({i,1});

		dist[0][i][0] = INF;
		dist[0][i][1] = INF;
		dist[1][i][0] = INF;
		dist[1][i][1] = INF;
	}
	queue<pii> q;
	q.push({P,0});
	dist[0][P][0] = 0;
	while(!q.empty()){
		pii u = q.front();
		q.pop();
		for(auto v:rev[u.F][u.S]){
			if(dist[0][v.F][v.S] > 1+dist[0][u.F][u.S]){
				dist[0][v.F][v.S] = 1+dist[0][u.F][u.S];
				q.push(v);
			}
		}
	}
	dist[1][P][1] = 0;
	q.push({P,1});
	while(!q.empty()){
		pii u = q.front();
		q.pop();
		for(auto v:rev[u.F][u.S]){
			if(dist[1][v.F][v.S] > 1+dist[1][u.F][u.S]){
				dist[1][v.F][v.S] = 1+dist[1][u.F][u.S];
				q.push(v);
			}
		}
	}
	int cyc0 = 0,cyc1 = 0;
	pii cur = {P,0};
	while(cyc0 <= 2*N){
		cur = nxt[cur.F][cur.S];
		cyc0++;
		if(cur.F == P and cur.S == 0) break;
	}
	if(cyc0 > 2*N) cyc0 = INF;
	cur = {P,1};
	while(cyc1 <= 2*N){
		cur = nxt[cur.F][cur.S];
		cyc1++;
		if(cur.F == P and cur.S == 1) break;
	}
	if(cyc1 > 2*N) cyc1 = INF;

	for(int i = 1; i <= N; i ++){
		gg0.pb(dist[0][i][1]);
		gg1.pb(dist[1][i][1]);
	}
	sort(gg0.begin(),gg0.end());
	sort(gg1.begin(),gg1.end());
	for(int i = 0; i < Q; i ++){
		queries.pb({G[i],i});
	}
	sort(queries.begin(),queries.end());
	int cur0 = 0,cur1 = 0;
	for(int i = 0; i < Q; i ++){
		while(cur0 < N and gg0[cur0] <= queries[i].F){
			cnt0[gg0[cur0]%cyc0]++;
			cur0++;
		}
		while(cur1 < N and gg1[cur1] <= queries[i].F){
			cnt1[gg1[cur1]%cyc1]++;
			cur1++;
		}
		if(queries[i].F%cyc0 <= MX) ans[queries[i].S] += cnt0[queries[i].F%cyc0];
		if(queries[i].F%cyc1 <= MX) ans[queries[i].S] += cnt1[queries[i].F%cyc1];
	}
	for(int i = 0; i < Q; i ++) answer(ans[i]);
}


