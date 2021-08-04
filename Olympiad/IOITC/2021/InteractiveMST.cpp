#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
// #define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))

vi query(vi W);//Do not change this line

// Do NOT read anything from stdin or write something to stdout/stderr
//You are free to add variables and functions at global scope here
// If you use global variables, remember to initialize them in the findHiddenPermutation() function.

// If it is impossible to determine the hidden permutation, this function must return {}
vi findHiddenPermutation(int m){
    // your code goes here
    // for example vector<int> mst_edges = query({3, 4, 2, 3, 1});
    vi ans(m,-1); 
    set<int> ex;
    int bridges = 0;
    vi cur;
    REP(i,m) cur.pb(i+1);
    vi orig_q = query(cur);
    vi q = orig_q;
    REP(i,m){
    	REP(j,m) cur[j]--;
    	cur[i] = m;
    	vi new_q;
    	if(i == m-1) new_q = orig_q;
    	else new_q = query(cur);
    	mii m;
    	for(auto x:q) m[x]++;
    	for(auto x:new_q) m[x]--;
    	int f = 0;
    	for(auto x:m){
    		if(x.S == 1){
    			ans[i] = x.F;
    			ex.insert(x.F);
    			f++;
    		}
    	}
    	q = new_q;
    	if(!f){
    		bridges++;
    		if(bridges == 2) return {};
    	}
    }
    REP(i,m){
    	if(ans[i] == -1){
    		REP(j,m){
    			if(ex.find(j) == ex.end()){
    				ans[i] = j;
    				break;
    			}
    		}
    	}
    }
    return ans;
}