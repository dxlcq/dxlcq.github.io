---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---



# <center> 2022-2023 Season </center>

## 2023 US Open
## 2023 Feb
## 2023 Jan

<a href="" target="_blank">-</a>



## 2022 Dec



<details><summary><a href="https://www.acwing.com/problem/content/4821/" target="_blank">AcWing 4818. 奶牛大学</a> code</summary><br>

**大意**

给定 $n$ 头奶牛，每头奶牛愿意支付的最高学费为 $c_i$。

我们可以设置一个学费 $x$，所有愿意支付 $x$ 及以上学费的奶牛都可以上学。

求我们能收取的最大学费，即 $x * 奶牛数量$。

如果存在多个解，$x$ 应该尽可能小。

**思路**

1. 显然，学费和愿意支付的奶牛数量之间存在
    * 学费高，支付的奶牛少
    * 学费低，支付的奶牛多

因此，我们不能单一的认为，学费越高越好，或者奶牛越多越好。

2. 那么，我们可以尝试枚举学费 $x$，
    然后统计一下，有多少奶牛愿意支付 $x$ 及以上的学费。
    此方法的时间复杂度为 $O(n^2)$。

3. 我们可以对原数组进行一次从大到小的排序。
    此时，我们枚举的学费 $x$，就是 $c_i$。
    而愿意支付 $x$ 及以上学费的奶牛数量，就是 $i$。



```cpp
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N=1e5+10;

LL c[N];    // 每头奶牛愿意支付的最高学费
int n;      // 奶牛数量
LL res;     // 赚的钱
int fees;   // 学费

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", c+i);
    sort(c+1, c+1+n, greater());    // 从大到小排序
    
    for(int i=1; i<=n; i++)         // 从大到小枚举
        if( res <= c[i] * i )       // 当前学费可以赚多少
            res  = c[i] * i, fees = c[i];   // 更新答案
    
    cout<<res<<" "<<fees;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/4822/" target="_blank">AcWing 4819. 喂饱奶牛</a> code</summary><br>

**大意**

给定一个序列，序列中有两种牛，`G` 和 `H`，`G` 吃 `G` 草，`H` 吃 `H` 草。

再给定一个数 $k$，表示每头牛可以移动的范围为 $[i-k, i+k]$。

现需要在选择一些位置，种植草，使得每头牛都能吃到草。

**思路**

1. 我们从左到右枚举每头牛，在每头牛可以到达的最右边种草。

2. 如果此位置已经被种草了，我们就不断的向左移动，直到找到一个没有被种草的位置。


```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=1e5+10;

char res[N];    // 种植方案(答案)
char g[N];      // 奶牛种类
int n, k, cnt;  // 奶牛数量 移动 种植数量

void solve(){
    cnt=0;
    memset(res, '.', sizeof res);
    cin>>n>>k;
    for(int i=1; i<=n; i++) cin>>g[i];
    
    for(int i=1; i<=n; i++)
    if( g[i] == 'G' ){
        int j=min(n, i+k);  // 种植 G 的位置
        res[j] = 'G'; cnt++;// 种植
        i=j+k;              // 可以影响到的右边界
    }
    
    for(int i=1; i<=n; i++)
    if( g[i] == 'H' ){
        int j=min(n, i+k);  // 种植 H 的位置
        while( res[j] == 'G' ) --j; // 思考:为什么--j的位置一定不会冲突?
        res[j] = 'H'; cnt++;
        i=j+k;
    }
    
    cout<<cnt<<"\n";
    for(int i=1; i<=n; i++)
        cout<<res[i];
    cout<<"\n";
}

