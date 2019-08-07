//
//  TEduBoardController.h
//  TEduBoard
//
//  Created by kennethmiao on 2019/4/8.
//  Copyright © 2019年 kennethmiao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TEduBoardDef.h"


@interface TEduBoardController : NSObject

/*********************************************************************************************************
 *
 *                                             一、基本流程接口
 *
 ********************************************************************************************************/
- (instancetype)init __attribute__((unavailable("Please use initWithParam:roomId:timSync initialize the TEduBoardView")));
- (instancetype)new __attribute__((unavailable("Please use initWithParam:roomId:timSync initialize the TEduBoardView")));
- (instancetype)initWithFrame:(CGRect)frame __attribute__((unavailable("Please use initWithParam:roomId:timSync initialize the TEduBoardView")));
/**
 * 添加事件回调监听
 * @param delegate      事件回调监听
 * @warning 建议在Init之前调用该方法以支持错误处理
 */
- (void)addDelegate:(id<TEduBoardDelegate>)delegate;
/**
 * 删除事件回调监听
 * @param delegate      事件回调监听
 * @warning 建议在Init之前调用该方法以支持错误处理
 */
- (void)removeDelegate:(id<TEduBoardDelegate>)delegate;
/**
 * 初始化白板
 * @param authParam         授权参数
 * @param roomId             课堂ID
 * @param initParam              可选参数，指定用于初始化白板的一系列属性值
 * @brief 可用 initParam.timSync 指定是否使用腾讯云IMSDK进行实时数据同步, initParam.timSync == true 时，会尝试反射调用腾讯云IMSDK作为信令通道进行实时数据收发（只实现消息收发，初始化、进房等操作需要用户自行实现），目前仅支持IMSDK 4.0以上版本
 * @warning 使用腾讯云IMSDK进行实时数据同步时，只支持一个白板实例，创建多个白板实例可能导致涂鸦状态异常
 */
- (instancetype)initWithAuthParam:(TEduBoardAuthParam *)authParam roomId:(UInt32)roomId initParam:(TEduBoardInitParam *)initParam;

/**
 * 获取白板渲染View
 * @brief iOS下取UIView*，macOS下取NSView*
 */
- (TEView *)getBoardRenderView;
/**
 * 添加白板同步数据
 * @param data      接收到的房间内其他人发送的同步数据
 * @brief 该接口用于多个白板间的数据同步，使用内置IM作为信令通道时，不需要调用该接口
 */
- (void)addSyncData:(NSString *)data;
/**
 * 设置白板是否开启数据同步
 * @param enable    是否开启
 * @brief 白板创建后默认开启数据同步，关闭数据同步，本地的所有白板操作不会同步到远端和服务器
 */
- (void)setDataSyncEnable:(BOOL)enable;
/**
 * 获取白板是否开启数据同步
 * @return 是否开启数据同步，YES 表示开启，NO 表示关闭
 */
- (BOOL)isDataSyncEnable;
/**
 * 重置白板
 * @brief 调用该接口后将会删除所有的白板页和文件
 */
- (void)reset;
/**
 * 获取版本号
 * @return NSString  版本号字符串
 */
+ (NSString *)getVersion;

/*********************************************************************************************************
 *
 *                                             二、涂鸦相关接口
 *
 ********************************************************************************************************/
/**
 * 设置白板是否允许涂鸦
 * @param enabled       是否允许涂鸦，true 表示白板可以涂鸦，false 表示白板不能涂鸦
 * @brief 白板创建后默认为允许涂鸦状态
 */
- (void)setDrawEnable:(BOOL)enabled;

/**
 * 获取白板是否允许涂鸦
 * @return 是否允许涂鸦，YES 表示白板可以涂鸦，NO 表示白板不能涂鸦
 */
- (BOOL)isDrawEnable;

/**
 * 设置白板默认背景色
 * @param color     要设置的默认背景色
 * @brief 白板创建后默认背景色为白色
 */
- (void)setGlobalBackgroundColor:(TEColor *)color;
/**
 * 获取白板默认背景色
 * @return 默认背景色
 */
- (TEColor *)getGlobalBackgroundColor;

/**
 * 设置当前白板页的背景色
 * @param color     要设置的背景色
 * @brief 白板页创建以后的默认背景色由SetDefaultBackgroundColor接口设定
 */
- (void)setBackgroundColor:(TEColor *)color;
/**
 * 获取当前白板页的背景色
 * @return 当前白板页的背景色
 */
- (TEColor *)getBackgroundColor;

/**
 * 设置当前白板页的背景图片
 * @param url       要设置的背景图片URL
 * @param mode      要使用的图片填充对齐模式
 * @brief 当URL是一个有效的本地文件地址时，该文件会被自动上传到COS,该接口与SetBackgroundH5接口互斥
 */
