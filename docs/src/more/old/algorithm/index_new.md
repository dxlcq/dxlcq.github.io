---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---

# 引子

1. 在项目目录下创建运行脚本 `ac.sh`

    ```shell
    cppVersion="c++17"
    runTime="3s"
    keepLine="30000"

    echo -n '⏳' > 'exes/out' && \
    g++ -g -std="$cppVersion" ac.cpp -o exes/ac && \
    cat 'exes/in' | \
    timeout "$runTime" sh -c "'exes/ac' > 'exes/out.raw'"

    if [ $? -ne 0 ]; then
        echo -e "\033[0;31m TLE "$runTime" \033[0m"
    fi  # 检查 timeout 命令的退出状态

    head -n "$keepLine" 'exes/out.raw' > 'exes/out'
    ```



2. 所有文件结构如此：
    ```
    ├── exes/
    |   ├── ac
    |   ├── in
    |   ├── out
    |   ├── out.raw
    |
    ├── ac.cpp
    ├── ac.sh
    ```

<br>

---

# 入门

<br>

---

# 基础

### 二分

* 作用：
* 时间复杂度：
* 核心思想：

```cpp
while(l<r){
    int mid = l+r >> 1;
    if(a[mid] >= x) r=mid;  // 右边是合法的, r向中间靠
    else l=mid+1;
}

while(l<r){
    int mid = l+r+1 >> 1;
    if(a[mid] <= x) l=mid;  // 左边是合法的, l向中间靠
    else r=mid-1;
}

int* b = lower_bound(a, a + 10, 3);	// 返回 第一个 3 的地址
vector<int>::iterator i = upper_bound(a.begin(), a.end(), 2);	// 返回迭代器
```

<br>

---

# 搜索

<br>

---

# 动规

<br>

---

# 字符串

## KMP

* 作用：字符串中查找子串
* 时间复杂度：$O(n+m)$，$n$ 为字符串长度，$m$ 为子串长度
* 核心思想：通过预处理子串，生成部分匹配表（前缀函数），利用此表在匹配过程中跳过匹配的部分

```cpp
vector<int> KMP(string s, string p){    // 返回所有匹配的位置
    int n=s.size(), m=p.size();
    s = " " + s, p = " " + p;
    vector<int> res, ne(m+1);
    for(int i=2, j=0; i<=m; i++){       // 预处理得部分匹配表
        while(j && p[j+1]!=p[i]) j=ne[j];
        if(p[i] == p[j+1]) j++;
        ne[i]=j;
    }   // m - ne[m] 为最小循环子串的长度
    for(int i=1, j=0; i<=n; i++){       // KMP 匹配
        while(j && p[j+1]!=s[i]) j=ne[j];
        if(s[i] == p[j+1]) j++;
        if(j == m){
            j = ne[j];                  // 当匹配成功时继续
            res.push_back(i-m);
        }
    }
    return res;
}
```

## Trie

* 作用：存储字符串集合，可查询某个字符串出现的次数
* 时间复杂度：插入与搜索均为 $O(n)$，空间占用小
* 核心思想：逐字符存储，利用字符串的公共前缀来节省存储空间，并加快查询速度

```cpp
class Trie{
public:
    Trie(int n=1e5):
        son(n+1, vector<int>(27)),  // 仅包含小写字母
        idx(0){};
    ~Trie(){};

    void insert(string &s){
        int p = 0;                  // deep
        for(auto &c: s){
            if(!son[p][c-'a'])
                son[p][c-'a'] = ++idx;
            p = son[p][c-'a'];
        }
        cnt[p]++;
    }

    int query(string &s){           // 此字符出现次数
        int p = 0;
        for(auto &c: s){
            if(!son[p][c-'a'])
                return 0;
            p = son[p][c-'a'];
        }
        return cnt[p];
    }

private:
    vector<vector<int>> son;        // 树
    map<int, int> cnt;              // 某节点结尾的字符串数量
    int idx;                        // 当前插入节点的值
};
```

<br>

---

# 数学

## 异或性质

## 大数运算

* 作用：高精度 加减乘除幂
* 时间复杂度：一次加减乘除为 $O(n)$，一次幂运算为 $O(\log n)$，前者的 $n$ 为数字的长度，后者的 $n$ 为 $num^n$
* 核心思想：

