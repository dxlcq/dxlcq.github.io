---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---


# 2 线性表

## 2.1 线性表的类型定义

> `线性表`
> * 由n个`数据元素`组成的有限序列
> 
> `数据元素`
> * 由n个`数据项`组成
> 
> 亦可称数据元素为记录, 线性表为文件, 文件由n条记录组成


---

## 2.2 线性表的顺序表示和实现

> `线性表的顺序表示`
>   * 一组连续的存储单元依次存储线性表的数据元素
>       * 逻辑相邻
>       * 物理相邻

<details><summary>初始化</summary> 

```cpp
#include <stdio.h>
#include <stdlib.h>

typedef int ELEM;       // 定义数据元素类型

struct List{            // 线性表
    ELEM*   begin;      // 线性表的起始地址
    int     length;     // 线性表的长度
    int     listsize;   // 线性表的大小
};
 
int InitList(List& L, const int len){           // 初始化线性表
    L.begin = (ELEM*)malloc(len * sizeof(ELEM));// 申请堆空间
    if(!L.begin) return 0;                      // 申请失败
    L.length    = 0;                            // 初始长度
    L.listsize  = len;                          // 线性表大小(总共)
    return 1;                                   // 初始化线性表成功
}

int main(){
    List L;
    InitList(L, 100);
    return 0;
}
```
</details>

<details><summary>销毁</summary> 

```cpp
int DestroyList(List& L){   // 销毁线性表
    free(L.begin);          // 释放空间
    L.length=0;             // 长度置0
    L.listsize=0;           // 大小置0
    return 1;               // 销毁成功
}
```
</details>

<details><summary>判断空表</summary> 

```cpp
int EmptyList(List& L){ // 判断线性表是否为空
    return L.length==0; // 如果为空,返回1,反之返回0
}
```
</details>

<details><summary>获取元素个数</summary> 

```cpp
int LenList(List& L){   // 获取表中元素个数
    return L.length;    // 返回表中元素个数
}
```
</details>

<details><summary>获取表的大小</summary> 

```cpp
int SizeList(List& L){  // 获取表的大小
    return L.listsize;  // 返回表的大小
}
```
</details>

<details><summary>获取第i个元素</summary> 

```cpp
int GetElem(List& L, int i, ELEM& e){   // 获取第i个元素
    if(!EmptyList(L) && i<=LenList(L)){ // 第i个元素是合法的,存在的
        e = *(L.begin+i-1);             // 直接拿
        return 1;                       // 成功获取
    }
    return 0;                           // 获取失败
}
```
</details>

<details><summary>获取第i个元素的前驱</summary> 

```cpp
int PriElem(List& L, int i, ELEM& e){   // 获取第i个元素的前驱
    if(GetElem(L, i-1, e)) return 1;
    return 0;
}
```
</details>

<details><summary>获取第i个元素的后继</summary> 

```cpp
int NextElem(List& L, int i, ELEM& e){  // 获取第i个元素的后继
    if(GetElem(L, i+1, e)) return 1;
    return 0;
}
```
</details>

<details><summary>在第i个位置前插入元素(令第i个位置为新元素)</summary> 

```cpp
int InsertElem(List& L, int i, ELEM e){     // 在第i个位置前插入元素e
    if(LenList(L) >= SizeList(L)) return 0; // 空间满
    for(int j=LenList(L); j>=i; j--)        // 挨个后移,从尾元素开始
        *(L.begin+j) = *(L.begin+j-1);      // L.begin+j-1 是最后一个元素的位置
    *(L.begin+i-1) = e;                     // L.begin+i-1  是第i个元素的位置
    L.length++;                             // 表的长度增加
    return 1;                               // 插入成功
}
```
</details>

<details><summary>删除第i个位置的元素</summary> 

```cpp
int DeleteElem(List& L, int i){
    if(EmptyList(L) || i>LenList(L)) return 0;  // 第i个元素是不合法的,不存在的
    for(int j=i; j<=LenList(L); j++)
        *(L.begin+i-1) = *(L.begin+i);          // 挨个前移
    L.length--;                                 // 长度减少
    return 1;                                   // 删除成功
}
```
</details>


<details><summary>合并两表</summary> 

