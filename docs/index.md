# ✈️

<style>
  .container {
    display: flex;
    text-align: center;
  }
  .item {
    flex: 1;
    margin: 3px 0;
  }
  .search-container {
    width: 100%; /* 搜索框宽度与页面相同 */
    margin: 0 auto;
  }
  .search-container textarea {
    width: 100%;
    padding: 5px;
    font-size: 16px;
    border: 1px solid #ccc;
    border-radius: 4px;
    background-color: transparent;
    outline: none;
    resize: none; /* 禁止用户手动调整大小 */
    overflow: hidden; /* 防止出现滚动条 */
  }
  /* 图标容器样式 */
  .rounded-icon {
    width: 32px; /* 图标宽度 */
    height: 32px; /* 图标高度 */
    border-radius: 10px; /* 圆角半径 */
    display: inline-block; /* 行内块元素 */
    cursor: pointer; /* 鼠标悬停时显示手型光标 */
    transition: transform 0.3s; /* 动画过渡效果 */
  }

  /* 鼠标悬停时的效果 */
  .rounded-icon:hover {
    transform: scale(1.05); /* 放大图标 */
  }

  /* 图标内的图片样式 */
  .rounded-icon img {
    width: 100%;
    height: 100%;
    object-fit: contain; /* 保持图像比例并完全适应容器 */
  }
</style>

<div class="search-container">
  <form action="https://dxlcq.cn/proxy" method="GET">
    <textarea id="searchBox" name="q" placeholder="Workers of all lands, Unite!" rows="1"
      oninput="this.style.height = ''; this.style.height = this.scrollHeight + 'px';"
      onkeydown="if(event.key==='Enter' && !event.shiftKey){
        event.preventDefault();
        if(this.value.trim() !== ''){ this.form.submit(); }
      }"></textarea>
  </form>
</div>

<script>
  window.onload = function() {
    document.getElementById('searchBox').focus(); // 页面加载时自动聚焦搜索框
  }
</script>

<br>

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="https://mail.cqu.edu.cn/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/zh/7/74/Chongqing_University_logo.svg"></div>
      <div style="font-size: 12px;">dxlcq@stu.cqu.edu.cn</div>
    </a>
  </div>

  <div class="item" style="font-size: 14px;">
    <div><a href="http://10.0.0.10:8080/" target="_blank"> ai </a></div>
    <div><a href="https://github.com/copilot" target="_blank"> copilot </a></div>
  </div>

  <div class="item">
    <a href="https://outlook.live.com/mail/0/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/d/df/Microsoft_Office_Outlook_%282018%E2%80%93present%29.svg"></div>
      <div style="font-size: 12px;">dxlcq@outlook.com</div>
    </a>
  </div>

</div>

---

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="http://10.0.0.10:8088" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1d/ISS-40_Thunderheads_near_Borneo.jpg/330px-ISS-40_Thunderheads_near_Borneo.jpg"></div>
      <div style="font-size: 12px;">私有云盘</div>
    </a>
  </div>

  <div class="item">
    <a href="https://www.kdocs.cn/?show=all" target="_blank">
      <div class="rounded-icon"><img src="https://website-prod.cache.wpscdn.com/img/ai-wps-office-logo.3a18f52.png"></div>
      <div style="font-size: 12px;">金山文档</div>
    </a>
  </div>

  <div class="item">
    <a href="https://www.alipan.com/drive/file/all" target="_blank">
      <div class="rounded-icon"><img src="https://img.alicdn.com/imgextra/i2/O1CN011vHpiQ251TseXpbH7_!!6000000007466-2-tps-120-120.png"></div>
      <div style="font-size: 12px;">阿里云盘</div>
    </a>
  </div>

</div>

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="https://www.icloud.com/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/fa/Apple_logo_black.svg/160px-Apple_logo_black.svg.png"></div>
      <div style="font-size: 12px;">iCloud</div>
    </a>
  </div>
  
  <div class="item">
    <a href="https://drive.google.com/drive/my-drive" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c1/Google_%22G%22_logo.svg/1200px-Google_%22G%22_logo.svg.png"></div>
      <div style="font-size: 12px;">Google Drive</div>
    </a>
  </div>

  <div class="item">
    <a href="https://onedrive.live.com/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/4/44/Microsoft_logo.svg"></div>
      <div style="font-size: 12px;">OneDrive</div>
    </a>
  </div>

</div>

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="https://account.apple.com/account/manage/section/information" target="_blank">
      <div style="font-size: 12px;">Apple</div>
    </a>
  </div>
  
  <div class="item">
    <a href="https://passwords.google.com/" target="_blank">
      <div style="font-size: 12px;">Google</div>
    </a> 
  </div>

  <div class="item">
    <a href="https://account.microsoft.com/" target="_blank">
      <div style="font-size: 12px;">Microsoft</div>
    </a>
  </div>

</div>

