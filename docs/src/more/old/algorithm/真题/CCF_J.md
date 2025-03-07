---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---

<!-->


J-1

<details><summary><a href="" target="_blank"></a> 16</summary>

```cpp
#include <iostream>

using namespace std;

int main(){
    unsigned short x, y;
    cin >> x >> y;
    x = (x | x << 2)& 0x33;
    x = (x | x << 1)& 0x55;
    y = (y | y << 2)& 0x33;
    y = (y | y << 1)& 0x55;
    unsigned short z = x | y << 1;
    cout << z << endl;
    return 0;
}
```

> 删去第 7 行与第 13 行的 unsigned，程序行为不变。

无符号数与有符号数，范围不同，但此题 `假设输入的 x,y 均是不超过 15 的自然数`。

> 将第 7 行与第 13 行的 short 均改为 char，程序行为不变。

显然，当输入 `10 11` 的时候，x = (char)1， y = (char)0，与程序原意不符。

> 程序总是输出一个整数“0”。

假设输入 `2 2`
x=2，y=2：`x<<2 = 8`，`8 | 2 = 10`，`x = 10 & 0x33 = 2`
x=2，y=2：`x<<1 = 4`，`4 | 2 = 6`，`x = 6 & 0x55 = 4`
x=4，y=2：`y<<2 = 8`，`8 | 2 = 10`，`y = 10 & 0x33 = 2`
x=4，y=2：`y<<1 = 4`，`4 | 2 = 6`，`y = 6 & 0x55 = 4`
x=4，y=4：`x | y << 1 = 4 | 4 << 1 = 4 | 8 = 12`
输出为 `12`，与题意不符

</details>

<details><summary><a href="" target="_blank"></a> 17</summary>

```cpp

```
</details>


<br>

J-2

<!-->

# 2021

<details><summary><a href="https://www.acwing.com/problem/content/4089/" target="_blank">AcWing 4086. 分糖果</a> code</summary>

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

LL n, l, r;

