* Ubuntu `20.04.6`
* Python `3.8`
* GCC `9.4.0`
* NUPACK `4.0.1.8`
* Rosetta `rosetta.binary.ubuntu.release-362.tar.bz2`
    * SCons `4.5.2`
* rDock `23.11.97_ubuntu-20.04_g++_x86_64`

<br>

* run_3dRNA_DNA `-`（暂时未用）
* PyRosetta4 `pyrosetta-2023.47+release.5fe66cd241a-cp38-cp38-linux_x86_64.whl` （暂时未用）
* vscode `1.84.2`（可选）


## NUPACK

**用于核酸结构预测和热力学性质计算，输出二维结构** [下载](https://nupack.org/download/overview) / [文档](https://docs.nupack.org/)

* 安装
    1. 创建虚拟环境

        ```bash
        conda create -n XD python=3.8
        ```

    2. 安装依赖软件
        
        ```bash
        source activate # 可能需要先激活环境
        ```
        ```
        conda activate XD
        conda install numpy scipy pip matplotlib pandas jupyterlab
        ```

    3. 安装 `NUPACK`

        ```bash
        python3 -m pip install -U nupack -f ./nupack-4.0.1.8/package
        ```

**Utilities example**

* 输入

    * Sequence（核酸序列），形如 `ACGT...`
    * Structure Constraints（结构约束），？
    * Temperature（温度），
    * Ion Concentration（离子浓度），
    * ...

* 输出
    * **序列** `AUCG...`
    * **二级结构** `((...))`


```py
from nupack import *

my_model = Model(material='dna', celsius=37)
'''
meterial:
    dna (*)
    rna
celsius(摄氏度):
    37 (*)
'''

# Define walker sequences
walker_seq = ['augcugcccccugugugaagca']

# Define intended walker structure 
walker_struc = '(20.23+.23)20'

# Suboptimal proxy structures and energies
my_subopt = subopt(strands=walker_seq, model=my_model, energy_gap=1.1)


# Print out seq
#for i in walker_seq:
#    print(i)

# Print out components of the result for the given complex
print('\nSuboptimal proxy structure(s):\n\nseq: ', walker_seq[0])

for i, s in enumerate(my_subopt):
    print('    %2d: %s (%.2f kcal/mol)' % (i, s.structure, s.energy))
```


<br>

---

## Rosetta

**123** [注册](https://els2.comotion.uw.edu/product/rosetta) / [下载](https://www.rosettacommons.org/software/license-and-download) / [文档](https://www.rosettacommons.org/docs/latest/Home)


* 安装
    1. 解压缩
        ```bash
        tar -xvjf rosetta.binary.ubuntu.release-362.tar.bz2
        ```
    2. 下载构建工具 [SCons](https://scons.org/pages/download.html)
        
        1. 解压缩
            ```bash
            tar -zxvf scons-4.5.2.tar.gz
            ```
        2. 安装
            ```bash
            cd scons-4.5.2
            python setup.py install
            ```
        3. 验证
            ```bash
            scons --version
            ```
    3. 下载依赖
        ```bash
        sudo apt-get install lib32z1-dev
        ```    
    4. 构建
        ```bash
        cd rosetta.binary.ubuntu.release-362/main/source
        ./scons.py -j8 mode=release bin
        ```

**farfar2**

* 输入
    * **序列** `AUCG...`
    * **二级结构** `((...))`

* 输出
    * 三级结构（`.pdb`）

```sh
/home/jiao/Desktop/'rosetta.binary.ubuntu.release-362'/main/source/bin/rna_denovo.linuxgccrelease -sequence "ucaggu aagcag" -secstruct "(....( )....)" -nstruct 2 -out:file:silent test.out -minimize_rna -dump
```

<br>

---

## rDock

**预测小分子与蛋白质或其他生物分子的结合方式和结合能力** [下载](https://rdock.github.io/download/) / [文档](https://rdock.github.io/documentation/html_docs/index.html)



<br>

* **安装**

    1. 下载依赖
        ```bash
        sudo apt install -y make git libpopt0 libpopt-dev g++
        ```
    2. 下载 rDock 及构建
        ```bash
        git clone https://github.com/CBDD/rDock
        cd rDock
        make
        ```
    3. 验证
        ```bash
        cd bin
        ./rbcavity -help
        ```

**输入**

* 蛋白质结构（`.pdb`）
* 小分子结构（`.mol2`）
* 评分函数
* ...

**输出**

* 分子对接结果
* 评分信息

<br>

---


## PyRosetta4

**对蛋白质进行结构预测、分子对接、蛋白质设计等** [注册](https://els2.comotion.uw.edu/product/rosetta) / [下载](https://graylab.jhu.edu/download/PyRosetta4/archive/release/) / [文档](https://www.pyrosetta.org/documentation)


* 安装

    1. 进入虚拟环境
        ```bash
        conda activate XD
        ```
    2. 安装
            
        ```bash
        pip install pyrosetta-2023.47+release.5fe66cd241a-cp38-cp38-linux_x86_64.whl
        ```


**输入**

* 蛋白质结构（`.pdb`）
* 评分函数
* 任务定义

**输出**

* 优化后的蛋白质结构（`.pdb`）
* 评分信息
* ...

<br>

---



## 环境构建全流程

* 升级系统
    1. `sudo apt update && sudo apt upgrade && sudo apt dist-upgrade && sudo apt autoremove` 
* py 环境
    1. 系统自带 `python3.8.10`，使用 `python3.8.10 --version` 可以验证
    2. 下载包管理器 `pip3`，使用 `sudo apt install python3-pip`
* 安装 nupack
    1. 使用浏览器下载 [NUPACK 4.0.1.9](https://nupack.org/download/software)
    2. 添加执行权限 `chmod +x nupack-4.0.1.9.zip`
    3. 将其解压至桌面 `unzip -d ~/Desktop/ nupack-4.0.1.9.zip`
    4. 手动安装 `pip3 install -U nupack -f ~/Desktop/nupack-4.0.1.9/package/`
* 测试
    1. `sudo apt install vim`
    2. `vim TestNupack.py`
        * 输入 `i` 进入插入模式
        * 粘贴代码
            ```py
            from nupack import *
            my_model = Model(material='dna', celsius=37)
            walker_seq = ['augcugcccccugugugaagca']
            walker_struc = '(20.23+.23)20'
            my_subopt = subopt(strands=walker_seq, model=my_model, energy_gap=1.1)
            print('\nSuboptimal proxy structure(s):\n\nseq: ', walker_seq[0])

            for i, s in enumerate(my_subopt):
                print('    %2d: %s (%.2f kcal/mol)' % (i, s.structure, s.energy))
            ```
        * 按下 `Esc` 键，再输入 `:wq`，保存退出
    3. 运行 `python3 TestNupack.py`
        * 看到如下消息，说明安装成功
            ```shell
            Suboptimal proxy structure(s):

            seq:  augcugcccccugugugaagca
                 0: .((((.............)))) (-1.65 kcal/mol)
                 1: .((((.............)))) (-1.65 kcal/mol)
                 2: .((((.(.........).)))) (-1.56 kcal/mol)
                 3: .((((.(.........).)))) (-1.56 kcal/mol)
                 4: ..(((.............))). (-1.29 kcal/mol)
                 5: ..(((.............))). (-1.29 kcal/mol)
                 6: ..(((.(.........).))). (-1.20 kcal/mol)
                 7: .((((.(.(.....).).)))) (-0.96 kcal/mol)
                 8: .(((...............))) (-0.67 kcal/mol)
                 9: .((((.(..(....).).)))) (-0.66 kcal/mol)
            ```
* 下载 Rosetta
    1. 下载 [Rosetta](https://www.rosettacommons.org/software/academic)
    2. 添加权限 `chmod +x rosetta.binary.ubuntu.release-371.tar.bz2`
    3. 解压 `tar -zvjf rosetta.binary.ubuntu.release-371.tar.bz2 -C ~/Desktop/`

* 安装构建工具 SCons 
    1. 下载 [SCons](https://sourceforge.net/projects/scons/files/scons/)
    2. 添加执行权限 `chmod +x SCons-4.7.0.tar.gz`
    3. 解压 `tar -zxvf SCons-4.7.0.tar.gz -C ~/Desktop/`
    4. 安装 `cd ~/Desktop/SCons-4.7.0/ && sudo python3 setup.py install`
    5. 验证 `scons --version`

* 下载依赖
    1. `sudo apt install lib32z1-dev`

* 构建 Rosetta
    1. 去目标目录 `cd rosetta.binary.ubuntu.release-371/main/source/`
    2. 搞个软链接 `sudo ln -s /usr/bin/python3 /usr/bin/python`
    2. 运行 `sudo ./scons.py -j20 mode=release bin`
        * `-j20` 是指用 20 个线程
    3. 创建文件夹 `mkdir ~/Desktop/TestRosetta && cd ~/Desktop/TestRosetta`
    4. 测试 `~/Desktop/rosetta.binary.ubuntu.release-371/main/source/bin/rna_denovo.linuxgccrelease -sequence "ucaggu aagcag" -secstruct "(....( )....)" -nstruct 2 -out:file:silent test.out -minimize_rna -dump`
        * 运行结束，出现下面几个文件则说明成功
            `add_chunks.pdb  init.pdb  random_moves.pdb  start_0.pdb  test.out`

* 在 py 中调用 rosetta
    
    `pip3 install pandas openpyxl`

    运行程序之前，需要新建一个 `res` 目录，存放所有的结果

    ```py
    from nupack import *
    import pandas as pd
    import subprocess
    import concurrent.futures

    # farfar shell 
    def farfar2(seq, sec):
        res = "/home/jiao/Desktop/'rosetta.binary.ubuntu.release-371'/main/source/bin/rna_denovo.linuxgccrelease"
        res = res + " -sequence \""
        res = res + seq
        res= res + "\" -secstruct \""
        res = res + sec
        res = res + "\""
        res = res + " -minimize_rna -dump"
        return res

    def task(seq, sec):
        process = subprocess.Popen(["mkdir", seq+sec], stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd="./res/")
        stdout, stderr = process.communicate()
        process = subprocess.Popen(farfar2(seq, sec), shell=True, stdout=subprocess.PIPE, text=True, cwd="./res/"+seq+sec)
        stdout, stderr = process.communicate()
        print(stdout)

    def main():
        # nupack
        df = pd.read_excel('list_40bit.xlsx', header=None)
        walker_seq = df.iloc[:, 1:2]
        my_model = Model(material='dna', celsius=37)

        with concurrent.futures.ThreadPoolExecutor(max_workers=20) as executor:
            for _, seq in walker_seq.iterrows():
                i = str(seq.values)[2:-2].lower()
                my_subopt = subopt(strands=i, model=my_model, energy_gap=1.1)

                futures = [executor.submit(task, i, str(j.structure)) for j in my_subopt]

            concurrent.futures.wait(futures)

    if __name__ == "__main__":
        main()
    ```