---

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="http://10.0.0.10:2026" target="_blank">
      <div class="rounded-icon"><img src="https://avatars.githubusercontent.com/u/55735736?s=200&v=4"></div>
      <div style="font-size: 12px;">Speed Test</div>
    </a>
  </div>

  <div class="item">
    <a href="http://cesu.cqwin.com/" target="_blank">
      <div class="rounded-icon"><img src="https://pp.myapp.com/ma_icon/0/icon_3722_1737177848/256"></div>
      <div style="font-size: 12px;">unicom</div>
    </a>
  </div>

  <div class="item">
    <a href="https://test.nju.edu.cn/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/zh/thumb/f/fb/%E5%8D%97%E4%BA%AC%E5%A4%A7%E5%AD%A6%E6%A0%A1%E5%BE%BD.svg/536px-%E5%8D%97%E4%BA%AC%E5%A4%A7%E5%AD%A6%E6%A0%A1%E5%BE%BD.svg.png?20121015073640"></div>
      <div style="font-size: 12px;">CN</div>
    </a>
  </div>

  <div class="item">
    <a href="https://www.speedtest.net/zh-Hans" target="_blank">
      <div class="rounded-icon"><img src="https://is1-ssl.mzstatic.com/image/thumb/Purple126/v4/04/fa/ac/04faace5-ae8f-313f-4d10-d809fb397e7f/AppIcon-85-220-0-4-2x.png/460x0w.webp"></div>
      <div style="font-size: 12px;">UN</div>
    </a>
  </div>

</div>

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="https://www.itdog.cn/tcping/" target="_blank">
      <div class="rounded-icon"><img src="https://favicon.yandex.net/favicon/v2/www.itdog.cn?size=32"></div>
      <div style="font-size: 12px;">Tcping</div>
    </a>
  </div>

  <div class="item">
    <a href="https://smbcloud.tp-link.com.cn/login.html" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/TPLINK_Logo_2.svg/2880px-TPLINK_Logo_2.svg.png"></div>
      <div style="font-size: 12px;">Router</div>
    </a>
  </div>

  <div class="item">
    <a href="http://10.0.0.2" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/0/08/Cisco_logo_blue_2016.svg/2880px-Cisco_logo_blue_2016.svg.png"></div>
      <div style="font-size: 12px;">Switch</div>
    </a>
  </div>

  <div class="item">
    <a href="http://10.0.0.3" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/8/84/OpenWrt_Logo.svg"></div>
      <div style="font-size: 12px;">Gateway</div>
    </a>
  </div>

</div>

<div class="container"> <!-- 1 -->

  <div class="item">
    <a href="https://dash.cloudflare.com/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/9/94/Cloudflare_Logo.png"></div>
      <div style="font-size: 12px;">赛博大善人</div>
    </a>
  </div>

  <div class="item">
    <a href="https://console.huaweicloud.com/" target="_blank">
      <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/zh/thumb/0/04/Huawei_Standard_logo.svg/1920px-Huawei_Standard_logo.svg.png"></div>
      <div style="font-size: 12px;">华为云</div>
    </a>
  </div>

  <div class="item">
    <a href="https://home.console.aliyun.com/" target="_blank">
      <div class="rounded-icon"><img src="https://img.alicdn.com/tfs/TB1qNVdXlGw3KVjSZFDXXXWEpXa-620-620.png"></div>
      <div style="font-size: 12px;">阿里云</div>
    </a>
  </div>

  <div class="item">
    <a href="https://console.cloud.tencent.com/" target="_blank">
      <div class="rounded-icon"><img src="https://avatars.githubusercontent.com/u/12334581"></div>
      <div style="font-size: 12px;">腾讯云</div>
    </a>
  </div>

</div>

---

<div class="container">
    <div class="item">
      <a href="https://www.youtube.com/@骄骄" target="_blank">
        <div class="rounded-icon"><img src="https://is1-ssl.mzstatic.com/image/thumb/Purple221/v4/f5/ac/a8/f5aca8ee-b304-1aec-c656-66a36ae88a94/logo_youtube_2024_q4_color-0-0-1x_U007emarketing-0-0-0-6-0-0-0-85-220.png/492x0w.webp"></div>
        <div style="font-size: 12px;">YouTube</div>
      </a> 
    </div>
    <div class="item">
      <a href="https://open.spotify.com/user/312fhhabg3hdhdlcyq5r7zidpt5e?si=2f6fcb6ff1c64a79&nd=1&dlsi=12f6bab9fb1446d8" target="_blank">
        <div class="rounded-icon"><img src="https://is1-ssl.mzstatic.com/image/thumb/Purple221/v4/7a/7a/63/7a7a63b4-6370-c782-c7c5-68d0f85d753a/AppIcon-0-0-1x_U007emarketing-0-7-0-0-85-220.png/460x0w.webp"></div>
        <div style="font-size: 12px;">Spotify</div>
      </a> 
    </div>
    <div class="item">
      <a href="https://x.com/dxlcqy" target="_blank">
        <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/X_logo_2023.svg/220px-X_logo_2023.svg.png"></div>
        <div style="font-size: 12px;">X</div>
      </a> 
    </div>
    <div class="item">
      <a href="https://www.tiktok.com/@dxlcq" target="_blank"> 
        <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/en/thumb/a/a9/TikTok_logo.svg/440px-TikTok_logo.svg.png"></div>
        <div style="font-size: 12px;">TikTok</div>
      </a> 
    </div>
    <div class="item">
      <a href="https://web.telegram.org/a/" target="_blank">
        <div class="rounded-icon"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/83/Telegram_2019_Logo.svg/300px-Telegram_2019_Logo.svg.png"></div>
        <div style="font-size: 12px;">Telegram</div>
      </a> 
    </div>

</div>