// https://codeforces.com/contest/869/problem/E
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define fored(i,l,r) for(int i=r; i>=l; --i)
#define el '\n'
#define sz(v) int(v.size())

using namespace std;

typedef  long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

const int N = 2500 + 1;
ll st[2*N][2*N];
struct stree{
  int n, m, neutro = 0;
  stree(int n, int m): n(n), m(m){ forn(i, 2*n) forn(j, 2*m) st[i][j] = neutro; }
  stree(vector<vi> a): n(sz(a)), m(n ? sz(a[0]) : 0){ build(a); } 
  inline ll op(ll a, ll b){ return a+b; }
  void build(vector<vi>& a){
    forn(i, n) forn(j, m) st[i+n][j+m] = a[i][j];
    forn(i, n) fored(j, 1, m-1) st[i+n][j] = op(st[i+n][j<<1], st[i+n][j<<1|1]);
    fored(i, 1, n-1) forn(j, 2*m) st[i][j] = op(st[i<<1][j], st[i<<1|1][j]);
  }
  void upd(int x, int y, ll v){
    st[x+n][y+m] = v;
    for(int j = y+m; j > 1; j >>= 1) st[x+n][j>>1] = op(st[x+n][j], st[x+n][j^1]);
    for(int i = x+n; i > 1; i >>= 1) 
      for(int j = y+m; j; j >>= 1) st[i>>1][j] = op(st[i][j], st[i^1][j]);
  }
  ll query(int x0, int x1, int y0, int y1){ // [x0, x1], [y0, y1]
    ll r = neutro;
    for(int i0 = x0+n, i1 = x1+n+1; i0 < i1; i0 >>= 1, i1 >>= 1){
      int t[4], q=0;
      if(i0&1) t[q++] = i0++;
      if(i1&1) t[q++] = --i1;
      forn(k, q) for(int j0 = y0+m, j1 = y1+m+1; j0 < j1; j0 >>= 1, j1 >>= 1){
        if(j0&1) r = op(r, st[t[k]][j0++]);
        if(j1&1) r = op(r, st[t[k]][--j1]);
      }
    }
    return r;
  }
};

int rd(){ return (rand() << 15) | rand();}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m, q; cin >> n >> m >> q;
  stree st(n, m);
  map<vi, int> id;
  forn(i, q){
    int t, r1, c1, r2, c2; 
    cin >>t >> r1 >> c1 >> r2 >> c2;
    --r1, --c1, --r2, --c2;
    if(t <= 2){
      if(t == 1) id[{r1, c1, r2, c2}] = rd();
      int val = (t == 1 ? 1 : -1) * id[{r1, c1, r2, c2}];

      st.upd(r1, c1, st.query(r1, r1, c1, c1) + val);
      st.upd(r2+1, c1, st.query(r2+1, r2+1, c1, c1) - val);
      st.upd(r1, c2+1, st.query(r1, r1, c2+1, c2+1) - val);
      st.upd(r2+1, c2+1, st.query(r2+1, r2+1, c2+1, c2+1) + val);
    } else{
      if(st.query(0, r1, 0, c1) == st.query(0, r2, 0, c2))
        cout << "Yes" << el;
      else cout << "No" << el;
    }
  }
}