## 二分模板

答案要求尽可能`小`，`右半边`合法，$\geq$ 目标值中，最小的一个，即`第一个`。

```cpp
while(l<r){
    int mid = l+r >> 1;
    if(a[mid] >= x) r=mid;  // 右边是合法的, r向中间靠
    else l=mid+1;
}
```

答案要求尽可能`大`，`左半边`合法，$\leq$ 目标值中，最大的一个，即`最后一个`。

```cpp
while(l<r){
    int mid = l+r+1 >> 1;
    if(a[mid] <= x) l=mid;  // 左边是合法的, l向中间靠
    else r=mid-1;
}
```


## 二分查找

<1details><summary><a href="https://www.luogu.com.cn/problem/P2249" target="_blank">Luogu P2249 【深基13.例1】查找</a> code</summary> 

<br>

**大意**

给定一个严格单调上升的数组，找到 $q$。

**思路**

1. 显然，我们可以枚举。

2. 每次找到中间的一个数 $x$，然后与 $p$ 比大小：
    * 如果 $p < x$，说明答案在 $p$ 的右边：
        ```
        L......p..x...R
               L..x...R
                
        更新 L = p
        ```
    * 如果 $x < p$，说明答案在 $p$ 的右边：
        ```
        L..x...p......R
        L..x...R 

        更新 R = p
        ```
    * 如果 $x = p$，找到。
```cpp
#include <iostream>
using namespace std;

const int N=1e6+10;

int a[N];
int n, m;

int low_b(int _a[], int l, int r, int x){
    while(l<r){
        int mid=l+r>>1;
        if(_a[mid] >= x) r=mid;
        else l=mid+1;
    }
    return a[l] == x ? l : -1;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    while(m--){
        int x; cin>>x;
        cout<<low_b(a, 1, n, x)<<" ";
    }
    return 0;
}
```


</details>

---
## 二分答案

> 如果题可以通过二分答案解决, 意味着一定是可以枚举答案解决的 ( 大概率TLE )
> 题目一般会要求我们找到一个答案, 这个答案是最优的 ( 一般来讲, 要么最小, 要么最大 )
> 只有当答案具有`单调性`的时候, 才能二分答案, 也就是左半边 ( 或者右半边 ) 的值都合法 ( 合法并不是指最优 )


