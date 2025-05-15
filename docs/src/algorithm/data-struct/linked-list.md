## 带头单链表

### 增

<details><summary>通过序列生成链表</summary>

<b>思路</b>

<ol>
<li> 创建一个头，即链表 </li>
<li> 向链表的尾部插入新的节点</li>
</ol>

```c
#include <stdio.h>
#include <stdlib.h>
const int N = 2e5+10;

struct node{
    int     val;
    node*   ne;
};

int a[N], n;

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", a+i);

    // 新建一个节点, 头节点, 也指此链表
    node* head = (node*)malloc(sizeof(node));
    head->val = 0;              // head 的 val 存放节点数量
    head->ne = NULL;            // head 的 ne 指向下一个节点

    // 新建一个指针, 当前操作位置
    node* pos = head;

    for(int i=1; i<=n; i++){
        // 新建一个节点, 新的节点
        node* newNode = (node*)malloc(sizeof(node));
        newNode->val = a[i];
        newNode->ne = NULL;

        pos->ne = newNode;      // 当前节点的下一个 = 新节点
        pos = newNode;          // 当前节点 = 新节点

        head->val ++;
    }

    pos = head->ne;
    while(pos != NULL){
        printf("%d ", pos->val);
        pos = pos->ne;
    }

    return 0;
}
```
</details>

<details><summary> <a href="https://leetcode.cn/problems/add-two-numbers/description/">LC 2. 两数相加</a> </summary>

<b>思路</b>

<ol>
<li> 将数全部加到其中一个链表中去，前期无法判断哪个链表长，因此都加 </li>
</ol>

```cpp
class Solution {
public:
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    bool flg = true;    // l1
    bool add = false;   // 是否存在进位
    ListNode* p1 = l1;
    ListNode* p2 = l2;
    ListNode* t = l1;   // 最后一位
    
    while(p1 && p2){
        int v = p1->val + p2->val + add;
        p1->val = v%10;
        p2->val = v%10;
        
        add = v/10;
        
        t = p1;

        p1 = p1->next;
        p2 = p2->next;
    }

    while(p1){
        flg = true;
        int v = p1->val + add;
        
        p1->val = v%10;
        add = v/10;

        t=p1;
        p1 = p1->next;
    }

    while(p2){
        flg = false;
        int v = p2->val + add;

        p2->val = v%10;
        add = v/10;

        t=p2;
        p2 = p2->next;
    }

    if(add){
        t->next = new ListNode(1);
    }

    return flg ? l1 : l2;
}
};
```
</details>

<details><summary> <a href="https://leetcode.cn/problems/merge-two-sorted-lists/description/"> LC 21. 合并两个有序链表 </a>  </summary>

<b>思路</b>

<ol>
<li>递归</li>
</ol>

```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == nullptr)
            return list2;
        else if(list2 == nullptr)
            return list1;
        else if(list1->val < list2->val){
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
```
</details>

<details><summary> <a href="https://leetcode.cn/problems/merge-k-sorted-lists/description/"> LC 23. 合并 K 个升序链表 </a>  </summary>

<b>思路</b>

<ol>
<li> 搞一个新的链表 h </li>
<li> 每次遍历确定一个最小的 </li>
<li> 将这个最小的往 h 上凑 </li>
</ol>

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        
        ListNode* h = new ListNode(-1); // 搞个头
        ListNode* pos = h;              // 当前操作位

        bool flg = true;
        while(flg){
            flg = false;
            int mmin = 0x3f3f3f3f;
            int j = 0;

            for(int i=0; i<lists.size(); i++){
                if(lists[i] && lists[i]->val < mmin){
                    j = i;
                    mmin = lists[i]->val;
                }
            }

            if(mmin != 0x3f3f3f3f){
                flg = true;
                pos->next = lists[j];
                pos = pos->next;            // 后移
                lists[j] = lists[j]->next;  // 后移
            }
        }

        return h->next;
    }   
};
```
</details>


### 删

<details><summary><a href="https://leetcode.cn/problems/remove-nth-node-from-end-of-list/">LC 19. 删除链表的倒数第 N 个结点</a></summary>

<b>思路</b>

<ol>
<li> 弄一个头节点出来 </li>
<li> 计算删除的位置，直接删除即可 </li>
</ol>

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 搞个头
        ListNode* h = new ListNode(0);
        h->next = head;
        // 算个长度
        ListNode* pos = head;
        int sz = 0;
        while(pos){
            sz ++;
            pos = pos->next;
        }
        n = sz - n;
        // 删除 n 节点之后的节点
        pos = h;
        while(n--) pos = pos->next;
        pos->next = pos->next->next;
        return h->next;
    }
};
```
</details>


### 改

<details><summary> <a href="https://leetcode.cn/problems/swap-nodes-in-pairs/description/"> LC 24. 两两交换链表中的节点 </a>  </summary>

<b>思路</b>

<ol>
<li> 弄一个头节点出来 </li>
<li> 每次获取后面俩节点，能换则换 </li>
</ol>

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* h = new ListNode(-1, head);// 搞一个头
        ListNode* pos = h;          // 操作位

        ListNode* a = nullptr, *b = nullptr;
        while(pos->next){
            a = pos->next;
            if(a->next){            // 如果 b 存在则换
                b = a->next;
                ListNode* c = b->next;

                pos->next = b;
                pos->next->next = a;
                pos->next->next->next = c;

                pos = pos->next;    // 一次后移
            }
            pos = pos->next;        // 一次后移

            a = b = nullptr;
        }

        return h->next;
    }
};
```
</details>

### 查


<br>

---

## 双向链表


<br>

---

## 循环链表