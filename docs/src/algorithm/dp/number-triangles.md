# 数字三角形


## 从搜索到规划

### 数字三角形

<details><summary><a href="https://www.luogu.com.cn/problem/P1216" target="_blank">Luogu P1216 [USACO1.5] [IOI1994]数字三角形 Number Triangles</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=1e3+10;

int n;
int dp[N][N];

int main(){
    memset(dp, -0x3f, sizeof dp);
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
            scanf("%d", &dp[i][j]);
    
    for(int i=2; i<=n; i++)
        for(int j=1; j<=i; j++)
            dp[i][j]=max(dp[i-1][j-1], dp[i-1][j])+dp[i][j];
    
    int ans=-0x3f3f3f3f;
    for(int i=1; i<=n; i++)
        ans=max(ans, dp[n][i]);
    cout<<ans;
    return 0;
}
```
</details>

## 从左上到右下

### 朴素

<details><summary><a href="https://www.acwing.com/problem/content/1017/" target="_blank">AcWing 1015. 摘花生</a> code</summary>

```cpp
#pragma G++ optimize("Ofast")
#include <iostream>
#include <cstring>
using namespace std;

const int N=110;

int dp[N][N];
int R, C;

void solve(){
    cin>>R>>C;
    for(int i=1; i<=R; i++)
        for(int j=1; j<=C; j++)
            cin>>dp[i][j];
    
    for(int i=1; i<=R; i++)
        for(int j=1; j<=C; j++)
            dp[i][j]=max(dp[i-1][j], dp[i][j-1])+dp[i][j];
    
    cout<<dp[R][C]<<"\n";
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    int T; cin>>T; while(T--)
    solve();
    return 0;
}
```
</details>

### 存在障碍

<details><summary><a href="https://www.luogu.com.cn/problem/P1002" target="_blank">Luogu P1002 [NOIP2002 普及组] 过河卒</a> code</summary>

```cpp
#define fst first
#define sed second
#include <iostream>
#include <set> 
using namespace std;

typedef pair<int, int> PII;

const int N = 30;

long long dp[N][N];   // 到达点 i, j 的最短路径
set <PII> H;

int main() {
    PII c, b;   // b是马
    cin >> c.fst >> c.sed >> b.fst >> b.sed;
    b.fst++, b.sed++, c.fst++, c.sed++;

    H.insert({ b.fst, b.sed });
    H.insert({ b.fst - 1, b.sed - 2 });
    H.insert({ b.fst - 2, b.sed - 1 });
    H.insert({ b.fst - 1, b.sed + 2 });
    H.insert({ b.fst - 2, b.sed + 1 });
    H.insert({ b.fst + 1, b.sed - 2 });
    H.insert({ b.fst + 2, b.sed - 1 });
    H.insert({ b.fst + 1, b.sed + 2 });
    H.insert({ b.fst + 2, b.sed + 1 });

    dp[0][1] = 1;

    for (int i = 1; i <= c.fst; i++)
        for (int j = 1; j <= c.sed; j++)
            if (H.count({ i, j }))
                dp[i][j] = 0;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

    cout << dp[c.fst][c.sed];

    return 0;
}
```
</details>

### 存在多种走法

<details><summary><a href="https://www.luogu.com.cn/problem/P7074" target="_blank">Luogu P7074 [CSP-J2020] 方格取数</a> code</summary>

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


### 允许重复走

<a href="https://www.luogu.com.cn/problem/P1004" target="_blank">Luogu P1004 [NOIP2000 提高组] 方格取数</a>

题目大意

1. 嘻嘻

解题思路

1. 如果分两次走，会因为第一次取走的数而影响第二次的取数，没有保证无后效性，因此考虑一次走完

2. 显然，第二次走，也可以看作是左上角到右下角，因此可以理解为两次从左上角到右下角取数

3. 用 $dp[i][j][x][y]$ 表示第一次走到 $(i, j)$，第二次走到 $(x, y)$ 的最大值

4. 如果 $(i, j) = (x, y)$，需要特判，因为只能取一次

<details><summary>code</summary>

```cpp
#include <iostream>
using namespace std;

const int N = 15;

int g[N][N];
int dp[N][N][N][N];
int n;

int main() {
  cin >> n;
  while (1) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (a == b && a == c && a == 0)
      break;
    g[a][b] = c;
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int x = 1; x <= n; x++)
        for (int y = 1; y <= n; y++) {

          int t = (i == x && j == y) ? g[i][y] : g[i][j] + g[x][y];

          dp[i][j][x][y] = max(dp[i][j][x][y], dp[i - 1][j][x - 1][y] + t);
          dp[i][j][x][y] = max(dp[i][j][x][y], dp[i - 1][j][x][y - 1] + t);
          dp[i][j][x][y] = max(dp[i][j][x][y], dp[i][j - 1][x - 1][y] + t);
          dp[i][j][x][y] = max(dp[i][j][x][y], dp[i][j - 1][x][y - 1] + t);
        }

  cout << dp[n][n][n][n];
  return 0;
}
```

</details>

### 重复走的优化

<details><summary><a href="https://www.luogu.com.cn/problem/P1006" target="_blank">Luogu P1006 [NOIP2008 提高组] 传纸条</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60;

int g[N][N];
int dp[N*2][N][N];
// 第一维存总的步数
// 第二维存第一次走的纵向距离，那么横向距离就是k-x
// 第三维存第二次的，同理

int n,m;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d", &g[i][j]);

    for(int k=2;k<=n+m;k++)
        for(int i=1;i<k&&i<=n;i++)
            for(int j=1;j< k&&j<=n;j++){
                
                int v      = g[i][k-i];
                if(i!=j) v+= g[j][k-j];

                dp[k][i][j] = max(dp[k][i][j], v + dp[k-1][i][j]);
                dp[k][i][j] = max(dp[k][i][j], v + dp[k-1][i][j-1]);
                dp[k][i][j] = max(dp[k][i][j], v + dp[k-1][i-1][j]);
                dp[k][i][j] = max(dp[k][i][j], v + dp[k-1][i-1][j-1]);
            }

    cout<<dp[n+m][n][n]<<endl;

    return 0;
}
```
</details>