<details><summary><a href="https://www.luogu.com.cn/problem/P1873" target="_blank">Luogu P1873 [COCI 2011/2012 #5] EKO / 砍树</a> code</summary> 

> 我们希望高度尽可能高, 那么就是答案尽可能大

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

const int N=1e6+10;

int a[N];
int n, m;

bool ck(int h){ // 检查h高度的和能不能达到m
    LL allh=0;
    for(int i=1; i<=n; i++)
        allh += max(0, a[i]-h);
    return allh>=m;
}

int main(){
    int l=0x3f3f3f3f, r=-0x3f3f3f3f;
    cin>>n>>m;
    for(int i=1; i<=n; i++) 
        scanf("%d", a+i), l=min(l, a[i]), r=max(r, a[i]);
    
    while(l<r){
        int mid = l+r+1>>1;
        if(ck(mid)) l=mid;
        else r=mid-1;
    }

    cout<<l;

    return 0;
}
```

</details>



<details><summary><a href="https://www.luogu.com.cn/problem/P2440" target="_blank">Luogu P2440 木材加工</a> code</summary> 

> 我们希望每根木头的长度尽可能大, 那么就是答案尽可能大

```cpp
#include <iostream>
using namespace std;

const int N=1e5+10;

int a[N];   // 每根木头的长度
int n, k;
int l=1, r=1e8;

bool ck(int len){   // 可不可以切k根len出来
    int cnt=0;
    for(int i=1; i<=n; i++)
        cnt+=a[i]/len;
    return cnt>=k;
}

int main(){
    cin>>n>>k;
    for(int i=1; i<=n; i++)
        scanf("%d", a+i);

    while(l<r){
        int mid = l+r+1>>1;        
        if(ck(mid)) l=mid;
        else r=mid-1;
    }

    if(ck(l)) cout<<l;
    else cout<<"0";

    return 0;
}
```

</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P2678" target="_blank">Luogu P2678 [NOIP2015 提高组] 跳石头</a> code</summary> 

> 经典题, 着重考察 check 函数的实现
> 最短跳跃距离的最大值, 答案尽可能大

```cpp
#include <iostream>
using namespace std;

const int N=5e4+10;

int L, m, n;
int a[N];

bool ck(int x){
    int k=m;
    int last=0; // 上一个地儿
    for(int i=1; i<=n; i++){
        if(a[i]-a[last] < x){
            k--;
            if(k<0) return 0;
            continue;
        }
        last=i;
    }
    return 1;
}

int main(){
    cin>>L>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    a[++n]=L;

    int l=0, r=1e9;
    while(l<r){
        int mid=l+r+1>>1;
        if(ck(mid)) l=mid;
        else r=mid-1;
    }

    cout<<l;

    return 0;
}
```

</details>

<details><summary><a href="https://www.luogu.com.cn/problem/P3853" target="_blank">Luogu P3853 [TJOI2007]路标设置</a> code</summary> 

> 更复杂的check函数, 此题求最小的空旷指数, 答案尽可能小

```cpp
#include <iostream>
using namespace std;

const int N=1e5+10;
int a[N];
int L, n, K;

int cnt(int x, int len){    // 将len分为x长, 分几节
    //if(x==0) return len-1;
    if(len%x==0) return len/x-1;
    else return len/x;
}

bool ck(int x){ // 检查x的距离, 是不是最大距离
    int k=K;
    for(int i=1; i<=n; i++){
        int len = a[i] - a[i-1];
        if(len > x) // 大了, 分就完事儿
            k -= cnt(x, len);
        if(k<0) return 0;
    }
    return 1;
}

int main(){
    cin>>L>>n>>K;
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    a[++n] = L;

    int l=1, r=L;
    while(l<r){ // 找 >=x 的
        int mid = l+r>>1;
        if(ck(mid)) r=mid;
        else l=mid+1;
    }
    cout<<l;
    return 0;
}
```

</details>


<details><summary><a href="https://www.luogu.com.cn/problem/P1182" target="_blank">Luogu P1182 数列分段 Section II</a> code</summary> 

> 每段和的最大值最小, 即答案尽可能小

```cpp
#include <iostream>
using namespace std;

const int N=1e5+10;

long long a[N];
int n, m;

bool ck(long long x){ // 检查x满足条件吗(区间不允许超过x)
    int last=0; // 上次结尾的点
    int k=m-1;
    for(int i=1; i<=n; i++){
        if(a[i]-a[i-1] > x) return 0;
        if(a[i]-a[last] > x){
            k--;
            last=i-1;
        }
        if(k<0) return 0;
    }
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++) scanf("%d", a+i), a[i]+=a[i-1];

    int l=1, r=1e9;
    while(l<r){
        int mid=l+r>>1;
        if(ck(mid)) r=mid;
        else l=mid+1;
    }

    cout<<l;

    return 0;
}
```

</details>


---

## 实数二分

<details><summary><a href="https://www.luogu.com.cn/problem/P3743" target="_blank">Luogu P3743 kotori的设备</a> code</summary> 

```cpp
#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e5 + 10;

int n, p;
int a[N], b[N];

bool ck(double sb) { // 用sb的时间
    double pp = p * sb; // 一共可以冲这么多电
    for (int i = 1; i <= n; i++) {
        pp -= max(0.0, a[i] * sb - b[i]);    // 要消耗的电 - 本来的电 = 需要冲的电
        if (pp < 0) return 0;
    }
    return 1;
}

int main() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);

    double l = 0, r = 1e12;

    while ( (r-l)>1e-6 ) {
        double mid = (l + r) / 2;
        if (ck(mid)) l = mid;
        else r = mid;
    }

    if ( fabs(1e12-l) <= 1e-6) cout << -1;
    else cout << l;

    return 0;
}
```

</details>

---
## STL

### lower_bound()

> 查找 `>=`目标值 的`第一个`元素

```cpp
int* b = lower_bound(a, a + 10, 3);	// 返回 第一个 3 的地址
cout << b-a;	// a[b-a] == *b == *(a+(b-a))
```

### upper_bound()

> 查找 `>` 目标值 的`第一个`元素

```cpp
vector<int>::iterator i = upper_bound(a.begin(), a.end(), 2);	// 返回迭代器
cout << i - a.begin();
```