- (void)setBackgroundImage:(NSString *)url mode:(TEduBoardImageFitMode)mode;
/**
 * 设置当前白板页的背景H5页面
 * @param url                要设置的背景H5页面URL
 * @info 该接口与SetBackgroundImage接口互斥
 */
- (void)setBackgroundH5:(NSString *)url;

/**
 * 设置要使用的白板工具
 * @param type      要设置的白板工具
 */
- (void)setToolType:(TEduBoardToolType)type;
/**
 * 获取正在使用的白板工具
 * @return 正在使用的白板工具
 */
- (TEduBoardToolType)getToolType;

/**
 * 设置画笔颜色
 * @param color     要设置的画笔颜色
 * @brief 画笔颜色用于所有涂鸦绘制
 */
- (void)setBrushColor:(TEColor *)color;
/**
 * 获取画笔颜色
 * @return 画笔颜色
 */
- (TEColor *)getBrushColor;

/**
 * 设置画笔粗细
 * @param thin      要设置的画笔粗细
 * @brief 画笔粗细用于所有涂鸦绘制，实际像素值取值(thin * 白板的高度 / 10000)px，如果结果小于1px，则涂鸦的线条会比较虚
 */
- (void)setBrushThin:(UInt32)thin;
/**
 * 获取画笔粗细
 * @return 画笔粗细
 */
- (UInt32)getBrushThin;

/**
 * 设置文本颜色
 * @param color     要设置的文本颜色
 */
- (void)setTextColor:(TEColor *)color;
/**
 * 获取文本颜色
 * @return 文本颜色
 */
- (TEColor *)getTextColor;

/**
 * 设置文本样式
 * @param style     要设置的文本样式
 */
- (void)setTextStyle:(TEduBoardTextStyle)style;

/**
 * 获取文本样式
 * @return 文本样式
 */
- (TEduBoardTextStyle)getTextStyle;

/**
 * 设置文本字体
 * @param family     要设置的文本字体
 */
- (void)setTextFamily:(NSString *)family;

/**
 * 获取文本字体
 * @return 文本字体
 */
- (NSString *)getTextFamily;

/**
 * 设置文本大小
 * @param size      要设置的文本大小
 * @brief 实际像素值取值(size * 白板的高度 / 10000)px
 */
- (void)setTextSize:(UInt32)size;
/**
 * 获取文本大小
 * @return 文本大小
 */
- (UInt32)getTextSize;


/**
 * 设置直线样式
 * @param style  直线样式
 * @brief 在TEduBoardToolType设置为TEDU_BOARD_TOOL_TYPE_LINE有效
 */
- (void)setLineStyle:(TEduBoardLineStyle *)style;
/**
 * 获取直线样式
 * @return 直线样式
 */
- (TEduBoardLineStyle *)getLineStyle;

/**
 * 设置椭圆绘制模式
 * @param mode  椭圆绘制模式
 * @brief 在TEduBoardToolType设置为TEDU_BOARD_TOOL_TYPE_OVAL和TEDU_BOARD_TOOL_TYPE_OVAL_SOLID有效
 */
- (void)setOvalDrawMode:(TEduBoardOvalDrawMode)mode;
/**
 * 获取椭圆绘制模式
 * @return 椭圆绘制模式
 */
- (TEduBoardOvalDrawMode)getOvalDrawMode;


/**
 * 撤销当前白板页上一次动作
 */
- (void)undo;
/**
 * 重做当前白板页上一次撤销
 */
- (void)redo;
/**
 * 清除涂鸦，同时清空背景色以及背景图片
 */
- (void)clear;
/**
 * 清除涂鸦
 */
- (void)clearDraws;


/*********************************************************************************************************
 *
 *                                             三、白板页操作接口
 *
 ********************************************************************************************************/
/**
 * 增加一页白板
 * @param url       要使用的背景图片URL，为空表示不指定背景图片
 * @return 白板ID
 * @brief 白板页会被添加到当前文件
 */
- (NSString *)addBoardWithBackgroundImage:(NSString *)url;
/**
 * 删除一页白板
 * @param boardId   要删除的白板ID，为空表示删除当前页
 * @brief 允许删除任意文件的白板页，默认白板页无法删除
 */
- (void)deleteBoard:(NSString *)boardId;
/**
 * 上一步
 * @brief 每个Step对应PPT的一个动画效果，若当前没有已展示的动画效果，则该接口调用会导致向前翻页
 */
- (void)prevStep;

/**
 * 下一步
 * @brief 每个Step对应PPT的一个动画效果，若当前没有未展示的动画效果，则该接口调用会导致向后翻页
 */
- (void)nextStep;

/**
 * 向前翻页
 * @brief 若当前白板页为当前文件的第一页，则该接口调用无效
 */
- (void)preBoard;
/**
 * 向后翻页
 * @brief 若当前白板页为当前文件的最后一页，则该接口调用无效
 */
- (void)nextBoard;
/**
 * 跳转到指定白板页
 * @param boardId       要跳转到的白板页ID
 * @brief 允许跳转到任意文件的白板页
 */