```cpp
string ADD(string A, string B, bool flg = 1) { // 默认 正序(正整数)输入 正序输出
    if (flg) reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    string res; int add = 0;
    for (int i = 0; i < A.size() || i < B.size() || add; i++) {
        if (i < A.size()) add += A[i] - '0';// 取值
        if (i < B.size()) add += B[i] - '0';// 取的A,B相同低位
        res += add % 10 + '0';              // +
        add /= 10;                          // 进位
    }
    if (flg) reverse(res.begin(), res.end());
    return res; // flg == 0 倒叙输入输出模式 (在连续计算时减少reverse次数,以提升性能)
}

string SUB(string A, string B) {  // 正序输入 正序输出
    if (!(A.size() > B.size() || (A.size() == B.size() && A >= B)))
        return "-" + SUB(B, A);   // 非 A > B 的情况
    reverse(A.begin(), A.end()); reverse(B.begin(), B.end());
    string res;                 // 低位向高位减
    for (int i = 0, t = 0; i < A.size(); i++) {
        int ai = A[i] - '0';                // 换成 int
        int bi = i < B.size() ? B[i] - '0' : 0; // B位数不够
        t = ai - bi - t;                    // 减去
        res.push_back((t + 10) % 10 + '0'); // 保证是正数
        if (t < 0) t = 1;                   // 借走了一位
        else t = 0;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string MUL(string A, int b) { // 正序输入 正序输出
    reverse(A.begin(), A.end());
    string res;
    int x = 0;
    for (int i = 0; i < A.size() || x; i++) {
        if (i < A.size()) x += (A[i] - '0') * b;
        res.push_back(x % 10 + '0');
        x /= 10;
    }   // 去前导0
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string DIV(string A, int b, int& r) {    // A / b = res ... r 
    string res;    // 正序(正整数)输入 正序输出
    r = 0;
    for (int i = 0; i < A.size(); i++) {
        int ai = A[i] - '0';
        r = r * 10 + ai;            // r从高位下来,故*10
        res.push_back(r / b + '0'); // 整数位压入res
        r %= b;                     // 余数
    }
    while (res.size() > 1 && res.front() == '0') res.erase(res.begin(), res.begin() + 1);
    return res; // 去除前导 0 
}

LL qmi(LL a, LL k, LL p){       // a^k == a^(k/2)^2
    if(k==0) return 1;          // 次方为 0
    LL res = qmi(a, k>>1, p);   // 计算 a^(k/2)
    if(!(k&1)) return (res%p * res%p) % p; 
    return (res%p * res%p * a) % p; // 对于不能除尽的, 还需再 *a
}
```

## 进制转换

* 作用：将 $num_a$ 转换为 $num_b$
* 时间复杂度：$O(n)$，其中 $n$ 为 $num$ 的长度
* 核心思想：

```cpp
string num_a2b(string num, int a, int b) {
    string res = "0", p = "1"; // 将 a 进制下的 num 转换为 10 进制
    for (int i = num.size() - 1; i >= 0; i--) {
        int t; // 判断当前位数字是多少
        if (num[i] >= '0' && num[i] <= '9') t = num[i] - '0';
        if (num[i] >= 'A' && num[i] <= 'Z') t = num[i] - 'A' + 10;
        //if(num[i]>='a' && num[i]<='z') t=num[i]-'a'+10;
        res = ADD(res, MUL(p, t));//res+=t*p; // t*(a^0, a^1, a^2)
        p = MUL(p, a); //p*=a; // (a^0, a^1, a^2)
    }
    if (b == 10) return res;
    num = res; res = ""; // 将 10 进制下的 num 转换为 b 进制
    while (num != "0") {
        int r;
        num = DIV(num, b, r);
        if (r >= 0 && r <= 9) r += '0';
        else r += 'A' - 10;
        res += r;
    }
    reverse(res.begin(), res.end());
    return res;
}
```

## 线筛 / 欧拉筛

* 作用：生成素数
* 时间复杂度：$O(n)$
* 核心思想：让每个合数只被它的最小质因子筛选一次

```cpp
bool st[N]={1, 1};  // 0,1 不是素数
int primes[N];      // 素数集, primes[0] 为素数个数

void makePrimes(int n){// 生成 [2,n] 的素数
    for(int i=2; i<=n; i++){
        if(!st[i]) primes[++(*primes)]=i;   // 登记素数
        for(int j=1; j<=(*primes) && primes[j]<=n/i; j++){
            st[primes[j]*i]=1;              // 筛掉
            if(i%primes[j]==0) break;       // i 是 primes[j] 的倍数
        }   // 如果 i 是 primes[j] 的倍数, primes[j] 就是其最小质因子
    }       // 因此, 我们不必用其他质因子去筛了
}
```

