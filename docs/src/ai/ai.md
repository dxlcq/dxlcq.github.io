## 参考

* [Chatbot Arena](https://lmarena.ai/?leaderboard)

* [huggingface](https://huggingface.co/models)

* [神经网络15分钟入门！足够通俗易懂了吧](https://zhuanlan.zhihu.com/p/65472471)

* [【闪客】一小时从函数到 Transformer](https://www.bilibili.com/video/BV1NCgVzoEG9/?share_source=copy_web&vd_source=5239464856c17c595a55df27f972f73d)

<br>

---

## GPU

* CPU 支持复杂指令集，而 GPU 只能执行简单指令集。简单的结构使得 GPU 可以在同一时间内处理更多的指令

* GPU 通过 SIMD（单指令多数据）来实现并行处理，在同一时间内对多个数据进行相同的操作，这使得它在处理大规模数据时具有更高的效率

## CUDA

* NVIDIA 推出的并行计算架构，本质就是一个 C 库，调用 GPU 参与计算

* 可以通过编写 CPU / GPU 代码进行矩阵运算查看效果

    <details>
    <summary>CPU 代码</summary>
    ```cpp
    #include <iostream>
    #include <thread>
    #include <vector>

    const int N = 3e3 + 10;

    std::vector<std::thread> threads;
    int A[N][N], B[N][N], C[N][N];
    int n = N - 10;

    void cpu_matrix_multiply(int i) {  // 线程函数，用于计算矩阵乘法的一行
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    int main() {
        // g++ main.cpp && ./a.out
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }  // 初始化矩阵 A, B

        auto start = std::chrono::high_resolution_clock::now();  // 记录开始时间

        for (int i = 1; i <= n; ++i)
            threads.emplace_back(cpu_matrix_multiply, i);
        for (auto& t : threads)
            t.join();

        auto end = std::chrono::high_resolution_clock::now();  // 记录结束时间
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

        return 0;
    }
    ```
    </details>

    <details>
    <summary>GPU 代码</summary>
    ```cpp
    #include <cuda_runtime.h>
    #include <chrono>
    #include <iostream>

    const int N = 3e3 + 10;
    int A[N][N], B[N][N], C[N][N];
    int n = N - 10;

    __global__ void cuda_matrix_multiply(int* A, int* B, int* C, int n) {
        int row = blockIdx.y * blockDim.y + threadIdx.y + 1;
        int col = blockIdx.x * blockDim.x + threadIdx.x + 1;

        if (row <= n && col <= n) {
            int sum = 0;
            for (int k = 1; k <= n; ++k) {
                sum += A[row * N + k] * B[k * N + col];
            }
            C[row * N + col] = sum;
        }
    }

    int main() {
        // nvcc main.cu && ./a.out
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }
        }  // 初始化矩阵 A, B

        // 分配 GPU 内存
        int *d_A, *d_B, *d_C;
        cudaMalloc(&d_A, N * N * sizeof(int));
        cudaMalloc(&d_B, N * N * sizeof(int));
        cudaMalloc(&d_C, N * N * sizeof(int));

        // 复制数据到 GPU
        cudaMemcpy(d_A, A, N * N * sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(d_B, B, N * N * sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(d_C, C, N * N * sizeof(int), cudaMemcpyHostToDevice);

        auto start = std::chrono::high_resolution_clock::now();

        dim3 blockSize(16, 16);
        dim3 gridSize((n + blockSize.x - 1) / blockSize.x, 
                      (n + blockSize.y - 1) / blockSize.y);

        cuda_matrix_multiply<<<gridSize, blockSize>>>(d_A, d_B, d_C, n);

        cudaDeviceSynchronize();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

        // 清理内存
        cudaFree(d_A);
        cudaFree(d_B);
        cudaFree(d_C);

        return 0;
    }
    ```
    </details>

<center>
<table>
<tr>
<td align="center">CPU</td>
<td align="center">GPU</td>
</tr>
<tr>
<td align="center">AMD 7900x</td>
<td align="center">NVIDIA 4070</td>
</tr>
<tr>
<td align="center">7s</td>
<td align="center">0.03s</td>
</tr>
</table>
</center>

## PyTorch

* PyTorch 是对 CUDA 的封装，提供了更高层次的 API 来简化 GPU 编程

## 机器学习

> “计算机程序可以在给定某种类别的任务 T 和性能度量 P 下学习经验 E（数据） ，如果其在任务 T 中的性能恰好可以用 P 度量，则随着经验 E（数据） 而提高。” -- Tom Mitchell

* f(x) = y
    机器学习的目标是通过数据来**创造**函数 f，使得输入 x 能够映射到输出 y

## 神经网络

* “神经网络的传播都是形如Y=WX+b的矩阵运算；为了给矩阵运算加入非线性，需要在隐藏层中加入激活层；输出层结果需要经过Softmax层处理为概率值，并通过交叉熵损失来量化当前网络的优劣”

* 神经网络的核心是通过多层的线性变换和非线性激活函数来学习复杂的函数关系

* 神经网络的训练过程是通过反向传播算法来调整权重和偏置，使得预测结果更接近真实值

## 深度学习

* 深度学习是神经网络的一种特殊形式，通常指的是具有多层隐藏层的神经网络

## 大模型

* 大模型通常指的是具有数十亿甚至数万亿参数的神经网络模型，这些模型可以通过大规模的数据集进行训练，从而学习到更复杂的特征和模式
