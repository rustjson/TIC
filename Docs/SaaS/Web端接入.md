### 1. 拼接链接打开课堂

- URL启动

```
https://tedu.qcloudtrtc.com/#/class/:class_id/:sdkappid?/:user_id?/:user_sig?/:user_token?
```

- 参数描述

参数名称|参数类型|参数描述
:--:|:--:|:--
sdkappid|int|腾讯云应用程序标识
class_id|int|课堂id
user_id|string|用户帐号
user_sig|string|腾讯云用户签名(用于登录IMSDK)
user_token|string|用户签名

以上参数如有疑义，请前往 https://git.code.oa.com/qcloud_edu/tic2.0/blob/daily/Docs/SaaS/%E6%93%8D%E4%BD%9C%E6%8C%87%E5%8D%97/%E4%BA%91API.md#21-%E5%88%9B%E5%BB%BA%E8%B4%A6%E5%8F%B7 
查看