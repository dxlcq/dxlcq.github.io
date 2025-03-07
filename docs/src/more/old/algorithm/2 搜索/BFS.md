---
html:
    toc: true           # 打开侧边目录
    toc_depth: 6        # 打开的目录层级
    toc_float: true     # 侧边悬停
    collapsed: true     # 只显示高级别标题(2)
    smooth_scroll: true # 页面滚动,标题变化
    number_sections: false  # 显示标题编号
    theme: united
--- 

>
> hh
>

## 矩阵上的BFS

<details><summary><a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1215" target="_blank">ybt 1215：迷宫</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int N = 1e2+10;
int dxy[4][2]={ {-1,0}, {1,0}, {0,-1}, {0,1} };

int n;          // 地图大小
char g[N][N];   // 地图
bool st[N][N];  // 走过没有
int sx, sy, ex, ey;

string solve(){
    memset(g, ' ', sizeof g);
    memset(st, 0, sizeof g);
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            cin>>g[i][j];
    cin>>sx>>sy>>ex>>ey;
    sx++, sy++, ex++, ey++;
    if(g[sx][sy]=='#' || g[ex][ey]=='#') return "NO";
    
    queue<PII> q;
    q.push({sx, sy}), st[sx][sy]=1;
    
    while(q.size()){
        auto t = q.front();
        q.pop();
        int x = t.first;
        int y = t.second;
        if(x == ex && y == ey) return "YES";
        
        for(int i=0; i<4; i++){
            int nx = x + dxy[i][0];
            int ny = y + dxy[i][1];
            
            if(nx>=1 && ny>=1 && nx<=n && ny<=n)
            if(g[nx][ny] == '.')
            if(st[nx][ny] == 0)
                q.push({nx, ny}), st[nx][ny]=1;
        }
    }
    return "NO";
}