## 六倍原理

* 作用：判断某数是否是素数
* 时间复杂度：
* 核心思想：素数只可能出现在 $6$ 的倍数附近，大于 $3$ 的质数一定为 $6 * i \pm 1$

```cpp
bool isPrime(LL x){
    if(x==2 || x==3   || x==5   ) return 1;
    if(x<2  ||(x%6!=1 && x%6!=5)) return 0; // 不与6的倍数相邻 
    for(LL i=5; i<=x/i; i+=6)  // 与6相邻, 但又有了因子 
        if(x%i==0 || x%(i+2)==0) return 0;
    return 1;
}
```

<br>

---

# 数据结构

## 栈

## 队列

## 单调栈

## 单调队列

## 并查集

1. 朴素并查集

* 作用：
* 时间复杂度：
* 核心思想：

```cpp
// 初始化
for(int i=1; i<=n; i++) p[i]=i;     // 自己是自己的祖先
// 查找
int find(int x){                    // 找 x 的祖先
    if(p[x] != x) p[x] = find(p[x]);// 如果 x 的祖先不是自己
    return p[x];                    // 会在这个过程中合并
}
// 合并
p[find(a)] = find(b);               // a -> b
```

2. 维护数量的并查集

* 作用：
* 时间复杂度：
* 核心思想：


## 线段树

