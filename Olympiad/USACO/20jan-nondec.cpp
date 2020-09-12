#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int ll
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
#define pb push_back
#define vi vector<int>
#define vvi vector<vi>

const int MOD = 1000000007;
const int MAXN = 50005;

int n,k,q;

vvi dp1[MAXN];  
vvi dp2[MAXN];

int a[MAXN];

int dp_sub[21][21][2];

void build(int l,int r){
    if(l > r) return;
    int mid = (l+r)/2;
    // dp1[mid][i][j] = number of non-dec non-empty sequences from mid-i..mid with max value = j
    FOR(i,1,k+1){
        FOR(j,i,k+1){
            dp_sub[i][j][0] = 0;
        }
    }
    FORD(ind,mid,l){
        FOR(i,1,k+1){
            FOR(j,i,k+1){
                dp_sub[i][j][1] = dp_sub[i][j][0];
                if(i <= a[ind] and a[ind] <= j){
                    dp_sub[i][j][1] += dp_sub[a[ind]][j][0];
                    if(j == a[ind]) dp_sub[i][j][1]++;
                    dp_sub[i][j][1] %= MOD;
                }
            }
        }
        dp1[mid].pb(vi(k+1));
        FOR(i,1,k+1){
            FOR(j,i,k+1){
                dp_sub[i][j][0] = dp_sub[i][j][1];
                if(i == 1) dp1[mid][mid-ind][j] = dp_sub[i][j][1];
            }
        }
    }
    // dp2[mid][i][j] = number of non-dec non-empty sequences from mid+1..mid+i with least value = j
    dp2[mid].pb(vi(k+1));
    FOR(i,1,k+1){
        FOR(j,i,k+1){
            dp_sub[i][j][0] = 0;
            if(j == k) dp2[mid][0][i] = dp_sub[i][j][0];
        }
    }
    FOR(ind,mid+1,r+1){
        FOR(i,1,k+1){
            FOR(j,i,k+1){
                dp_sub[i][j][1] = dp_sub[i][j][0];
                if(i <= a[ind] and a[ind] <= j){
                    dp_sub[i][j][1] += dp_sub[i][a[ind]][0];
                    if(i == a[ind]) dp_sub[i][j][1]++;
                    dp_sub[i][j][1] %= MOD;
                }
            }
        }
        dp2[mid].pb(vi(k+1));
        FOR(i,1,k+1){
            FOR(j,i,k+1){
                dp_sub[i][j][0] = dp_sub[i][j][1];
                if(j == k) dp2[mid][ind-mid][i] = dp_sub[i][j][1];
            }
        }
    }

    build(l,mid-1);
    build(mid+1,r);
}

int query(int l,int r,int x,int y){
    int mid = (l+r)/2;
    if(x <= mid and mid <= y){
        int res = 0;
        int sm = 0;
        FORD(i,k,1){
            sm = (sm+dp2[mid][y-mid][i])%MOD;
            res += (dp1[mid][mid-x][i]*(sm+1))%MOD;
            res %= MOD;
        }
        res += sm+1;
        return res%MOD;
    }
    if(mid < x) return query(mid+1,r,x,y);
    else return query(l,mid-1,x,y);
}
 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("nondec.in","r",stdin);
    freopen("nondec.out","w",stdout);

    cin >> n >> k;
    FOR(i,1,n+1) cin >> a[i];
    build(1,n);
    cin >> q;
    REP(i,q){
        int x,y; cin >> x >> y;
        cout << query(1,n,x,y) << "\n";
    }
}