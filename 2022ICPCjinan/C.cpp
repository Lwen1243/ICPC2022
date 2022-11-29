#include<bits/stdc++.h>
#define int long long
using namespace std ;
const int MAXN = 505 ;
const int mod = 998244353 ;
int n ;
int dp[MAXN][MAXN] ;
vector<int> g[MAXN] ;
int tot[MAXN] ;
int siz[MAXN] ;
int fac[MAXN] ;
int dfs1(int u,int fa) {
    int res = 1;
    tot[u] = 0;
    siz[u] = 1;
    for (int v : g[u]) {
        if (v == fa)continue;
        res *= dfs1(v, u); res %= mod;
        tot[u]++;
        siz[u] += siz[v];
    }
    res *= fac[tot[u]]; res %= mod;
    return res;
}

void dfs(int u, int fa) {
    vector<vector<int>>f(n + 10, vector<int>(n + 10, 0));
    f[0][0] = 1;
    for (int v : g[u]) {
        if (v == fa)continue;
        for (int i = tot[u]; i>=1; i--) {
            for (int sz = siz[u]; sz>=siz[v]; sz--) {
                //g[i + 1][sz + siz[v]] += f[i][sz]
                //g[i][sz]+=f[i - 1][sz - siz[v]]
                f[i][sz] += f[i - 1][sz - siz[v]];
                f[i][sz] %= mod;
            }
        }
    }
    for (int v : g[u]) {
        if (v == fa)continue;
        for (int i = 1; i <= tot[u]; i++) {
            for (int sz = siz[v]; sz <= siz[u]; sz++) {
                f[i][sz] -= f[i - 1][sz - siz[v]];
                f[i][sz] = (f[i][sz] + mod) % mod;
            }
        }
        
        vector<int>g(n + 10, 0);
        for (int i = 0; i <= tot[u] - 1; i++) {
            for (int k = 0; k <= siz[u]; k++) {
                g[k + 1] += (fac[i] * fac[tot[u] - 1 - i])%mod * f[i][k];
                g[k + 1] %= mod;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                if (i + k <= n) {
                    dp[v][i + k] += dp[u][i] * g[k];
                    dp[v][i + k] %= mod;
                }
            }
        }
        for (int i = tot[u]; i >= 1; i--) {
            for (int sz = siz[u]; sz >= siz[v]; sz--) {
                f[i][sz] += f[i - 1][sz - siz[v]];
                f[i][sz] %= mod;
            }
        }
    }
    for (int v : g[u]) {
        if (v == fa)continue;
        dfs(v, u);
    }
}

void slove() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++)fac[i] = (i * fac[i - 1]) % mod;
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dp[1][1] = dfs1(1, 0);
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int k = 1; k <= n; k++)sum += dp[i][k];
        // int invsum = inv(sum);
        for (int k = 1; k <= n; k++) {
            cout << (dp[i][k] * dp[1][1]) % mod * sum % mod << " ";
        }
        cout << endl;
    }
}

signed main()
{
    slove() ;
    return 0 ;
}