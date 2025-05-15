## 2023

### JT1 小苹果

<a href="https://www.luogu.com.cn/problem/P9748" target="_blank">Luogu P9748 [CSP-J 2023] 小苹果</a> | <a href="" target="_blank">视频解析</a>

题目大意

1. 给定 $1,2,3,...,n-1,n$，总共 $n$ 个数。

2. 从 **第 $1$ 个数** 开始，每隔 $2$ 个数取走一个，即取走 $1,4,7...$（记为 $1$ 天）。

3. 剩下的数为 $2,3,5,6...$；重复上述操作，直到取走 $n$。

4. 问，第几天会取完 $n$，第几天会取走 $n$ ？

解题思路

1. 因为每隔 $2$ 个数取走一个，我们不妨将其 $3$ 个一组进行考虑。

    1. `1 2 3 | 4 5 6 | 7`，当 $n = 7 (n \% 3 = 1)$ 时，在第 $1$ 天取走 $n$，取走 $\lceil \frac{n}{3} \rceil = 3$ 个数；

        `2 3 5 | 6 `，继续取数，在第 $2$ 天取走 $\lceil \frac{n}{3} \rceil = 2$ 个数；

        `3 5`，继续取数，在第 $3$ 天取走 $\lceil \frac{n}{3} \rceil = 2$ 个数；

        `5`，继续取数，在第 $4$ 天取走所有的数。

    2. `1 2 3 | 4 5 6 | 7 8`，当 $n = 8 (n \% 3 = 2)$ 时，第 $1$ 天结束，取走 $\lceil \frac{n}{3} \rceil = 3$ 个数；

        `2 3 5 | 6 8`，此时 $n = 5 (n \% 3 = 2)$，第 $2$ 天结束，取走 $\lceil \frac{n}{3} \rceil = 2$ 个数；

        `3 5 8`，此时 $n = 3 (n \% 3 = 0)$，第 $3$ 天结束，取走 $\lceil \frac{n}{3} \rceil = 1$ 个数；

        `5 8`，此时 $n = 2 (n \% 3 = 2)$，第 $4$ 天结束，取走 $\lceil \frac{n}{3} \rceil = 1$ 个数；

        `8`，此时 $n = 1 (n \% 3 = 1)$，在第 $5$ 天取走 $n$，取走所有的数。
        
    3. `1 2 3 | 4 5 6 | 7 8 9`，可以用上述相同的方法分析。

2. 可以发现，我们重复取数的过程，当第一次 $n \% 3 = 1$，就是取走 $n$ 之时，取走所有数的花费就是不断取走 $\lceil \frac{n}{3} \rceil$ 个数，看多少次操作后 $n$ 为 $0$；

<details><summary>代码</summary>

```cpp
#include <iostream>
using namespace std;

int n, ans1, ans2;

int main(){
    cin >> n;
    while(n){
        ans1 ++;
        if(n%3 == 1 && !ans2) ans2 = ans1;
        n -= (n+2)/3;
    }
    cout << ans1 << " " << ans2;
    return 0;
}
```
</details><br>


### JT2 公路

<a href="https://www.luogu.com.cn/problem/P9749" target="_blank">Luogu P9749 [CSP-J 2023] 公路</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定 $n$ 个站点，第 $i$ 个站点到第 $i+1$ 个站点间的距离为 $v[i]$。

    2. 站点 $i$ 的油价为 $a[i]$，初始时油箱为空，油箱可以装任意多的油，$1$ 单位油可以前进 $d$。

    3. 问，从站点 $1$ 到站点 $n$ 最少需要花费多少钱加油？

* 解题思路

    1. 对于 $i$ 站点后面的 $j$ 站点，无外乎三种情况：

        1. 油价大于 $a[i]$，那么不如在 $i$ 站点加油；

        2. 油价等于 $a[i]$，那么在哪里加油都一样；

        3. 油价小于 $a[i]$，那么肯定在 $j$ 站点加油。
    
    2. 因为最开始油箱为空，必须在 $1$ 站点加油，那么我们需要找到一条油价的 **下降序列**。

    3. 此种贪心方法不会陷入局部最优，因为为了到达 `j` 站点，必须在 `i` 站点加足量的油。

