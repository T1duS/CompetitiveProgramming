/*
Soln:
Find dist from 0 to all points
Let the closest point be mn
Find dist from mn to all points

You can now distinguish whether a point lies to the left or right of mn by this equation
dist[0][i] == dist[0][mn]+dist[mn][i]
Solve for left and right parts individually

For left part for example, sort points by distance from mn
Assign them(x) D type and calculate location. location[smallest D]+dist(smallest D,x)
Now verify if they are actually D type. Find closest C point to the left to location[x]
using binary search.
If it was indeed D type, you have the following relation
location[x]-location[(closest C)] + dist(mn,closest) = dist(mn,x)

Using this you can calculate all answers 
*/

#include "rail.h"
#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define all(v) v.begin(),v.end()

#define TRACE
 
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

int dist[3][5005];

vector<pii> cees,dees;

void findLocation(int N, int first, int location[], int stype[]){
	FOR(i,1,N){
		dist[0][i] = getDistance(i,0);
	}
	int mn = 1;
	FOR(i,1,N){
		if(dist[0][mn] > dist[0][i]) mn = i;
	}
	FOR(i,1,N){
		if(i != mn) dist[1][i] = getDistance(mn,i);
	}
	
	location[0] = first;
	stype[0] = 1;
	location[mn] = first+dist[0][mn];
	stype[mn] = 2;

	vector<pii> lft,rgt;
	FOR(i,1,N){
		if(i != mn){
			// trace(i,dist[0][i],dist[1][i]);
			if(dist[0][i] == dist[0][mn]+dist[1][i]) lft.pb({dist[1][i],i});
			else rgt.pb({dist[0][i],i});
		}
	}
	sort(all(lft));
	sort(all(rgt));

	// trace(mn);

	int prevC = 0,prevD = mn;
	cees.pb({-first,0});
	dees.pb({location[mn],mn});
	for(auto x:lft){
		// trace(x.S);
		location[x.S] = location[prevC]+getDistance(prevC,x.S);
		stype[x.S] = 2;
		// trace(location[x.S]);
		int closest = cees[lower_bound(all(cees),make_pair(-location[x.S],-1))-cees.begin()].S;
		// trace(closest);
		if(location[x.S]-location[closest]+dist[1][closest] != dist[1][x.S]){
			location[x.S] = location[mn]-dist[1][x.S];
			stype[x.S] = 1;
			cees.pb({-location[x.S],x.S});
			prevC = x.S;
		}
		// trace(stype[x.S],location[x.S]);
	}
	for(auto x:rgt){
		location[x.S] = location[prevD]-getDistance(prevD,x.S);
		stype[x.S] = 1;
		int closest = dees[lower_bound(all(dees),make_pair(location[x.S],-1))-dees.begin()].S;
		if(location[closest]-location[x.S]+dist[0][closest] != dist[0][x.S]){
			location[x.S] = location[0]+dist[0][x.S];
			stype[x.S] = 2;
			dees.pb({location[x.S],x.S});
			prevD = x.S;
		}
	}
}
