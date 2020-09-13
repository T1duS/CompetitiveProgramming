#include "routers.h"
#include<bits/stdc++.h>
using namespace std;
 
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
 
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define remin(a,b) a = min(a,b)
#define remax(a,b) a = max(a,b)
 
vi find_routers(int l, int n, int q) {
    vi ans;
    vector<pii> quer;
    ans.pb(0);
    FOR(i,1,n){
    	int low = ans.back()+1,high = l-2*(n-1-i)+1,mid;
    	for(auto x:quer){
    		if(x.S < i-1) continue;
    		else if(x.S == i-1) remax(low,x.F+1);
    		else if(x.S >= i){
    			remin(high,x.F-2*(x.S-i));
    		}
    	}
    	while(low < high){
    		mid = (low+high)/2;
    		if(ans.back()+2*(mid-ans.back()-1)+2*(n-i-1) > l){
    			high = mid-1;
    			continue;
    		}
    		int c = use_detector(mid);
    		quer.pb({mid,c});
    		if(c < i){
    			low = mid+1;
    		}
    		else if(c == i){
    			high = mid;
    		}
    		else{
    			high = mid-1;
    		}
    	}
    	ans.pb(ans.back()+2*(low-ans.back()-1));
    }
    return ans;
}