<details><summary>代码</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;

const int N = 1e5+10;

LL v[N], a[N];
LL n, d;
LL ans;

PII p[N];
LL m;

int main(){
    cin >> n >> d;
    for(int i=2; i<=n; i++) cin >> v[i];    // v[i] = 到上一个站点的距离
    for(int i=1; i<=n; i++) cin >> a[i];    // 油价
    a[n] = -1;  // 最后一个站点肯定不需要加油，但是我们希望能到达最后一个站点

    p[++m] = {a[1], v[1]};
    LL len = 0;
    for(int i=2; i<=n; i++){
        len += v[i];
        if(a[i] < p[m].fst){    // 出现了更优惠的油价
            p[++m] = {a[i], len};
            len = 0;
        }
    }

    /*
    for(int i=1; i<=m; i++)
        cout << p[i].fst << " " << p[i].sed << "\n";
    */

    LL l = 0;   // 上次加油剩余的距离
    for(int i=1; i<m; i++){
        // 加油量 = (距离(p[i+1].sed) - l) / 消耗(d)
        // 花费 = 加油量 * p[i].fst 
        // 多余距离 = 加油量 * d + l - 距离(p[i+1].sed)
        LL addoil = (p[i+1].sed - l + d-1) / d;
        ans += addoil * p[i].fst;
        l = addoil * d + l - p[i+1].sed;
    }
    
    cout << ans;

    return 0;
}
```
</details><br>

### JT3 一元二次方程

<a href="https://www.luogu.com.cn/problem/P9750" target="_blank">Luogu P9750 [CSP-J 2023] 一元二次方程</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 模拟

* 解题思路

    1. 见代码

<details><summary>代码</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<int, int> PII;

int a, b, c, d;

PII simple(int p, int q){   // 约分
    int pq = __gcd(abs(p), abs(q));
    return {p/pq, q/pq};
}

void solve(){
    cin >> a >> b >> c;
    d = b*b - 4*a*c;    // delta

    if(d < 0){          // 1. 无解
        printf("NO\n");
    }else if(d == 0){   // 2. 单解 -b / 2a
        PII res = simple(-b, 2*a);
        if(a < 0) res = {-res.fst, -res.sed};       // 负数情况
        if(res.sed == 1) printf("%d\n", res.fst);   // 2.1 分母为 1
        else printf("%d/%d\n", res.fst, res.sed);   // 2.2 分母不为 1
    }else{              // 3. 两解 -b(+-sqrt(d)) / 2a
        if(int sd = sqrt(d); sd*sd == d){           // 3.1 sqrt(d) 为整数
            PII res;
            if(a>0) res = simple(-b + sd, 2*a);     // 确定谁在前面
            else    res = simple(-b - sd, 2*a);
            if(a < 0) res = {-res.fst, -res.sed};       // 负数情况
            if(res.sed == 1) printf("%d\n", res.fst);   // 3.1.1 分母为 1
            else printf("%d/%d\n", res.fst, res.sed);   // 2.1.2 分母不为 1    
        }else{                                      // 3.2 sqrt(d) 不为整数
            // 有理数部分约分
            PII res = simple(-b, 2*a);
            if(a < 0) res = {-res.fst, -res.sed};       // 负数情况
            // 处理有理数部分 -b / 2a 
            if(res.fst != 0){
                if(res.sed == 1) printf("%d+", res.fst);
                else printf("%d/%d+", res.fst, res.sed);
            }
            // 处理无理数部分 sd / 2a
            res = {1, abs(2*a)};
            int t = 0;                  // 剩下的无理部分
            for(int r=sd; r>=1; r--)    
                if(d % (r*r) == 0) {    // 找到一个平方因子，sqrt(27) = 3 sqrt(3)
                    res.fst *= r;
                    t = d / (r*r);
                    break;
                }
            // 约分
            res = simple(res.fst, res.sed);

            if(res.fst == res.sed) printf("sqrt(%d)\n", t);
            else if(res.sed == 1)  printf("%d*sqrt(%d)\n", res.fst, t);
            else if(res.fst == 1)  printf("sqrt(%d)/%d\n", t, res.sed);
            else printf("%d*sqrt(%d)/%d\n", res.fst, t, res.sed);
        }
    }
}

int main(){
    int T, M; cin >> T >> M; while(T--)
    solve();
    return 0;
}
```
</details><br>



