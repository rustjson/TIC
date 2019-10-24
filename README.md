## 下载说明

<font color="#FF0000">注意：</font> 由于`Github`默认不支持大文件上传，请您在clone代码前先安装[Git-LFS](./Git-LFS.md)，用于实现Github对大文件的支持。请使用以下命令clone代码，**勿直接`Download ZIP`**。
```
git clone https://github.com/tencentyun/TIC.git
```

如果您访问 Github 或安装 Git-LFS 遇到问题，请使用腾讯云分流地址下载：

<table>
<tr>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Windows</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
</tr>
<tr>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/Web.zip">Download Zip</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/小程序.zip">Download Zip</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/Windows.zip">Download Zip</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/Android.zip">Download Zip</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/iOS.zip">Download Zip</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/macOS.zip">Download Zip</a></td>
</tr>
</table>

## 方案简介

腾讯云在线教育互动课堂（Tencent Interact Class，TIC）是集实时音视频、交互式白板涂鸦、IM 聊天室、PPT 课件共享、屏幕分享和录制回放等功能于一体的一站式在线教育互动课堂解决方案。

为了适应不同客户的需求，我们把互动课堂的接入方案分成了 SaaS 和 PaaS 两种。下面的表中列举了这两种方案的主要区别。
客户可以根据自身情况灵活选择。我们也支持这两种方案的无缝切换。

|能力|SaaS |  PaaS |
| :-- | :-- |  :-- |
| 课程管理 | 控制台/云 API | 云 API |
| 客户端 | 互动课堂 App/集成课堂 UI 组件 | 集成 SDK |
| 视频和白板录制 | 本地/云端 | 云端 |
| 数据统计和回调 | 支持 | 不支持 |

功能模块列表：

| 功能 | pc/mac | 桌面 Chrome | Android/iOS | 小程序 |
| --- | --- | --- | --- | --- |
| 实时音视频 | 支持 | 支持 | 支持 | 支持 |
| 直播 | 支持 | 支持 | 支持 | 支持 |
| 点播 | 支持 | 支持 | 支持 | 支持 |
| 本地录制 | 支持 | - | - | - |
| 云端录制 | 支持 | 支持 | 支持 | 支持 |
| 屏幕分享 | 支持 | 仅观看 | 仅观看 | 仅观看 |
| 播片 | 支持 | 仅观看  | 仅观看 | 仅观看 |
| 互动白板 | 支持 | 支持 | 支持 | 支持 |
| IM聊天 | 支持 | 支持 | 支持 | 支持 |


### SaaS 方案

