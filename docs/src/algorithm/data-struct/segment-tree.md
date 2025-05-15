## Template


操作 **加** 与 **乘**，维护 **极大极小值** 与 **和**

```c
typedef long long int LL;

#define N 200010
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int l, r;
    LL mul;     // lazytag
    LL add;     // lazytag
    LL sum;     // 维护的结果们
    LL mmax;    
    LL mmin;
} node;

node tr[4*N];
LL a[N];
LL MOD = 1e15;

void pushup(int u) {
    tr[u].sum = (tr[u<<1].sum + tr[u<<1|1].sum) % MOD;
    tr[u].mmax = max(tr[u<<1].mmax, tr[u<<1|1].mmax);
    tr[u].mmin = min(tr[u<<1].mmin, tr[u<<1|1].mmin);
}   // 将 u 节点左右子树的信息更新到 u 节点

void pushdown(int u) {
    int l = u << 1;
    int r = u << 1 | 1;
    // 将 mul * 儿子的值 + add * 区间长度
    tr[l].sum = (tr[u].mul * tr[l].sum + tr[u].add * (tr[l].r - tr[l].l + 1)) % MOD;
    tr[r].sum = (tr[u].mul * tr[r].sum + tr[u].add * (tr[r].r - tr[r].l + 1)) % MOD;
    // 更新极值
    tr[l].mmax= (tr[u].mul * tr[l].mmax+ tr[u].add) % MOD;
    tr[r].mmax= (tr[u].mul * tr[r].mmax+ tr[u].add) % MOD;
    tr[l].mmin= (tr[u].mul * tr[l].mmin+ tr[u].add) % MOD;
    tr[r].mmin= (tr[u].mul * tr[r].mmin+ tr[u].add) % MOD;
    // lazytag 下放
    tr[l].mul = tr[l].mul * tr[u].mul % MOD;
    tr[r].mul = tr[r].mul * tr[u].mul % MOD;
    tr[l].add = (tr[l].add * tr[u].mul + tr[u].add) % MOD;
    tr[r].add = (tr[r].add * tr[u].mul + tr[u].add) % MOD;
    // 父节点 lazytag 恢复初始
    tr[u].mul = 1;
    tr[u].add = 0;
}   // 将 u 节点的信息更新到 u 节点的左右子树
    
void modify_mul(int u, int l, int r, LL v) {
    if(l > tr[u].r  || tr[u].l > r) return; // 没有交集
    if(l <= tr[u].l && tr[u].r <= r){       // 完全包含
        tr[u].mul = (tr[u].mul * v) % MOD;
        tr[u].add = (tr[u].add * v) % MOD;
        tr[u].sum = (tr[u].sum * v) % MOD;
        tr[u].mmax= (tr[u].mmax* v) % MOD;
        tr[u].mmin= (tr[u].mmin* v) % MOD;
        return;
    }
    pushdown(u);
    modify_mul(u<<1,   l, r, v);
    modify_mul(u<<1|1, l, r, v);
    pushup(u);
}

void modify_add(int u, int l, int r, LL v) {
    if(l > tr[u].r  || tr[u].l > r) return;
    if(l <= tr[u].l && tr[u].r <= r){
        tr[u].add = (tr[u].add + v) % MOD;
        tr[u].sum = (tr[u].sum + v * (tr[u].r - tr[u].l + 1)) % MOD;
        tr[u].mmax= (tr[u].mmax+ v) % MOD;
        tr[u].mmin= (tr[u].mmin+ v) % MOD;
        return;
    }
    pushdown(u);
    modify_add(u<<1,   l, r, v);
    modify_add(u<<1|1, l, r, v);
    pushup(u);
}

node query(int u, int l, int r) {
    if(l > tr[u].r || tr[u].l > r){
        node T = {0, 0, 1, 0, 0, 0, 0};
        return T;
    }
    if(l <= tr[u].l && tr[u].r <= r) return tr[u];
    pushdown(u);
    node ans;   // 合并答案
    node left = query(u<<1,   l, r);
    node right= query(u<<1|1, l, r);
    ans.sum = (left.sum + right.sum) % MOD;
    ans.mmax= max(left.mmax, right.mmax);
    ans.mmin= min(left.mmin, right.mmin);
    return ans;
}

void build(int u, int l, int r) {
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
```


* 区间开根号
* 区间修改


<br>

---