### JT4 

<a href="https://www.luogu.com.cn/problem/P9751" target="_blank">Luogu P9751 [CSP-J 2023] 旅游巴士</a> | <a href="" target="_blank">视频解析</a> | <a href="https://mp.weixin.qq.com/s?__biz=MzI1NTA2MDk5MA==&mid=2457235257&idx=1&sn=fc630a7217480236d78c8cf846461ab8&chksm=fca224999ffb25c9c10a67e73a5509c00857b47b272f89ca790c6f503d240ec7ae0a28270716&mpshare=1&scene=23&srcid=0915H7wD6F3QO8tiBooB99q5&sharer_shareinfo=38e5e9814b3e62dabeeee8ecc9d5b3a4&sharer_shareinfo_first=38e5e9814b3e62dabeeee8ecc9d5b3a4#rd" target="_blank">推荐阅读</a>

* 题目大意

    1. 给定

* 解题思路

    1. 假设

<details><summary>代码</summary>

```cpp

```
</details><br>

---

## 2022

### JT1 乘方

<a href="https://www.luogu.com.cn/problem/P8813" target="_blank">Luogu P8813 [CSP-J 2022] 乘方</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 计算 $a^b$ 次方的值，如果结果大于 $1e9$，则输出 $-1$。

* 解题思路
    
    1. $1$ 的任意（$>1$）次方均为 $1$。

    2. 因为 $\sqrt{a} * \sqrt{b} = \sqrt{a * b}$。

    3. 可以在累乘的时候，判断 $\sqrt{a^{b'}} * \sqrt{a}$ 是否大于 $\sqrt{1e9}$。

<details><summary>代码</summary>

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e5+10;

int a, b;

int main(){
    cin >> a >> b;
    if(a == 1){
        cout << 1;
        return 0;
    }

    int res = a;
    for(int _=2; _<=b; _++){
        // sqrt(a) * sqrt(b) = sqrt(a*b)
        if(int(sqrt(res) * sqrt(a)) > int(sqrt(1e9))){
            cout << "-1";
            return 0;
        }
        res *= a;
    }

    cout << res;

    return 0;
}
```
</details><br>

### JT2 解密

<a href="https://www.luogu.com.cn/problem/P8814" target="_blank">Luogu P8814 [CSP-J 2022] 解密</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定 $n, e, d$，求 $p, q$，满足：
        
        * $n = p * q$；
        
        * $e * d = (p-1)*(q-1) + 1$。

* 解题思路

    1. 展开 $e * d = p * q - p - q + 2$

        移项 $p + q = p * q - e * d + 2$

    2. 令 $p + q = m$，因为 $p = \frac{n}{q}$

        替换 $\frac{n}{q} + q = m$

        代入 $q^2 - m * q + n = 0$

    3. 通过求根公式即可求出 $q$。

<details><summary>代码</summary>

```cpp
#include <iostream>
#include <cmath>
using namespace std;

typedef long long LL;

void solve(){
    LL n, d, e, m, p, q;
    cin >> n >> d >> e;
    m = n - e * d + 2;
    // a = 1, b = -m, c = n
    if(LL delta = m*m-4*n; delta < 0){
        puts("NO");
    } else {
        // -b +- sqrt(delta) / 2a
        p = (m - sqrt(delta)) / 2;
        q = n / p;
        if(p+q == m && p*q == n){
            cout << p << " " << q << endl;
            return ;
        }
        puts("NO");
    }
}

int main(){
    int T; cin >> T; while(T--)
    solve();
    return 0;
}
```
</details><br>


### JT4 上升点列

<a href="https://www.luogu.com.cn/problem/P8816" target="_blank">Luogu P8816 [CSP-J 2022] 上升点列</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定 $n$ 个点，还可以再添加 $k$ 个点，找到一个点列，点列中任意相邻两个点满足：

        * $\{x_i + 1,y_i\} = \{x_{i+1},y_{i+1}\}$

        * 或 $\{x_i,y_i + 1\} = \{x_{i+1},y_{i+1}\}$

* 解题思路

    1. 因为 $n <= 500$ 的范围很小，$n^3$ 的复杂度也可以接受，不妨尝试一下暴力做法。

    2. 我们计算出所有合法点对，即 $\{x_i,y_i\} <= \{x_j, y_j\}$，$i$ 点则可以到达 $j$ 点，计算两点间的曼哈顿距离，如果不能到达则设置为极大值。

        * 注意，计算的距离需要 $-1$，因为相邻两个点无需加点。

    3. 再通过 $Floyd$ 做一遍松弛操作，可以得到合法点对的最短距离（在没加点的情况下）。

    4. 遍历所有的点对：
        
        * $i$ 到 $j$ 需要加点的数量 $=$ 曼哈顿距离 $-$ 已有点的距离；

        * 最长上升点列 $=$ 曼哈顿距离 $+$ 还未使用的加点数量。

<details><summary>代码</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;

const LL inf = 1e18;
const int N = 510;

PII a[N];       // 所有的点
LL dis[N][N];   // 两点之间的距离
LL n, k;

LL manhattan(int i, int j){
    return abs(a[i].fst - a[j].fst) + abs(a[i].sed - a[j].sed);
}

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> a[i].fst >> a[i].sed;

    // 建图
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(i != j && a[i].fst <= a[j].fst && a[i].sed <= a[j].sed)
                dis[i][j] = manhattan(i, j) - 1;// 如果 i -> j 是合法的，那么就计算距离
            else                                // -1 是因为相邻的情况下无需加点
                dis[i][j] = inf;                // 否则就是无穷大

    // Floyd 求最短路
    for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        // 松弛操作
    
    // 输出答案
    LL ans = 1;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(dis[i][j] <= k)  // i -> j 的距离小于等于 k，可以加点
                ans = max(ans, manhattan(i, j) - dis[i][j] + k + 1);
                // 两点之间的曼哈顿距离 - 已有点 + 可加点 + 1

    cout << ans;

    return 0;
}
```
</details><br>

---

## 2021

### JT1 分糖果

<a href="https://www.luogu.com.cn/problem/P7909" target="_blank">Luogu P7909 [CSP-J 2021] 分糖果</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. $n$ 个小朋友，平分 $L-R$ 块糖果，平分后可能存在多余的糖果。

    2. 问，多余的糖果在糖果数量为多少时达到最大？

* 解题思路

    1. 假设有 $3$ 个小朋友：

        * 若每人分 $1$ 块，糖果为 $3 - 5$ 块；

        * 若每人分 $2$ 块，糖果为 $6 - 8$ 块；
    
    2. 显然，在上述的完美情况下 $L/n == R/n$，能够拿到的最大糖果数量是 $R/n$。

    3. 其他情况下，则肯定为 $n-1$ 块。

<details><summary>代码</summary>

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

LL n, l, r;

int main(){
    cin >> n >> l >> r;
    
    if(l/n == r/n) cout << r%n; // 如果在同一个区间
    else cout<<n-1;
    
    return 0;
}
```
</details><br>



---

## 2017

### JT1 成绩

<a href="https://www.luogu.com.cn/problem/P3954" target="_blank">Luogu P3954 [NOIP2017 普及组] 成绩</a> | <a href="" target="_blank">视频解析</a>

<details><summary>代码</summary>

```cpp
#include <iostream>
using namespace std;

int main(){
    int a, b, c;
    cin >> a >> b >> c;
    cout << a*0.2 + b*0.3 + c*0.5;
    return 0;
}
```
</details><br>


### JT2 图书管理员

<a href="" target="_blank">Luogu P3955 [NOIP2017 普及组] 图书管理员</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定 $n$ 本书的编号，$m$ 个编号的后缀；

    2. 问，此后缀能匹配的最小编号是多少？无法匹配则输出 $-1$。

* 解题思路

    1. 对所有书的编号进行排序。

    2. 拿到一个后缀，顺序对所有编号的后缀匹配，匹配上则输出即可。

<details><summary>代码</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1010;
int a[N];
int n, m;

int main(){
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+1, a+1+n);

    while(m--){
        int l, p;
        cin >> l >> p;

        bool flg = false;
        for(int i=1; i<=n; i++){
            string s = to_string(a[i]);
            if(s.length() < l) continue;
            if(s.substr(s.size()-l) == to_string(p)){
                cout << a[i] << "\n";
                flg = true;
                break;
            }
        }

        if(flg == false)
            puts("-1");
    }

    return 0;
}
```
</details><br>


### JT3 棋盘

<a href="https://www.luogu.com.cn/problem/P3956" target="_blank">Luogu P3956 [NOIP2017 普及组] 棋盘</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 求最短路。

* 解题思路

    1. 每次合法转移有三种情况：

        * 下一个点为有色，两点颜色相同（不管是变色相同还是本就相同）；$0$ 花费过去；

        * 下一个点为有色，两点颜色不同（不管是变色相同还是本就相同）；$1$ 花费过去。

        * 下一个点为无色，当前点不是变色而来的；$2$ 花费过去；

<details><summary>代码</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;

const int N=110;
const int dxy[4][2]={ {-1,0},{1,0},{0,-1},{0,1} };

int g[N][N];    // 地图 红色1 黄色2 无色0
int n, m;

int dis[N][N];  // 最短路

int bfs(PII s, PII e){ 
    memset(dis, 0x3f, sizeof dis);
    
    queue<pair<PII, PII>> q;    // 第二个参数 { uxy变的颜色(没变为0), 魔法的花销 }
    dis[s.fst][s.sed] = 0;  
    q.push({s, {0, 0}});
    
    while(q.size()){
        auto u = q.front();
        q.pop();
        
        int ux = u.fst.fst;
        int uy = u.fst.sed;
        
        for(int i=0; i<4; i++){ // 去四个方向
            int nx = ux + dxy[i][0];
            int ny = uy + dxy[i][1];
            
            if(nx<1 || ny<1 || nx>n || ny>n) continue;
            
            // 下一个点为无色，且本点颜色不为 0
            if( g[nx][ny] == 0 && g[ux][uy] ){
                if( dis[nx][ny] > u.sed.sed + 2){
                    dis[nx][ny] = u.sed.sed + 2;
                    q.push({ {nx,ny}, {g[ux][uy], dis[nx][ny]} }); // 这是个变色玩意儿
                }
            }
            // 下一个点为有色，两点颜色相同（本就相同，或者变色后相同）
            else if(g[nx][ny] && (g[nx][ny] == g[ux][uy] || g[nx][ny] == u.sed.fst)){   // 相同, 可以通过变的去
                if( dis[nx][ny] > u.sed.sed){
                    dis[nx][ny] = u.sed.sed;
                    q.push({ {nx,ny}, {0, dis[nx][ny]} });
                }
            }
            // 下一个点为有色，两点颜色不同（本就不同，或者变色后不同）
            else if(g[nx][ny] && ((g[ux][uy] && g[nx][ny] != g[ux][uy]) || (u.sed.fst && g[nx][ny] != u.sed.fst)))
                if( dis[nx][ny] > u.sed.sed + 1){
                    dis[nx][ny] = u.sed.sed + 1;
                    q.push({ {nx,ny}, {0, dis[nx][ny]} });
                }
            
        }    
    }
    
    return dis[e.fst][e.sed] != 0x3f3f3f3f ? dis[e.fst][e.sed] : -1;
}

int main(){
    cin >> n >> m;
    for(int i=1; i<=m; i++){
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        g[x][y] = z+1;
    }
    cout << bfs({1,1}, {n,n});
    return 0;
}
```
</details><br>

---

## 2016

### JT1 买铅笔

<a href="https://www.luogu.com.cn/problem/P1909" target="_blank">Luogu P1909 [NOIP2016 普及组] 买铅笔</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定

* 解题思路

    1. 假设

<details><summary>代码</summary>

```cpp
#include <iostream>
using namespace std;

int n;

int main(){
    cin>>n;
    int ans = 0x3f3f3f3f;
    for(int i=1; i<=3; i++){
        int a, b; cin>>a>>b;
        ans = min(ans,  b * ((n+a-1)/a) );
    }
    cout<<ans;
    return 0;
}
```
</details><br>

### JT2 回文日期

<a href="https://www.luogu.com.cn/problem/P2010" target="_blank">Luogu P2010 [NOIP2016 普及组] 回文日期</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定一个起始日期和一个终止日期，求这两个日期之间有多少个回文日期，即满足：
        
        1. `YYYYMMDD` 是合法的日期；
        
        2. `YYYYMMDD` 是回文。

* 解题思路

    1. 对于回文类型的题目，我们首先考虑列举出所有的回文，然后再判断是否合法，而不是列举出所有的合法日期，然后再判断是否回文。

    2. 通过 `YYYY` 直接生成 `YYYYMMDD` 的回文
    
    3. 判断 `YYYYMMDD` 是否合法

<details><summary>代码</summary>

```cpp
#include <iostream>
using namespace std;

int a, b, ans;

int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool ck(int y, int m, int d){
    if((y*1e4+m*1e2+d)<a || (y*1e4+m*1e2+d)>b) return 0;
    
    months[2]=28;
    if(y%400==0 || y%4==0 && y%100!=0) months[2]=29;
    if(m<1 || m>12) return 0;
    if(d<1 || d>months[m]) return 0;
    return 1;
}

int main(){
    cin>>a>>b;
    
    for(int i=a/10000; i<=b/10000; i++)
        if( ck(i, (i%10)*10+(i/10%10), (i/100%10)*10+(i/1000)) ) ans++;

    cout<<ans;
    
    return 0;
}
```
</details><br>


### JT3 海港

<a href="https://www.luogu.com.cn/problem/P2058" target="_blank">Luogu P2058 [NOIP2016 普及组] 海港</a> | <a href="" target="_blank">视频解析</a>

* 题目大意

    1. 给定 $n$ 条信息，每条信息 $t, k, x_1, x_2, ... , x_k$： 

        * $t$ 时间，$k$ 个人，第 $i$ 个人的国籍为 $x_i$。

    2. 问，对于每条信息，在 $(vt, t+86400]$ 时间内，有多少种国籍？

* 解题思路

    1. 将所有的信息保存下来，按照时间排序（也就是题目给的顺序）；

    2. 对于每条信息，该条船上的人的国籍肯定需要考虑；

    3. 对于每条信息，回望过去，是否有船超过了时间范围：
        
        * 没有超过，那么就不用考虑；
        
        * 超过了，那么就需要将这条船上的人干掉。

<details><summary>代码</summary>

```cpp
#define pb push_back
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int N = 1e5+10;

vector<int> a[N];   // 每条船上人的国籍
int T[N];           // 每条船到达的时间
int n;
map<int, int> ans;

int main(){
    int n; cin>>n;
    for(int i=1; i<=n; i++){
        int m;
        cin>>T[i]>>m;
        for(int j=1; j<=m; j++){
            int x; cin>>x;
            a[i].pb(x);
        }
    }

    queue<int> q;               // 每条信息
    for(int i=1; i<=n; i++){    // 遍历每条信息
        q.push(i);              // 对于第 i 条船，肯定要考虑
        for(auto &j: a[i]) ans[j]++;    // 国籍数量

        // 如果队头的船，不在时间范围内内，干掉
        while( T[i] - T[q.front()] >= 86400){
            for(auto &k: a[q.front()]){
                ans[k]--;
                if(ans[k] == 0) ans.erase(k);
            }
            q.pop();
        }
        cout<<ans.size()<<"\n";
    }

    return 0;
}
```
</details><br>