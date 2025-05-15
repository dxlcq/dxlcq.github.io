---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---

[全国青少年软件编程等级考试标准（C语言V1.0）](https://file.qceit.org.cn/fileroot/resource/ff03c400-fee9-4f5b-a6f5-e93f8a72e79e/20200629135433696-%E5%85%A8%E5%9B%BD%E9%9D%92%E5%B0%91%E5%B9%B4%E8%BD%AF%E4%BB%B6%E7%BC%96%E7%A8%8B%E7%AD%89%E7%BA%A7%E8%80%83%E8%AF%95%E6%A0%87%E5%87%86%EF%BC%88C%E8%AF%AD%E8%A8%801%E7%BA%A7-10%E7%BA%A7%EF%BC%89-20190927.pdf)

# 三级

## 枚举

<details><summary><a href="" target="_blank"></a>余数相同问题（202109） code</summary>

<br>

**大意**

给定三个数：$a, b, c$
求 $x$，使得 $ a \% x = b \% x = c \% x $

**思路**

1. 最简单的办法，从小到大枚举 $x$。

```cpp
#include <iostream>
using namespace std;

const int N = 1e5+10;

int a, b, c;

int main(){
	cin>>a>>b>>c;
	int x=1;
	while(++x)
		if(a%x == b%x && a%x == c%x){
			cout<<x;
			break;
		}

	return 0;
}
```
</details>


<details><summary><a href="" target="_blank"></a>课程冲突（202109） code</summary>

<br>

**大意**

给定 $n$ 门课程，以及他们的开课时间 $[a, b]$，
定义冲突程度为：对于任意两门课，他们的重合天数
求，最大的冲突程度。

**思路**

1. 我们首先需要枚举所有课

2. 对于任意的两门课，求他们的冲突时间
	即，给定 $(a_1, b_1) $ 和 $(a_2, b_2)$，求他们重合的部分
	即，$min(b_1, b_2) - max(a_1, a_2)$

```cpp
#include <iostream>
using namespace std;

const int N = 1e3+10;

int a[N], b[N];
int n, ans;

int main(){
	cin>>n;
	for(int i=1; i<=n; i++) scanf("%d%d", a+i, b+i);
	
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			ans = max(ans, min(b[i], b[j]) - max(a[i], a[j]));
	
	cout<<ans;

	return 0;
}
```
</details>


<details><summary><a href="" target="_blank"></a>我家的门牌号 code</summary>

<br>

**大意**

门牌号从 $1$ 开始编号，假定有 $i$ 家，
门牌号之和为 $1+2+3+ ... +i$，令其为 $all$，
假定我的门牌号是 $j$，存在 $all - 2*j = n$，
给定 $n$，求 $i,j$。

**思路**

1. 显然，我们不知道自己的门牌号，自己的门牌号是需要枚举求出的。

2. 我们假设，现在有 $1,2,3,4...$ 个门牌号，我们可以很轻松的求出 $all$。

3. 在求出 $all$ 之后，枚举检查，是否存在一个门牌号，使得条件成立。

```cpp
#include <iostream>
using namespace std;

const int N = 1e5+10;
int all;

int main(){
	int n; cin>>n;
	for(int i=1; ; i++){	// 门牌号之和
		all += i;			// 
		for(int j=1; j<=i; j++)
			if(all - j*2 == n){
				cout<<j<<" "<<i;
				return 0;
			}
	}

	return 0;
}
```
</details>

## 递推

<details><summary><a href="" target="_blank"></a>菲波那契数列（202109） code</summary>

**大意**

求斐波那契数列第 $a$ 个数对 $1e4$ 取模的结果


**思路**

1. 顺序求 $fib$，将结果保存下来

```cpp
#include <iostream>
using namespace std;

const int mod = 1e4;
const int N = 1e6+10;
int a[N];

int main(){
	a[1] = a[2] = 1;
	for(int i=3; i<=1000000; i++)
		a[i] = (a[i-2] + a[i-1]) % mod;

	int n; cin>>n;
	while(n--){
		int x; cin>>x;
		cout<<a[x]<<"\n";
	}

	return 0;
}
```
</details>

## 递归

生成括号（202109）
广义格雷码（202109）

<br>

---

# 五级

## 搜索

[基本算法之搜索](http://noi.openjudge.cn/ch0205/)
[算法之搜索](http://noi.openjudge.cn/ch0407/)

<details><summary><a href="http://noi.openjudge.cn/ch0205/1789/" target="_blank">1789:算24</a> no code</summary><br>

**大意**




```cpp

```
</details>


<details><summary><a href="" target="_blank"></a>漫漫回国路（202009） code</summary>

<br>

**大意**

给定一个 $N*N$ 大小的矩阵 $g$。
$g[i][j]$ 的含义为 $i->j$ 的花费，如果是 $-1$，则说明无法到达
现让我们求 $1->N$ 是否能到达（不考虑花费和重复到达）。

**思路**

1. 不用考虑花费，那么 $g[i][j]$ 仅有两种状态，可以到达和不可到达。

2. 直接跑一遍传递闭包就好了。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

const int N = 20;

bool g[N][N];	// 1 表示可以飞
int n;

void solve(){
	memset(g, 0, sizeof g);
	cin>>n;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++){
			int x; cin>>x;
			if(x>0) g[i][j] = 1;
		}

	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			for(int k=1; k<=n; k++)
				g[i][j] = g[i][j] || (g[i][k] && g[k][j]);

	if(g[1][n]) puts("YES");
	else puts("NO");

	return ;
}

int main(){
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```
</details>


<details><summary><a href="" target="_blank"></a>鸣人和佐助（202009） code</summary>

<br>

**大意**

给定一个矩阵 $g$，每个位置有四种状态
* `@` 起点
* `+` 终点
* `*` 可以花费 $0$ 代价通过
* `#` 可以花费 $1$ 代价通过

每次移动花费时间 $1$，给定初始的能量，
求从起点到终点花费的最短时间

**思路**

1. 求最短路，那么肯定是 BFS 了
	* 对于可以直接通过的点，直接拓展
	* 对于需要花费代价的点，要么拓展，要么花费 $1$ 代价拓展
	* 显然，每个点可能会二次到达，所以有必要维护一个 $dis$：到达 $i,j$ 点的最小花费

2. 因此，我们队列中的每个元素，应当有:
	* 当前位置 $x, y$
	* 当前花费时间 $w$
	* 当前剩余能量 $v$

```cpp
#define fst first
#define sed second
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> PII;
const int dxy[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
const int inf = 0x3f3f3f3f;
const int N = 300;

bool g[N][N];
int dis[N][N];
int m, n, t;
PII S, E;	// 起点和终点

struct one{
	int x, y;
	int w, v;
};

int main(){
	memset(dis, 0x3f, sizeof dis);
	cin>>m>>n>>t;
	for(int i=1; i<=m; i++){
		string tt; cin>>tt;
		for(int j=1; j<=n; j++){
			if(tt[j-1] == '@') S = {i, j};
			if(tt[j-1] == '+') E = {i, j}, g[i][j] = 1;
			if(tt[j-1] == '*') g[i][j] = 1;
			if(tt[j-1] == '#') g[i][j] = 0;
		}
	}

	queue<one> q; q.push({S.fst, S.sed, 0, t}), dis[S.fst][S.sed] = 0;
	
	while(q.size()){
		auto u = q.front(); q.pop();

		if(u.x == E.fst && u.y == E.sed){
			cout<<u.w;
			return 0;
		}

		for(int i=0; i<4; i++){
			int nx = u.x + dxy[i][0];
			int ny = u.y + dxy[i][1];
			if(nx < 1 || nx > m || ny < 1 || ny > n) continue;
			
			if(g[nx][ny]){	// 可以直接去

				if(dis[nx][ny] > u.w)
					q.push({nx, ny, u.w+1, u.v}), dis[nx][ny] = u.w+1;

			}else{			// 不能直接去

				if(u.v && dis[nx][ny] > u.w)
					q.push({nx, ny, u.w+1, u.v-1}), dis[nx][ny] = u.w+1;

			}
		}
	}
	
	cout<<-1;
	return 0;
}
```
</details>

## 贪心

[基本算法之贪心](http://noi.openjudge.cn/ch0206/)
[算法之贪心](http://noi.openjudge.cn/ch0406/)

<details><summary><a href="" target="_blank"></a>装箱问题（202009） code</summary>

<br>

**大意**

给定若干个 $1*1, 2*2, 3*3, 4*4, 5*5, 6*6$ 的物品，需要将其全部放入 $6*6$ 的箱子里。

求至少需要多少个箱子。

**思路**

1. 我们尝试从大的往小的放，每种物品的数量看作 $n_{6,5,4,3,2,1}$：
    * $6*6$: 需要 $n_6$ 个箱子
    * $5*5$: 需要 $n_5$ 个箱子
        * 此时，箱子中可能空位，可以放置 $(n_5 * 11)$ 个 $(1*1)$ 的物品
    * $4*4$: 需要 $n_4$ 个箱子
        * 此时，箱子中可能空位，可以放置 $(n_4 * 5)$ 个 $(2*2)$ 的物品
        * 此时，箱子中可能空位，可以放置 $max(0, n_4 * 5 - n_2)$ 个 $(1*1)$ 的物品
    * $3*3$：需要 $(n_3+3) / 4$ 个箱子
        * 如果 $n_3 \% 4==0$，不存在空位
        * 如果 $n_3 \% 4==1$，可以放置 $5$ 个 $(2*2)$ 的物品 
            * 尝试继续塞下 $max(0, 5-n_2) * 4 + 7$ 个 $(1*1)$ 的物品
        * 如果 $n_3 \% 4==2$，可以放置 $3$ 个 $(2*2)$ 的物品
            * 尝试继续塞下 $max(0, 3-n_2) * 4 + 6$ 个 $(1*1)$ 的物品
        * 如果 $n_3 \% 4==3$，可以放置 $1$ 个 $(2*2)$ 的物品
            * 尝试继续塞下 $max(0, 1-n_2) * 4 + 5$ 个 $(1*1)$ 的物品
    * $2*2$：需要 $(n_2+8) / 9$ 个箱子
        * 如果 $n_2 \% 9==0$，不存在空位
        * 否则，可以放置 $36 - 4 * n_2 \% 9$ 个 $(1*1)$ 的物品
    * $1*1$：需要 $(n_1+35) / 36$ 个箱子

```cpp
#include <iostream>
using namespace std;

const int N = 1e5+10;

int n1,n2,n3,n4,n5,n6;

void solve(){
	int ans=0;
	ans += n6;
	
	ans += n5;
	n1 = max(0, n1 - n5*11);
	
	ans += n4;
	n1 = max(0, n1 - max(0, n4*5-n2));
	n2 = max(0, n2 - n4*5);

	ans += (n3+3)/4;
	if(n3%4==1){
		n1 = max(0, n1-(max(0, 5-n2)*4+7));
		n2 = max(0, n2-5);
	}
	else if(n3%4==2){
		n1 = max(0, n1-(max(0, 3-n2)*4+6));
		n2 = max(0, n2-3);
	}
	else if(n3%4==3){
		n1 = max(0, n1-(max(0, 1-n2)*4+5));
		n2 = max(0, n2-1);
	}

	ans += (n2+8)/9;
	if(n2%9){
		n1 = max(0, n1 - max(0, 36 - 4*n2%9));
	}

	ans += (n1+35)/36;

	cout<<ans<<"\n";

	return ;
}

int main(){
	while(cin>>n1>>n2>>n3>>n4>>n5>>n6, n1||n2||n3||n4||n5||n6)
		solve();
	return 0;
}
```
</details>

## 分治

[基本算法之分治](http://noi.openjudge.cn/ch0204/)
[算法之分治](http://noi.openjudge.cn/ch0404/)




<br>

---


# 六级

## 数据结构

<details><summary><a href="https://tctm.cpolar.cn/submission/449347" target="_blank">字符串插入（202305a）</a> code</summary><br>

**大意**

**思路**

```cpp
#include <iostream>
#include <string>
using namespace std;

const int N = 1e5+10;

string s, sub;

int main(){
    while(cin >> s >> sub){
        int idx = 0;
        char maxC = 0;
        for(int i=0; i<s.size(); i++)
            if(maxC < s[i])
                maxC = s[i], idx = i;
        
        s.insert(idx + 1, sub);
        cout << s << "\n";
    }
    return 0;
}
```
</details>

<details><summary><a href="https://tctm.cpolar.cn/problem/4307" target="_blank">生日相同 2.0（202309a）</a> code</summary><br>

**大意**

**思路**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> res[13][32];

bool cmp(string a, string b){
    if(a.size() < b.size()) return 1;   // 长度
    if(a.size() > b.size()) return 0;   
    if(a < b) return 1;                 // 字典序
    if(a > b) return 0;
    return 0;
}

int main(){
    int n; cin >> n;
    for(int i=1; i<=n; i++){
        string name;
        int m, d;
        cin >> name >> m >> d;
        res[m][d].push_back(name);
    }

    bool flg = 0;

    for(int i=1; i<=12; i++)
        for(int j=1; j<=31; j++)
            if(res[i][j].size() > 1){
                flg = 1;
                sort(res[i][j].begin(), res[i][j].end(), cmp);
                cout << i << " " << j << " ";
                for(auto name: res[i][j])
                    cout << name << " ";
                cout << "\n";
            }
    
    if(flg == 0)
        cout << "None";

    return 0;
}
```
</details>

<br>

## 栈

<details><summary><a href="" target="_blank">栈的基本操作（202209a）</a> code</summary><br>

**大意**

**思路**

```cpp
#pragma G++ optimize("Ofast", 3)
#define fst first

#define sed second

#define pb push_back

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const int dxy[][2]={ {-1,0},{1,0},{0,-1},{0,1} };
const int N = 2e5+10;

int n;

void solve(){
	stack<int> stk;
	cin >> n;

	bool flg = 1;
	while(n--){
		string op;
		cin >> op;
		if(op == "push"){
			int x; cin >> x;
			if(flg == 0) continue;

			stk.push(x);
		}else{
			if(flg == 0) continue;

			if(stk.size() == 0){
				cout << "error\n";
				flg = 0;
				continue;
			}

			stk.pop();
		}
	}

	if(flg == 0) return ;

	stack<int> t;
	while(stk.size()){
		t.push(stk.top());
		stk.pop();
	}

	while(t.size()){
		cout << t.top() << " ";
		t.pop();
	}

	cout << "\n";
}

int main(){
	int T; cin>>T; while(T--)
	solve();
	return 0;
}
```
</details>

<details><summary><a href="https://tctm.cpolar.cn/problem/4305" target="_blank">栈基本操作（202305b）</a> code</summary><br>

**大意**

**思路**

```cpp
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

const int N = 1e5+10;

stack<int> stk;
queue<pair<string, int>> q;
int b[N];
int n;

int main(){
    cin >> n;
    // 出栈序列
    for(int i=1; i<=n; i++) cin >> b[i];
    b[0] = 1;

    // 入栈顺序
    for(int i=1; i<=n; i++){
        stk.push(i);
        q.push({"PUSH", i});
        while(stk.size() && stk.top() == b[ b[0] ])
            stk.pop(), ++b[0], q.push({"POP", b[b[0]-1]});
    }

    if(stk.size()) cout << "NO";
    else
        while(q.size())
            cout << q.front().first << " " << q.front().second << "\n", q.pop();

    return 0;
}
```
</details>

<details><summary><a href="https://tctm.cpolar.cn/problem/4308" target="_blank">合法出栈序列（202309b）</a> code</summary><br>

**大意**

**思路**

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int N = 1e5+10;

string x, s;

int main(){
    cin >> x;
    while(cin >> s){
        stack<char> a, b, t;
        for(int i=x.size()-1; i>=0; i--) a.push(x[i]);
        for(int i=s.size()-1; i>=0; i--) b.push(s[i]);

        while(a.size()){
            t.push(a.top());
            a.pop();

            while(t.size() && t.top() == b.top())
                t.pop(), b.pop();
        }

        if(t.size() == 0) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
```
</details>


<details><summary><a href="https://tctm.cpolar.cn/problem/4309" target="_blank">括号画家（202309c）</a> code</summary><br>

**大意**

**思路**

```cpp
#include <iostream>
#include <stack>
using namespace std;

const int N = 1e5+10;

stack<int> stk;

int main(){
    char c;
    while(cin >> c){
        int x;
        if(c == '(' || c == ')') x = 1;
        if(c == '[' || c == ']') x = 2;
        if(c == '{' || c == '}') x = 3;
        
        if(stk.size() && stk.top() == x)
            stk.pop();
        else
            stk.push(x);
    }

    if(stk.size()) cout << "No";
    else cout << "Yes";

    return 0;
}
```
</details>

<br>

## 队列

<details><summary><a href="https://tctm.cpolar.cn/problem/4319" target="_blank">队列和栈（202312X）</a> code</summary><br>

**大意**

**思路**

```cpp
#pragma G++ optimize("Ofast", 3)
#define fst first

#define sed second

#define pb push_back

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const int dxy[][2]={ {-1,0},{1,0},{0,-1},{0,1} };
const int N = 2e5+10;

int n;

void solve(){
	stack<int> stk;
	queue<int> q;
	cin >> n;

	bool flg = 1;
	while(n--){
		string op;
		cin >> op;
		if(op == "push"){
			int x; cin >> x;
			if(flg == 0) continue;

			stk.push(x);
			q.push(x);
		}else{
			if(flg == 0) continue;

			if(stk.size() == 0 || q.size() == 0){
				cout << "error\nerror\n";
				flg = 0;
				continue;
			}

			stk.pop();
			q.pop();
		}
	}

	if(flg == 0) return ;

	while(q.size()){
		cout << q.front() << " ";
		q.pop();
	}

	stack<int> t;
	while(stk.size()){
		t.push(stk.top());
		stk.pop();
	}

	cout << "\n";

	while(t.size()){
		cout << t.top() << " ";
		t.pop();
	}

	cout << "\n";
}

int main(){
	int T; cin>>T; while(T--)
	solve();
	return 0;
}
```
</details>


<details><summary><a href="https://tctm.cpolar.cn/problem/4306" target="_blank">双端队列（202305d）</a> code</summary><br>

**大意**

**思路**

```cpp
#pragma G++ optimize("Ofast", 3)
#define fst first

#define sed second

#define pb push_back

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int inf = 0x3f3f3f3f;
const int dxy[][2]={ {-1,0},{1,0},{0,-1},{0,1} };
const int N = 2e5+10;

int n;

void solve(){
    cin >> n;
    deque<int> q;
    while(n--){
        int op, x;
        cin >> op >> x;
        if(op == 1)
            q.push_back(x);
        else{
            if(x == 1) q.pop_back();
            else q.pop_front();
        }
    }

    if(q.size() == 0)
        cout << "NULL\n";

    while(q.size())
        cout << q.front() << " ", q.pop_front();
    cout << "\n";
}

int main(){
    int T; cin>>T; while(T--)
    solve();
    return 0;
}
```
</details>


<br>

---