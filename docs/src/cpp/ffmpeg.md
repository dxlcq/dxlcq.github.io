## 参考

[官网](https://ffmpeg.org/) | [下载](https://ffmpeg.org/download.html) | [文档](https://ffmpeg.org/documentation.html)

[中文文档 6.0.1](https://ffmpeg.github.net.cn/documentation.html)

<br>

---

## setup

### linux

1. 下载 `wget` / 解压 `tar -xvf` / 提权 `chmod +x`

2. 下载编译工具 `sudo apt install nasm pkg-config`

2. `sudo apt install libsdl2-dev`

3. 配置安装选项 `./configure --prefix=/.../FFmpeg-x.y.z --enable-shared --enable-sdl`

4. 编译安装 `make && make install`

5. 编写测试代码
    ```cpp
    #define __STDC_CONSTANT_MACROS

    extern "C" {
    #include <libavutil/avutil.h>
    }
    #include <iostream>

    int main(){
        std::cout << av_version_info() << std::endl;
        return 0;
    }
    ```

6. 编译
    ```bash
    g++ a.cpp -I/.../FFmpeg-7.0.1/include -L/.../FFmpeg-7.0.1/lib -lavutil
    ```

### windows

<br>

---

## use_ffmpeg

> ```bash
> ffmpeg \
> -y \                              # 全局参数（如果输出文件已存在，则覆盖它）
> -c:a libfdk_aac -c:v libx264 \    # 输入文件参数（指定音频和视频编解码器）
> -i input.mp4 \                    # 输入文件
> -c:a libvorbis -c:v libvpx-vp9 \  # 输出文件参数（指定输出音频和视频编解码器）
> output.webm                       # 输出文件
> ```

### drawtext

```bash
ffmpeg \
-y \
-i input.mp4 \
-vf "drawtext='你好' \
output.mp4
```




<br>

---

## dev

### avutil

通用的辅助函数和数据结构

### swscale

视频的像素格式和分辨率转换，缩放、色彩空间转换

### swresample

音频的采样率转换和通道布局转换

### avcodec

音频和视频的编解码

### avformat

音视频容器格式的封装和解封装

### avdevice

处理捕获和播放设备的输入输出操作

### avfilter

提供音视频滤镜功能，用于处理音视频数据流中的过滤操作