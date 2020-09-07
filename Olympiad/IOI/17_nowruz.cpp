#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define pii pair<int,int>
#define F first
#define S second
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define pb push_back

int n,m,BEST;
char a[1025][1025];
int b[1025][1025];
int c[1025][1025];
bool vis[1025][1025];

vector<pair<pii,pii> >  v;

vector<int> dx = {-1,1,0,0};
vector<int> dy = {0,0,-1,1};

bool valid(int i,int j){
    if(i == 0 or i > n) return false;
    if(j == 0 or j > m) return false;
    return a[i][j] == '.' and b[i][j];
}

signed main(){
    srand(time(0));
    cin >> n >> m >> BEST;
    FOR(i,1,n+1){
        FOR(j,1,m+1){
            cin >> a[i][j];
            b[i][j] = -1;
        }
    }
    FOR(i,1,n+1){
        FOR(j,1,m+1){
            if(!valid(i,j)) continue;
            int deg = 0;
            REP(k,4){
                if(valid(i+dx[k],j+dy[k])) deg++;
            }
            int r1 = rand()%2000;
            int r2 = rand()%2000;
            int r = r1*2000+r2;
            v.pb({{deg,r},{i,j}});
        }
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    
    int st = 0,ans = -1;
    while(st < (int)v.size() and runtime() < 100){
        int x = v[st].S.F;
        int y = v[st].S.S;
        int leaf = 0;
        FOR(i,1,n+1){
            FOR(j,1,n+1){
                vis[i][j] = 0;
                b[i][j] = -1;
            }
        }
        queue<pair<pii,pii> > q;
        q.push({{x,y},{-1,-1}});

        while(!q.empty()){
            pii u = q.front().F;
            pii par = q.front().S;
            q.pop();
            int flag = 0,d = 0;
            REP(k,4){
                int new_x = u.F+dx[k];
                int new_y = u.S+dy[k];
                if(!valid(new_x,new_y)) continue;
                d++;
                if(make_pair(new_x,new_y) == par) continue;
                if(b[new_x][new_y] == 1) flag = 1;
            }
            if(flag){
                b[u.F][u.S] = 0;
                continue;
            }
            if(d == 1) leaf++;
            b[u.F][u.S] = 1;
            REP(k,4){
                int new_x = u.F+dx[k];
                int new_y = u.S+dy[k];
                if(b[new_x][new_y] == -1 and valid(new_x,new_y)){
                    q.push({{new_x,new_y},u});
                }
            }
        }



        if(leaf > ans){
            ans = leaf;
            FOR(i,1,n+1){
                FOR(j,1,m+1){
                    c[i][j] = b[i][j];
                }
            }
        }
        st++;
    }
    FOR(i,1,n+1){
        FOR(j,1,m+1){
            if(c[i][j] == 1) cout << ".";
            else if(a[i][j] == '#') cout << "#";
            else cout << "X";
        }
        cout << "\n";
    }
}