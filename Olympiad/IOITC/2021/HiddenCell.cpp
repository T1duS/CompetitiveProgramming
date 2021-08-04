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

bool doesPathExist(const vector<string>& M);//Do not change this line

// Do NOT read anything from stdin or write something to stdout/stderr
//You are free to add variables and functions at global scope here
// If you use global variables, remember to initialize them in the findHiddenCell() function.
int n;

bool check(vi gg){
    vector<string> M(n, string(n, '0'));
    REP(j,n){
        M[0][j] = '1';
        M[n-1][j] = '1';
    }
    for(auto x:gg){
        FOR(i,2,n-1) M[i][x+1] = '1';
        FOR(i,1,n-2) M[i][x-1] = '1';
    }
    return doesPathExist(M);
}

pii findHiddenCell(int N){
	n = N;
    vector<string> M(N, string(N, '1'));
    REP(j,n) M[1][j] = '0';
    if(doesPathExist(M)){
        int low = 1,high = n-2,mid;
        while(low < high){
            mid = (low+high)/2;
            REP(j,n) M[2][j] = '0';
            FOR(j,low,mid+1) M[2][j] = '1';
            if(doesPathExist(M)){
                high = mid;
            }
            else low = mid+1;
        }
        return {1,high};
    }
    REP(j,n){
        M[1][j] = '1';
        M[n-2][j] = '0';
    }
    if(doesPathExist(M)){
        int low = 1,high = n-2,mid;
        while(low < high){
            mid = (low+high)/2;
            REP(j,n) M[n-3][j] = '0';
            FOR(j,low,mid+1) M[n-3][j] = '1';
            if(doesPathExist(M)){
                high = mid;
            }
            else low = mid+1;
        }
        return {n-2,high};
    }
    vi cur;
    REP(i,3){
        vi bruh;
        FOR(j,1,n-1){
            if(j%3 == i) bruh.pb(j);
        }
        if(i == 2 or check(bruh)){
            cur = bruh;
            break;
        }
    }
    while(SZ(cur) > 1){
        vi half1,half2;
        REP(i,SZ(cur)){
            if(i < SZ(cur)/2) half1.pb(cur[i]);
            else half2.pb(cur[i]);
        }
        if(check(half1)) cur = half1;
        else cur = half2;
    }
    int col = cur[0];
    int low = 2,high = n-2,mid;
    REP(i,n){
        REP(j,n){
            if(j == col) M[i][j] = '0';
            else M[i][j] = '1';
        }
    }
    while(low < high){
        mid = (low+high)/2;
        REP(i,n) M[i][col+1] = '1';
        FOR(i,low,mid+1) M[i][col+1] = '0';
        if(doesPathExist(M)) low = mid+1;
        else high = mid;
    }
    return {high,col};
}