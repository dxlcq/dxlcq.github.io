## LIS 最长上升子序列



**模版**

* 时间复杂度：$O(n)$，主要是因为循环

* 空间复杂度：$O(n)$，主要是因为数组


```cpp
// Longest Increasing Subsequence

```

<br>

### 朴素

<a href="https://www.luogu.com.cn/problem/B3637" target="_blank">Luogu B3637 最长上升子序列</a>

题目大意

1. 嘻嘻

解题思路

2. 嘻嘻

<details><summary>code</summary>

```cpp
#include <iostream>
using namespace std;

const int N = 5e3 + 10;

int a[N], dp[N];  // dp[i] 以 a[i] 作为结尾的子序列长度
int n;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) {
    dp[i] = 1;
    for (int j = 1; j < i; j++) {  // a[i] 与 a[j] 比较
      if (a[i] > a[j]) dp[i] = max(dp[i], dp[j] + 1);
    }
    dp[0] = max(dp[0], dp[i]);
  }
  cout << dp[0];
  return 0;
}
```

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=1e6+10;
int a[N];  
int dp[N]; // 长度为 i 结尾的最长子序列，结尾是dp[i]

int main(){
    int n;
    cin>>n;
    for(int i=1; i<=n; i++) 
        scanf("%d", &a[i]);
    
    dp[1]=a[1]; // 长度为1的子序列，结尾是第一个数
    int res=1;  // 当前最长子序列长度为 1
    
    for(int i=2; i<=n; i++)
        if(a[i]>dp[res])    // 如果 下个数 比 结尾大，子序列长度增加
            dp[++res]=a[i];
        else                // 反之，这个数可以更新更短的序列结尾
            *lower_bound(dp+1, dp+1+res, a[i])=a[i];
    
    cout<<res;
    
    return 0;
}
```

</details>

<br>


<details><summary><a href="https://www.luogu.com.cn/problem/T285024" target="_blank">Luogu T285024 最大上升子序列和</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=1e4+10;

int a[N], dp[N];
int n;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++){
        dp[i]=a[i]; // 和
        for(int j=1; j<i; j++)
            if( a[i] > a[j] )
                dp[i] = max(dp[i], dp[j] + a[i]);   // 和
            *dp = max(*dp, dp[i]);
            
    }
    cout<<(*dp);

    return 0;
}
```
</details>


<details><summary><a href="https://www.luogu.com.cn/problem/U234151" target="_blank">Luogu U234151 怪盗基德的滑翔翼</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=1e2+10;

int a[N], dp[N];
int n;

void solve(){
    memset(a, 0, sizeof a);
    memset(dp, 0, sizeof dp);
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", a+i);

    for(int i=1; i<=n; i++){
        dp[i]=1;
        for(int j=1; j<i; j++)
            if( a[i] < a[j] )
                dp[i] = max(dp[i], dp[j]+1);
        *a = max(*a, dp[i]);
    }

    memset(dp, 0, sizeof dp);
    for(int i=n; i>=1; i--){
        dp[i]=1;
        for(int j=n; j>i; j--)
            if( a[i] < a[j] )
                dp[i] = max(dp[i], dp[j]+1);
        *a = max(*a, dp[i]);
    }

    cout<<*a<<"\n";

    return ;
}

int main(){
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```
</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P1091" target="_blank">Luogu P1091 [NOIP2004 提高组] 合唱队形</a> code</summary>

```cpp
#include <stdio.h>

const int N=110;

int a[N], dp[N], dp2[N];
int n;

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    
    // 最长上升子序列
    for(int i=1; i<=n; i++){
        dp[i]=1;
        for(int j=1; j<i; j++)
            if(a[i]>a[j]) dp[i] = dp[i] > dp[j]+1 ? dp[i] : dp[j]+1;
    }
    
    // 最长下降子序列
    for(int i=n; i>=1; i--){
        dp2[i]=1;
        for(int j=n; j>i; j--)
            if(a[i]>a[j]) dp2[i] = dp2[i]> dp2[j]+1 ? dp2[i] : dp2[j]+1;
            
        *dp = *dp > dp[i]+dp2[i]-1 ? *dp : dp[i]+dp2[i]-1;
    }

    printf("%d", n-*dp);
    return 0;
}
```
</details>



<br>

--- 

## LCS 最长公共子序列

> Longest Common Subsequence


<details><summary><a href="https://leetcode.cn/problems/longest-common-subsequence/" target="_blank">LC 1143. 最长公共子序列</a> code</summary>

```cpp
class Solution {
public:
    int longestCommonSubsequence(string a, string b) {
        int A = a.size(), B = b.size();
        a = " " + a, b = " " + b; 
        int dp[1010][1010]={0};
        for(int i=1; i<=A; i++)
            for(int j=1; j<=B; j++){
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                if(a[i] == b[j]) 
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
            }
        return dp[A][B];
    }
};
```
</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P1439" target="_blank">Luogu P1439 【模板】最长公共子序列</a> code</summary>

```cpp
#include <iostream>
#include <map>
using namespace std;

const int N=1e5+10;

int a[N], dp[N], n, res=1;  // 当前最长子序列长度为 1
map<int, int> hs;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", a+i), hs[ a[i] ] = i;   // 某某数字对应第几位
    for(int i=1; i<=n; i++) scanf("%d", a+i), a[i] = hs[ a[i] ];// 给换回去

    dp[1]=a[1]; // 长度为1的子序列，结尾是第一个数
    for(int i=2; i<=n; i++)
        if(a[i]>dp[res])    // 如果 下个数 比 结尾大，子序列长度增加
            dp[++res]=a[i];
        else                // 反之，这个数可以更新更短的序列结尾
            *lower_bound(dp+1, dp+1+res, a[i])=a[i];
    
    cout<<res;
    return 0;
}
```
</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P2516" target="_blank">Luogu P2516 [HAOI2010]最长公共子序列</a> code</summary>

```cpp

```
</details>


<br>

--- 

## LCIS 最长公共上升子序列

> Longest Common Increasing Subsequence



<details><summary><a href="https://www.acwing.com/problem/content/274/" target="_blank">AcWing 272. 最长公共上升子序列</a> code</summary>

```cpp

```
</details>