![](https://main.qcloudimg.com/raw/ea3692fd322dbcc7d86c3fc3cc6d3c59.jpg)

**demo体验**

<table>
<tr>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
<th style="text-align:center">Windows</th>
</tr>
<tr>
<td style="text-align:center"><a href="https://tedu.qcloudtrtc.com/">立即体验</a></td>
<td style="text-align:center">即将推出</td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/c9619497d26c6d4ed75921ce2a298596.png" width="150"/></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/35664baf9512c57ac3c2b5436ab5d567.png" width="150"/></td>
<td style="text-align:center"><a href="http://dldir1.qq.com/hudongzhibo/Saas/TClass_Demo.dmg">立即体验</a></td>
<td style="text-align:center"><a href="http://dldir1.qq.com/hudongzhibo/Saas/TClass_Setup_Demo.exe">立即体验</a></td>
</tr>
</table>

demo 功能可参考下面的桌面端/移动端使用手册。

**SaaS 方案接入**

1. 客户端基本功能介绍。具体请参考 [SaaS基本功能介绍](./SaaS/Saas%e5%9f%ba%e6%9c%ac%e5%8a%9f%e8%83%bd%e4%bb%8b%e7%bb%8d.md)
2. 在控制台进行课堂管理和老师/学生管理。具体请参考 [SaaS控制台使用手册](./SaaS/Saas%e6%8e%a7%e5%88%b6%e5%8f%b0%e4%bd%bf%e7%94%a8%e6%89%8b%e5%86%8c.md)
3. 下载桌面端 App，体验完整功能。具体请参考 [SaaS 桌面端使用手册](./SaaS/Saas%e6%a1%8c%e9%9d%a2%e7%ab%af%e4%bd%bf%e7%94%a8%e6%89%8b%e5%86%8c.md)
4. 下载移动端 App，体验完整功能。具体请参考 [SaaS 移动端使用手册](./SaaS/Saas%e7%a7%bb%e5%8a%a8%e7%ab%af%e4%bd%bf%e7%94%a8%e6%89%8b%e5%86%8c.md)
5. 直接使用腾讯云互动课堂 App 的客户，具体请参考[SaaS 客户端纯应用方式接入指南](./SaaS/Saas%e5%ae%a2%e6%88%b7%e7%ab%af%e7%ba%af%e5%ba%94%e7%94%a8%e6%96%b9%e5%bc%8f%e6%8e%a5%e5%85%a5%e6%8c%87%e5%8d%97.md)
6. 需要自行开发 App 的客户，具体请参考[SaaS客户端组件方式接入指南](./SaaS/Saas%e5%ae%a2%e6%88%b7%e7%ab%af%e7%bb%84%e4%bb%b6%e6%96%b9%e5%bc%8f%e6%8e%a5%e5%85%a5%e6%8c%87%e5%8d%97.md)
7. 可以使用云API完成控制台所有功能，具体请参考[云 API 接入指南](./SaaS/%E6%93%8D%E4%BD%9C%E6%8C%87%E5%8D%97/%E4%BA%91API.md)

正式接入前，请阅读[购买指南](./%E8%B4%AD%E4%B9%B0%E6%8C%87%E5%8D%97.md)后，发送邮件申请开通服务。

### PaaS 方案

![](https://main.qcloudimg.com/raw/4fd896e4a8f70e417d004645f6276927.png)

**demo 体验**

<table>
<tr>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
<th style="text-align:center">Windows</th>
</tr>
<tr>
<td style="text-align:center"><a href="https://tic-demo-1259648581.cos.ap-shanghai.myqcloud.com/index.html">立即体验</a></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/b660a6c57aecebf6a0c749a1daf8532a.jpg" width="150"/></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/cd2145e71c50374ddafae1714ee9f6e8.png" width="150"/></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/1e40ee772f79317b14a0a55587343ae7.png" width="150"/></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/tic/TICDemo_Mac.zip">立即体验</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/tic/TICDemo_Windows.zip">立即体验</a></td>
</tr>
</table>

**PaaS 方案接入**

1. 通过调用 REST API，实现课件转码和录制等功能。
2. 客户按自身的业务逻辑，集成互动白板、实时音视频和即时通信 IM，完成上课流程的闭环。
3. 客户也可以集成 TIC 源码，该源码集成了互动白板、实时音视频和即时通信 IM，可快速完成上课流程的闭环。
4. 通过集成云API，托管课堂数据到腾讯云，实现课堂管理功能。
 - [TIC 快速接入](./PaaS/README.md)
 - [互动白板](./PaaS/Docs/SDK文档/互动白板功能说明.md)
 - [实时音视频](https://github.com/tencentyun/TRTCSDK)
 - [即时通信 IM](https://github.com/tencentyun/TIMSDK)
 - [文档转码服务](./PaaS/Docs/%E6%96%87%E6%A1%A3%E8%BD%AC%E7%A0%81.md)
 - [后台实时录制服务](./PaaS/Docs/%E5%AE%9E%E6%97%B6%E5%BD%95%E5%88%B6.md)
 - [云API](./PaaS/Docs/云API.md)

正式接入前，请阅读[购买指南](./%E8%B4%AD%E4%B9%B0%E6%8C%87%E5%8D%97.md)后，发送邮件申请开通服务。