```cpp
#include <stdio.h>

typedef long long int LL;

#define N 1000010
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int l, r;
    LL mul;     // lazytag 乘
    LL add;     // lazytag 加
    LL upd;     // lazytag 改
    int d;      // 是否有 upd 操作
    LL sum;     // 维护的结果们
    LL mmax;    
    LL mmin;
} node;

node tr[4*N];
LL a[N];
//LL MOD = 1e18;
LL inf = 1e18;

void pushup(int u){
    tr[u].sum = (tr[u<<1].sum + tr[u<<1|1].sum);// % MOD;
    tr[u].mmax = max(tr[u<<1].mmax, tr[u<<1|1].mmax);
    tr[u].mmin = min(tr[u<<1].mmin, tr[u<<1|1].mmin);
}   // 将 u 节点左右子树的信息更新到 u 节点，通常是结果上传

void pushdown(int u){
    int l = u << 1;
    int r = u << 1 | 1;
        
    if(tr[u].d == 1){   // 存在修改
        // 更新 值
        tr[l].sum = (tr[u].upd * (tr[l].r - tr[l].l + 1));// % MOD;
        tr[r].sum = (tr[u].upd * (tr[r].r - tr[r].l + 1));// % MOD;
        tr[l].mmax= tr[u].upd;
        tr[r].mmax= tr[u].upd;
        tr[l].mmin= tr[u].upd;
        tr[r].mmin= tr[u].upd;
        // 更新懒标
        tr[l].upd = tr[u].upd;
        tr[r].upd = tr[u].upd;
        tr[l].d = 1;
        tr[r].d = 1;
        // 需要一并清除子树 mul add
        tr[l].mul = 1;
        tr[r].mul = 1;
        tr[l].add = 0;
        tr[r].add = 0;
        // 父节点 lazytag 恢复初始
        tr[u].upd = 0;
        tr[u].d = 0;
    }

    // 更新值
    tr[l].sum = (tr[u].mul * tr[l].sum + tr[u].add * (tr[l].r - tr[l].l + 1));// % MOD;
    tr[r].sum = (tr[u].mul * tr[r].sum + tr[u].add * (tr[r].r - tr[r].l + 1));// % MOD;
    tr[l].mmax= (tr[u].mul * tr[l].mmax+ tr[u].add);// % MOD;
    tr[r].mmax= (tr[u].mul * tr[r].mmax+ tr[u].add);// % MOD;
    tr[l].mmin= (tr[u].mul * tr[l].mmin+ tr[u].add);// % MOD;
    tr[r].mmin= (tr[u].mul * tr[r].mmin+ tr[u].add);// % MOD;
    // 更新懒标
    tr[l].mul = tr[l].mul  * tr[u].mul;// % MOD;
    tr[r].mul = tr[r].mul  * tr[u].mul;// % MOD;
    tr[l].add = (tr[l].add * tr[u].mul + tr[u].add);// % MOD;
    tr[r].add = (tr[r].add * tr[u].mul + tr[u].add);// % MOD;
    // 父节点 lazytag 恢复初始
    tr[u].mul = 1;
    tr[u].add = 0;

}   // 将 u 节点的信息更新到 u 节点的左右子树，主要是懒标记更新


void modify_mul(int u, int l, int r, LL v){
    if(l > tr[u].r  || tr[u].l > r) return; // 没有交集
    if(l <= tr[u].l && tr[u].r <= r){       // 完全包含
        tr[u].mul = (tr[u].mul * v);// % MOD;
        tr[u].add = (tr[u].add * v);// % MOD;
        // 修改 u（直接通过 v 修改）
        tr[u].sum = (tr[u].sum * v);// % MOD; 
        tr[u].mmax= (tr[u].mmax* v);// % MOD; 
        tr[u].mmin= (tr[u].mmin* v);// % MOD; 
        return;
    }
    pushdown(u);
    modify_mul(u<<1,   l, r, v);
    modify_mul(u<<1|1, l, r, v);
    pushup(u);
}


void modify_add(int u, int l, int r, LL v){
    if(l > tr[u].r  || tr[u].l > r) return;
    if(l <= tr[u].l && tr[u].r <= r){
        tr[u].add = (tr[u].add + v);// % MOD;
        // 修改 u（直接通过 v 修改）
        tr[u].sum = (tr[u].sum + v * (tr[u].r - tr[u].l + 1));// % MOD;
        tr[u].mmax= (tr[u].mmax+ v);// % MOD;
        tr[u].mmin= (tr[u].mmin+ v);// % MOD;
        return;
    }
    pushdown(u);
    modify_add(u<<1,   l, r, v);
    modify_add(u<<1|1, l, r, v);
    pushup(u);
}

void modify_upd(int u, int l, int r, LL v){
    if(l > tr[u].r  || tr[u].l > r) return;
    if(l <= tr[u].l && tr[u].r <= r){
        tr[u].mul = 1;  // 无视
        tr[u].add = 0;  // 无视
        tr[u].upd = v;
        tr[u].d = 1;    // 存在修改
        // 修改 u（直接通过 v 修改）
        tr[u].sum = (v * (tr[u].r - tr[u].l + 1));// % MOD;
        tr[u].mmax= v;
        tr[u].mmin= v;
        return;
    }
    pushdown(u);
    modify_upd(u<<1,   l, r, v);
    modify_upd(u<<1|1, l, r, v);
    pushup(u);
}

node query(int u, int l, int r) {
    if(l > tr[u].r || tr[u].l > r){
        node T = {0, 0, 1, 0, 0, 0, 0, -inf, inf};
        return T;
    }
    if(l <= tr[u].l && tr[u].r <= r) return tr[u];
    pushdown(u);
    node ans;   // 合并答案
    node left = query(u<<1,   l, r);
    node right= query(u<<1|1, l, r);
    ans.sum = (left.sum + right.sum);// % MOD;
    ans.mmax= max(left.mmax, right.mmax);
    ans.mmin= min(left.mmin, right.mmin);
    return ans;
}

void build(int u, int l, int r){
    tr[u].l = l;
    tr[u].r = r;
    tr[u].mul = 1;
    // 其余为 0
    if(l == r) {
        tr[u].sum = a[l];
        tr[u].mmax= a[l];
        tr[u].mmin= a[l];
    }else{
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

int n, q;

int main(){
    scanf("%d%d", &n, &q);
    for(int i=1; i<=n; i++) scanf("%lld", a+i);

    build(1, 1, n);

    for(int i=1; i<=n; i++){
        LL op, l, r, v;
        scanf("%lld %lld %lld", &op, &l, &r);
        if(op == 1){
            scanf("%lld", &v);
            modify_upd(1, l, r, v);
        }else if(op == 2){
            scanf("%lld", &v);
            modify_add(1, l, r, v);
        }else if(op == 3){
            printf("%lld\n", query(1, l, r).mmax);
        }
    }

    return 0;
}
```


<br>

---

# 图论

## LCA

<br>

---

# 计算几何

<br>

---

# game

## CCF-J

## CIE

## GESP