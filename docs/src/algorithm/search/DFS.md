## Template

### 组合

* 从 $n$ 个元素中选出 $k$ 个，不考虑顺序

    > $\{1, 2\}$ 与 $\{2, 1\}$ 视为 **同一组合**  

* 数量：$C_{n}^{k} = \frac{n!}{k! (n-k)!} = C_{n}^{n-k}$

<details><summary> dfs 求组合 <a href=""></a></summary>

```cpp
#include <iostream>
using namespace std;

int n, k;               // 从 n 个选 k 个
char a[9];
bool st[9];

void dfs(int u, int m){ // 选到 u 个，选了 m 个
    // 答案
    if(m == k){
        for(int i=1; i<=n; i++)
            if(st[i] == 1)
                cout << a[i] << " ";
        cout << "\n";
        return ;
    }

    // 边界
    if(u > n){
        return ;
    }

    // 情况 1，选择
    st[u] = 1;
    dfs(u+1, m+1);

    // 情况 2, 不选择
    st[u] = 0;
    dfs(u+1, m);
}

int main(){
    cin >> n >> k;
    for(int i=1; i<=n; i++) a[i] = 'a' + i - 1;
    dfs(1, 0);
    return 0;
}
```
</details>

<br>


### 排列

* 从 $n$ 和元素中选出 $k$ 个，并考虑顺序

    > $\{1, 2\}$ 与 $\{2, 1\}$ 视为 **不同排序**

* 数量：$A_{n}^{k} = \frac{n!}{(n-k)!}$

<details><summary> dfs 求排列 <a href=""></a></summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N=2e5+10;

int n, k;
char a[N];
bool st[N];

vector<char> ans;

void dfs(){
    if(ans.size() == k){
        for(auto i: ans)
            cout << i << " ";
        cout << "\n";
        return ;
    }

    for(int i=1; i<=n; i++)
        if(st[i] == 0){
            st[i] = 1;
            ans.push_back(a[i]);
            dfs();

            st[i] = 0;
            ans.pop_back();
        }
}

int main(){
    cin >> n >> k;
    for(int i=1; i<=n; i++) a[i] = 'a' + i - 1;
    dfs();
    return 0;
}
```

</details>


<br>

### 全排列

* 从 $n$ 和元素中选出 $n$ 个，并考虑顺序

    > $\{1, 2, 3\}, \{1, 3, 2\}, \{2, 1, 3\}, \{2, 3, 1\}, \{3, 1, 2\}, \{3, 2, 1\}$

* 数量：$n!$

<details><summary><a href="" target="_blank"></a>dfs 求全排列</summary>

```cpp

```
</details>

<br>

### 排列组合

* 从 $n$ 和元素中选出 $k$ 个，并考虑顺序，并允许重复

    > $\{1, 1\}, \{1, 2\}, \{2, 1\}, \{2, 2\},$

* 数量：$n^k$




<br>

----


##### 如何表示，从上一层到下一层的多条路径？

<details><summary><a href="https://www.acwing.com/problem/content/3505/" target="_blank">AcWing 3502. 不同路径数</a> code</summary>

> `每次可以沿上下左右四个方向前进一步`意味着对于每个节点, 我们有四种选择
> 在代码中, 我们应该如何实现, 从 `{x,y}` -> `{x-1, y}` 这个点的操作呢
> 喜闻乐见的一种方式就是直接x-1, 但在比赛中, 我们常常通过一个 `dx[4], dy[4]` 数组来实现
> 可以模拟一下 `dx[4]={-1,0,1,0}, dy[4]={0,-1,0,1}`
> `nx = x + dx[0]`
> `ny = y + dy[0]` 
> 此时, 上下左右的转移就被我们写进了循环中, 大大减少了重复代码量

```cpp
#include <iostream>
#include <set>
using namespace std;

const int N=10;

int dxy[4][2]={ {-1,0}, {1,0}, {0,-1}, {0,1} };

set<int> cnt; 
int mp[N][N];
int n, m, k, res;

void dfs(int x, int y, int w){
    if(w > k){
        cnt.insert(res);
        return ;
    }
    
    for(int i=0; i<4; i++){
        int nx = x + dxy[i][0];
        int ny = y + dxy[i][1];
        
        if(nx>=1 && ny>=1 && nx<=n && ny<=m){
            res = res*10 + mp[nx][ny];   
            dfs(nx, ny, w+1);
            res /= 10;
        }
    }
}

