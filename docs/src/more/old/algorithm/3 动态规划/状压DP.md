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


# 棋盘类(基于连通性)问题

## 玉米田

<a href="https://www.acwing.com/problem/content/329/" target="_blank">AcWing 327. 玉米田</a>

<details><summary>二进制表示状态</summary> 

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

const int N=14;
const int MOD=1e8;

int dp[N][1<<N];    // 在第 i 行, 第 j 种种植方案,有dp[i][j]种种植方案
vector<int> st;     // 所有的合法状态及此状态种植数量
vector<int> h[1<<N];// 状态 i -> 状态 j 

int g[N];
int n, m;

bool ck(int i){     // 检查 状态 i 是否合法
    for(int j=m-1; j>0; j--)    // 即检查是否有相邻的 1
        if( ((i>>j)&1) && ((i>>(j-1))&1) ) return 0;
    return 1;
}

bool ck2(int i, int j){ // 检查两个状态 是否有重合的 1
    if(i&j) return 0;   // 如果有,就说明冲突了
    return 1;   
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            int x; cin>>x;
            g[i]<<=1;
            g[i]+=!x;   // 将 1 设为不可种植, 而状态中二进制下为 1 的那个位置表示种植了
        }        
        //for(int j=m-1; j>=0; j--)
        //    cout<<(g[i]>>j & 1);
        //cout<<"\n";
    }
    for(int i=0; i<(1<<m); i++) // 计算所有状态(一行中所有的可能)
        if(ck(i)) st.pb(i);

    for(auto &a: st)    // 枚举状态 a 
    for(auto &b: st)    // 枚举状态 b
        if(ck2(a, b)) h[a].pb(b);   // 计算所有可以转移的状态(上下行可以相互转换)

    dp[0][0]=1;
    for(int i=1; i<=n+1; i++)           // 枚举行,多枚举一行,简易输出
    for(auto &a: st) if(ck2(a, g[i]))   // 判断第i行能否使用状态 a
    for(auto &b: h[a])                  // a可以由b状态转移来
            dp[i][a] = (dp[i][a] + dp[i-1][b])%MOD;

    cout<<dp[n+1][0];

    return 0;
}
```
</details>

## 国王

<a href="http://ybt.ssoier.cn:8088/problem_show.php?pid=1592" target="_blank">一本通 1592. 国王</a>

<details><summary>玉米田升级</summary> 

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
#define fst first
#define sed second
typedef long long LL;
typedef pair<int, int> PII;

const int N=12;
LL dp[N][N*N][1<<N];  // 第 i 行,放置j个国王,放置状态k,方案数dp[i][j][k]
vector<PII> st;       // 所有合法状态 及 该状态下放置的国王数量
vector<int> h[1<<N];  // 状态 i -> 状态 j

int n, k;

bool ck(int i){     // 检查 i 是否响铃         
    for(int j=n-1; j>0; j--)    // 即检查是否有相邻的 1 
        if( (i>>j&1) && (i>>(j-1)&1) ) return 0;
    return 1;
}

int cnt(int i){     // 计算该状态有多少个国王
    int res=0;      // 即有多少个 1
    for(int j=n-1; j>=0; j--)
        res+=(i>>j)&1;
    return res;
}

int main(){
    cin>>n>>k;

    for(int i=0; i<(1<<n); i++)     // 所有状态
        if(ck(i)) st.pb({i, cnt(i)});

    for(auto &[a,_]: st)
    for(auto &[b,_]: st)
        if((a&b)==0 && ck(a|b)) // a&b == 0 : 上下不相邻
            h[a].pb(b);         // ck(a|b)  : 或运算后,斜线方向不冲突

    dp[0][0][0]=1;

    for(int i=1; i<=n+1; i++)   // 枚举行
    for(int j=0; j<=k; j++)     // 枚举国王
    for(auto &[a,c]: st)        // 枚举状态
    for(auto &b: h[a])          // a 可以由 b 转移而来
        if(j>=c)
            dp[i][j][a] += dp[i-1][j-c][b];

    cout<<dp[n+1][k][0];
    return 0;
}
```
</details>

## 蒙德里安的梦想

<a href="https://www.acwing.com/problem/content/293/" target="_blank">AcWing 291. 蒙德里安的梦想</a>

