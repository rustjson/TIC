### 1. 拼接链接打开课堂

- URL启动

```
https://tedu.qcloudtrtc.com/class/:classId/:sdkAppId?/:userId?/:userSig?/:token?
```

- 参数描述

参数名称|参数类型|参数描述
:--:|:--:|:--
sdkappid|int|腾讯云应用程序标识
class_id|int|课堂id
user_id|string|用户帐号
user_token|string|用户密码
user_sig|string|腾讯云用户签名(用于登录IMSDK)