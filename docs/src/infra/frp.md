**frp + 内网 IPv4**

<details><summary>小鸡穿透</summary>

<a href="https://console.chickfrp.com/#/penManage/tunnel">管理面板</a> │
<a href="http://help.chickfrp.com/#/%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8">官方文档</a> │
固定ip，高带宽（1.25MB/s），高流量（5GB）

<ol>
<li> 下载 <code>wget https://chickfrp.com/download/frp045/linux/frp_0.45.0_linux_amd64.tar.gz</code> </li>
<li> 解压 <code>tar -zxvf frp*.tar.gz</code> </li>
<li> 复制 管理面板中的配置文件代码 </li>
<li> 替换 <code>frpc.ini</code> 文件 </li>
<li> 穿透 <code>./frpc</code> </li>
</ol>

</details>

<details><summary>cpolar</summary>

<a href="https://dashboard.cpolar.com/status">管理面板</a> │
<a href="https://www.cpolar.com/docs">官方文档</a> │
无固定ip，低带宽（128K/s），流量无限

<ol>
<li> 安装 <code>curl -L https://www.cpolar.com/static/downloads/install-release-cpolar.sh │ sudo bash</code> </li>
<li> 查看 <code>token</code> 在管理面板</li>
<li> 脚本 <code>vim /home/jiao/.cpolar/cpolar.yml</code> </li>

    ```yaml
    authtoken: xxxxxxxxxxxxxxxx
    tunnels:
        a:         
            addr: 80        
            proto: http     
        b:             
            addr: 3001
            proto: http
    ```

<li> 穿透 <code>sudo cpolar start-all -config /home/jiao/.cpolar/cpolar.yml</code> </li>
</ol>

</details>

<details><summary>花生壳</summary>

<a href="https://console.hsk.oray.com/forward">管理面板</a> │
<a href="https://service.oray.com/question/11630.html">官方文档</a> │
两个固定ip

<ol>
<li> 安装 <code>dpkg -i phddns-5.0.0-amd64.deb</code> </li>
<li> 运行 <code>phddns start</code> </li>
<li> 查看 <code>phddns status</code> </li>
<li> 登录 <code>sn码</code> + <code>admin</code> 登录管理面板</li>
<li> 穿透 管理面板添加映射 </li>
</ol>

</details>