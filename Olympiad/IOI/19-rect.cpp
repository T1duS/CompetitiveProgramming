#include "rect.h"
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
#define pii pair<int,int>
#define F first
#define S second
#define all(v) v.begin(),v.end()
#define SZ(v) (int)v.size()
 
const ll MX = 2505;
 
ll ans = 0;
int n,m; 
int gl[MX][MX],gr[MX][MX],gu[MX][MX],gd[MX][MX];
int glfuck[MX][MX],grfuck[MX][MX],gufuck[MX][MX],gdfuck[MX][MX];

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
 
void check_rectangle(int x1,int y1,int x2,int y2){
    if(gr[x1][y1-1] == y2+1){
    	if(grfuck[x1][y1-1] < x2) return;
    }
    else if(gl[x1][y2+1] == y1-1){
    	if(glfuck[x1][y2+1] < x2) return;
    }
    else return;

    if(gd[x1-1][y1] == x2+1){
    	if(gdfuck[x1-1][y1] < y2) return;
    }
    else if(gu[x2+1][y1] == x1-1){
    	if(gufuck[x2+1][y1] < y2) return;
    }
    else return;

    ans++;
}
 
ll count_rectangles(vector<vi> a){
    n = a.size();
    m = a[0].size();
    if(n <= 2 or m <= 2) return 0;
    REP(i,n+2){
    	REP(j,m+2){
    		gl[i][j] = gr[i][j] = gu[i][j] = gd[i][j] = -1;
    	}
    }
    FORD(i,n-1,0){
        stack<int> st;
        REP(j,m){
            while(st.size() and a[i][st.top()] <= a[i][j]){
            	if(j-1 > st.top()) gr[i][st.top()] = j;
                st.pop();
            }
            st.push(j);
        }
        while(!st.empty()) st.pop();
        FORD(j,m-1,0){
            while(st.size() and a[i][st.top()] <= a[i][j]){
            	if(j+1 < st.top()) gl[i][st.top()] = j;
                st.pop();
            }
            st.push(j);
        }
        REP(j,m){
        	if(gr[i][j] != -1){
        		if(gr[i][j] == gr[i+1][j]){
        			grfuck[i][j] = grfuck[i+1][j];
        		}
        		else if(gl[i+1][gr[i][j]] == j){
        			grfuck[i][j] = glfuck[i+1][gr[i][j]];
        		} 
        		else grfuck[i][j] = i;
        	}
        	if(gl[i][j] != -1){
        		if(gl[i][j] == gl[i+1][j]){
        			glfuck[i][j] = glfuck[i+1][j];
        		}
        		else if(gr[i+1][gl[i][j]] == j){
        			glfuck[i][j] = grfuck[i+1][gl[i][j]];
        		} 
        		else glfuck[i][j] = i;
        	}
        }
    }
    FORD(j,m-1,0){
        stack<int> st;
        REP(i,n){
            while(st.size() and a[st.top()][j] <= a[i][j]){
            	if(i-1 > st.top())  gd[st.top()][j] = i;
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty()) st.pop();
        FORD(i,n-1,0){
            while(st.size() and a[st.top()][j] <= a[i][j]){
            	if(i+1 < st.top()) gu[st.top()][j] = i;
                st.pop();
            }
            st.push(i);
        }
        REP(i,n){
        	if(gd[i][j] != -1){
        		if(gd[i][j] == gd[i][j+1]){
        			gdfuck[i][j] = gdfuck[i][j+1];
        		}
        		else if(gu[gd[i][j]][j+1] == i){
        			gdfuck[i][j] = gufuck[gd[i][j]][j+1];
        		} 
        		else gdfuck[i][j] = j;
        	}
        	if(gu[i][j] != -1){
        		if(gu[i][j] == gu[i][j+1]){
        			gufuck[i][j] = gufuck[i][j+1];
        		}
        		else if(gd[gu[i][j]][j+1] == i){
        			gufuck[i][j] = gdfuck[gu[i][j]][j+1];
        		} 
        		else gufuck[i][j] = j;
        	}
        }
    }
    vector<ll> bruh;
    FOR(i,1,n-1){
        FOR(j,1,m-1){
            // topleft
            if(gr[i][j-1] != -1 and gd[i-1][j] != -1){
            	bruh.pb((i)*MX*MX*MX+(j)*MX*MX+(gd[i-1][j]-1)*MX+gr[i][j-1]-1);
            }
            // topright
            if(gl[i][j+1] != -1 and gd[i-1][j] != -1){
                bruh.pb((i)*MX*MX*MX+(gl[i][j+1]+1)*MX*MX+(gd[i-1][j]-1)*MX+j);
            }
            // bottomleft
            if(gr[i][j-1] != -1 and gu[i+1][j] != -1){
            	bruh.pb((gu[i+1][j]+1)*MX*MX*MX+(j)*MX*MX+(i)*MX+gr[i][j-1]-1);
            }
            // bottomright
            if(gl[i][j+1] != -1 and gu[i+1][j] != -1){
            	bruh.pb((gu[i+1][j]+1)*MX*MX*MX+(gl[i][j+1]+1)*MX*MX+(i)*MX+j);
            }
            // clockwise
            if(gr[i][j-1] != -1 and gd[i-1][gr[i][j-1]-1] != -1){
            	bruh.pb((i)*MX*MX*MX+(j)*MX*MX+(gd[i-1][gr[i][j-1]-1]-1)*MX+gr[i][j-1]-1);
            }
            // anti-clockwise
            if(gl[i][j+1] != -1 and gd[i-1][gl[i][j+1]+1] != -1){
            	bruh.pb((i)*MX*MX*MX+(gl[i][j+1]+1)*MX*MX+(gd[i-1][gl[i][j+1]+1]-1)*MX+j);
            }
        }
    }
    sort(all(bruh));
    REP(i,SZ(bruh)){
    	if(i == 0 or bruh[i] != bruh[i-1]){
			check_rectangle(bruh[i]/(MX*MX*MX),(bruh[i]/(MX*MX))%MX,(bruh[i]/MX)%MX,bruh[i]%MX);
    	}
    }
    return ans;
}