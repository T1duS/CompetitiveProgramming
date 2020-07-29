/*
Soln:
http://blog.brucemerry.org.za/2014/07/ioi-2014-day-1-analysis.html
*/

#include "game.h"
#include <bits/stdc++.h>
using namespace std;

int adj[1505][1505];
int par[1505];
int N;

void initialize(int n) {
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			adj[i][j] = 1;
		}
		par[i] = i;
	}
	N = n;
}

int find(int u){
	if(par[u] == u) return u;
	return par[u] = find(par[u]);
}

void merge(int u,int v){
	for(int i = 0; i < N; i ++){
		adj[u][i] += adj[v][i];
		adj[i][u] = adj[u][i];
	}
	par[v] = u;
}

int hasEdge(int u, int v) {
	u = find(u);
	v = find(v);
    if(adj[u][v] == 1){
    	merge(u,v);
    	return 1;
    }
    adj[u][v]--;
    adj[v][u]--;
    return 0;
}