int main(){
    int T; cin>>T; 
    while(T--) solve();
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/4823/" target="_blank"> AcWing 4820. 逆向工程</a> 跳过</summary><br>

枚举可能的第一个分支代码，筛选出剩余的行，继续枚举第二个分支


</details>

---











# <center>2021-2022 Season</center>

## 2022 US Open 



<details><summary><a href="https://www.acwing.com/problem/content/4443/" target="_blank">AcWing 4440. 照相</a> code</summary><br>

**大意**

给定一个长度为 $n$ 的字符串，字符串从 `1` 开始编号，且只有 `G` 和 `H`。

我们可以对字符串进行翻转，每次翻转的范围为 $[1, 2 i]$。

最终希望字符串中的 `G` 尽可能多的出现在偶数位。

**思路**

1. 翻转是偶数，字符串的长度也是偶数，我们可以将字符串看作 
   `GG`, `HH`, `GH`, `HG` 组成的。

2. 显然，`GG` 和 `HH` 翻转后，答案不会变化。
    我们可以进一步将题目抽象，将 `GH` 看作 0，`HG` 看作 1。
    题目转换为将一个 01 字符串变为全 1 字符串的最小步数。

3. 我们考虑以下这个样例：`HG GH HG GH HG`
    1. `GH GH HG GH HG`
    2. `HG HG HG GH HG`
    3. `GH GH GH GH HG`
    4. `HG HG HG HG HG`

4. 再考虑一个样例：`GH HG GH HG GH`
    1. `HG HG GH HG GH`
    2. `GH GH GH HG GH`
    3. `HG HG HG HG GH`
    4. `GH GH GH GH GH`
    5. `HG HG HG HG HG`

```cpp
#include <iostream>
#include <string>
using namespace std;

int n, ans;
string s, st;
int main(){
    cin>>n>>s;
    for(int i=0;i<n;i+=2){
        if(s[i]=='G' && s[i+1]=='H') st+='0';
        else if(s[i]=='H' && s[i+1]=='G') st+='1';
    }

    for(int i=0; i<st.size()-1; i++)//将一个 01 字符串变为全 1 字符串的最小步数
        if(st[i]!=st[i+1]) ans++;

    if(st[st.size()-1]=='0') ans++;//特判：如果最后一个是 0 ，那么还需要将整个字符串翻转 1 次

    cout<<ans<<endl;

    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/4444/" target="_blank">AcWing 4441. 谎牛计数</a> code</summary><br>

**大意**

给定 $n$ 条信息，每条信息有两种形式：
* 目标值 $>= x$
* 目标值 $<= x$

不是所有信息都是真的，我们需要求出最少有多少条信息是假的。

即找到一个目标值，使得信息为真的信息数量最多。

**思路**

1. 我们可以枚举目标值，然后统计一下，有多少条信息是真的。
    而这个目标值，显然是信息中的 $x$。

```cpp
#define pb push_back
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int>G, L, a;
int n;

int main(){
    cin>>n;
    while(n--){
        string s;
        int x;
        cin>>s>>x;
        if(s=="G") G.pb(x);
        else L.pb(x);
        
        a.pb(x);
    }
    
    int ans=0x3f3f3f3f;
    for(auto &x: a){        // 假设目标在 x 这个位置
        int res = 0;
        for(auto &j: G)
            if(j > x) res++;// 假话
        for(auto &j: L)
            if(j < x) res++;// 假话
        ans = min(ans, res);
    }
    cout<<ans;
    
    return 0;
}
```

2. 可以通过排序优化

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=1e3+10;

int l[N], r[N]; // bessie在奶牛第i头奶牛的 左 \ 右
int ans=0x3f3f3f3f;

int main(){
    int n; cin>>n;
    for(int i=1; i<=n; i++){
        char c[2]; int x;
        scanf("%s%d", c, &x);
        if(c[0]=='G') r[ ++ *r ] = x;
        else l[ ++ *l ] = x;
    }
    sort(l+1, l+1+*l);
    sort(r+1, r+1+*r);
    
    for(int i=1; i<=*r; i++){   // 假设, 第i头奶牛说 在我右边 是正确的
        
        int j=1;
        for(; j<=*l; j++)   // 那么, 对于 (l[j] < r[i]) 的j头奶牛说 在我左边 就是错误的
            if( l[j]>=r[i] )
                break;
        
        ans=min(ans, (*r-i)+j-1);
    }
    
    cout<<ans;
    return 0;
}
```

</details>

<details><summary><a href="https://www.acwing.com/problem/content/4445/" target="_blank">AcWing 4442. 炼金术</a> code</summary><br>

**大意**

给定一个树形的合成关系，且保证一定是 较小的数 合成 较大的数。
并不保证 较小的数 只能合成 一种 较大的数。

```
      5 
     / \
    3   4
   /   
  2
 /
1
```

求，最大的数 $n$，最多可以合成多少个。

**思路**

1. 显然，我们不能用贪心的思想。
   某一个数全部用于合成 $x$，结果在合成 $y$ 的时候不够了。

2. 换个角度思考，如果我们知道了 $n$ 的数量，我们可以反推儿子们的数量，
   检查是否有足够的儿子，可以合成 $n$。

3. 显然，答案是具有单调性的，左半边合法，即找 $<=x$ 中，最大的一个

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
    
#define pb push_back

const int N=110;

int a[N], bk[N];
vector<int> h[N];   // 合成 i 所需要的金属
int n, k;

bool dfs(int u, int cntu){  // 能否获得 cntu 个材料 u
    if( a[u] >= cntu ) {    // 已经拥有
        a[u] -= cntu;
        return 1;  
    }
    if( h[u].size()==0 )    // 不足且无法合成
        return 0;  
    
    cntu-=a[u], a[u]=0;     // 还需要cntu个a[u] 
    for(auto nu: h[u])      // 尝试使用 nu 进行合成
        if( !dfs(nu, cntu-a[u]) ) 
            return 0;
    return 1;
}

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    cin>>k;
    for(int i=1; i<=k; i++){
        int l, m; cin>>l>>m;
        for(int j=1; j<=m; j++){
            int mi; cin>>mi;
            h[l].pb(mi);
        }
    }

    memcpy(bk, a, sizeof a);

    int l=a[n], r=1e6;
    while(l<r){
        memcpy(a, bk, sizeof a);
        int mid = l+r+1>>1;
        if(dfs(n, mid)) l = mid;
        else r = mid - 1;
    }
    cout<<l;

    return 0;
}
```

</details>



## 2022 Feb

<details><summary><a href="https://www.acwing.com/problem/content/4369/" target="_blank">AcWing 4366. 上课睡觉</a> code</summary><br>


**大意**

给定一个数组 $a$，将其划分为 $k$ 个区间，使得每个区间和相等，求最少的操作次数。

**思路**

1. 显然，合并实际上只有一种方案，就是相邻合并。

2. 我们可以通过合并成 $1,2,3,4...$ 堆，计算出每堆的大小 $sum, \frac{sum}{2}, \frac{sum}{3}, \frac{sum}{4}...$。

3. 通过计算前缀和，就可以非常方便的计算出，每堆的大小。

```cpp
#include <iostream>
using namespace std;

const int N=1e6+10;

int a[N];
int n, mmax, sum;

bool ck(int m){
    int cnt=0;
    for(int i=1; i<=n; i++){
        cnt += a[i];
        if(cnt == m) cnt=0;
        else if(cnt > m) return 0;
    }
    return 1;
}

void solve(){
    cin>>n;
    mmax=0, sum=0;
    for(int i=1; i<=n; i++) 
        scanf("%d", a+i), mmax=max(mmax, a[i]), sum+=a[i];
    
    if(sum==0){                 // 每一堆为0
        cout<<0<<"\n";
        return ;
    }
    for(int i=1; i<=sum; i++)   // 枚举, 每一堆为1-sum
        if(sum%i==0 && ck(i)){
            cout<<n - sum / i<<"\n";
            return ;
        }
}

