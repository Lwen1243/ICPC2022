#include<bits/stdc++.h>
#define int long long
using namespace std ;
const int MAXN = 505 ;
const int mod = 998244353 ;
int n ;
int dp[MAXN][MAXN] ;
vector<int> edge[MAXN] ;
int tot[MAXN] ;
int siz[MAXN] ;
int fac[MAXN] ;

int dfs(int x, int fa)
{
    int res = 1 ;
    tot[x] = 0 ;
    siz[x] = 1 ;
    for(auto v : edge[x] )
    {
        if( v == fa ) continue;
        res *= dfs(v, x) ;
        res %= mod ;
        tot[x] ++ ;
        siz[x] += siz[v] ;
    }
    res *= fac[tot[x]] ;
    res %= mod ;
    return res ;
}

void sear(int u, int fa)
{
    vector<vector<int>>dpt(n+1, vector<int>(n + 1, 0)) ;
    dpt[0][0] = 1 ;
    for(auto v : edge[u])
    {
        if( v == fa ) continue;
        for(int i = tot[u] ; i >= 1 ; i -- )
        {
            for(int sz = siz[u] ; sz >= siz[v] ; sz -- )
            {
                dpt[i][sz] += dpt[i - 1][sz - siz[v]] ;
                dpt[i][sz] %= mod ;
            }
        }
    }
    for(auto v : edge[u] )
    {
        if( v == fa ) continue;
        for(int i = 1 ; i <= tot[u] ; i ++ )
        {
            for(int sz = siz[v] ; sz <= siz[u] ; sz ++ )
            {
                dpt[i][sz] -= dpt[i - 1][sz - siz[v]] ;
                dpt[i][sz] = ( dpt[i][sz] + mod ) % mod ;
            }
        }
        vector<int> edge(n + 10, 0) ;
        for(int i = 0 ; i < tot[u] ; i ++ )
        {
            for(int j = 0 ; j <= siz[u] ; j ++ )
            {
                edge[j + 1] += ( fac[i] * fac[tot[u] - 1 - i]) % mod * dp[i][j] ;
                edge[j + 1] %= mod ;
            }
        }
        for(int i = 1 ; i <= n ; i ++ )
        {
            for(int j = 1 ; j <= n ; j ++ )
            {
                if( i + j <= n )
                {
                    dp[v][i + j] += dp[u][i] * edge[j] ;
                    dp[v][i + j] %= mod ;
                }
            }
        }
        for(int i = tot[u] ; i >= 1 ; i -- )
        {
            for(int sz = siz[u] ; sz >= siz[v] ; sz -- )
            {
                dpt[i][sz] += dpt[i - 1][sz - siz[v]] ;
                dpt[i][sz] %= mod ;
            }
        }
    }
    for(auto v : edge[u])
    {
        if( v == fa ) continue;
        sear(v, u) ;
    }
}

signed main()
{
    fac[0] = 1 ;
    for(int i = 1 ; i <= MAXN ; i ++ ) fac[i] = ( i * fac[i - 1] ) % mod ;
    cin >> n ;
    for(int i = 1 ; i < n ; i ++ )
    {
        int u ,v ;
        scanf("%lld%lld",&u, &v) ;
        edge[u].push_back(v) ;
        edge[v].push_back(u) ;
    }
    dp[1][1] = dfs(1, 0) ;
    sear(1, 0) ;
    for(int i = 1 ; i <= n ; i ++ )
    {
        int sum = 0 ;
        for(int j = 1 ; j <= n ; j ++ ) sum += dp[i][j] ;
        int invsum = inv(sum) ;
    }
}