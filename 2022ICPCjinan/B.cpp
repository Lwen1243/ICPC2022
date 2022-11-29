#include<bits/stdc++.h>
#define ll    long long
#define mp    make_pair
#define fi    first
#define se    second
using namespace std;
const int MAXN = 1000005 ;
int T,n,m;
ll a1,b1,a2,b2,q[MAXN],ans[MAXN];
pair<ll,int> p[17000006];
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld%lld%d",&a1,&b1,&a2,&b2,&n);
		ll _=(a1+b1)*(a2+b2);
		m=n;
		for(int i=1;i<=n;++i){
			scanf("%lld",q+i);
			if(q[i]<_*2)p[i]=mp(q[i],i);
			else p[i]=mp(q[i]%_+_,i);
		}
		for(int i=1;i<=(a2+b2)*2;++i){
			p[++m]=mp((a1+b1)*i-b1,-4);
			p[++m]=mp((a1+b1)*i,-3);
		}
		for(int i=1;i<=(a1+b1)*2;++i){
			p[++m]=mp((a2+b2)*i-b2,-2);
			p[++m]=mp((a2+b2)*i,-1);
		}
		sort(p+1,p+m+1);
		ll A=0,B=0,t=0,_B=0;
		int x=1,y=1;
		for(int i=1;i<=m;++i){
			ll _t=p[i].fi;
			if(x)A+=_t-t;
			if(y)B+=_t-t;
			if(B>A)B=A;
			t=_t;
			if(t==_)_B=B;
			if(p[i].se==-4||p[i].se==-3)x^=1;
			else if(p[i].se==-2||p[i].se==-1)y^=1;
			else ans[p[i].se]=B;
		}
		for(int i=1;i<=n;++i){
			if(q[i]>=_*2)ans[i]+=(q[i]/_-1)*(B-_B);
		}
		for(int i=1;i<=n;++i)printf("%lld\n",ans[i]);
	}
	return 0;
}