# 互动课堂

互动课堂解决方案是对以下多个独立的腾讯云服务的整合，旨在为您提供一套快速上手使用的在线教育解决方案。

- [实时音视频 `TRTC`](https://github.com/tencentyun/TRTCSDK)（提供音视频通信能力）
- [云通信 `TIM`](https://github.com/tencentyun/TIMSDK)（提供云通信能力）
- [互动白板 `TEduBoard`](./Docs/PaaS/SDK文档/互动白板功能说明.md)（提供文件展示及涂鸦展示能力）

互动课堂设计初衷在于抽象出这些云服务在 `在线教育场景` 下通用的使用流程，为您屏蔽各个云服务琐碎的初始化、鉴权流程等技术细节，让您能专注于业务逻辑开发。

虽然抽象出来的这套使用流程已经比较具有通用性，但是考虑到您可能还是会有一些细节上的特殊定制化需求，互动课堂这一层的代码我们以开源的形式放出，您可以根据您的实际需求进行修改定制。

## 下载说明

<font color="#FF0000">注意：</font> 由于`Github`默认不支持大文件上传，请您在clone代码前先安装[Git-LFS](./Git-LFS.md)，用于实现Github对大文件的支持。请使用以下命令clone代码，<font color="#FF0000">勿</font>直接`Download ZIP`。
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


## 快速体验

#### SaaS体验

![](https://main.qcloudimg.com/raw/ea3692fd322dbcc7d86c3fc3cc6d3c59.jpg)

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

#### PaaS体验

为了便于开发人员以最简明的方式调试接口，我们准备了各个平台的开发demo。

![](https://main.qcloudimg.com/raw/4fd896e4a8f70e417d004645f6276927.png)

<table>
<tr>
<th style="text-align:center"></th>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
<th style="text-align:center">Windows</th>
</tr>
<tr>
<td>体验链接</td><td style="text-align:center"><a href="https://tic-demo-1259648581.cos.ap-shanghai.myqcloud.com/index.html">立即体验</a></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/b660a6c57aecebf6a0c749a1daf8532a.jpg" width="150"/></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/cd2145e71c50374ddafae1714ee9f6e8.png" width="150"/></td>
<td style="text-align:center"><img src="https://main.qcloudimg.com/raw/1e40ee772f79317b14a0a55587343ae7.png" width="150"/></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/tic/TICDemo_Mac.zip">立即体验</a></td>
<td style="text-align:center"><a href="https://tic-res-1259648581.file.myqcloud.com/demo/tic/TICDemo_Windows.zip">立即体验</a></td>
</tr>
<td>源码链接</td><td style="text-align:center"><a href="../../../Web">Github</a></td>
<td style="text-align:center"><a href="../../../小程序">Github</a></td>
<td style="text-align:center"><a href="../../../Android">Github</a></td>
<td style="text-align:center"><a href="../../../iOS">Github</a></td>
<td style="text-align:center"><a href="../../../macOS">Github</a></td>
<td style="text-align:center"><a href="../../../Windows">Github</a></td>
</tr>
</table>


下载源码后，为避免开发测试导致账号被强制下线，您需要替换自己的`SdkAppId`和测试账号信息。在 [实时音视频应用列表](https://console.cloud.tencent.com/rav) 中选择对应的应用，**点击下载公私钥**并输入私钥**生成 Demo 配置文件内容**，替换 Demo 中配置文件的账号内容即可开始测试。

|所属平台|配置文件路径|
|-|-|
|Android|Android/Demo/app/src/main/res/raw/config.json|
|iOS|iOS/Demo/TICDemo/TICDemo/Config/config.json|
|Windows|Windows/Demo/config.json|
|macOS|macOS/Demo/TICDemo_Mac/TICDemo_Mac/Config/config.json|
|Web|Web/Demo/js/account_dev.js|
|小程序|小程序/Demo/miniprogram/pages/tic/account.js|

## 购买指南

[购买指南](./Docs/购买指南.md)

## 接入文档


<table>
<tr>
<th style="text-align:center"></th>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
<th style="text-align:center">Windows</th>
</tr>
<tr>
<td>互动课堂（TIC）</td><td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Web/互动课堂接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/小程序/互动课堂接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Android/互动课堂接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/iOS/互动课堂接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/macOS/互动课堂接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Windows/互动课堂接入文档.md">Doc</a></td>
</tr>
<td>互动白板（TEduBoard）</td><td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Web/互动白板接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/小程序/互动白板接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Android/互动白板接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/iOS/互动白板接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/macOS/互动白板接入文档.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/SDK文档/Windows/互动白板接入文档.md">Doc</a></td>
</tr>
</table>



## 版本信息

<table>
<tr>
<th style="text-align:center"></th>
<th style="text-align:center">Web</th>
<th style="text-align:center">小程序</th>
<th style="text-align:center">Android</th>
<th style="text-align:center">iOS</th>
<th style="text-align:center">macOS</th>
<th style="text-align:center">Windows</th>
</tr>
<tr>
<td>互动课堂（TIC）</td><td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/Web_TIC_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/小程序_TIC_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/Android_TIC_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/iOS_macOS_TIC_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/iOS_macOS_TIC_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动课堂/Windows_TIC_ReleaseNotes.md">Doc</a></td>
</tr>
<td>互动白板（TEduBoard）</td><td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/Web_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/小程序_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/Android_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/iOS_macOS_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/iOS_macOS_ReleaseNotes.md">Doc</a></td>
<td style="text-align:center"><a href="./Docs/PaaS/版本信息/互动白板/Windows_ReleaseNotes.md">Doc</a></td>
</tr>
</table>


## 更多功能

- [实时录制](./Docs/PaaS/实时录制.md)
- [课后录制](./Docs/PaaS/课后录制.md)
- [文档转码](./Docs/PaaS/文档转码.md)

## 常见问题
- [常见问题](./Docs/PaaS/常见问题.md)
