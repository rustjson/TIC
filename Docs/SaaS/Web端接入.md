### 1. 拼接链接打开课堂

- URL启动

```
https://tedu.qcloudtrtc.com/class/:classId/:sdkAppId?/:userId?/:userSig?/:token?
```

- 参数描述

参数名称|参数类型|参数描述
:--:|:--:|:--
sdkAppId|int|腾讯云应用程序标识
classId|int|课堂id
userId|string|用户帐号
userSig|string|腾讯云用户签名(用于登录IMSDK)
token|string|用户签名