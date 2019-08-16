# 1.SaaS客户端接入流程

![](https://main.qcloudimg.com/raw/6bc87cb24381be162af59ece11c991af.png)

1. 控制台添加老师/学生账户信息；

2. 在控制台上提前准备上课课件；

3. 创建课堂，获取课堂ID；

4. 在1-3步骤之后，您可以拿到classID、userID和userToken等关键信息，加上腾讯云互动课堂统一分配的机构码，这样您就可以使用腾讯云互动课堂客户端进行授课上课了。


> 更多控制台的使用，可以参考[控制台使用手册]()


# 2.关键参数解释及获取方式

参数ID|参数类型|解释|获取方式
:--:|:--:|:--:|:--
company_id|int|机构码：获取机构的信息(机构名称，应用icon等)的唯一标识|申请Saas服务邮件获取 具体见
class_id|int|课堂id：获取课堂信息的唯一标识|通过云API 创建课堂获取
user_id|string|用户帐号|通过云API 创建用户获取
user_token|string|用户签名|通过云API 创建用户获取
user_sig|string|腾讯云签名 登录必要的腾讯云模块用|1如果用户把私钥托管给我们，不用填 2如果没有托管，请拿IMSDK私钥自行计算

# 3.各个端接入流程

## 3.1 桌面端（应用方案）
<div id="electron_location"></div>

目前桌面客户端暂时只提供纯应用方式拉起，后期会提供库方式整合 目前桌面端支持MAC和PC
业务方通过云API 对课堂，用户，课件进行管理。应用只负责上课授课和课中互动。
目前应用页面只支持定制应用名称和icon，页面布局后期会通过云API方式逐步开放。


###  下载按照互动课堂应用
mac: http://dldir1.qq.com/hudongzhibo/Saas/TClass_Saas.dmg
win: http://dldir1.qq.com/hudongzhibo/Saas/TClass_Setup_Saas.exe

在用户机器上安装互动课堂组件。在Win10上必需使用管理员权限安装。


###  进入课堂

   进入课堂之前，必须得通过控制台或者云API方式创建课堂，指定老师（学生可选)。

####  通过浏览器启动应用直接进入课堂 


   如果已经安装过应用，可以通过浏览器方式直接拉起来。（MAC需点击启动一次才能拉起，受限electron注册网络协议）
没有安装，会提示下载地址。 目前支持的浏览器有Chrome Safari。

```
https://tedu.qcloudtrtc.com/#/class/company_id/:class_id/:user_id?/:user_sig?/:user_token?
```


  参数如何获取 参数上面的表格


#### 点击启动进入课堂

  桌面点击应用启动 输入机构码，课堂ID，用户ID 用户密码的加入课堂

成功进入课堂一次之后 会记住机构码 课堂ID 用户ID



## 3.2 WEB端
<span id="web_location"></span>

目前WEB客户端暂时只提供纯网页方式拉起，后期会提供库方式整合

###  URL启动

```
https://tedu.qcloudtrtc.com/#/class/company_id/:class_id/:user_id?/:user_sig?/:user_token?
```

### example - 不带登录态
```
company_id(机构码) => 100001
class_id（课堂id） => 1000713668
```

https://tedu.qcloudtrtc.com/#/class/100001/1000713668


## 3.3 移动端

### 安装

Android：应用宝搜索《腾讯云互动课堂》
iOS：App Store 搜索《腾讯云互动课堂》

### 使用

参考[互动课堂 SaaS 移动端 App 使用文档](#Android_location)