- (void)gotoBoard:(NSString *)boardId;

/**
 * 向前翻页
 * @param resetStep     是否重置白板步数
 * @brief 若当前白板页为当前文件的第一页，则该接口调用无效
 */
- (void)preBoard:(BOOL)resetStep;
/**
 * 向后翻页
 * @param resetStep     是否重置白板步数
 * @brief 若当前白板页为当前文件的最后一页，则该接口调用无效
 */
- (void)nextBoard:(BOOL)resetStep;
/**
 * 跳转到指定白板页
 * @param boardId       要跳转到的白板页ID
 * @param resetStep     是否重置白板步数
 * @brief 允许跳转到任意文件的白板页
 */
- (void)gotoBoard:(NSString *)boardId resetStep:(BOOL)resetStep;

/**
 * 获取当前白板页ID
 * @return 当前白板页ID
 */
- (NSString *)getCurrentBoard;
/**
 * 获取所有文件的白板列表
 * @return 所有文件的白板列表
 */
- (NSArray<NSString *> *)getBoardList;
/**
 * 设置当前白板页宽高比
 * @param ratio     要设置的白板宽高比
 * @brief 格式如"4:3" "16:9"
 */
- (void)setBoardRatio:(NSString *)ratio;
/**
 * 获取当前白板页宽高比
 * @return 白板宽高比，格式与SetBoardRatio接口参数格式一致
 */
- (NSString *)getBoardRatio;
/**
 * 设置当前白板页缩放比例
 * @param scale                要设置的白板缩放比例
 * @brief 支持范围: [100，300]，实际缩放比为: scale/100
 */
- (void)setBoardScale:(UInt32)scale;

/**
 * 获取当前白板页缩放比例
 * @return 白板缩放比例，格式与SetBoardScale接口参数格式一致
 */
- (UInt32)getBoardScale;
/**
 * 设置白板内容自适应模式
 * @param mode                要设置的白板内容自适应模式
 * @info 设置自适应模式后会影响所有后续白板内容操作,受影响接口包括：AddFile、AddH5PPTFile
 */
- (void)setBoardContentFitMode:(TEduBoardContentFitMode)mode;
/**
 * 获取白板内容自适应模式
 * @return 白板内容自适应模式
 */
- (TEduBoardContentFitMode)getBoardContentFitMode;

/*********************************************************************************************************
 *
 *                                             四、文件操作接口
 *
 ********************************************************************************************************/
/**
 * 增加文件
 * @param path      要增加的文件路径
 * @return NSString 文件Id
 * @brief 支持 PPT、PDF、Word、Excel，调用该接口后，SDK会先将文件上传到COS后再执行后续操作，因此该接口会触发文件上传相关回调，文件上传成功后，将自动切换到该文件
 */
- (NSString *)addFile:(NSString *)path
__attribute__((deprecated("接口已废弃，后续会删除，不建议使用，添加文件请统一使用addTranscodeFile接口")));
/**
 * 增加H5动画PPT文件
 * @param url       要增加的H5动画PPT的URL
 * @return NSString 文件Id
 * @brief 调用该接口后，SDK会在后台进行H5加载，期间用户可正常进行其它操作，加载成功或失败后会触发相应回调，H5加载成功后，将自动切换到该文件
 */
- (NSString *)addH5PPTFile:(NSString *)url
__attribute__((deprecated("接口已废弃，后续会删除，不建议使用，添加文件请统一使用addTranscodeFile接口")));
/**
 * 添加转码文件
 * @param result 文件转码结果
 * @return NSString 文件Id
 */
- (NSString *)addTranscodeFile:(TEduBoardTranscodeFileResult *)result;
/**
 * 删除文件
 * @param fileId        要删除的文件ID
 * @brief 文件ID为空时表示当前文件，默认文件无法删除
 */
- (void)deleteFile:(NSString *)fileId;
/**
 * 切换文件
 * @param fileId        要切换到的文件ID
 * @brief 文件ID为必填项，为空将导致文件切换失败
 */
- (void)switchFile:(NSString *)fileId;
/**
 * 获取当前文件ID
 * @return 当前文件ID
 */
- (NSString *)getCurrentFile;
/**
 * 获取白板中上传的所有文件的文件信息列表
 * @return 文件信息列表
 */
- (NSArray<TEduBoardFileInfo *> *)getFileInfoList;
/**
 * 获取指定文件id的文件信息
 * @param fileId   文件ID
 * @return 文件信息
 */
- (TEduBoardFileInfo *)getFileInfo:(NSString *)fileId;

/**
 * 获取指定文件的白板列表
 * @param fileId        文件ID
 * @return 白板列表
 */
- (NSArray<NSString *> *)getFileBoardList:(NSString *)fileId;
/**
 * 清空指定文件的所有白板涂鸦
 * @param fileId        文件ID
 */
- (void)clearFileDraws:(NSString *)fileId;

@end

