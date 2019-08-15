本文主要介绍如何快速地将 TICSaaS 组件集成到您的项目中，只要按照如下步骤进行配置，就可以完成组件的集成工作。

# 开发环境要求
* Android studio 3.0+
* Android 4.3 （API 19）及以上系统

# 快速集成SDK
TICSaaS组件已经发布到jcenter，您可以通过配置gradle自动下载更新。只需要用 Android Studio 打开需要集成 SDK 的工程（本文以 TICSaaSDemo 为例），然后通过简单的三个步骤修改 app/build.gradle 文件，就可以完成 SDK 集成：

* 第一步：添加 SDK 依赖
在 dependencies 中添加  TICSaaS 以其它模块 的依赖。

```groovy
 dependencies {
    // TIC SaaS 组件
    implementation "com.tencent.ticsaas:core:0.1.11-alpha"
    // 实时音视频
    implementation "com.tencent.liteav:LiteAVSDK_TRTC:6.5.7272"
    // 云通信 IM SDK
    implementation "com.tencent.imsdk:imsdk:4.3.145"
    implementation "com.tencent.imsdk:mobilepbforimsdk:1.6.0.45"
    // 腾讯云互动白板
    implementation "com.tencent.teduboard:TEduBoardSdk:2.2.2.99"
}
```

第二步：指定 App 使用架构
在 defaultConfig 中，指定 App 使用的 CPU 架构(目前 TICSaaS  支持 armeabi和armeabi-v7a ) 。

```groovy
  defaultConfig {
      ndk {
          abiFilters "armeabi", "armeabi-v7a"
      }
  }
```
第三步：使用JDK 1.8编译

```groovy
compileOptions {
    sourceCompatibility 1.8
    targetCompatibility 1.8
}
```

第四步：同步 SDK
单击 Sync Now 按钮，如果您的网络连接 jcenter 没有问题，很快 SDK 就会自动下载集成到工程里。

# 使用方法
## 初始化
在Application的onCreate()中初始化
```java
        // 主进程初始化
        if (SessionWrapper.isMainProcess(this)) {
            ClassroomManager.getInstance().init(this);
        }
```

相应地，在onTerminate()反初始化。
```java
        // 主进程反初始化
        if (SessionWrapper.isMainProcess(this)) {
            ClassroomManager.getInstance().unInit();
        }
```

## 申请必要权限（Android 6.0以上）
Android 6.0以上系统，拉起组件前，须动态申请麦克风录音，摄像头和写存储器权限。
```java
Manifest.permission.RECORD_AUDIO
Manifest.permission.CAMERA
Manifest.permission.WRITE_EXTERNAL_STORAGE
```
可参考[请求应用权限](https://developer.android.com/training/permissions/requesting?hl=zh-cn)
## 调起SaaS组件
只需要传递5个参数，即可调起SaaS组件主页面，分别是机构ID、课堂ID、用户ID、用户Token和用户Sig，如下：
```java
    private void launchInActivity(int companyID, int classID, String userID, String userToken, String userSig) {
        Intent intent = new Intent(this, InClassActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        Bundle bundle = new Bundle();
        bundle.putInt("company_id", companyID);
        bundle.putInt("class_id", classID);
        bundle.putString("user_id", userID);
        bundle.putString("user_token", userToken);
        bundle.putString("user_sig", userSig);
        intent.putExtras(bundle);
        startActivity(intent);
    }
```

## 全屏显示
为了达到更好的视觉效果，推荐App使用全屏模式，如，使用NoActionBar类主题：
```xml
    <style name="AppTheme" parent="Theme.AppCompat.Light.NoActionBar">
        <!-- Customize your theme here. -->
        ...
    </style>
```