int main(){
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/4370/" target="_blank">AcWing 4367. 拍照2</a> code</summary><br>

**大意**

给定一个序列 $a$，一个目标序列 $b$，允许一种操作：
* 将 $a$ 中的元素向左移动任意个位置

求最少的操作次数，使得 $a$ 变为 $b$。

**思路**

1. 样例2：
    * 将 4 向前移动
    * 将 2 向前移动

2. 很容易想到用双指针来解决这个问题，$i$ 指向 $a$，$j$ 指向 $b$：
    * 如果 $a_i$ 与 $b_j$ 相等，$i++, j++$
    * 如果 $a_i$ 与 $b_j$ 不相等，$j++$，并且记录一下 $b_j$，表示需要从后面移动一个
    * 如果 $a_i$ 是被记录过的数，$i++$（此数是被前移的数）。


```cpp
#include <iostream>
#include <unordered_set>
using namespace std;

const int N=1e5+10;

int a[N], b[N];
unordered_set<int> cnt;
int n;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++)
        scanf("%d", a+i);
    for(int i=1; i<=n; i++)
        scanf("%d", b+i);
    
    int i=1, j=1;
    
    while(i<=n && j<=n){
        if(cnt.count(a[i])){
            i++;
            continue;
        }
        if(a[i]==b[j]){
            i++, j++;
            continue;
        }
        if(a[i]!=b[j]){
            cnt.insert(b[j]);
            j++;
        }
    }
    
    cout<<cnt.size();
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/4371/" target="_blank">AcWing 4368. 积木</a> code</summary><br>

**大意**

4 个骰子，每个骰子有 6 个字母，
给出一个 1-4 长度的字符串，判断是否可以由这 4 个骰子中的 1-4 个组成。

**思路**

对于字符串的第一个位置，有 4 个骰子可以选择，第二个位置有 3 个骰子可以选择，以此类推。

如果第一个位置选择了骰子 1（如果可以选择），那么第二个位置就只能选择 2,3,4 中的一个。

以此类推，去第二个位置，选择骰子。

参考：[递归实现组合型枚举](http://dxll.love:2023/algorithm/1%20%E5%9F%BA%E7%A1%80/%E9%80%92%E5%BD%92.html#%E9%80%92%E5%BD%92%E5%AE%9E%E7%8E%B0%E7%BB%84%E5%90%88%E5%9E%8B%E6%9E%9A%E4%B8%BE)

```cpp
#include <iostream>
#include <string>
#include <set>
using namespace std;

bool st[4]; // 每个骰子是否有用
set<char> a[4];
int n;
string t;
bool flg;

void dfs(int u, int x){ // 第几个骰子, 第几个字符
    if(u>4) return ;
    if(flg) return ;
    
    if(x>=t.size()){
        flg=1;
        return ;
    }
    
    for(int i=0; i<4; i++)
        if(!st[i])                  // 如果没有使用
            if(a[i].count(t[x])){   // 如果骰子上有
                st[i]=1;
                dfs(u+1, x+1);
                st[i]=0;    // 恢复现场
            }
        else
            dfs(u+1, x);            // 不使用
    
}

int main(){
    cin>>n;
    
    cin>>t; for(char c: t) a[0].insert(c);
    cin>>t; for(char c: t) a[1].insert(c);
    cin>>t; for(char c: t) a[2].insert(c);
    cin>>t; for(char c: t) a[3].insert(c);
    
    while(n--){
        cin>>t;
        if(t.size() > 4){
            puts("NO");
            continue;
        }
        
        flg=0;
        for(int i=0; i<4; i++) st[i]=0;
        
        dfs(0, 0);
        if(flg)
            puts("YES");
        else
            puts("NO");
    }
    
    return 0;
}
```

</details>



## 2022 Jan


<details><summary><a href="https://www.acwing.com/problem/content/description/4332/" target="_blank">AcWing 4329. Herdle</a> code</summary><br> 

**大意**

给定两个 $3$ X $3$ 的方阵 $a$ 和 $b$ ，每个方阵中每个位置由 $A-Z$ 组成，

* 绿色：对于 $i$ 行 $j$ 列，$a$ 方阵中的字母与 $b$ 方阵中的字母相同
* 黄色：不考虑被判定为绿色的格子，如果该字母在 $a$ 方阵中出现的次数大于 $b$ 方阵中出现的次数，那么该格子为黄色

**思路**

```
a:          b:  
    DD          AA
    BB          BD

res：
    空空
    绿黄
```

特别的：

```
a:          b:  
    DA         CD
    AA         DD

res：       或          或
    空空        空黄        空空
    空黄        空空        黄空
```



```cpp
#include <iostream>
#include <cstring>
using namespace std;

int n, ans1, ans2;
int cnt1[26];
int cnt2[26];

string a[3], b[3];

int main(){
    for(int i=0; i<3; i++) cin>>a[i];
    for(int i=0; i<3; i++) cin>>b[i];
    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            cnt1[ a[i][j]-'A' ]++,
            cnt2[ b[i][j]-'A' ]++;
    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if( a[i][j] == b[i][j] ){
                ans1++;
                cnt1[ a[i][j]-'A' ]--,
                cnt2[ b[i][j]-'A' ]--;
            }
        
    for(int i=0; i<26; i++)
        if(cnt1[i] && cnt2[i])
            ans2 += min(cnt1[i], cnt2[i]);
    
    cout<<ans1<<"\n"<<ans2;
    
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/4333/" target="_blank">AcWing 4330. 非传递骰子</a> code</summary><br>

**大意**

给定长为 $4$ 的数组 $a$ 和 $b$，每个数组中的元素为 $1-10$。
求一长为 $4$ 的数组 $c$，满足：
* $a > b > c > a$

其中 $ > $ 的定义是：数组中所有元素两两比较，
如果 $a_i > b_i$ 的数量比 $b_i > a_i$ 的数量多，那么 $a$ 大于 $b$。

**思路**

1. 枚举 $c$ 的每个元素，然后检查一下是否满足条件。

```cpp
#include <iostream>
using namespace std;

int a[5], b[5], c[5];
bool flg;

bool ck(int x[], int y[]){  // x赢 > y赢 1
    int res=0;
    for(int i=1; i<=4; i++)
        for(int j=1; j<=4; j++)
            if(x[i] > y[j]) res++;
            else if(y[j] > x[i]) res--;
    return res>0;
}

void dfs(int u){    // 当前赋值的
    if(flg) return ;
    if(u>4){
        
        if(ck(a, b) && ck(b, c) && ck(c, a))
            flg=1;
            
        if(ck(b, a) && ck(a, c) && ck(c, b))
            flg=1;
            
        return ;
    }
    
    for(int i=1; i<=10; i++){
        c[u]=i;
        dfs(u+1);
    }
    
    return ;
}

void solve(){
    flg=0;
    for(int i=1; i<=4; i++) scanf("%d", a+i);
    for(int i=1; i<=4; i++) scanf("%d", b+i);
    
    dfs(1); // 枚举 c 的可能
    
    if(flg) puts("yes");
    else puts("no");
    
    return ;
}

int main(){
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/4334/" target="_blank">AcWing 4331. 大旱</a> 跳过</summary><br>

差分


</details>

## 2021 Dec


<details><summary><a href="https://www.acwing.com/problem/content/description/4264/" target="_blank">AcWing 4261. 孤独的照片</a> code</summary><br>

**大意**

给定一个只包含 $H$ 和 $G$ 序列，找出满足以下条件的子序列的数量

* 长度 >= 3
* 有且仅有一个 $H$ 或 $G$

**思路**

1. 我们假设第 $i$ 个位置的牛是孤独的，孤独就有下面三种情况：
    1. `_HGH_`，等价于 `_GHG_`
    2. `__HHG`，等价于 `__GGH`
    3. `GHH__`，等价于 `HGG__`

2. 用左边三种举例：
    1. 孤独的子序列数量为：左边 $H$ 的数量 * 右边 $H$ 的数量
    2. 孤独的子序列数量为：左边 $H$ 的数量 - 1
    3. 孤独的子序列数量为：右边 $H$ 的数量 - 1

3. 因此，我们只需要统计每个位置，左右两边不同的牛的数量即可。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

typedef long long LL;
const int N=5e5+10;

string s;
int n, l[N], r[N];

int main(){
    cin>>n>>s; s=" "+s;
    
    for(int i=1, cntH=0, cntG=0; i<=n; i++) // 左边
        if( s[i]=='H' ){
            l[i]=cntG;  // 左边G的数量（左边不同者的数量）
            cntH++;     // H的数量+1
            cntG=0;     // G被H截胡了，所以G归零
        }
        else            // 同上
            l[i]=cntH, cntG++, cntH=0;
    
    for(int i=n, cntH=0, cntG=0; i>=1; i--) // 右边
        if( s[i]=='H' ){
            r[i]=cntG;
            cntH++;
            cntG=0;
        }
        else
            r[i]=cntH, cntG++, cntH=0;
    
    LL ans=0;
    for(int i=1; i<=n; i++)
        ans += 1LL*l[i]*r[i] + max(0, l[i]-1)+ max(0, r[i]-1);
    
    cout<<ans;
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/description/4265/" target="_blank">AcWing 4262. 空调</a> code</summary> 

<br>

**大意**

给定两个长度为 $n$ 的数组，$p$ 与 $t$。
我们可以对 $t$ 执行一次操作，使得区间 $[i, j]$ 中的所有数 $+1$ 或者 $-1$。
最终使得数组 $t=p$，求最少的操作次数。

**思路**

1. 为了使得 $t=p$，对于第 $i$ 位而言，$t_i$ 只需要加上 $p_i-t_i$。
    $t_i+p_i-t_i=p_i$。
    因此，我们可以处理出来一个数组 $c$，其中 $c_i=p_i-t_i$。

现在的问题：将 $c$ 数组，操作成一个全 $0$ 的数组，求最少的操作次数。

2. 每次是对区间进行操作，因此，不妨对数组做一次差分，然后再考虑。
   分析一下样例，下面是已经求完差分后的数组 $c$。
   `2 0 -2 3 0` $->$ `0 0 0 3 0`：将第 $1$ 位 $-2$，第 $3$ 位 $+2$，操作 $2$ 次。
   `0 0 0 3 0` $->$ `0 0 0 0 0`：将第 $4$ 位 $-3$, 第 $6$ 位 $+3$，操作 $3$ 次。
    可以发现，差分后的数组，加减是对应的：如果我某一位加了 $6$，后面必然会减去 $6$。

因此，我们统计我们加的次数 $a$，和减的次数 $b$。
如果 $a=b$      操作次数是 $a$ 或 $b$。
如果 $a \neq b$ 操作次数是 $max(a, b)$。


```cpp
#include <iostream>
using namespace std;

const int N=2e5+10;

int n;
int p[N], t[N], c[N];

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d", p+i);
    for(int i=1; i<=n; i++) scanf("%d", t+i);
    for(int i=1; i<=n; i++) c[i] = p[i] - t[i];
    for(int i=n; i>1; i--) c[i] = c[i] - c[i-1];
    
    int a=0, b=0;
    for(int i=1; i<=n; i++)
        if(c[i]>0) a+=c[i];
        else b+=abs(c[i]);

    cout<<max(a, b);
    return 0;
}
```

</details>


<details><summary><a href="https://www.acwing.com/problem/content/4266/" target="_blank">AcWing 4263. 走路回家</a> code</summary> 

<br>

**大意**

给定一个 $n \times n$ 大小的矩阵 $g$，对于每个点 $g[i][j]$，
有两种状态，可以到达和不可到达。
我们需要从 $(1,1)$ 点走到 $(n,n)$ 点，只能向下或者向右走，且转向次数 $\leq k$。
求到达 $(n,n)$ 点的方案次数。

**思路**

1.  我们先考虑，在转向次数不受限的情况下，走到 $(n,n)$ 点的方案数量。
    定义一个 $dp[i][j]$，代表到达 $(i,j)$ 点的方案数量。因此，有：

$$ dp[i][j] = dp[i-1][j] + dp[i][j-1] $$

2.  我们在此基础上，统计一下，到达 $(i,j)$ 的转向次数。
    显然，是不行的。因为不同方案到达 $(i,j)$ 的转向次数可能不同。
    顺着此思路继续考虑，我们是否可以统计，转向 $1,2,\cdots,k$ 次，到达 $(i,j)$ 的方案数量。
    很容易想到，定义一个 $dp[i][j][k]$，即到达 $(i,j)$ 点，转向 $k$ 次的方案数量。

只剩一个问题，如何判断，当前是否转向？

3.  在本题中，转向被定义为：
    * $(i,j-1) -> (i,j)$，$(i,j) -> (i+1,j)$
    * $(i-1,j) -> (i,j)$，$(i,j) -> (i,j+1)$
    因此，我们可以增加一个状态，康康 $(i,j)$ 是从上面来的，还是从左边来的。
    定义一个 $dp[i][j][k][op]$

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N=55;

int n, kk, ans;
string s;
int g[N][N], dp[N][N][5][2];

void solve(){
    cin>>n>>kk;
    ans=0;
    memset(g, 0, sizeof g);
    memset(dp, 0, sizeof dp);

    for(int i=1; i<=n; i++){
        cin>>s;
        for(int j=1; j<=n; j++)
            if(s[j-1]=='H') g[i][j]=1;
    }

    dp[1][1][0][0]=1; // 向右
    dp[1][1][0][1]=1; // 向下

    for(int i=1; i<=n; i++)             // 枚举所有的点
        for(int j=1; j<=n; j++){
            if(i==1 && j==1) continue;  // 忽略 (1,1)
            if(g[i][j]) continue;       // 如果不能到达
            
            for(int k=0; k<=kk; k++){   // 枚举所有的转向次数
                if ((i == 1 || j == 1) && k != 0) continue; // 初始化第一行第一列
                    dp[i][j][k][0] = dp[i][j-1][k][0];      // 继续向右
                    dp[i][j][k][1] = dp[i-1][j][k][1];      // 继续向下
                    if (k > 0)  // 允许上一步到这一步变向
                        dp[i][j][k][0] += dp[i][j-1][k - 1][1],   // 本来是向下的，现在向右走
                        dp[i][j][k][1] += dp[i-1][j][k - 1][0];   // 本来是向右的，现在向下走
            }
        }

    for (int k = 0; k <= kk; k ++ ) 
        ans += dp[n][n][k][0] + dp[n][n][k][1];
        
    printf("%d\n", ans);

    return ;
}

int main(){
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

</details>

---




# <center>2020-2021 Season</center>

## 2021 US Open

<details><summary><a href="https://www.acwing.com/problem/content/3748/" target="_blank">AcWing 3745. 牛的学术圈 I</a> code</summary>

<br>

**大意**

给定一个数组 $c$，$c_i$ 是每篇文章被引用的次数。
我们可以使其中任意 $\leq L$ 篇文章引用次数 $+1$。
学术成就定义为 $h$：存在 $h$ 篇论文，引用次数 $\geq h$。
求最大的 $h$。

**思路**

1.  在不考虑 $L$ 的情况下，如果将文章引用次数按照降序排序，
    如果 $c[i] \geq i$，那么 $i$ 就是一个合法的 $H$，观察样例 `100 3 2 1`：
    * $c[1]$：存在 $1$ 篇论文，引用次数 $\geq 1$：`100`。
    * $c[2]$：存在 $2$ 篇论文，引用次数 $\geq 2$：`100 3`。
    * $c[3]$：不存在 $3$ 篇论文，引用次数 $\geq 3$：`100 3 2`。

2.  这个数组可以分为两部分，左边部分是合法，右边部分是不合法，
    显然，我们引用合法的论文，是不会增加我们的 $h$，
    我们需要将不合法论文中，较大的进行引用。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N=2e5+10;

int a[N];
int n, l;

int main(){
    cin>>n>>l;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    
    sort(a+1, a+1+n, greater());    // 从大到小排
    int i=1;
    while(a[i]>=i && i<=n-l) i++;   // 走过合法部分，同时后面必须留够 l 个
    for(int j=0; j<l; j++) a[i+j]++;// 引用选定的 l 个
    
    sort(a+1, a+1+n, greater());    
    i=1;                            
    while(a[i]>=i && i<=n) i++;     // 找到第一个不合法的地儿
    cout<<i-1;
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3749/" target="_blank">AcWing 3746. 牛的学术圈 II</a> code</summary>

<br>

**大意**

给定 $k$ 行，每行 $n$ 个字符串。
$n$ 个字符串按照贡献从大到小，字典序从小到大给出。
规定，贡献越小，资历越大。
对于任意两个字符串，我们需要判断谁的资历更高，或者说无法判断。

**思路**

1.  对于一行字符串 $s[n]$，如果存在 $s_i > s_j (i<j)$，
    则可以断定 $s_i$ 的贡献大于 $s_j$。
    进而得出：$[1,i]$ 的贡献都大于 $[j,n]$。

2.  为了找出所有的关系，我们枚举 $j$，
    在 $[1,j)$ 范围中，找到 $s_i > s_j$：$[1,i]$ 的贡献都大于 $j$。

```cpp
#include <iostream>
#include <map>
#include <cstring>
using namespace std;

const int N=110;

int g[N][N];
map<string, int> tr;
int k, n;

int main(){
    cin>>k>>n;
    for(int i=1; i<=n; i++){
        string t; cin>>t;
        tr[t] = i;  // t 是第 i 名成员
    }
    for(int l=1; l<=k; l++){
        string s[N];
        int flg=1;
        for(int j=1; j<=n; j++){
            cin>>s[j];
            if(s[j-1] > s[j]) flg=j;            // 当找到一个地方 s[i] > s[j]
            for(int i=1; i<flg; i++)            // [1-i]的贡献均大于 j
                g[ tr[s[i]] ][ tr[s[j]] ] = 1,
                g[ tr[s[j]] ][ tr[s[i]] ] = -1;   
        }
    }

    for(int i=1; i<=n; i++, cout<<"\n")
        for(int j=1; j<=n; j++)
            if(i==j) cout<<"B";
            else{
                if(g[i][j] == 1) cout<<"0";
                if(g[i][j] == -1) cout<<"1";
                if(g[i][j] == 0) cout<<"?";
            }

    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3750/" target="_blank">AcWing 3747. 牛的学术圈 III</a> code</summary>

<br>

**大意**

给定一个 $N$ 行，$M$ 列的矩阵 $g$。
对于 $g[i][j]$，有三种状态：`C` `G` `.`。
对于 `G` 而言，其上下左右四个位置的 `C` ，可以在 `G` 处建立关系，
每个 `G` 只能使用一次，求建立不重复关系的最大数量。

**思路**

1. 每个 `G` 只能使用一次，那么我们从 `G` 的角度去考虑，枚举 `G`，
   同时统计 `G` 的四周有多少 `C`：
   `C` $< 2$：不会存在关系；
   `C` $= 2$：存在一对关系；
   `C` $> 2$：存在至少两对关系。

2. 此时，我们考虑一下，关系重复建立的情况：
   `C1` `G1`
   `G2` `C2`   
   显然，当出现类似上面的排列时，`C1` 和 `C2` 可以同时在 `G1`，`G2` 建立关系，
   因此，需要维护一下每一对关系。

3. 对于两个 `G`，他们最多只会重复一对儿关系。

```cpp
#define fst first
#define sed second
#include <iostream>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int N=1e3+10;
const int dxy[4][2]={ {-1,0},{1,0},{0,-1},{0,1} };

int n, m, ans;
string g[N];

set<pair<PII, PII>> only; // 一对唯一的奶牛

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>g[i];
        g[i] = " "+g[i];
    }
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(g[i][j] == 'G'){ // 如果有草
                
                vector<PII> cnt;
                for(int k=0; k<4; k++){
                    int nx = i + dxy[k][0];
                    int ny = j + dxy[k][1];
                    
                    if( g[nx][ny] == 'C' ) cnt.push_back({nx, ny});
                }
                
                if(cnt.size() > 2) ans++;
                if(cnt.size() == 2){
                    int x1 = cnt[0].fst, y1 = cnt[0].sed;
                    int x2 = cnt[1].fst, y2 = cnt[1].sed;
                    
                    if( only.count( { {x1,y1}, {x2,y2} } ) ||
                        only.count( { {x2,y2}, {x1,y1} } ) )
                        continue;
                    else{
                        ans++;
                        only.insert({ {x1,y1}, {x2,y2} });
                        only.insert({ {x2,y2}, {x1,y1} });
                    }
                }
            }
    
    cout<<ans;
    
    return 0;
}
```
</details>

## 2021 Feb

<details><summary><a href="https://www.acwing.com/problem/content/description/3373/" target="_blank">AcWing 3370. 牛年</a> code</summary><br>

**大意**

给定 $12$ 个生肖，每次给出一条信息：
* $A$ 是 $B$ 左边（previous）的第一个 $C$ 年
* $A$ 是 $B$ 右边（next）的第一个 $C$ 年

通过若干条信息，求出 $Bessie$ 与 $Elsie$ 的年份差。

**思路**

1. 我们需要确定每头牛与 $Bessie$ 的年份差。
   显然，$Bessie$ 与 $Bessie$ 的年份差为 $0$，$Bessie$ 的生肖是牛。

2. 对于每条信息，我们先计算生肖的差值，再计算年份的差值。
   为了方便计算生肖的差值，我们可以直接将生肖复制成三份，
   然后从中间开始向前向后找。

```cpp
#include <iostream>
#include <cstring>
#include <map>
using namespace std;

map<string, int> ans;
map<string, string> u;    // 每头牛的生肖

string sx[]={
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat",
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat",
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"
};

int main(){
    int Q; cin>>Q;
    
    ans["Bessie"]=0;
    u["Bessie"]="Ox";
    
    while(Q--){
        string s[10];
        for(int i=1; i<=8; i++) cin>>s[i];
        string A=s[1], B=s[8];
        u[A] = s[5];    // 可以直接确定 A 的生肖
        
        // 先找到 B 的位置
        int idxA, idxB;
        for(int i=12; i<=23; i++) 
            if(sx[i]==u[B]){
                idxB=i;
                break;
            }
        
        if(s[4]=="previous"){
            // 再找到 A 的位置，A < B
            idxA = idxB - 1;
            while(sx[idxA] != u[A]) idxA--;
            ans[A] = ans[B] - (idxB-idxA);
        }else{
            // 同上，不过是向右找，A > B
            idxA = idxB + 1;
            while(sx[idxA] != u[A]) idxA++;
            ans[A] = ans[B] + (idxA-idxB);
        }
    }
    
    cout<<abs(ans["Elsie"]);
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3374/" target="_blank">AcWing 3371. 舒适的奶牛</a> code</summary><br>

**大意**

给定一个 $n \times n$ 的矩阵，每个位置有两种状态：有牛，没牛。
每次加入一头牛，如果这头牛的上下左右四个位置有 $3$ 头牛，那么这头牛舒服。
求每次加入一头牛后，舒服的牛的数量。

**思路**

1.  每次加入一头牛，只会影响上下左右四个位置的舒服情况。
    因此，我们只需要检查这四个位置的舒服情况即可。

2.  检查这头牛的舒服情况：
    * 如果这头牛的上下左右四个位置有 $3$ 头牛，那么这头牛舒服。
    * 否则，这头牛不舒服。

3.  检查周围四头牛的舒服情况：
    * 如果这头牛之前不舒服，但是现在舒服了，那么答案 $+1$。
    * 如果这头牛之前是舒服的，但是现在不舒服了，那么答案 $-1$。

```cpp
#pragma GCC optimize(3, "inline", "Ofast")

#include <stdio.h>

//int N=1010;

int g[1010][1010];
int f[1010][1010]; // 记录这个位置的牛是否舒适

int dxy[4][2]={ {-1,0}, {1,0}, {0,-1}, {0,1} };

// 每一次加入后，只会影响上下左右四个方向的奶牛舒不舒服
// 那么再check一下

// 检查(x,y)奶牛舒服
int check(int x, int y){
    int res=0;
    
    for(int i=0; i<4; i++){
        int nx=x+dxy[i][0];
        int ny=y+dxy[i][1];
        
        if( nx<0 || ny <0 ) continue;
        
        if(g[nx][ny]==1)
            res++;
    }
    
    if(res==3) return 1;
    return 0;
}

int main(){
    int n, ans=0;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        g[a][b]=1;
        
        // 检查这头牛
        if( check(a, b) ) ans++, f[a][b]=1;
        
        // 检查周围四头牛
        for(int i=0; i<4; i++){
            int nx=a+dxy[i][0];
            int ny=b+dxy[i][1];
            
            // 有牛, 舒服, 没被舒服过
            if(g[nx][ny] && check(nx, ny) && f[nx][ny]==0){
                ans++;
                f[nx][ny]=1;
                continue;
            }
            
            // 有牛,不舒服了,曾经舒服过
            if(g[nx][ny] && check(nx, ny)==0 && f[nx][ny]==1){
                ans--;
                f[nx][ny]=0;
                continue;
            }
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/3375/" target="_blank">AcWing 3372. 顺时针围栏</a> code</summary><br>

**大意**

给定一个字符串，仅包含 `N` `E` `S` `W`，代表向北、向东、向南、向西行进一格。

求行进完毕后，被围起来的路径是否是顺时针的。

**思路**

1.  我们不能通过一次移动方向，判断是否顺时针。于是有了：
    `NE` `ES` `SW` `WN`
    而其他组合，都是逆时针（两个字符不相等）。

2. 因此，我们只需要遍历一遍字符串，判断顺时针组合出现的数量即可。

```cpp
#include <iostream>
#include <string>
using namespace std;

const int N=2e5+10;

string solve(){
    int res=0;
    string s; cin>>s;
    for(int i=0; i<s.size()-1; i++)
        if(s[i] != s[i+1]){
            string t = string(1, s[i]) + string(1, s[i+1]);
            if(t=="NE" || t=="ES" || t=="SW" || t=="WN") res++;
            else res--;
        }

    if(res>0) return "CW";
    return "CCW";
}

int main(){
    int T; cin>>T;
    while(T--) cout<<solve()<<"\n";
    return 0;
}
```
</details>

## 2021 Jan

<1details><summary><a href="https://www.acwing.com/problem/content/description/3361/" target="_blank">AcWing 3358. 放养但没有完全放养</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

string str, sub;

int main(){
    cin>>str>>sub;
    
    int i=0;
    int ans=0;
    
    while(i<sub.size()){
        
        
        for(int j=0; j<str.size(); j++)
            if(sub[i]==str[j]){
                i++;
            }
        
        ans++;
    }
    
    cout<<ans;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3362/" target="_blank">AcWing 3359. 更多奇怪的照片</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 奇数、偶数的数量
int odd, even;

int main(){
    int n;
    cin>>n;
    for(auto i=1; i<=n; i++){
        int t;
        scanf("%d", &t);
        
        if(t&1) 
            odd++;
        else
            even++;
    }
    // 我有奇数的个数
    // 有偶数的个数
    // 那么他们相同的部分，一定可以配 min(odd, even)*2 组数
    // 剩下 a = abs(odd-even) 数量的 全奇 或者 全偶
    // 若全奇
    //      （偶数个）2个奇数的和是偶数
    //      显然，我们必定可以配出 (a/3)*2 组 
    //      对于没使用的奇数，一个会影响俩，直接ans--
    //      如果 a - int(a/3) * 2 >=1 , ans -= ( a - int(a/3) * 2 )
    // 若全偶
    //      不管了，再加一个
    
    int ans=min(odd, even)*2;
    
    //cout<<odd<<" "<<even<<endl;
    
    if(odd>even){
        int a=abs(odd-even);
        
        //cout<<a<<endl;
        
        ans += (int(a/3))*2;    // 全奇配的
        
        //cout<<ans;
        
        a -= ( int(a/3)*3 );    // 剩余的
        
        if(a==2)
            ans++;
        else if(a==1)
            ans--;
    }
    else if(even>odd)
        ans++;
    
    cout<<ans;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3363/" target="_blank">AcWing 3360. 牛棚</a> code</summary><br>

**大意**

给定两个数组 $a, b$
将 $a$ 排列，使得 $a$ 中的每个元素都不大于 $b$ 中的对应元素。

**思路**

1. 我们可以将 $a$ 从大到小排序，然后看他能放入 $b$ 的那几个位置。

2. 对于第 $i$ 位，前面的 $i$ 个位置都已经被放置，所以能放的位置 $res - i + 1$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 30;

LL a[N], b[N];
LL ans=1;
int n;

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++) cin>>b[i];
    
    sort(a+1, a+1+n, greater());    // 将 a 从大到小排序
    for(int i=1; i<=n; i++){        // 看每一位能放到多少个位置去
        int res=0;
        for(int j=1; j<=n; j++)
            if(a[i] <= b[j]) res++; // 可以放到 res 个 b 里面去
        ans *= res - i + 1;
    }

    cout<<ans;

    return 0;
}
```
</details>

## 2020 Dec

<details><summary><a href="https://www.acwing.com/problem/content/description/3349/" target="_blank">AcWing 3346. 你知道你的ABC吗</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int n[10];
int used[10];

int main(){
    for(int i=1; i<=7; i++)
        cin>>n[i];
    sort(n+1, n+8);
    
    do{
        sort(n+1, n+4);
        
        // a+b
        if( n[1]+n[2] != n[4] ) continue;
        // b+c
        if( n[2]+n[3] != n[5] ) continue;
        // a+c
        if( n[1]+n[3] != n[6] ) continue;
        // a+b+c
        if( n[1]+n[2]+n[3] != n[7] ) continue;
        
        for(int i=1; i<=3; i++)
            cout<<n[i]<<" ";
        break;
        
    }
    while(next_permutation(n+1, n+7));
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/3350/" target="_blank">AcWing 3347. 菊花链</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=1010;

int hua[N];

int main(){
    int n=0;
    cin>>n;
    for(int i=1; i<=n; i++){
        scanf("%d", &hua[i]);
        hua[i]+=hua[i-1];     // 做一个前缀和
    }
    
    int res=n; // 提前一朵花 
    
    for(int j=1; j<=n; j++){
        for(int i=1; i<j; i++){ // 这里取消等号 等于的时候是一朵花
            // i-j的照片
            int all=hua[j]-hua[i-1]; // 花瓣数量
            int duo=j-i+1;           // 花朵数量
            double pp=(double)all/duo;
            int p=all/duo;
            //cout<<i<<"-"<<j<<":"<<pp<<endl;
            if( pp-p>1e-6 )continue;
            

            // 检查花k是否是平均的花
            for(int k=i; k<=j; k++)
                if( p==(hua[k]-hua[k-1]) ){
                    res++;
                    break;
                }
            
        }
    }
    
    cout<<res;
    
    return 0;
}
```
</details>

---

# <center>2019-2020 Season</center>

## 2020 US Open

## 2020 Feb

<details><summary><a href="https://www.acwing.com/problem/content/1673/" target="_blank">AcWing 1671. 三角形</a> code</summary>

```cpp
#pragma GCC optimize(2, 3, "Ofast", "inline")

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PII;

#define x first
#define y second

PII a[110];

int main(){
    int n;
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);
    
    LL ans=-1;
    
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
    for(int k=1; k<=n; k++)
        if(a[i].x==a[j].x && a[j].y==a[k].y)
            ans=max(ans,  llabs(a[j].y-a[i].y)*llabs(a[k].x-a[j].x)  );
        
    cout<<ans;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/1674/" target="_blank">AcWing 1672. 疯狂的科学家</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int N=1e3+10;

string A, B;

int main(){
    int n;
    cin>>n;
    cin>>A>>B;
    
    int res=0;
    for(int i=0; i<A.size(); i++){
        
        if(A[i]!=B[i]){
            i++;
            while(A[i]!=B[i]) i++;
            i--;
            res++;
        }
    
    }
    
    cout<<res;
    
    return 0;
}
```
</details>

## 2020 Jan

<details><summary><a href="https://www.acwing.com/problem/content/1444/" target="_blank">AcWing 1442. 单词处理器</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
    int n, k;
    cin>>n>>k;
    string str;
    int a=0;
    for(int i=1; i<=n; i++){
        cin>>str;
        
        if( str.size()+a > k ){
            cout<<endl;
            a=0;
        }
        
        cout<<str<<" ";
        a+=str.size();
    }
    
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/1445/" target="_blank">AcWing 1443. 拍照</a> code</summary>

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

const int N=1e3+10;

int a[N], b[N];

int main(){
    int n=0;
    cin>>n;
    for(int i=1; i<n; i++) scanf("%d", &b[i]);
    
    for(int k=1; k<=n; k++){          
        unordered_map<int, int> hash; 
                // 记录某个数字是否出现
        a[1]=k; // 第一个数字是k
        hash[k]++;
        
        int i=2;
        for( ; i<=n; i++){
            a[i]=b[i-1]-a[i-1];
            
            if(hash[a[i]]) break;        // 位置重复的牛
            if(a[i]<=0 || a[i]>n) break; // 不该出现的牛
            
            hash[a[i]]++;
        }
        
        if(i>n) break; // a排序完成
    }
    
    for(int i=1; i<=n; i++) cout<<a[i]<<" ";
    
    return 0;
}
```
</details>

## 2019 Dec

<details><summary><a href="https://www.acwing.com/problem/content/1461/" target="_blank">AcWing 1459. 奶牛体操</a> code</summary>

```cpp
#include <iostream>
using namespace std;

const int N=30;

int a[N][N];

int main(){
    int k, n;
    cin>>k>>n;
    // k次训练
    // n头奶牛
    for(int i=1; i<=k; i++)
        for(int j=1; j<=n; j++)
            scanf("%d", &a[i][j]);
    
    int ans=0;
    
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++){
            
            // x必须先出现
            int x=a[1][i], y=a[1][j];
            
            bool flg = 1;
            // 遍历其余次训练情况
            for(int m=2; m<=k && flg; m++)
                for(int t=1; t<=n; t++)
                    if( a[m][t] == y){
                        flg=0;
                        break;
                    }
                    else if( a[m][t] == x )
                        break;
            
            if(flg) ans++;
        }
    
    cout<<ans;
    
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/1462/" target="_blank">AcWing 1460. 我在哪？</a> code</summary>

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int n, ans;
string s;

bool ck(int res){
    set<string> H;
    for(int i=0; i+res<=n; i++)
        if(H.count(s.substr(i, res))) return 0;
        else H.insert(s.substr(i, res));
    return 1;
}

int main(){
    cin>>n>>s;
    for(ans=1; ans<n; ans++)
        if( ck(ans) ) break;
    cout<<ans;
    return 0;
}
```
</details>


---

# <center>2018-2019 Season</center>

## 2019 US Open

<details><summary><a href="https://www.acwing.com/problem/content/1472/" target="_blank">AcWing 1470. 水桶传递队列</a> code</summary>

```cpp
#define fst first
#define sed second

#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

char g[15][15];  // 地图
int used[15][15];// 是否到达过
int ans[15][15]; // 到达该点的最短路径
int dxy[4][2]={ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 结束点
int ex, ey;
// 开始点
int sx, sy;

void BFS(int x, int y){
    
    queue<PII> q;
    q.push( {x, y} );
    used[x][y]=1;
    
    while( q.size() ){
        
        int nx = q.front().fst;
        int ny = q.front().sed;
        
        for(int i=0; i<4; i++){
            int nnx = nx+dxy[i][0];
            int nny = ny+dxy[i][1];
            
            if(nnx>=1&&nnx<=10 && nny>=1&&nny<=10)
            if(used[nnx][nny]==0)
            if(g[nnx][nny]!='R')
            {
                ans[nnx][nny]=ans[nx][ny]+1;
                used[nnx][nny]=1;
                q.push( {nnx, nny} );
                if(g[nnx][nny]=='B') return ;
            }
            
        }
        
        q.pop();
    }
    
}

int main(){
    
    for(int i=1; i<=10; i++){
        for(int j=1; j<=10; j++){
            scanf("%c", &g[i][j]);
            if(g[i][j]=='L')
                sx=i, sy=j;
            if(g[i][j]=='B')
                ex=i, ey=j;
        }
        getchar();
    }
    
    BFS(sx, sy);
    
    cout<<ans[ex][ey]-1;
    
    return 0;
}
```
</details>


## 2019 Feb

<details><summary><a href="https://www.acwing.com/problem/content/1685/" target="_blank">AcWing 1683. 困牛放牧</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[3];

int main(){
    cin>>a[0]>>a[1]>>a[2];
    sort(a, a+3);
    
    if(a[1]-a[0]==1 && a[2]-a[1]==1){ // 6 7 8
        cout<<0<<endl<<0;
        return 0;
    }
    
    int mmin=0;
    int mmax = max(a[2]-a[1]-1, a[1]-a[0]-1);
    
    if(a[1]-a[0]==2 || a[2]-a[1]==2)
        mmin=1;
    else
        mmin=2;
    
    cout<<mmin<<endl<<mmax;
    return 0;
}
```
</details>

<details><summary><a href="https://www.acwing.com/problem/content/1686/" target="_blank">AcWing 1684. 大型植被恢复</a> code</summary>

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back

#define x first
#define y second
typedef pair<int, int> PII;

// 每只奶牛喜欢的两块草地
PII a[160];
// 每块草地种的草
int res[110];
// 该草地不能和那些草地的草相同
vector<int> ad[110];

int main(){
    int n, m;
    cin>>n>>m;
    
    for(int i=1; i<=m; i++){
        scanf("%d%d", &a[i].x, &a[i].y);
        ad[a[i].x].pb(a[i].y);
        ad[a[i].y].pb(a[i].x); // 1号草场的不能和5，6冲突
    } 
    
    for(int i=1; i<=n; i++){
        
        // 从四块草地里选
        for(int d=1; d<=4; d++){
            
            bool flag=1;
            for(int j=0; j<ad[i].size(); j++)
                if(res[ ad[i][j] ]==d){ // 冲突
                    flag=0;
                    break;
                }
            
            if(flag){
                res[i]=d;
                break;
            }            
        }
        
    }
    
    for(int i=1; i<=n; i++)
        cout<<res[i];
    
    return 0;
}
```
</details>

## 2019 Jan

<details><summary><a href="https://www.acwing.com/problem/content/1697/" target="_blank">AcWing 1695. 果壳游戏</a> code</summary>

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 小模拟
int arr[110][4];
int n;

// 在第 u 个壳下面
int ke(int u){
    int k[4]={0};
    k[u]=1;
    int res=0;
    
    for(int i=1; i<=n; i++){
        
        swap(k[ arr[i][1] ], k[ arr[i][2] ]);
        if(k[ arr[i][3] ]) res++;
    }
    //cout<<res<<endl;
    return res;
}

int main(){
    
    cin>>n;
    for(int i=1; i<=n; i++) scanf("%d%d%d", &arr[i][1], &arr[i][2], &arr[i][3]);
    
    int ans=0;
    for(int i=1; i<=3; i++)
        ans = max( ans, ke(i) );
    
    cout<<ans;
    
    return 0;
}
```
</details>

## 2018 Dec

<details><summary><a href="https://www.acwing.com/problem/content/1716/" target="_blank">AcWing 1714. 混合牛奶</a> code</summary>

```cpp
#include <iostream>
using namespace std;

int C[5], M[5];

int main(){
    for(int i=1; i<=3; i++)
        scanf("%d%d", &C[i], &M[i]);
    
    for(int i=1; i<=33; i++){
        // 桶1 到 桶2
        int t=M[1]+M[2];
        if( t>C[2] ){   // 不够装
            M[2]=C[2];  // 装满
            M[1]=t-M[2];// 桶1的奶
        }
        else{
            M[1]=0;
            M[2]=t;
        }
        
        // 桶2 到 桶3
        t=M[2]+M[3];
        if( t>C[3] ){   // 不够装
            M[3]=C[3];  // 装满
            M[2]=t-M[3];// 桶2的奶
        }
        else{
            M[2]=0;
            M[3]=t;
        }
        
        // 桶3 到 桶1
        t=M[3]+M[1];
        if( t>C[1] ){   // 不够装
            M[1]=C[1];  // 装满
            M[3]=t-M[1];// 桶3的奶
        }
        else{
            M[3]=0;
            M[1]=t;
        }
        
    }
    
    // 桶1 到 桶2
    int t=M[1]+M[2];
    if( t>C[2] ){   // 不够装
        M[2]=C[2];  // 装满
        M[1]=t-M[2];// 桶1的奶
    }
    else{
        M[1]=0;
        M[2]=t;
    }
    
    cout<<M[1]<<endl<<M[2]<<endl<<M[3];
    
    return 0;
}
```
</details>


<details><summary><a href="https://www.acwing.com/problem/content/1717/" target="_blank">AcWing 1715. 桶列表</a> code</summary>

```cpp
#include <iostream>
using namespace std;

int arr[1010];

int main(){
    int n;
    cin>>n;
    for(int i=1; i<=n; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        
        arr[a]+=c;
        arr[b]-=c;
    }
    
    int ans=0;
    
    for(int i=1; i<=1000; i++){
        arr[i]+=arr[i-1];
        ans=max(ans, arr[i]);
    }
    
    cout<<ans;
    
    return 0;
}
```
</details>

---


# <center>2017-2018 Season</center>