int main(){
    cin>>n>>l>>r;
    
    if(l/n==r/n) cout<<r%n; // 如果在同一个区间
    else cout<<n-1;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/4090/" target="_blank">AcWing 4087. 插入排序</a> code</summary>

<br>


**大意**

给定一个序列 `a`，每次可以对该序列做两种操作：

1. 令 `a[x] = v`
2. 查询 `a[x]` 在排序后，所在的位置


**思路**

1. 如果每次查询操作都重新排序，那么必定会超时，因此尝试先排序
2. 排序后会丢失部分信息，因此有必要记录下来
    * `a[i].fst` 记录值
    * `a[i].sed` 记录其在原序列的位置
3. 对 `a` 排序
4. `a` 排序后无法快速找到原序列，因此有必要建立一个索引，`p[x] = i`
    * 原序列中第 `x` 位，现在在 `i` 位
5. 对于查询，我们只需要输出 `p[x]`
6. 对于修改
    * 定位到当前的位置 `p[x]`，令 `a[ p[x] ] = v`
    * 将 `a[ p[x] ]` 移动到合适的位置即可


```cpp
#define fst first
#define sed second
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

typedef pair<int, int> PII;

const int N=8e3+10;

PII a[N];   // 数组
int n, q;

int p[N];    // 索引

int main(){
    cin>>n>>q;
    for(int i=1; i<=n; i++){
        scanf("%d", &a[i].fst);
        a[i].sed = i;
    }
    
    sort(a+1, a+1+n);
    for(int i=1; i<=n; i++)
        p[ a[i].sed ] = i;
    
    for(int _=1; _<=q; _++){
        int qq, x, v; scanf("%d", &qq);
        
        if( qq==1 ){
            scanf("%d%d", &x, &v);
            
            // 定位到原数组的位置
            x = p[x];
            
            // 将a[i].fst 转换为 v, 检查其应该左移还是右移动
            if( a[x].fst > v ){   // 左移动
                a[x].fst = v;
                for(int i=x; i>=2; i--)
                    if(a[i] < a[i-1]){
                        swap(a[i], a[i-1]);
                    
                        p[ a[i].sed ] = i;
                        p[ a[i-1].sed ] = i-1;
                    }
                    else break;
            }else
            if( a[x].fst < v ){   // 右移动
                a[x].fst = v;
                for(int i=x; i<=n-1; i++)
                    if(a[i] > a[i+1]){
                        swap(a[i], a[i+1]);
                    
                        p[ a[i].sed ] = i;
                        p[ a[i+1].sed ] = i+1;
                    }
                    else break;
            }
        }else{
            scanf("%d", &x);
            printf("%d\n", p[x]);
        }
    }
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/description/4091/" target="_blank">AcWing 4088. 网络连接</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
#include <sstream>
#include <map>
using namespace std;

const int N=1e3+10;

map<string, int> serv;
int n;

int s2i(string s){
    stringstream ss;
    ss<<s;
    int res;
    ss>>res;
    return res;
}

string i2s(int num){
    stringstream ss;
    ss<<num;
    string res;
    ss>>res;
    return res;
}

bool ck(string s){
    int a[5];
    string cmp;
    sscanf(s.c_str(), "%d.%d.%d.%d:%d", a, a+1, a+2, a+3, a+4);
    
    for(int i=0; i<4; i++){
        if(a[i]<0 || a[i]>255) return 0;
        cmp += i2s(a[i]) + ".";
    }
    cmp[cmp.size()-1]=':'; // 替换最后一个'.'
    
    if(a[4]<0 || a[4]>65535) return 0;
    cmp += i2s(a[4]);
    return s == cmp;
}

int main(){
    cin>>n;
    for(int i=1; i<=n; i++){
        string op, ad; cin>>op>>ad;
        
        if(op == "Server"){
            if(ck(ad))  // 符合规范
                if(serv.count(ad))
                    cout<<"FAIL\n";
                else
                    serv[ad] = i, cout<<"OK\n";
            else
                cout<<"ERR\n";
        }
        else{
            if(ck(ad))  // 符合规范
                if(serv.count(ad))
                    cout<<serv[ad]<<"\n";
                else
                    cout<<"FAIL\n";
            else
                cout<<"ERR\n";
        }
    }
    
    
    return 0;
}
```
</details>

---

# 2020

<details><summary><a href="https://www.acwing.com/problem/content/2769/" target="_blank">AcWing 2767. 优秀的拆分</a> code</summary>

```cpp
#include <iostream>
#include <queue>
using namespace std;

int n;
int a[30];

int main(){
    a[1]=1;
    for(n=1; a[n]<=1e7;){
        ++n;
        a[n] = a[n-1]*2;
    }
    
    queue<int> q;
    int k; cin>>k;
    
    while(n>=2){
        if(k >= a[n]) k-=a[n], q.push(a[n]);
        n--;
    }
    if(k==0)
        while(q.size()){
            cout<<q.front()<<" ";
            q.pop();
        }
    else
        cout<<-1;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/2770/" target="_blank">AcWing 2768. 直播获奖</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=1e5+10;

int n, w;   

int a[610]; // 每个分数段的成绩

int calc(int cnt){  // 获奖人数
    if(!cnt) cnt=1; // 如果获奖人数为0
    for(int i=600; ; i--){
        cnt -= a[i];
        if(cnt<=0) return i;
    }
}

int main(){
    cin>>n>>w;
    for(int i=1; i<=n; i++){
        int ai; scanf("%d", &ai);
        a[ ai ] ++;
        cout<<calc(i * w / 100)<<" ";
    }
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/2772/" target="_blank">AcWing 2770. 方格取数</a> code</summary>

```cpp
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

const int N=1e3+10;

int g[N][N];
LL dp[N][N][2];
int n, m;

int main(){
    //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    memset(g, -0x3f, sizeof g);
    memset(dp, -0x3f, sizeof dp);
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d", &g[i][j]);

    dp[1][1][0]=dp[1][1][1]=g[1][1];
    for(int i=2; i<=n; i++) // 用手导第一列
        dp[i][1][0] = dp[i][1][1] = dp[i-1][1][0] + g[i][1];
    //for(int i=n-1; i>=1; i--)
    //    dp[i][1][1] = dp[i+1][1][1] + g[i][1];
    //for(int i=1; i<=n; i++)
    //    dp[i][1][0] = dp[i][1][1] = max(dp[i][1][0], dp[i][1][1]);

    for(int j=2; j<=m; j++){
        for(int i=1; i<=n; i++) // 从上到下，从左边来，从上面来
            dp[i][j][0] = max(dp[i][j-1][0], dp[i-1][j][0]) + g[i][j];

        for(int i=n; i>=1; i--) // 从下到上，从左边来，从下面来
            dp[i][j][1] = max(dp[i][j-1][1], dp[i+1][j][1]) + g[i][j];
        
        for(int i=1; i<=n; i++)
            dp[i][j][0] = dp[i][j][1] = max(dp[i][j][0], dp[i][j][1]);
    }

    cout<<dp[n][m][1];
    return 0;
}
```
</details>

---

# 2019

<details><summary><a href="https://www.acwing.com/problem/content/1163/" target="_blank">AcWing 1161. 数字游戏</a> code</summary>

```cpp
#include <iostream>
using namespace std;

int main(){
    char c; 
    int ans;
    while(cin>>c)
        if(c=='1')
            ans++;
    cout<<ans;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/1164/" target="_blank">AcWing 1162. 公交换乘</a> code</summary>

```cpp
#pragma G++ optimize("Ofast", 2, 3)
#define fst first
#define sed second
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
int n, ans;

int main(){
    cin>>n;
    
    vector<PII> q;
    
    for(int i=1; i<=n; i++){
        int x, y, z; cin>>x>>y>>z;
        ans+=y;
        
        if(x==0)    // 获得券
            q.push_back({y, z});
        else{       // 找券
            
            while( q.size() && z - q[0].sed > 45 )
                q.erase(q.begin(), q.begin()+1);    // 清空过期券
            
            for(int j=0; j<q.size(); j++)
                if( q[j].fst >= y ){
                    q.erase(q.begin()+j, q.begin()+j+1);
                    ans-=y;
                    break;
                }            
        }
    }
    
    cout<<ans;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/description/1165/" target="_blank">AcWing 1163. 纪念品</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=110;

int dp[10010];  // 第 i+1 天, 可以增加的金币的最大值
int w[N][N];    // 第 i 天, 第 j 种物品的价值

int t, n, m;    // 天数, 纪念品数量, 金币数量

int main(){
    cin>>t>>n>>m;
    for(int i=1; i<=t; i++)
        for(int j=1; j<=n; j++)
            scanf("%d", &w[i][j]);
    
    for(int i=1; i<=t-1; i++){      // 枚举天数
        memset(dp, 0, sizeof dp);
        
        for(int j=1; j<=n; j++)     // 枚举商品
            for(int k=w[i][j]; k<=m; k++)   // 枚举钱(当前这个商品的价值 到 我身上的所有钱)
                dp[k] = max(dp[k], dp[k-w[i][j]] + w[i+1][j] - w[i][j] );
        // 枚举商品是为了考虑所有可能购买或出售的纪念品
        // 枚举钱是为了考虑所有可能的购买或出售纪念品的组合
        // 
        // 通过枚举商品和钱, 我们可以找到在当前这一天
        // 使用当前拥有的金币, 可以获得的最大收益
        // 然后, 我们可以使用这个最大收益来更新dp数组
        
        m += dp[m];
    }
    
    cout<<m;
    
    return 0;
}
```
</details>

---

# 2018


<details><summary><a href="https://www.acwing.com/problem/content/475/" target="_blank">AcWing 473. 标题统计</a> code</summary>

```cpp
#include <iostream>
using namespace std;

char c;
int ans;

int main(){
    while(cin>>c)
        if(c>='A' && c<='Z' || c>='a' && c<='z' || c>='0' && c<='9')
            ans++;
    cout<<ans;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/476/" target="_blank">AcWing 474. 龙虎斗</a> code</summary>

```cpp
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

LL a[N];   // 兵营
LL dragon, tiger, n;
LL m, s1, p1, s2, p2, cha;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    cin >> m >> p1 >> s1 >> s2;
    a[p1] += s1;

    for (int i = 1; i <= n; i++)
        if (i < m)
            dragon += (m - i) * a[i];
        else if (i > m)
            tiger += (i - m) * a[i];

    p2 = m;
    cha = llabs(dragon - tiger);

	for (int i = 1; i <= n; i++){
		if (i < m && llabs(dragon - tiger + s2 * (m - i)) < cha ) 
	        p2 = i, cha = llabs(dragon - tiger + s2 * (m - i));
		if (i > m && llabs(dragon - tiger - s2 * (i - m)) < cha)
			p2 = i, cha = llabs(dragon - tiger - s2 * (i - m));
	}
    cout << p2;

    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/description/478/" target="_blank">AcWing 476. 对称二叉树</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=1e6+10;

int l[N], r[N], v[N], cnt[N];   // 每个节点的子树,权,子树数量
int n;

void dfs(int i){ // 计算以 i 为节点子树数量
    if(l[i]) dfs(l[i]);
    if(r[i]) dfs(r[i]);
    cnt[i] = cnt[l[i]] + cnt[r[i]] + 1;
}

bool ck(int i, int j){ // 检查 i,j 是不是对称
    if(v[i] != v[j] || cnt[i] != cnt[j]) return 0;  // 权,树不同
    if(i == 0 && j == 0) return 1;  // 两边都是空树
    if(ck(l[i], r[j]) && ck(r[i], l[j])) return 1;
    return 0;   
}

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", v+i);
    for(int i=1; i<=n; i++){
        int a, b; scanf("%d%d", &a, &b);
        l[i] = (a==-1)?0:a, r[i] = (b==-1)?0:b;
    }
    dfs(1);
    
    for(int i=1; i<=n; i++)
        if( ck(l[i], r[i]) )    // 检查以 i 为根的子树
            v[0] = max(v[0], cnt[i]);
    
    cout<<v[0];
    
    return 0;
}
```
</details>

---

# 2017


<details><summary><a href="https://www.acwing.com/problem/content/473/" target="_blank">AcWing 471. 棋盘</a> code</summary>

```cpp
```
</details>


---

# 2015

<details><summary><a href="https://www.acwing.com/problem/content/description/463/" target="_blank">AcWing 461. 金币</a> code</summary>

```cpp
#include <iostream>
using namespace std;

int k, ans, one=1, x=1, y=1;

int main(){
    cin>>k;
    for(int i=1; i<=k; i++, x++){
        ans+=one;
        if(x==y){
            x=0;
            y++;
            one++;
        }
    }
    cout<<ans;
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/464/" target="_blank">AcWing 462. 扫雷游戏</a> code</summary><br>

**大意**

给定一个 $n*m$ 的矩阵，每个点只有两种状态
* 地雷 `*`
* 未知 `?`

求每个 `?` 周围（上下左右，左上左下右上右下）的地雷数量

**思路**

1. 遍历每个点，如果是地雷，输出 `*`，否则输出周围的地雷数量

2. 对于每个未知的点，遍历其周围的8个点，如果是地雷，那么这个点的地雷数量加一


```cpp
#include <iostream>
using namespace std;

const int N=1e2+10;

int dxy[8][2]={ {-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1} };

char g[N][N];
int res[N][N];
int n, m;

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            cin>>g[i][j];
            
    for(int i=1; i<=n; i++, cout<<"\n")
        for(int j=1; j<=m; j++){
            for(int k=0; k<8; k++)
                res[i][j] += g[ i+dxy[k][0] ][ j+dxy[k][1] ]=='*';
        
            if(g[i][j]=='*')
                cout<<'*';
            else 
                cout<<res[i][j];
        }
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/465/" target="_blank">AcWing 463. 求和</a> code</summary><br>

**大意**

给定一个长度为 $n$ 的数组，数组中每个元素有两个值，一个编号

* 数字。为方便，叫做 $num$
* 颜色。为方便，叫做 $cor$
* 编号。从 $1$ 开始单调递增

数字与颜色都是 $1$ 到 $1e5$ 的整数，
换言之，我们有颜色1，颜色2，颜色3...

定义一个三元组 $(x, y, z)$，满足

* $x < y < z$
* $y - x = z - y$ 即 $x + z = 2y$
* $cor[x] = cor[z]$

此三元组的分数为

* $(x+z) * (num[x] + num[z])$

求所有合法三元组的分数和

**思路**

1. 由于 $x+z = 2y$，可知 $x$ 与 $z$ 奇偶性相同，
因此，对于所有的 $x < z$，$y$ 肯定存在

2. 由于都与 $y$ 无关，问题转换为：
    * $x < z$，其中 $x$ 与 $z$ 奇偶性相同
    * $cor[x] = cor[z]$

3. 因为需要颜色相同，我们不妨将颜色相同的拉出来单独考虑。样例：
    蓝色（颜色 2）：$num[1]=5,num[2]=5,num[5]=2$
    * 奇数 $1,5$，分数为 $(1+5)*(5+2) = 42$
    * 偶数 无

    红色（颜色 3）：$num[3]=3,num[4]=2,num[6]=2$
    * 奇数 无
    * 偶数 $4,6$，分数为 $(4+6)*(2+2) = 40$
    
4. **重点**
    1. 假设，同奇偶性存在下面三个数：$num[a], num[b], num[c]$，其中 $a < b < c$
       那么，此颜色，此奇偶性下，分数为
        $(a+b)*(num[a]+num[b]) +$
        $(a+c)*(num[a]+num[c]) +$
        $(b+c)*(num[b]+num[c]) $

        化简：

        **$(a*num[a] + b*num[b] + c*num[c]) * 1 + $**
        **$(a+b+c)*(num[a]+num[b]+num[c])$**


    2. 假设，同奇偶性存在下面四个数：$num[a], num[b], num[c], num[d]$，其中 $a < b < c < d$
       那么，此颜色，此奇偶性下，分数为
        $(a+b)*(num[a]+num[b]) +$
        $(a+c)*(num[a]+num[c]) +$
        $(a+d)*(num[a]+num[d]) +$
        $(b+c)*(num[b]+num[c]) +$
        $(b+d)*(num[b]+num[d]) +$
        $(c+d)*(num[c]+num[d]) $
        化简：
        **$(a*num[a] + b*num[b] + c*num[c] + d*num[d]) * 2 + $**
        **$(a+b+c+d)*(num[a]+num[b]+num[c]+num[d])$**

5. 因此，对于同颜色，同奇偶性，有：
    

**$sum = (n-2) * \sum_{i=1}^{n} (i*num[i]) + \sum_{i=1}^{n} i * \sum_{i=1}^{n} num[i]$**


```cpp
#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e5+10;
const int MOD = 10007;

int num[N], cor[N]; // 数字和颜色
vector<PII> a[N][2];// 同奇同色
int n, m;

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", num+i);
    for(int i=1; i<=n; i++) scanf("%d", cor+i);
    
    for(int i=1; i<=n; i++)
        a[ cor[i] ][ i&1 ].push_back({i, num[i]});
    
    LL ans=0;
    for(auto c: a)
    for(int k=0; k<=1; k++)
        if(c[k].size()>=2){
            LL one=0, two=0, thr=0;
            for(auto &[i,j]: c[k]){
                one = (one + ((LL)i*j) % MOD) % MOD;
                two = (two + i) % MOD;
                thr = (thr + j) % MOD;
            }
            ans += (one * (c[k].size()-2)) + (two * thr);
            ans %= MOD;
        }
    
    cout<<ans%MOD;
    
    return 0;
}
```
</details>


---

# 2014

<details><summary><a href="https://www.acwing.com/problem/content/description/459/" target="_blank">Acwing 457. 珠心算测验</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=110;

int n, res;
int a[N];   // 是否有这个数
bool st[20010]; // 是否能算出来

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
            st[ a[i]+a[j] ] = 1;
    for(int i=1; i<=n; i++)
        if(st[a[i]]) res++;
    cout<<res;
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/460/" target="_blank">Acwing 458. 比例简化</a> code</summary><br>

**大意**

给定 $1$ 个分数 $A/B$ 和 $L$，求出一个分数 $A_1/B_1$，使得 $A1_/B_1$ 是一个最简分数，满足：
* $A_1 <= L$ 且 $B_1 <= L$。
* $A_1/B_1 >= A/B$。
* $A_1/B_1 - A/B$ 尽可能小。 


**思路**

1. 由于 $L$ 很小，我们可以枚举 $A_1$ 和 $B_1$，然后再判断是否满足条件。


```cpp
#include <iostream>
using namespace std;

int A, B, L;
int A1, B1;
int A2=999, B2=1;

int gcd(int a, int b){
    return b ? gcd(b, a%b) : a;
}

int main(){
    cin>>A>>B>>L;
    for(A1=1; A1<=L; A1++)  // 枚举
    for(B1=1; B1<=L; B1++)
        if(A1*B >= A*B1)    // 满足A1/B1 >= A/B
        if(gcd(A1, B1)==1)  // 两数互质
        if(A1*B2 < A2*B1)   // 更小
            A2=A1, B2=B1;
    cout<<A2<<" "<<B2;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/461/" target="_blank">AcWing 459. 螺旋矩阵</a> code</summary><br>

**大意**

给定一个螺旋矩阵，求出某个位置的值。

**思路**

1. 可以发现螺旋矩阵以下几个特点：
    1. 每一圈数的个数都是 $n*4-4$，$n$ 是当前圈的边长。
        这意味着每一圈，数字减少 $8$ 个。
    2. 每一圈的左上角的数字都是最小的。

2. 故，我们可以先求出这个位置在第几圈，然后再求出这个位置具体的值。

假设，左上角数字 $v$，边长 $n$，左上角点 `i,i`，右下角点 `j,j`，寻找点 `x,y`
* 若 `x,y` 在上边，那么 `v + y-i` 就是答案。`y-i` 是横向的距离。
* 若 `x,y` 在右边，那么 `v + n-1 + x-i` 就是答案。`n-1` 是上边的长度，`x-i` 是纵向的距离。
* 若 `x,y` 在下边，那么 `v + n*2-2 + j-y` 就是答案。`n*2-2` 是上边和右边的长度，`j-y` 是横向的距离。
* 若 `x,y` 在左边，那么 `v + n*3-3 + j-x` 就是答案。`n*3-3` 是上边、右边和下边的长度，`j-x` 是纵向的距离。


```cpp
#include <iostream>
using namespace std;

typedef long long LL;

int n, x, y, ans=1;

int main(){
    cin>>n>>x>>y;
    // ans 是左上角的数字，n 是当前圈的边长
    // i 是左上角的横纵坐标
    // j 是右下角的横纵坐标
    for(int i=1, j=n; i<=j; i++, j--, ans+=n*4-4, n-=2)
        if(x==i){      // 上
            cout<<ans+(y-i);
            break;
        }
        else if(x==j){ // 下
            cout<<ans+(j-y)+n*2-2;
            break;
        }
        else if(y==i){ // 左
            cout<<ans+(j-x)+n*3-3;
            break;
        }
        else if(y==j){ // 右
            cout<<ans+(x-i)+n-1;
            break;
        } 
    
    return 0;
}
```
</details>

---

# 2013

<details><summary><a href="https://www.acwing.com/problem/content/455/" target="_blank">Acwing 453. 计数问题</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=1e6+10;

int n, X, ans;

int calc(int i){   // 计算i中有几个X
    int res=0;
    while(i){
        if(i%10==X) res++;
        i/=10;
    }
    return res;
}

int main(){
    cin>>n>>X;
    for(int i=1; i<=n; i++)
        ans+=calc(i);
    cout<<ans;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/456/" target="_blank">Acwing 454. 表达式求值</a> code</summary><br>

**大意**

给定一个只含 `[0, 2^31-1]` `+` `*` 的表达式，求出它的值。

**思路**

如果表达式中有多种运算符，显然用栈来做是最好的。但此题只有 `+` `*` 两种运算符。

1. 我们从第一个数开始考虑，首先接受一个数 `tmp`，然后循环接受一个运算符 `ch`，和数 `num`。
    * 如果 `ch` 为 `+`，那么左边的数 `tmp` 就可以加到答案上了，因为 `tmp` 不会影响后面的运算。
      将 `num` 赋值给 `tmp`，继续循环。
    * 如果 `ch` 为 `*`，那么 `tmp` 就要乘上 `num`，将 `tmp*num` 看作一个整体。
      将 `tmp*num` 赋值给 `tmp`，继续循环。 



```cpp
#include <iostream>
using namespace std;

typedef long long LL;

const int N=1;

LL ans, tmp, num;
char ch;

int main(){
    cin>>tmp;
    while(cin>>ch>>num)
        if(ch=='+')
            ans+=tmp,
            tmp=num;
        else
            tmp=(tmp*num)%10000;
    cout<<(ans+tmp)%10000;
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/457/" target="_blank">AcWing 455. 小朋友的数字</a> code</summary><br>

**大意**

给定一个数组 $a[n]$，通过这个数组可以得到一个数组 $b[n]$，
$b[i]$ 表示 $a[1] \sim a[i]$ 中最大的子序列和。

* 样例
    $a[n]$ = `1` `2` `3` `4` `5`
    $b[n]$ = `1` `3` `6` `10` `15`

* 更具有一般性的样例
    $a[n]$ = `1` `-2` `3` `-4` `5`
    $b[n]$ = `1` `-1` `3` `-1` `5`

* 更具有一般性的样例
    $a[n]$ = `9` `-2` `3` `-4` `2`
    $b[n]$ = `9` `7` `10` `6` `8`

通过 $b[n]$ 可以得到特征值数组，$b[i] = max(b[j])$，其中 $j ∈ [1, i]$。

通过 $a[n]$ 和 $b[n]$ 可以得到一个新的数组 $c[n]$，
$c[i] = max(c[j]+b[j])$，其中 $j ∈ [1, i)$，
特别的，$c[1] = b[1]$。

求最大的 $c[i]$。

**思路**

1. 求出 $b[n]$。就是在 $a[n]$ 中求最大子序列和。
   $i=1$ 时，$b[1] = a[1]$
    $i>1$ 时，$b[i] = max(b[i-1]+a[i], a[i])$

2. 求出 特征数组 $b[n]$，即
    $b[i] = max(b[j])$，其中 $j ∈ [1, i]$。

3. 求出 $c[n]$，即
    $c[i] = max(c[j]+b[j])$，其中 $j ∈ [1, i)$，
    特别的，$c[1] = b[1]$。

4. 求出最大的 $c[i]$。

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

const int N=1e6+10;

LL n, p;
LL a[N], b[N];
__int128 c[N];

int main(){
    cin>>n>>p;
    for(int i=1; i<=n; i++) scanf("%lld", &a[i]);
    
    b[1]=a[1];
    for(int i=2; i<=n; i++) b[i] = max(b[i-1]+a[i], a[i]);
    for(int i=2; i<=n; i++) b[i] = max(b[i-1], b[i]);
    
    c[1]=b[1];
    __int128 mmax = c[1]+b[1];
    for(int i=2; i<=n; i++){
        c[i] = mmax;
        mmax = max(mmax, c[i] + b[i]);
    }
    
    mmax = c[1];
    for(int i=2; i<=n; i++) mmax=max(mmax, c[i]);

    printf("%lld", mmax%p);
    
    /* 
    cout<<"\n";
    for(int i=1; i<=n; i++) printf("%12lld", a[i]); cout<<"\n";
    for(int i=1; i<=n; i++) printf("%12lld", b[i]); cout<<"\n";
    for(int i=1; i<=n; i++) printf("%12lld", c[i]); cout<<"\n";
    */
    
    return 0;
}
```
</details>














<br><br><br><br><br><br><br><br>

# AK CSPJ

---

<center>根据 <a href=https://noi.ccf.org.cn/xw/2023-03-15/788060.shtml>NOI大纲</a> 制定的30天训练计划, 剑指 CSP-J 一等奖!</center>




### 基础巩固七天乐

> 前7天的目标是 csp-j2 的第一题，大量基础题，保证第一题的正确性和解题的速度

* 第 1 天 [顺序结构](/base/algorithm/Content/0%20入门/顺序结构.html) 算法竞赛及OJ的概念
* 第 2 天 [分支结构](/base/algorithm/Content/0%20入门/分支结构.html) if
* 第 3 天 [循环结构](/base/algorithm/Content/0%20入门/循环结构.html) 循环优化（特判）、嵌套循环
* 第 4 天 [数组](/base/algorithm/Content/0%20入门/数组.html) 一维数组、vector等
* 第 5 天 [字符串](/base/algorithm/Content/0%20入门/字符串.html) 字符串处理及简单技巧 string <-> int
* 第 6 天 [函数与结构体](/base/algorithm/Content/0%20入门/函数.html) pair及利用函数简化解题思路
* 第 7 天 [枚举与模拟](/base/algorithm/Content/1%20基础/模拟.html) 各种常见的问题

> 通过前7天的题海战术，对暴力和模拟已经有了较为深刻的了解
> 一般而言，已经能写出第二题的暴力做法了

### 两周专题突破

> 8-15天的目标是 csp-j2 的第二题
> 掌握简单算法及数据结构，在暴力的基础上进行优化，第二题轻松拿下

* 第 8 天 [高精度](/base/algorithm/Content/5%20数学/数的运算.html) 进制转换
* 第 9 天 [二(N)叉树](/base/algorithm/Content/7%20图论/二叉树.html) 简单树及特殊树
* 第 10 天 [递归与递推](/base/algorithm/Content/1%20基础/递归.html)
* 第 11 天 [DFS](/base/algorithm/Content/2%20搜索/DFS.html) 暴搜思想
* 第 12 天 [BFS](/base/algorithm/Content/2%20搜索/BFS.html) 暴搜最优及洪水覆盖 
* 第 13 天 [二分](/base/algorithm/Content/1%20基础/二分.html) 一种常见优化
* 第 14 天 [前缀和与差分](/base/algorithm/Content/1%20基础/前缀和.html)
* 第 15 天 [素数筛法](/base/algorithm/Content/5%20数学/质数.html)

> 16-21天的目标是 csp-j2 的第三题和第四题
> 或许一时想不出标程解法，但暴力算法未尝不能一试

* 第 16 天 [图论 单源最短路]() 邻接矩阵 及 邻接表
* 第 17 天 [图论 多源最短路]()
* 第 18 天 [DP 数字三角形模型]() 
* 第 19 天 [DP 子序列模型]()
* 第 20 天 [DP 背包模型]()
* 第 21 天 [DP 状态机模型]()

### 历届真题回顾

* 每日一套USACO CU或CCF-J

---