int main(){
    cin>>n>>m>>k;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            scanf("%d", &mp[i][j]);
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            dfs(i, j, 0);   // 位置以及当前位数
    
    cout<<cnt.size();
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/1116/" target="_blank">AcWing 1114. 棋盘问题</a> code</summary>

> 我们首先思考一下, 求方案数, 肯定是不能重复的
> 那么我们可以再回想一下, dfs的搜索方案会重复吗? 我们上一道一题的去重是为什么?
> 思考完, 考虑一下这道题如何解决(自己尝试写一个, 先把输入写了), 他的关键之处在于`要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列`
> 画一个4*4的图就好理解了, 直接平板上画
> 这时候, 就可以引入另外一个东西了`used`数组

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N = 10;

char a[N][N];
bool x[N], y[N];  // 该行, 列有没有使用  
int n, k, ans;

void dfs(int i, int w) {
    if (w == k) {
        ans++;
        return;
    }
    if (i > n) return;
    for (int j = 1; j <= n; j++)
        if (!x[i] && !y[j] && a[i][j] == '#') {
            x[i] = y[j] = 1;
            dfs(i + 1, w + 1);
            x[i] = y[j] = 0;
        }
    dfs(i + 1, w);

    return;
}

void solve() {
    while (cin >> n >> k) {
        if (n == -1 && k == -1) return;
        memset(x, 0, sizeof x);
        memset(y, 0, sizeof y);
        ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> a[i][j];
        dfs(1, 0);
        cout << ans << "\n";
    }
    return;
}

int main() {
    solve();
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/description/118/" target="_blank">AcWing 116. 飞行员兄弟</a> code</summary>

```cpp
#define fst first
#define sed second

#include <iostream>
using namespace std;

typedef pair<int, int> PII;

int g[5][5]; // 需要将所有值变为 0  

PII step[100], ans[100];

bool check(){
    for(int i=1; i<=4; i++)
        for(int j=1; j<=4; j++)
            if(g[i][j])
                return 0;
    return 1;
}

void updata(){
    if(ans[0].fst < step[0].fst) return ;
    
    ans[0].fst=step[0].fst;
    for(int i=1; i<=step[0].fst; i++)
        ans[i].fst = step[i].fst,
        ans[i].sed = step[i].sed;
}

// 改变该点状态
void change(int x, int y){
    for(int i=1; i<=4; i++)
        g[x][i]^=1, g[i][y]^=1;
    g[x][y]^=1;
}

void dfs(int x, int y){
    
    // 到达边界
    if(x>4){
        // 如果结果合法（是解，但非最优）
        if ( check() )
        // 更新（如果是更优解，就更新）
            updata();
        // 结束
        return ;    
    }
    
    // 改变当前点状态
    change(x, y);
    // 更新答案
    step[0].fst++;
    step[ step[0].fst ] = {x, y};
    
    if(y==4)
        dfs(x+1, 1);
    else
        dfs(x, y+1);
    
    // 恢复现场
    change(x, y);
    step[0].fst--;
    
    if(y==4)
        dfs(x+1, 1);
    else
        dfs(x, y+1);
}

int main(){
    // 获取地图
    for(int i=1; i<=4; i++){
    for(int j=1; j<=4; j++){
        char c;
        scanf("%c", &c);
        if(c=='+') g[i][j]=1;
    }
    getchar();
    }
    
    ans[0].fst=99;
    
    // 枚举每个点的状态
    dfs(1,1);
    
    cout<<ans[0].fst<<endl;
    for(int i=1; i<=ans[0].fst; i++)
        cout<<ans[i].fst<<" "<<ans[i].sed<<endl;
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P1219" target="_blank">Luogu P1219 [USACO1.5]八皇后 Checker Challenge
</a> code</summary>

> 此题在上一题的基础上加入斜线

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N=50;

int cnt=0;  // 记录解的个数
vector<int> ans;
bool x[N], y[N], r[N], l[N];
int n;

void dfs(int c){    // 第几层
    if(ans.size() == n){
        if(++cnt<=3){
            for(auto i: ans) cout<<i<<" ";
            cout<<"\n";
        }
        return ;
    }

    for(int i=1; i<=n; i++)
        if(!x[c] && !y[i] && !r[i-c+10] && !l[i+c]){
            x[c] =   y[i] =   r[i-c+10] =   l[i+c] = 1;
            ans.push_back(i);
            dfs(c+1);
            x[c] =   y[i] =   r[i-c+10] =   l[i+c] = 0;
            ans.pop_back();
        }
}

int main(){
    cin>>n;
    dfs(1);
    cout<<cnt;
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/description/1623/" target="_blank">Acwing 1621. N 皇后问题</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=3000;

int x[N], y[N], r[N], l[N], a[N];

bool add(int i, int j){
    if(++x[i]!=1) return 0;
    if(++y[j]!=1) return 0; 
    if(++r[j-i+1000]!=1) return 0;
    if(++l[i+j]!=1) return 0;
    return 1;
}

void solve(){
    int n; cin>>n;
    memset(x, 0, sizeof x);
    memset(y, 0, sizeof y);
    memset(r, 0, sizeof r);
    memset(l, 0, sizeof l);
    for(int i=1; i<=n; i++) scanf("%d", a+i);

    for(int i=1; i<=n; i++)
        if( !add(i, a[i]) ){
            puts("NO");
            return ;
        }
    puts("YES");
    return ;
}

int main(){
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/4221/" target="_blank">Acwing 4218. 翻转</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=20;

int g[N][N];
int bk[N][N];
int m, n;
string ans;
int anscnt=0x3f3f3f3f;

void cg(int x, int y){
    g[x][y] = g[x][y] ? 0: 1;
    g[x-1][y] = g[x-1][y] ? 0: 1;
    g[x+1][y] = g[x+1][y] ? 0: 1;
    g[x][y-1] = g[x][y-1] ? 0: 1;
    g[x][y+1] = g[x][y+1] ? 0: 1;
}

bool ck(){
    for(int j=1; j<=n; j++)
        if(g[m][j]) return 0;
    return 1;
}

void dfs(int u, string res, int cnt){
    if(u>n){
        memcpy(bk, g, sizeof bk);   // 备份一下
        
        for(int i=2; i<=m; i++)
            for(int j=1; j<=n; j++)
                if(g[i-1][j])
                    cg(i, j), res += "1", cnt++;
                else
                    res += "0";
        for(int j=1; j<=n; j++) res += "0";
        
        if(!ck()) {
            memcpy(g, bk, sizeof g);    // 恢复
            return ;
        }
        memcpy(g, bk, sizeof g);    // 恢复
        
        if(cnt < anscnt || ans=="" || res<ans) ans = res, anscnt = cnt; 
        return ;
    }
    
    dfs(u+1, res+"0", cnt);  // 不改变
    
    cg(1,u);  // 改变
    dfs(u+1, res+"1", cnt+1);
    cg(1,u);  // 恢复现场
}

int main(){
    cin>>m>>n;
    
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            scanf("%d", &g[i][j]);
    
    dfs(1, "", 0); 
    
    
    int k=0;
    
    if(ans=="")cout<<"IMPOSSIBLE";
    
    for(int i=1; i<=m; i++, cout<<"\n")
        for(int j=1; j<=n; j++)
            cout<<ans[k++]<<" ";
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/97/" target="_blank">AcWing 95. 费解的开关</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=10;

int dxy[4][2]={ {-1,0}, {1,0}, {0,-1}, {0,1} };

// 地图 地图备份
int g[N][N], backup[N][N];
int ans=0x3f3f3f3f;

bool check(){
    for(int i=0; i<5; i++)
        if(!g[4][i]) return 0;
    return 1;
}

void bf(){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            backup[i][j]=g[i][j];
}

void rbf(){
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            g[i][j]=backup[i][j];
}

void change(int x, int y){
    for(int i=0; i<4; i++){
        int nx=x+dxy[i][0];
        int ny=y+dxy[i][1];
        if(nx<0 || ny<0) continue;
        g[nx][ny]^=1;
    }
    g[x][y]^=1;
}

// w是当前已经改变的次数
void dfs(int u, int w){
    
    if(w > ans) return ;
    
    // 到达边界
    if(u>4){
        // 保存当前地图
        bf();
        // 直接计算下面4层
        for(int i=1; i<5 && w<=6; i++)
            for(int j=0; j<5; j++)
                if(!g[i-1][j])
                    change(i, j), w++;
        
        if(w<=6 && check()) ans=min(ans, w);
        // 恢复回去
        rbf();
        return ;
    }
    
    // 改变
    change(0, u);
    dfs(u+1, w+1);
    change(0, u);
    
    // 不改变
    dfs(u+1, w);
}


int main(){
    int n;
    cin>>n;
    
    while(n--){
        ans=0x3f3f3f3f;
        
        for(int i=0; i<5; i++)
            for(int j=0; j<5; j++){
                scanf("%1d", &g[i][j]);
                backup[i][j]=g[i][j];
            }
        
        // 第一排的第几个点
        // 已经改变了几次
        dfs(0, 0);
        
        if(ans==0x3f3f3f3f)
            puts("-1");
        else
            cout<<ans<<"\n";
    }
    
    return 0;
}
```
</details>

---

## 一般DFS


<details><summary><a href="https://www.luogu.com.cn/problem/P2392" target="_blank">Luogu P2392 kkksc03考前临时抱佛脚</a> code</summary>


kkk 需要做 $4$ 科习题集
$A$ 科共有 $s_1$ 道题目，每道题目的消耗时间分别是 $A_1, A_2, A_3, ..., A_{s_1}$
$B$ 科共有 $s_2$ 道题目，每道题目的消耗时间分别是 $B_1, B_2, B_3, ..., B_{s_2}$
$C$ 科共有 $s_3$ 道题目，每道题目的消耗时间分别是 $C_1, C_2, C_3, ..., C_{s_3}$
$D$ 科共有 $s_4$ 道题目，每道题目的消耗时间分别是 $D_1, D_2, D_3, ..., D_{s_4}$

- kkk 可以同时计算两道题目，kkk 必须一科一科的复习

因此这个条件，**完成复习的最短时间 -> 完成每科的最短时间之和**

具体的，我们现在需要解决，完成 $s_i$ 道题目花费的最短时间

- 最短时间 $>=$  $\lceil 所有时间/2 \rceil$

因此，我们不妨考虑 **做题时间的所有排列**，依次累加到 $res$

当 $res >= \lceil 所有时间/2 \rceil$，$res$ 就是其中的一个可行解

最小的 $res$ 就是最短时间

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=30;

int s[N], a[N], ans=0;

int main(){
    for(int i=1; i<=4; i++) scanf("%d", s+i);

    for(int k=1; k<=4; k++){
        int all = 0;
        for(int j=1; j<=s[k]; j++) scanf("%d", a+j), all += a[j];
        sort(a+1, a+1+s[k]);
        
        int res = 0x3f3f3f3f;
        do{
            int A=0;
            // 在该顺序下, 最小时间花费
            for(int j=1; j<=s[k]; j++){
                A+=a[j];
                if(A>=(all+1)/2 || A>res) break;
            }
            res = min(res, A);
            if(A == (all+1)/2) break;
        }while(next_permutation(a+1, a+1+s[k]));
        
        ans += res;
    }

    cout<<ans;
    return 0;
}
```
</details>

<details><summary><a href="https://www.luogu.com.cn/problem/P1019" target="_blank">Luogu P1019 [NOIP2000 提高组] 单词接龙</a> code</summary>

给定一些单词，将单词连接起来

此时有两个问题

1. 对于单词 $a$ 和 $b$，$b$ 能否接到 $a$ 的后面
    显然，我们只需要截取 $a$ 的后面 $i$ 位，$b$ 的前面 $i$ 位
    如果截取的部分相同，且不等于 $a$ 和 $b$，那么 $b$ 就可以接到 $a$ 后面

2. 对于单词 $a$ 和 $b$，接龙后是什么样子？
    我们已经知道他们相同的部分，那么只需要用 **$a + b剩下的部分$** 就是连接后的串

此时，我们只需要从第一个单词开始，看此单词能够与那些单词连接。然后是第二个单词...

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 21;

int n;
string word[N];
int g[N][N];
int used[N];
int ans;

void dfs(string dragon, int last)
{
    ans = max((int)dragon.size(), ans);

    used[last] ++ ;

    for (int i = 0; i < n; i ++ )
        if (g[last][i] && used[i] < 2)
            dfs(dragon + word[i].substr(g[last][i]), i);

    used[last] -- ;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> word[i];
    char start;
    cin >> start;

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
        {
            string a = word[i], b = word[j];
            for (int k = 1; k < min(a.size(), b.size()); k ++ )
                if (a.substr(a.size() - k, k) == b.substr(0, k))
                {
                    g[i][j] = k;
                    break;
                }
        }

    for (int i = 0; i < n; i ++ )
        if (word[i][0] == start)
            dfs(word[i], i);

    cout << ans << endl;

    return 0;
}
```
</details>