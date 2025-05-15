

<details><summary>noip</summary>

<a href="https://my.noip.com/dynamic-dns">管理面板</a> │
<a href="https://www.noip.com/support/knowledgebase/install-linux-3-x-dynamic-update-client-duc/">官方文档</a> │ 
<a href="https://www.noip.com/support/knowledgebase/automatic-ipv6-updates-linux-duc/">Linux IPv6 使用方法</a>

<ol>

<li> <a href="https://my.noip.com/dynamic-dns/duc">下载</a> </li>
<li> 解压 <code>tar -zxvf noip*.tar.gz</code> </li>
<li> 安装 <code>cd binaries && apt install ./noip-duc_3.0.0-beta.5_amd64.deb</code> </li>
<li> 运行 noip-duc --username 账号 --password 密码 -g 域名 --ip-method http://ip1.dynupdate6.no-ip.com/<code></code> </li>

</ol>

</details>