int main(){
    int T; cin>>T;
    while(T--) cout<<solve()<<"\n";
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/1098/" target="_blank">AcWing 1096. 地牢大师</a> code</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;
const int N=110;

int dxy[6][3]={ {-1,0,0}, {1,0,0}, {0,-1,0}, {0,1,0}, {0,0,-1}, {0,0,1} };

char g[N][N][N]; // 地牢
int dis[N][N][N];// 最短路
int l, r, c;    

int main(){
    while(cin>>l>>r>>c){
        if(l==0 && r==0 && c==0) break;
        memset(dis, 0x3f, sizeof dis);

        queue<pair<int, PII>> q;

        for(int i=1; i<=l; i++)
        for(int j=1; j<=r; j++)
        for(int k=1; k<=c; k++){
            cin>>g[i][j][k];
            if(g[i][j][k]=='S')
                dis[i][j][k]=0,
                q.push({i,{j, k}});
        }

        bool flg = 0;
        while(q.size()){
            int i = q.front().fst;
            int j = q.front().sed.fst;
            int k = q.front().sed.sed;
            q.pop();
            if(g[i][j][k]=='E') {
                flg=1;
                cout<<"Escaped in "<<dis[i][j][k]<<" minute(s).\n";
                break;
            }
            for(int _=0; _<6; _++){
                int ni = i + dxy[_][0];
                int nj = j + dxy[_][1];
                int nk = k + dxy[_][2];

                if(ni>=1 && ni<=l && nj>=1 && nj<=r && nk>=1 && nk<=c)
                if(g[ni][nj][nk]!='#')
                if(dis[ni][nj][nk]==0x3f3f3f3f){
                    dis[ni][nj][nk] = dis[i][j][k]+1;
                    q.push({ni, {nj, nk}});
                }
            }
        }

        if(!flg) cout<<"Trapped!\n";
    }
    return 0;
}
```
</details>

---

## 一般BFS


<details><summary><a href="https://www.acwing.com/problem/content/1102/" target="_blank">AcWing 1100. 抓住那头牛</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int N=1e5+10;

int g[N];   // 地图
int dis[N]; // 最短路
int n, k;

bool ck(int x){
    if(x>=0 && x<=max(n, k)+1 && dis[x]==0x3f3f3f3f) return 1;
    return 0;
}

int main(){
    cin>>n>>k;
    memset(dis, 0x3f, sizeof dis);
    queue<int> q;
    dis[n]=0;
    q.push(n);
    while(q.size()){
        int u = q.front();
        q.pop();
        if(u==k){
            cout<<dis[u];
            break;
        }

        if(ck(u-1))
            dis[u-1] = dis[u]+1,
            q.push(u-1);
        if(ck(u+1))
            dis[u+1] = dis[u]+1,
            q.push(u+1);
        if(ck(u*2))
            dis[u*2] = dis[u]+1,
            q.push(u*2);
    }

    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/4222/" target="_blank">AcWing 4219. 找倍数</a> code</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<string, int> psi;

void solve(int n){
    queue<psi> q;
    q.push({"1", 1});
    
    while(q.front().sed!=0){
        auto u = q.front();
        q.pop();
        
        // 拓展1
        q.push({u.fst+"1", (u.sed*10+1)%n});
        // 拓展0
        q.push({u.fst+"0", (u.sed*10+0)%n});
    }
    cout<<q.front().fst<<"\n";
}

int main(){
    int _;
    while(cin>>_, _) solve(_);
    return 0;
}
```
</details>



<details><summary><a href="https://www.acwing.com/problem/content/description/4223/" target="_blank">AcWing 4220. 质数路径</a> code</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N=1e4+10;

bool st[N]={1, 1};  // 0,1不是素数
int primes[N];

void make_primes(int n){// 生成 n 以内的素数
    for(int i=2; i<=n; i++){
        if(!st[i]) primes[++(*primes)]=i;   // 登记素数
        for(int j=1; j<=(*primes) && primes[j]<=n/i; j++){
            st[primes[j]*i]=1;              // 筛掉
            if(i%primes[j]==0) break;       // i 是 primes[j] 的倍数
        }   // 如果 i 是 primes[j] 的倍数, primes[j] 就是其最小质因子
    }       // 因此, 我们不必用其他质因子去筛了
}

PII q[10000000];

void solve(){
    int a, b; cin>>a>>b;
    
    int f=1,e=0;
    q[++e] = {a, 0};
    
    while(f<=e && q[f].fst != b){
        auto u = q[f];
        ++f;

        // 改变个位
        for(int i=1; i<=9; i+=2){
            int n = (u.fst/10)*10 + i;
            if( !st[n] && n!=u.fst )
                q[++e] = {n, u.sed+1};
        }
        // 改变十位
        for(int i=0; i<=9; i++){
            int n = (u.fst/100)*100 + i*10 + u.fst%10;
            if( !st[n] && n!=u.fst )
                q[++e] = {n, u.sed+1};
        }
        // 改变百位
        for(int i=0; i<=9; i++){
            int n = (u.fst/1000)*1000 + i*100 + u.fst%100;
            if( !st[n] && n!=u.fst )
                q[++e] = {n, u.sed+1};
        }
        // 改变千位
        for(int i=1; i<=9; i++){
            int n = i*1000 + u.fst%1000;
            if( !st[n] && n!=u.fst )
                q[++e] = {n, u.sed+1};
        }
    }
    cout<<q[f].sed<<"\n";
}

int main(){
    make_primes(1e4);    
    int T; cin>>T; 
    while(T--) solve();
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/4225/" target="_blank">AcWing 4222. 罐子</a> code</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <stack>
#include <set>
using namespace std;

const int N = 1e5 + 10;

typedef pair<int, int> PII;

int A, B, C;

struct {
	int come;
	int ddd;
	int ceng;
	int a;
	int b;
} q[N];

int h = 1, t = 0;

PII calc(int i, PII ab) {
	if (i == 1) return { A, ab.sed };
	if (i == 2) return { ab.fst, B };
	if (i == 3) return { 0, ab.sed };
	if (i == 4) return { ab.fst, 0 };
	if (i == 5) {   // a -> b
		int d = min(ab.fst, B - ab.sed);  // 最多能接受多少
		return { ab.fst - d, ab.sed + d };
	}
	if (i == 6) {
		int d = min(ab.sed, A - ab.fst);
		return { ab.fst + d, ab.sed - d };
	}
}

void ppp(int i) {
	if (i == 1) cout << "FILL(1)\n";
	if (i == 2) cout << "FILL(2)\n";
	if (i == 3) cout << "DROP(1)\n";
	if (i == 4) cout << "DROP(2)\n";
	if (i == 5) cout << "POUR(1,2)\n";
	if (i == 6) cout << "POUR(2,1)\n";
}

int main() {
	cin >> A >> B >> C;
	// (从那个点来, 那个点做的操作是), 当前层数
	q[++t] = { 0,0,0,0,0 };

	set<PII> cnt;

	while (h <= t) {
		auto u = q[h++];

		for (int i = 1; i <= 6; i++) {

			PII ab = calc(i, { u.a, u.b });

			if (cnt.count(ab))
				continue;
			else {       // 从 h-1 那里来
				q[++t] = { h - 1, i, u.ceng + 1, ab.fst, ab.sed };
				cnt.insert(ab);
			}

            if (ab.fst == C || ab.sed == C) {
				cout << q[t].ceng << "\n";

				stack<int> ans;
				while (q[t].come != 0) {
					ans.push(q[t].ddd);
					t = q[t].come;
				}

				while (ans.size()) {
					ppp(ans.top());
					ans.pop();
				}

				return 0;
			}

		}
	}

    cout<<"impossible";

	return 0;
}
```
</details>