## 参考

* [动手学深度学习（Pytorch 版）](https://zh.d2l.ai/chapter_preface/index.html)


## tensor

tensor, 多维数组, 张量

### 创建 tensor

0 阶张量, 标量, Scalar

```python
a1 = torch.tensor(3.14)
a2 = torch.zeros(())        # 0
a3 = torch.ones(())         # 1
a4 = torch.rand(())         # 随机数
a5 = torch.full((), 3.14)   # 3.14
```

1 阶张量, 向量, Vector

```python
a1 = torch.arange(0, 12, 3)     # [0, 3, 6, 9]
a2 = torch.linspace(0, 12, 3)   # [0, 6, 12]
a3 = torch.logspace(-1, -4, 4)  # [0.1, 0.01, 0.001, 0.0001]

a4 = torch.rand(3)              # [0.x, 0.x, 0.x] 均匀分布
a5 = torch.randn(3)             # [0.x, 0.x, 0.x] 标准正态分布
a6 = torch.randint(0, 10, (3,)) # [0, 10) 的随机整数, 3 个
a7 = torch.randperm(10)         # [0, 9] 的随机排列, 10 个
```

2 阶张量, 矩阵, Matrix

```python
a1 = torch.eye(3)               # [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
a2 = torch.diag(torch.tensor([1, 2, 3])) # [[1, 0, 0], [0, 2, 0], [0, 0, 3]]
```

### 变换 tensor

```python

```

### 广播机制

## 数据预处理

## 神经网络

本质就是线性函数+非线性函数+线性函数+非线性函数+..., 最终使其能够拟合任意复杂的函数, 从而能够处理各种复杂的任务

> 线性回归就是一个线性函数
>
> * y_pred -> (无变换) -> 预测值 -> 均方误差损失
> 
> Softmax 回归就是一个线性函数 + Softmax 函数
> 
> * 线性输出 -> Softmax 函数 -> 概率分布 -> 交叉熵损失
>
> 逻辑回归就是一个线性函数 + Sigmoid 函数
>
> * 线性输出 -> Sigmoid 函数 -> 概率p -> 交叉熵损失



### 线性回归 (数值预测)

找出一组权重 w 和偏置 b，让预测值 y 尽可能接近真实值

```python
import torch
import sklearn

# 获取数据集
data = sklearn.datasets.fetch_california_housing()

# X 是特征数据, y 是目标变量
X, y = data.data, data.target

# 对特征数据进行标准化处理, 使其具有零均值和单位方差
X = sklearn.preprocessing.StandardScaler().fit_transform(X)

# 将数据集划分为训练集和测试集, 其中测试集占 20%, 随机种子设置为 42 以确保结果可复现
X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(
    X, y, test_size=0.2, random_state=42)

# 将数据转换为 PyTorch 的张量格式
X_train = torch.tensor(X_train, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.float32).view(-1, 1)
X_test = torch.tensor(X_test, dtype=torch.float32)
y_test = torch.tensor(y_test, dtype=torch.float32).view(-1, 1)

# 定义一个简单的线性回归模型
model = torch.nn.Linear(X_train.shape[1], y_train.shape[1])

# 定义损失函数
criterion = torch.nn.MSELoss()

# 定义优化器, 使用随机梯度下降 (SGD) 算法, 学习率设置为 0.01
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

# 训练模型
for epoch in range(1000):
    # 前向传播
    # predictions = W * X_train + b
    # 其中 W 是模型的权重参数, b 是模型的偏置参数, 这两个参数会在训练过程中不断更新以最小化损失函数
    predictions = model(X_train)

    # 计算损失
    # 1/n * sum(y_train_i - predictions_i)^2
    # 用均方误差作为损失函数, 目的是让模型的预测值尽可能接近真实值 y_train
    loss = criterion(predictions, y_train)

    # 清零梯度
    optimizer.zero_grad()

    # 计算损失的梯度
    # dloss/dW, dloss/db
    # 损失对 W 的偏导, 损失对 b 的偏导, 这些梯度将用于更新模型参数 W 和 b
    loss.backward()

    # 梯度下降更新参数
    # W = W - learning_rate * dloss/dW
    # b = b - learning_rate * dloss/db
    # 根据计算得到的梯度更新 W 和 b 的值, learning_rate 控制每次更新的(步长)大小
    optimizer.step()

    # 每 100 个 epoch 输出一次损失值
    if (epoch+1) % 100 == 0:
        print(f'Epoch [{epoch+1}/1000], Loss: {loss.item():.4f}')

# 在测试集上评估模型
model.eval()  # 设置模型为评估模式
with torch.no_grad():  # 禁用梯度计算
    test_predictions = model(X_test)
    test_loss = criterion(test_predictions, y_test)
    print(f'Test Loss: {test_loss.item():.4f}')
```

上面的代码实际上是**全量梯度下降 GD**, 因为每次迭代都使用了整个训练集来计算损失和梯度

对于 PyTorch 而言, 实现**随机梯度下降 SGD**就是用 1 个样本来计算损失和梯度, 实现**小批量随机梯度下降 Mini-batch SGD**就是用 32 或其他小批量样本来计算损失和梯度

> 在小数据集上, Mini-batch SGD 比 GD 更慢

### Softmax 回归 (多项逻辑回归)

```python
import torch
import sklearn

data = sklearn.datasets.load_iris()

X, y = data.data, data.target

X = sklearn.preprocessing.StandardScaler().fit_transform(X)

X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(
    X, y, test_size=0.2, random_state=42)

X_train = torch.tensor(X_train, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.long)
X_test = torch.tensor(X_test, dtype=torch.float32)
y_test = torch.tensor(y_test, dtype=torch.long)

# 输入特征数为 4, 输出类别数为 3
model = torch.nn.Linear(X_train.shape[1], len(set(y_train.numpy())))

# 定义损失函数
# ?
criterion = torch.nn.CrossEntropyLoss()

optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

for epoch in range(1000):
    predictions = model(X_train)

    # 计算损失
    # 线性函数会算出每个类别的分数, [[2.5, -1.3, 0.8], [], ...], 然后将其转换为概率
    # e^2.5                     e^-1.3                    e^0.8                     (指数化: 将所有类别的分数转换为正数, 以便计算概率)
    # e^2.5 + e^-1.3 + e^0.8    e^2.5 + e^-1.3 + e^0.8    e^2.5 + e^-1.3 + e^0.8    (归一化: 得到概率)
    # 0.82                      0.01                      0.17
    # 以上就是 softmax 函数的作用, 将线性函数的输出转换为概率分布, 然后计算交叉熵损失
    # -ln(正确类别的概率)
    # 若第一个类别是正确的, 则损失为 -ln(0.82) = 0.20
    # 若第二个类别是正确的, 则损失为 -ln(0.01) = 4.60 (可以发现, 正确类别的概率越小, 损失越大, 狠狠的惩罚模型)
    loss = criterion(predictions, y_train)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    # 每 100 个 epoch 输出一次损失值
    if (epoch + 1) % 100 == 0:
        print(f'Epoch [{epoch+1}/1000], Loss: {loss.item():.4f}')

model.eval()
with torch.no_grad():
    test_predictions = model(X_test)
    _, predicted_labels = torch.max(test_predictions, 1)
    accuracy = (predicted_labels == y_test).float().mean()
    print(f'Accuracy: {accuracy.item():.4f}')
```

### 逻辑回归 (Sigmoid)

### Fashion-MNIST

```python
import torch
import torchvision

transform = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor(),  # 将图像转换为张量, 并将像素值缩放到[0, 1]范围
    torchvision.transforms.Normalize((0.5, ), (0.5, ))  # [0, 1] -> [-1, 1]
])

train_dataset = torchvision.datasets.FashionMNIST(root='./',
                                                  train=True,
                                                  download=True,
                                                  transform=transform)
train = torch.utils.data.DataLoader(train_dataset, batch_size=64, shuffle=True)

model = torch.nn.Linear(28 * 28, 10).to(device='cuda')
criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.05)

model.train()
for epoch in range(20):

    loss = 0.0

    for X_batch, y_batch in train:
        X_batch = X_batch.view(-1, 28 * 28).to(device='cuda')
        y_batch = y_batch.to(device='cuda')

        predictions = model(X_batch)
        loss_batch = criterion(predictions, y_batch)
        loss += loss_batch.item()

        optimizer.zero_grad()
        loss_batch.backward()
        optimizer.step()

    print(f'Epoch [{epoch+1}/20], Loss: {loss/len(train):.4f}')

model.eval()
with torch.no_grad():
    test_dataset = torchvision.datasets.FashionMNIST(root='./',
                                                     train=False,
                                                     download=True,
                                                     transform=transform)
    test = torch.utils.data.DataLoader(test_dataset,
                                       batch_size=64,
                                       shuffle=False)

    accuracy_sum = 0.0
    accuracy_count = 0

    for X_test, y_test in test:
        X_test = X_test.view(-1, 28 * 28).to(device='cuda')
        y_test = y_test.to(device='cuda')

        test_predictions = model(X_test)

        _, predicted_labels = torch.max(test_predictions, 1)

        accuracy_sum += (predicted_labels == y_test).sum().item()
        accuracy_count += y_test.size(0)

    print(f'Accuracy: {accuracy_sum / accuracy_count:.4f}')
```

## 多层感知机 MLP



## CNN 卷积神经网络

## 现代卷积神经网络

## RNN 循环神经网络

## 现代循环神经网络

## Attention 注意力机制

## 算法优化

## 计算优化