<details><summary>只考虑一半</summary> 

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define pb push_back
typedef long long LL;

const int N=12;

LL dp[N][1<<N]; // 第 i 列,状态 j,方案数量dp[i][j]
bool st[1<<N];  // 所有状态 
int n, m;       // n 行 m 列

bool ck(int i){
    int cnt=0;
    for(int j=0; j<n; j++)
        if(i>>j & 1)
            if(cnt & 1) return 0;
            else cnt=0;
        else
            cnt++;
    if(cnt & 1) return 0;
    return 1;
}

void solve(){
    for(int i=0; i<(1<<n); i++)
        if(ck(i)) st[i]=1;

    dp[0][0]=1;

    for(int i=1; i<=m; i++)
    for(int a=0; a < 1<<n; a++) // 第 i-i 列的状态
    for(int b=0; b < 1<<n; b++) // 第  i  列的状态
        if(!(a&b) && st[a|b])   // 第 i-1列不能出现交集(a&b==0), 剩下的空位能完整放下 | 
            dp[i][b] += dp[i-1][a];

    cout<<dp[m][0]<<"\n";
}

// 统计总的方案数,我们不必枚举 - 和 | 的摆放可能
// 只需要枚举 - 或者 | 的方案数
// 因为 摆放的小方格方案数 等价于 横着摆放的小方格方案数
//
// 按照之前的思路,我们要找出第 i 列的所有合法状态
// 第 i-1 是铺满的状态,第i列会"支"出来某些地方
// 按照枚举 - 的思路,剩下的位置只能放 |
// 因此合理状态就是,第i列可以完全放下 |

int main(){
    while(cin>>n>>m, n||m){
        memset(dp, 0, sizeof dp);
        memset(st, 0, sizeof st);
        solve();
    }
    return 0;
}
```
</details>

## 炮兵阵地

<a href="https://www.acwing.com/problem/content/294/" target="_blank">AcWing 292. 炮兵阵地</a>

<details><summary> </summary> 

```cpp

```
</details>

## 积木画

<a href="https://www.acwing.com/problem/content/4409/" target="_blank">AcWing 4406. 积木画</a>

<details><summary>蒙德里安降级</summary> 

```cpp
#include <iostream>
using namespace std;

const int N=1e7+10;
const int MOD=1e9+7;
int n;

int dp[N][3];   // 前 i 列, 第 i 列的状态是(0,1,2) 全部伸出、上面伸出、下面伸出 

int main(){
    cin>>n;
    
    dp[0][0]=1;
    
    /*  对于 第i列 三种情况
    情况1: dp[i][0] -> 
        i +1 +2 
        * *     // 放个 | 的    dp[i+1][0]
        * *
        
        * * *   // 放俩 - 的    dp[i+2][0]
        * * *    
        
        * * *   // 放个 Γ 的    dp[i+2][1]
        * *
        
        * *     // 放个 L 的    dp[i+2][2]
        * * *    
    
    情况2: dp[i][1] ->
        i +1 +2
        *       // 下面放 - 的  dp[i+1][2]
        * *
        
        * *     //     放 」的  dp[i+1][0]
        * *
        
    情况3: dp[i][2] ->
        i +1 +2
        * *     // 上面放 - 的  dp[i+1][1]
        *
        
        * *     //     放 7 的  dp[i+1][0]
        * *
    */
    
    for(int i=0; i<=n; i++){
        dp[i+1][0] += dp[i][0]; dp[i+1][0]%=MOD;
        dp[i+2][0] += dp[i][0]; dp[i+2][0]%=MOD;
        dp[i+2][1] += dp[i][0]; dp[i+1][1]%=MOD;
        dp[i+2][2] += dp[i][0]; dp[i+2][2]%=MOD;
        dp[i+1][2] += dp[i][1]; dp[i+1][2]%=MOD;
        dp[i+1][0] += dp[i][1]; dp[i+1][0]%=MOD;
        dp[i+1][1] += dp[i][2]; dp[i+1][1]%=MOD;
        dp[i+1][0] += dp[i][2]; dp[i+1][0]%=MOD;
    }
    
    cout<<dp[n][0];
    
    return 0;
}
```
</details>

# 集合类问题



# 旅行商TSP问题