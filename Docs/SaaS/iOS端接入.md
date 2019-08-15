# 互动课堂 SaaS 组件 iOS 端集成文档
## 1. 快速接入
> TIC_SaaS_SDK（即互动课堂 SaaS 组件，下同） 支持 iOS 8 及以上系统，支持 Cocoapods 集成，集成完之后还需进行相应的工程配置。

### 1.1 pod 集成
在项目 Podfile 文件中加入：

```
pod 'TIC_SaaS_SDK'    
```

安装：

```
pod install
```
如遇无法找到 SDK 或无法安装 SDK 最新版本问题，尝试运行以下命令更新本地的 CocoaPods 仓库

```
pod repo update
```

TIC_SaaS_SDK 依赖了以下一些 pod 库，在`pod install`会自动安装，如果您的 App 中也用到了这些 pod 库，可以直接删除，用 TIC_SaaS_SDK 依赖安装的即可。

```
pod 'Masonry'
pod 'YYModel'
pod 'TXLiteAVSDK_TRTC'
pod 'TXIMSDK_iOS'
pod 'AFNetworking'
pod 'MJRefresh'
pod 'Bugly'
pod 'MBProgressHUD'
```

### 1.2 工程配置
由于互动课堂组件具备音视频直播互动功能，所以要用到 iPhone 或 iPad 的相机和麦克风，需要在项目的`info.plist`文件中增加`Privacy - Camera Usage Description`和`Privacy - Microphone Usage Description`两项，并设置相应中文描述。

### 1.3 集成验证
在`appdelegate.m`中导入头文件`<TIC_SaaS_SDK/TIC_SaaS_SDK.h>`，该头文件包含了`TIC_SaaS_SDK`中所有公开的头文件，调用`TICManager`的`getVersion`方法获取版本号：

```objc
#import <TIC_SaaS_SDK/TIC_SaaS_SDK.h>

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    NSLog(@"%@",[TICManager getVersion]);
    return YES;
}
```
如果集成没问题，控制台就能打印出`TICSDK`的版本号。

## 2. 使用详解
### 2.1 头文件概览

SDK 中暴露的公开头文件如下表：

类名 | 主要功能
--------- | ---------
TIC_SaaS_SDK.h | SDK 总头文件类，包含了开发者可能用到的所有头文件，开发者集成时，只需导入该头文件即可
TICManager.h | 互动课堂管理类，互动课堂SDK对外主要接口类，提供了【初始化】、【加入课堂】、【获取版本】等接口。
TICClassroomViewController.h | 课堂主页视图控制器，承载了课堂主页的 UI 和逻辑


### 2.2 使用流程

使用互动课堂 SaaS 组件只需要两步：
1. **初始化**
2. **加入课堂**

### 初始化
调用`TICManager`中的 `initWithSdkAppId:callback:`方法，传入腾讯云应用程序标识，进行 SDK 的初始化。

```objc
/**
 初始化，默认开启 bugly，建议 App 启动时调用

 @param sdkAppId 腾讯云应用程序标识
 @param callback 回调
 */
- (void)initWithSdkAppId:(int)sdkAppId callback:(void (^)(int code, NSString *desc))callback;
```

需要注意的是，互动课堂 SaaS 组件中用到了 [腾讯 bugly](https://bugly.qq.com/v2/) 服务，初始化后默认就会开启，如果你的 App 也用到了腾讯 bugly，可调用以下接口，`isOpen` 参数传 `NO` 来关闭组件中的 bugly 服务:

```objc
/**
  初始化【建议 App 启动时调用】

 @param sdkAppId 腾讯云应用程序标识
 @param isOpen 是否开启SDK内 bugly 模块
 @param callback 回调
 
 @discussion 如用户自己的 App 也用到了 bugly，建议关闭 SDK 内的bug
 */
- (void)initWithSdkAppId:(int)sdkAppId openBugly:(BOOL)isOpen callback:(void (^)(int code, NSString *desc))callback;
```


### 加入课堂
调用以下接口加入课堂
```objc
/**
 加入课堂

 @param config 课堂配置
 @param succ 成功回调
 @param failed 失败回调
 */
- (void)joinClassroomWith:(TICClassroomConfig *)config succ:(void (^)(void))succ failed:(void (^)(int code, NSString *errMsg))failed;
```

该接口接入一个课堂配置参数，其原型为`TICClassroomConfig`类
```objc
/**
 课堂配置类，加入课堂时需传入这些信息
 */
@interface TICClassroomConfig : NSObject

@property (nonatomic, copy) NSString *classID;  // 课堂ID
@property (nonatomic, copy) NSString *userID;   // 用户ID
@property (nonatomic, copy) NSString *userToken;// 用户密码
@property (nonatomic, strong) NSNumber *companyID;  // 机构码（腾讯云互动课堂后台为每个注册企业的分配唯一标识码）
@property (nonatomic, copy) NSString *userSig;  // 用户签名（没有在腾讯云互动课堂后台设置IM私钥的，必填；设置了IM私钥的填 nil）

@end
```

同时，开发者还需要在加入课堂接口的成功回调中唤起课堂主页控制器 `TICClassroomViewController` ，示例代码如下：

```objc
// 设置课堂配置信息
TICClassroomConfig *config = [[TICClassroomConfig alloc] init];;
config.classID = classID;
config.userID = userID ;
config.userToken = userToken;
config.companyID = companyID;
config.userSig = userSig;

// 调用加入课堂接口，加入课堂，传入 config 对象
[[TICManager sharedInstance] joinClassroomWith:config succ:^{
    // 加入课堂成功，唤起课堂主页控制器
    TICClassroomViewController *vc = [[TICClassroomViewController alloc] initWithClassId:classID];
    [controller presentViewController:vc animated:YES completion:nil];
} failed:^(int code, NSString * _Nonnull errMsg) {
      // 加入课堂失败
    NSLog(@"加入课堂失败：%d %@", code, errMsg);
}];
```

> 注意：
> `TICClassroomViewController` 要使用指定的初始化方法进行初始化 ` initWithClassId:` 并传入课堂 ID.
> `TICClassroomViewController` 课堂主页控制器只支持横屏展示

成功唤起课堂主页控制器后，即可使用课堂内的业务和功能。