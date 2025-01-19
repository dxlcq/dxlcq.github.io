[云图](https://cloud-atlas.readthedocs.io/zh-cn/latest/index.html)

[设备拓扑图](https://www.kdocs.cn/view/l/cvkIlSwbLP8Q) / [文件层级图](https://www.kdocs.cn/view/l/cqwqBmcLAQpT)


## 驱动和软件

* [NV 驱动](https://www.nvidia.com/en-us/software/nvidia-app/) / [INTEL 驱动](https://www.intel.com/content/www/us/en/support/detect.html)

* [MS 激活](https://github.com/massgravel/Microsoft-Activation-Scripts) `irm https://get.activated.win | iex`

* [微软商店免费下载](https://store.rg-adguard.net/)

* [状态监控](https://github.com/zhongyang219/TrafficMonitor) / [Bandizip](https://www.bandisoft.com/bandizip/) / [Office](https://otp.landian.vip/zh-cn/download.html) / [WPS](https://www.wps.cn/) / [todesk](https://dl.todesk.com/windows/ToDesk_Lite.exe)

* [VM-win-linux](https://support.broadcom.com/group/ecx/productdownloads?subfamily=VMware%20Workstation%20Pro) / [VM-mac](https://support.broadcom.com/group/ecx/productdownloads?subfamily=VMware%20Fusion)


<br>

---

## Hyper-V 直通 GPU

* [使用离散设备分配部署图形设备](https://learn.microsoft.com/zh-cn/windows-server/virtualization/hyper-v/deploy/deploying-graphics-devices-using-dda)

**关机、关闭虚拟机的动态内存、关闭检查点、关闭安全启动**

* 直通 GPU

    ```powershell
    # 目标虚拟机
    $vm = "dda"

    # 1. 虚拟机关机
    Set-VM -Name $vm -AutomaticStopAction TurnOff
    # 2. 启用CPU的写合并功能
    Set-VM -GuestControlledCacheTypes $true -VMName $vm
    # 3. 配置 32 位 MMIO（内存映射 I/O）空间
    Set-VM -LowMemoryMappedIoSpace 3Gb -VMName $vm
    # 4. 配置大于 32 位的 MMIO 空间
    Set-VM -HighMemoryMappedIoSpace 33280Mb -VMName $vm

    # 1. 查找所有 pnp 设备
    $pnpdevs = Get-PnpDevice -presentOnly
    # 2. 筛选出制造商为 NVIDIA 且属于“显示”类别的设备
    $gpudevs = $pnpdevs | Where-Object {$_.Class -like "Display" -and $_.Manufacturer -like "NVIDIA"}
    # 3. 获取第一个设备的设备位置路径
    $locationPath = ($gpudevs | Get-PnpDeviceProperty DEVPKEY_Device_LocationPaths).data[0]

    # 1. 禁用该设备
    Disable-PnpDevice -InstanceId $gpudevs[0].InstanceId
    # 2. 从主机中卸载该设备
    Dismount-VMHostAssignableDevice -Force -LocationPath $locationPath
    # 3. 将设备分配给虚拟机
    Add-VMAssignableDevice -LocationPath $locationPath -VMName $vm
    ```

* 取消直通 GPU

    ```powershell
    # 目标虚拟机（同上）

    # 1. 查找所有 pnp 设备
    $pnpdevs = Get-PnpDevice
    # 2. 筛选出制造商为 NVIDIA 且属于“显示”类别的设备
    $gpudevs = $pnpdevs | Where-Object {$_.Class -like "Display" -and $_.Manufacturer -like "NVIDIA"}
    # 3. 获取第一个设备的设备位置路径
    $locationPath = ($gpudevs | Get-PnpDeviceProperty DEVPKEY_Device_LocationPaths).data[0]

    # 1. 从虚拟机中移除设备
    Remove-VMAssignableDevice -LocationPath $locationPath -VMName $vm
    # 2. 重新启用该设备
    Mount-VMHostAssignableDevice -LocationPath $locationPath
    ```

* 查询

    ```powershell
    # 查看设备
    Get-PnpDevice | Where-Object {$_.FriendlyName -like "*NVIDIA*"}

    # 获取 locationPath
    $locationPath = Get-PnpDevice | Where-Object {$_.FriendlyName -like "*NVIDIA*"} | Get-PnpDeviceProperty DEVPKEY_Device_LocationPaths

    # 确认 locationPath
    Write-OutPut $locationPath
    ```

<br>

---

## WSL2

**安装**

* 自动安装 [官方文档](https://learn.microsoft.com/en-us/windows/wsl/install) / [基本命令](https://learn.microsoft.com/zh-cn/windows/wsl/basic-commands)
    
    * 启用适用于 Linux 的 Windows 子系统
    
    ```sh
    wsl --update --web-download     # 更新 WSL
    ```

    ```sh
    wsl -l -o                       # 查看可用 Linux 发行版
    ```

    ```sh
    wsl --install -d Ubuntu-22.04   # 下载安装 Ubuntu 22.04
    ```

    ```sh
    wsl -l -v                       # 查看已安装的
    ```

    ```sh
    wsl --unregister Ubuntu         # 删除 Ubuntu
    ```
    

* 手动安装：[ms/WSL](https://github.com/microsoft/WSL/releases)

<br>

**镜像网络** [官方文档](https://learn.microsoft.com/zh-cn/windows/wsl/networking#mirrored-mode-networking)

* 创建 `C:\Users\<UserName>\.wslconfig` 文件
    ```sh
    [wsl2]
    networkingMode=mirrored
    dnsTunneling=true
    autoProxy=true
    ```

<br>

**启动脚本**

1. win + r 输入  `shell:startup`
2. 新建 `wsl.vbs` 文件
    ```sh
    Set ws = WScript.CreateObject("WScript.Shell")        
    ws.run "wsl -d Ubuntu-22.04 -u user /home/user/startupsh"
    ```

<br>

**挂载网络磁盘** [非官文档](https://www.public-health.uiowa.edu/it/support/kb48568/)

1. 下载软件 `sudo apt install cifs-utils`

2. 创建挂载目录 `sudo mkdir /mnt/z`

3. 挂载 `sudo mount -t drvfs Z: /mnt/z`

4. 持久化 `vim /etc/fstab`
    ```sh
    Z: /mnt/z drvfs defaults 0 0
    ```