```cpp
int MergeList(List& A, List& B, List& C){               // 合并有序表AB至C中
    for(int i=1, j=1; i<=LenList(A) || j<=LenList(B);){ // i指向A, j指向B
        ELEM ai, bj;                                    
        GetElem(A, i, ai), GetElem(B, j, bj);           // 获取元素
        if(i<=LenList(A) && (ai<=bj || j>LenList(B)))   // 能够插入到C中,一定满足
            InsertElem(C, i+j-1, ai), i++;              // A中还有元素
        if(j<=LenList(B) && (bj<=ai || i>LenList(A)))   // ai<=bi 或 B中没有元素
            InsertElem(C, i+j-1, bj), j++;              // B同理
    }
    return 1;                                           // 合并成功
}
```
</details>

---

## 2.3 线性表的链式表示和实现

> `线性表的链式表示`
>   * 一组任意的存储单元依次存储线性表的数据元素
>       * 逻辑相邻
>       * 物理不相邻

<details><summary>生成一个结点</summary> 

```cpp
node* MakeNode(ELEM e = 0) {    // 创建结点
    node* p = (node*)malloc(sizeof(node));
    if (!p) return NULL;        // 申请失败
    p->date = e;                
    p->next = NULL;
    return p;                   // 申请成功
}
```
</details>

<details><summary>释放一个结点</summary> 

```cpp
void FreeNode(node* p) {        // 释放结点
    free(p);
}
```
</details>

<details><summary>初始化</summary> 

```cpp
#include <stdio.h>
#include <stdlib.h>

typedef int ELEM;

struct node {
    ELEM    date;   // 数据
    node*   next;   // 后继
};

struct List {
    int     len;    // 长度
    node*   head;   // 头结点
};

int InitList(List& L) {     // 初始化
    L.head = MakeNode();    // 创建头结点
    L.len = 0;              // 长度
    if (L.head) return 1;   // 创建成功
    return 0;               // 创建失败
}

int main() {
    List L;
    InitList(L);    // L.head指向表的头节点
    
    return 0;
}
```
</details>

<details><summary>销毁</summary> 

```cpp
int DestroyList(List& L) {  // 销毁表
    node* p = L.head;       // p指向 i
    while (p) {             // i 不为空
        L.head = p->next;   // i 指向 i+1
        free(p);            // 删除 i
        p = L.head;         // p指向 i+1
    }                       // 当p指向空的时候,结束
    return 1;               // 销毁成功
}
```
</details>

<details><summary>判断空表</summary> 

```cpp
int EmptyList(List& L) {    // 判断表是否空
    return L.len == 0;
}
```
</details>

<details><summary>获取元素个数</summary> 

```cpp
int LenList(List& L) {      // 获取元素个数
    return L.len;
}
```
</details>

<details><summary>获取第i个元素</summary> 

```cpp
node* GetElem(List& L, unsigned int i) {// 获取第 i 个元素
	if (i > LenList(L))                 // 查找范围不合法
        return NULL;                    // 获取失败
    node* p = L.head;                   // p 指向头节点
    for (int j = 1; j <= i; j++)        // p会指向后驱 i 次
        p = p->next;                        
    return p;                           // 获取成功
}
```
</details>

<details><summary>获取第i个元素的前驱</summary> 

```cpp
node* GetElemPri(List& L, unsigned int i) { // 获取第 i 个元素的前驱
    return GetElem(L, i - 1);
}
```
</details>

<details><summary>获取第i个元素的后继</summary> 

```cpp
node* GetElemNext(List& L, unsigned int i) {// 获取第 i 个元素的后继
    return GetElem(L, i + 1);
}
```
</details>

<details><summary>在第i个位置前插入元素</summary> 

```cpp
int InsertElemPri(List& L, unsigned int i, ELEM e) {    // 在第 i 个元素前插入元素
    if (i == 0 || i > LenList(L)) return 0; // 插入位置不合法
    node* p = GetElemPri(L, i);             // 第 i 个元素的前驱
    node* elem = MakeNode(e);               // 创建结点     
    if (!p) return 0;                       // 失败
    if (!elem) return 0;                    // 失败
    elem->next = p->next;                   // 新结点指向 i
    p->next = elem;                         // 前驱指向新结点
    L.len++;
    return 1;
}
```
</details>

<details><summary>在第i个位置后插入元素</summary> 

```cpp
int InsertElemNext(List& L, unsigned int i, ELEM e) {   // 在第 i 个元素后插入元素
    if (i > LenList(L))return 0;            // 插入位置不合法, 允许在第0个结点后插入
    node* p = GetElem(L, i);                // 第 i 个元素
    node* elem = MakeNode(e);               // 创建结点     
    if (!p) return 0;                       // 失败
    if (!elem) return 0;                    // 失败
    elem->next = p->next;                   // 新结点指向 i
    p->next = elem;                         // 前驱指向新结点
    L.len++;
    return 1;
}
```
</details>

