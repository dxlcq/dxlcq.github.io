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


# 2022 国 CB

<details><summary><a href="https://www.lanqiao.cn/problems/2191/learning/?page=1" target="_blank">C 卡牌</a> code</summary> 

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

const int N=2e5+10;

int a[N];   // 第 i 种卡牌有 a[i] 张
int b[N];   // 第 i 种卡牌最多凑 b[i] 张
LL n, m;

bool ck(LL x){  // 能不能凑 x 套
    LL mm=m;
    for(int i=1; i<=n; i++){
        if(a[i] >= x)
            continue;   // 一张不用换
        else if(a[i] + b[i] < x)
            return 0;   // 不够换
        else if(a[i] + b[i] >= x)
            mm-=x-a[i];   // 置换
        if(mm<0) return 0;
    }
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    for(int i=1; i<=n; i++) scanf("%d", b+i);
    
    LL l=1, r=1e11;
    while(l<r){
        LL mid = l+r+1>>1;
        if(ck(mid)) l=mid;
        else r=mid-1;
    }

    cout<<l;

    return 0;
}
```
</details>

<details><summary><a href="https://www.lanqiao.cn/problems/2193/learning/?page=1" target="_blank">D 最大数字</a> code</summary> 

```cpp
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

typedef long long LL;

const int N=1;

string s;
int a, b;
LL ans=-1;

LL s2i(string s){
    stringstream ss;
    ss<<s;
    LL res;
    ss>>res;
    return res;
}

void dfs(int u){    // 当前改变第几位
    ans = max(ans, s2i(s));
    if(!a && !b) return ;
    if(u>=s.size()) return ;
    
    if(s[u]=='9'){
        dfs(u+1);
        return ;
    }

    if(a>0){    // 用加法的方式
        int add = min(a, 9-(s[u]-'0')); // 增加多少

        s[u]+=add, a-=add;
        dfs(u+1);
        s[u]-=add, a+=add;  // 恢复现场
    }

    if(b>0){    // 用减法的方式
        int sub = min(b, (s[u]-'0')+1);
        
        if(s[u]-sub != '0'-1){
            dfs(u+1);   // 你还不如不减呢
            return ;
        }

        s[u]='9', b-=sub;
        dfs(u+1);
        s[u]='0'+sub-1, b+=sub;  // 恢复现场
    }

}

int main(){
    cin>>s>>a>>b;

    dfs(0); 
    cout<<ans;
    return 0;
}
```
</details>

<details><summary><a href="https://www.lanqiao.cn/problems/2194/learning/?page=1" target="_blank">E 出差</a> code</summary> 

```cpp
#pragma G++ optimzie("Ofast")
#define fst first
#define sed second
#define pb push_back
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <queue>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int dxy[][2]={ {-1,0},{1,0}, {0,-1}, {0,1} };
const double PI = acos(-1.0);
const int inf = 0x3f3f3f3f;
const int MOD = 1e9+7;
const int N = 1e3+10;

int C[N];

int n, m; // 点、边
vector<PII> edge[100010]; // edge[x]={y,z} x->y=z
int dis[N]; // 最短路
bool st[N]; // 是否已确定最短路
// O(mlogm)
int dijkstra(int s, int e){
    // fst存dis[i] sed存i
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    // 初始化
    memset(dis, 0x3f, sizeof dis);
    dis[s]=0;
    // 起点入队
    heap.push({dis[s], s});
    while(heap.size()){
        auto x=heap.top().sed; // 取最小点
        heap.pop();
        // 在出堆的时候判断、确定是否确定最短路
        if(st[x]) continue;
        st[x]=1; // 确定最短路
        // 对该点进行松弛操作
        for(auto& [y, z]: edge[x])
        if( dis[y]>dis[x]+z+C[y] ){
            dis[y]=dis[x]+z+C[y];
            heap.push({dis[y], y});
        }
    }
    return dis[e];
}

void solve(){
    cin>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", C+i);
    for(int i=1; i<=m; i++){
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        edge[x].pb({y, z});
        edge[y].pb({x, z});
    }

    cout<<dijkstra(1, n)-C[n];

    return ;
}

int main(){
    //ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    //int T; cin>>T; while(T--)
    solve();
    return 0;
}
```
</details>

<details><summary><a href="https://www.lanqiao.cn/problems/2195/learning/?page=1" target="_blank">F 费用报销</a> code</summary> 

```cpp
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

const int N=1e3+10;

int v[N];   // 月份转换为天 第i天的钱
int dp[N];  // 前i张可以得到的最大价值

int n, m, k;

int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int calc(int mon, int day){ 
    for(int i=1; i<mon; i++)
        day+=months[i];
    return day;
}

int main(){
    cin>>n>>m>>k;
    for(int i=1; i<=n; i++){
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        v[calc(x, y)]=max(v[calc(x, y)], z);
    }

    for(int i=1; i<=365; i++){  
        dp[i]=max(v[i], dp[i-1]);       // 不选择
        if(i-k>=1 && dp[i-k]+v[i]<=m)   // 选择
            dp[i] = max(dp[i], dp[i-k]+v[i]);
    }

    cout<<dp[365];

    return 0;
}
```
</details>

<details><summary><a href="" target="_blank">G </a> code</summary> 

```cpp

```
</details>

<details><summary><a href="" target="_blank">H </a> code</summary> 

```cpp

```
</details>

<details><summary><a href="" target="_blank">I </a> code</summary> 

```cpp

```
</details>

<details><summary><a href="" target="_blank">J </a> code</summary> 

```cpp

```
</details>

---