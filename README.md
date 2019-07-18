# 互动课堂

互动课堂解决方案是对以下多个独立的腾讯云服务的整合，旨在为您提供一套快速上手使用的在线教育解决方案。

- [实时音视频 `TRTC`](https://github.com/tencentyun/TRTCSDK)（提供音视频通信能力）
- [云通信 `TIM`](https://github.com/tencentyun/TIMSDK)（提供云通信能力）
- [互动白板 `TEduBoard`](./Docs/PaaS/SDK文档/互动白板功能说明.md)（提供文件展示及涂鸦展示能力）

互动课堂设计初衷在于抽象出这些云服务在 `在线教育场景` 下通用的使用流程，为您屏蔽各个云服务琐碎的初始化、鉴权流程等技术细节，让您能专注于业务逻辑开发。

虽然抽象出来的这套使用流程已经比较具有通用性，但是考虑到您可能还是会有一些细节上的特殊定制化需求，互动课堂这一层的代码我们以开源的形式放出，您可以根据您的实际需求进行修改定制。


## 快速体验

<font color="#FF0000">注意：</font> 由于`Github`默认不支持大文件上传，请您在clone代码前先安装[Git-LFS](./Git-LFS.md)，用于实现Github对大文件的支持。请使用以下命令clone代码，<font color="#FF0000">勿</font>直接`Download ZIP`。
```
git clone https://github.com/tencentyun/TIC.git
```


#### 体验Demo

下载客户端，输入相同的课堂ID即可快速体验。

| 平台 | 快速体验 |
|---------|---------|
| Web | 即将推出 |
| 小程序 | 即将推出 |
| Windows |  [申请体验](./Docs/购买指南.md) |
| Android | 即将推出 |
| iOS | 即将推出 |
| macOS | [申请体验](./Docs/购买指南.md)  |

#### 开发Demo

为了便于开发人员以最简明的方式调试接口，我们准备了各个平台的开发demo。

| 平台 | 源码下载 | 快速体验 |
<!--|---------|---------|---------|-->
| Web | [点击前往](./Web) | [体验链接](https://tic-demo-1259648581.cos.ap-shanghai.myqcloud.com/index.html) |
|小程序  | [点击前往](./小程序)   | ![](https://main.qcloudimg.com/raw/db3055ade262e17bcd8711026f487ae7.png) |
| Windows |[点击前往](./Windows)  | - |
|Android  | [点击前往](./Android)  | - |
| iOS | [点击前往](./iOS) | - |
| macOS |[点击前往](./macOS)   | - |

## 购买指南

[购买指南](./Docs/购买指南.md)

## 接入文档

| 平台 | 互动课堂（TIC） | 互动白板（TEduBoard） |
|---------|---------|---------|
| Web | [接入文档](./Docs/PaaS/SDK文档/Web/互动课堂接入文档.md) | [接入文档](./Docs/PaaS/SDK文档/Web/互动白板接入文档.md) |
|小程序  | [接入文档](./Docs/PaaS/SDK文档/小程序/互动课堂接入文档.md)   | [接入文档](./Docs/PaaS/SDK文档/小程序/互动白板接入文档.md) |
| Windows |[接入文档](./Docs/PaaS/SDK文档/Windows/互动课堂接入文档.md) | [接入文档](./Docs/PaaS/SDK文档/Windows/互动白板接入文档.md) |
|Android  | [接入文档](./Docs/PaaS/SDK文档/Android/互动课堂接入文档.md) | [接入文档](./Docs/PaaS/SDK文档/Android/互动白板接入文档.md) |
| iOS | [接入文档](./Docs/PaaS/SDK文档/iOS/互动课堂接入文档.md) | [接入文档](./Docs/PaaS/SDK文档/iOS/互动白板接入文档.md) |
| macOS | [接入文档](./Docs/PaaS/SDK文档/macOS/互动课堂接入文档.md) | [接入文档](./Docs/PaaS/SDK文档/macOS/互动白板接入文档.md) |


## 版本信息

| 平台 | 互动课堂（TIC） | 互动白板（TEduBoard） |
|---------|---------|---------|
| Web | [版本信息](./Docs/PaaS/版本信息/互动课堂/Web_TIC_ReleaseNotes.md) | [版本信息](./Docs/PaaS/版本信息/互动白板/Web_ReleaseNotes.md) |
|小程序  | [版本信息](./Docs/PaaS/版本信息/互动课堂/小程序_TIC_ReleaseNotes.md)   | [版本信息](./Docs/PaaS/版本信息/互动白板/小程序_ReleaseNotes.md) |
| Windows |[版本信息](./Docs/PaaS/版本信息/互动课堂/Windows_TIC_ReleaseNotes.md) | [版本信息](./Docs/PaaS/版本信息/互动白板/Windows_ReleaseNotes.md) |
|Android  | [版本信息](./Docs/PaaS/版本信息/互动课堂/Android_TIC_ReleaseNotes.md) | [版本信息](./Docs/PaaS/版本信息/互动白板/Android_ReleaseNotes.md) |
| iOS | [版本信息](./Docs/PaaS/版本信息/互动课堂/iOS_macOS_TIC_ReleaseNotes.md) | [版本信息](./Docs/PaaS/版本信息/互动白板/iOS_macOS_ReleaseNotes.md) |
| macOS | [版本信息](./Docs/PaaS/版本信息/互动课堂/iOS_macOS_TIC_ReleaseNotes.md) | [版本信息](./Docs/PaaS/版本信息/互动白板/iOS_macOS_ReleaseNotes.md) |



## 更多功能

- [实时录制](./Docs/PaaS/实时录制.md)
- [课后录制](./Docs/PaaS/课后录制.md)
- [文档转码](./Docs/PaaS/文档转码.md)

## 常见问题
- [常见问题](./Docs/PaaS/常见问题.md)