<details><summary>删除第i个位置的元素</summary> 

```cpp
int DeleteElem(List& L, int i) {                    // 删除第 i 个元素
    if (EmptyList(L) || i > LenList(L)) return 0;   // 第i个元素是不合法的,不存在的
    node* p = L.head;                               // 指向头
    for (int j = 1; j < i; j++) p = p->next;        // 指向后驱 i-1 次,最终指向第 i-1 个元素
    node* bp = p->next;                             // 标记一下第i个结点
    p->next = p->next->next;                        // p 指向 第i个结点的后继, 直接跳过 i 
    FreeNode(bp);                                   // 释放结点
    return 1;                                       // 删除成功
}
```
</details>




<details><summary>合并两表</summary> 

```cpp
int MergeList(List& A, List& B, List& C) {  // 合并有序表AB至C中
    node* pa = A.head->next;                // 指向A的第一个元素
    node* pb = B.head->next;                // 指向B的第一个元素
    while (pa || pb) {                      // 如果还存在
        ELEM ne = 0;
		if (pa && (!pb || pa->date <= pb->date))
            ne = pa->date, pa = pa->next;
        else if (pb && (!pa || pb->date <= pa->date))
            ne = pb->date, pb = pb->next;
        InsertElemNext(C, LenList(C), ne);  // 插入新元素到C的最后
    }
    return 1;
}
```
</details>




--- 

## 2.4 一元多项式的表示及相加








# 6 树和二叉树

## 6.1 树的定义

**树** 是 n（n>=0）个结点的有限集。当n=0时，称为空树，在任意一棵非空树中，存在：
* 有且仅有一个特定的称为根（Root）的结点
    * 没有父节点的节点称为根节点
* 任意非根结点 **有且仅有一个** 父结点
* 除了根结点外，每个子结点可以分为多个不相交的子树
* 树中没有环路

#### 基本术语

* 结点的度：结点拥有的子树的个数


# 6.x 树的拓展

## 分类

#### 有序无序：
* **无序 / 自由树**：结点的各子节点之间 **没有** 顺序关系
* **有序 / 搜索 / 查找树**：结点的各子节点之间 **有** 顺序关系

#### 平衡非平衡：
* **非平衡树**
* **平衡树**：
    任意节点的两个子树的高度差不超过一个固定的常数
    * **绝对平衡树**：`常数 = 0`，即从根节点到任意叶子节点的路径长度相等
    * **相对平衡树**：当我们说到平衡树时，一般指相对平衡树

#### 分叉情况：
* **等叉树**：子结点个数相同
    * **二叉树**：所有结点的度不超过  2
        * **完全二叉树**：叶子结点只能出现在最下层和次下层，并且最下层的结点都集中在该层最左边的若干位置的二叉树
            * **满二叉树**：所有叶子结点都在最下层的完全二叉树
    * **n叉树**：所有结点的度不超过 n
    * **霍夫曼树**：带权路径最短的二叉树
* **不等叉树**：子结点个数不一定相同
    * **B树**：


####  常见树：
* [二叉搜索树](#bst) $BST$，$Binary ~ Sort ~ Tree$，又被翻译为 *二叉排序树、二叉查找树*
    二叉搜索树期望复杂度为 $O(logn)$，最坏情况下退化为偏斜二元树 $O(n)$
    因此改进为 **平衡二叉搜索树**：
    * [平衡二叉树]() $AVL$，$Adelson-Velsky ~ and ~ Landis ~ Tree$
    * [红黑树]() $RB$，$Red ~ Black ~ Tree$
    * [伸展树] $Splay$，$Splay ~ Tree$
    * [替罪羊树] $Scapegoat$，$Scapegoat ~ Tree$


* [B树]() $B-Tree$
    * [B+树]() $B+Tree$
    * [B*树]() $B*Tree$


## BST

二叉搜索树具有如下性质：

* 若结点左子树不空，则 **左** 子树上任意结点的值均 **小于** 它的 **根** 结点的值
* 若结点右子树不空，则 **右** 子树上任意结点的值均 **大于** 它的 **根** 结点的值
* 任意结点的左右子树也分别为 **二叉搜索树**

显然，在此树中查找某个结点的花费为树的高度，因此：

* 查找：$O(logn)$
* 插入：$O(logn)$
* 删除：$O(logn)$



    