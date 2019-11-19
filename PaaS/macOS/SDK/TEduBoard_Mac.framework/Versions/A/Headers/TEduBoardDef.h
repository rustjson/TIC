//
//  TEduBoardDef.h
//  TEduBoard
//
//  Created by kennethmiao on 2019/4/2.
//  Copyright © 2019年 kennethmiao. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
typedef UIView TEView;
typedef UIColor TEColor;
#else
#import <AppKit/AppKit.h>
typedef NSView TEView;
typedef NSColor TEColor;
#endif


/**
 * 白板工具类型
 */
typedef NS_ENUM(NSInteger, TEduBoardToolType)
{
    TEDU_BOARD_TOOL_TYPE_MOUSE          = 0,    //鼠标
    TEDU_BOARD_TOOL_TYPE_PEN            = 1,    //画笔
    TEDU_BOARD_TOOL_TYPE_ERASER         = 2,    //橡皮擦
    TEDU_BOARD_TOOL_TYPE_LASER          = 3,    //激光笔
    TEDU_BOARD_TOOL_TYPE_LINE           = 4,    //直线
    TEDU_BOARD_TOOL_TYPE_OVAL           = 5,    //空心椭圆
    TEDU_BOARD_TOOL_TYPE_RECT           = 6,    //空心矩形
    TEDU_BOARD_TOOL_TYPE_OVAL_SOLID     = 7,    //实心椭圆
    TEDU_BOARD_TOOL_TYPE_RECT_SOLID     = 8,    //实心矩形
    TEDU_BOARD_TOOL_TYPE_POINT_SELECT   = 9,    //点选工具
    TEDU_BOARD_TOOL_TYPE_RECT_SELECT    = 10,   //选框工具
    TEDU_BOARD_TOOL_TYPE_TEXT           = 11,   //文本工具
    TEDU_BOARD_TOOL_TYPE_ZOOM_DRAG      = 12,   //缩放移动
};

/**
 * 白板图片填充对齐模式定义
 * @brief 当以宽度基准等比例放大，则居左和居右同居中对齐效果一致；当以高度基准等比例放大，则居顶和居底同居中对齐效果一致
 */
typedef NS_ENUM(NSInteger, TEduBoardImageFitMode) {
    TEDU_BOARD_IMAGE_FIT_MODE_CENTER        = 0,    //以宽度或者高度为基准居中对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_LEFT          = 4,    //以宽度或者高度为基准左对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_TOP           = 5,    //以宽度或者高度为基准顶对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_RIGHT         = 6,    //以宽度或者高度为基准右对齐等比例放大
    TEDU_BOARD_IMAGE_FIT_MODE_BOTTOM        = 7,    //以宽度或者高度为基准底对齐等比例放大
};

/**
 * 白板内容自适应模式（内容包括图片、文件、PPT动画）
 */
typedef NS_ENUM(NSInteger, TEduBoardContentFitMode) {
    TEDU_BOARD_CONTENT_FIT_MODE_NONE            = 0,        //不使用内容自适应，默认模式，不自动调整白板宽高比，内容等比例缩放居中显示，内容宽高<=白板宽高
    TEDU_BOARD_CONTENT_FIT_MODE_CENTER_INSIDE   = 1,        //自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高<=容器宽高
    TEDU_BOARD_CONTENT_FIT_MODE_CENTER_COVER    = 2,        //自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高>=容器宽高
};

/**
 * 白板图片状态定义
 */
typedef NS_ENUM(NSInteger, TEduBoardImageStatus)
{                                                   //状态描述              对应WEB白板事件
    TEDU_BOARD_IMAGE_STATUS_LOADING         = 1,    //背景图片正在加载        CONSTANT.EVENT.IMG_START_LOAD
    TEDU_BOARD_IMAGE_STATUS_LOAD_DONE       = 2,    //背景图片加载完成        CONSTANT.EVENT.IMG_LOAD
    TEDU_BOARD_IMAGE_STATUS_LOAD_ABORT      = 3,    //背景图片加载中断        CONSTANT.EVENT.IMG_ABORT
    TEDU_BOARD_IMAGE_STATUS_LOAD_ERROR      = 4,    //背景图片加载错误        CONSTANT.EVENT.IMG_ERROR
};

/**
 * 白板文本样式
 */
typedef NS_ENUM(NSInteger, TEduBoardTextStyle)
{
    TEDU_BOARD_TEXT_STYLE_NORMAL            = 0,    //常规样式
    TEDU_BOARD_TEXT_STYLE_BOLD              = 1,    //粗体样式
    TEDU_BOARD_TEXT_STYLE_ITALIC            = 2,    //斜体样式
    TEDU_BOARD_TEXT_STYLE_BOLD_ITALIC       = 3,    //粗斜体样式
};

/**
 * 白板错误码定义（严重）
 */
typedef NS_ENUM(NSInteger, TEduBoardErrorCode)
{
    TEDU_BOARD_ERROR_INIT               = 1,       //白板加载失败
    TEDU_BOARD_ERROR_AUTH               = 2,       //服务鉴权失败，请先购买服务
    TEDU_BOARD_ERROR_LOAD               = 3,       //白板加载失败
    TEDU_BOARD_ERROR_TIM_INVALID        = 5,       //腾讯云IMSDK不可用
    TEDU_BOARD_ERROR_TIM_HISTORYDATA    = 6,       //同步历史数据失败
    TEDU_BOARD_ERROR_RUNTIME            = 7,       //白板运行错误
};

/**
 * 白板错误码定义（警告）
 */
typedef NS_ENUM(NSInteger, TEduBoardWarningCode)
{
    TEDU_BOARD_WARNING_SYNC_DATA_PARSE_FAILED       = 1,    //接收到其他端的同步数据解析失败
    TEDU_BOARD_WARNING_TIM_SEND_MSG_FAILED          = 2,    //腾讯IMSDK发送消息失败
    TEDU_BOARD_WARNING_H5PPT_ALREADY_EXISTS         = 3,    //当要添加的H5PPT已存在时抛出该警告
    TEDU_BOARD_WARNING_ILLEGAL_OPERATION            = 5,    //白板历史数据加载完成之前禁止操作
};

/**
 * 白板上传状态
 */
typedef NS_ENUM(NSInteger, TEduBoardUploadStatus)
{
    TEDU_BOARD_UPLOAD_STATUS_SUCCEED       = 1,    //上传成功
    TEDU_BOARD_UPLOAD_STATUS_FAILED        = 2,    //上传失败
};

/**
 * H5背景状态定义
 */
typedef NS_ENUM(NSInteger, TEduBoardBackgroundH5Status)
{
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOADING       = 1,    //H5背景正在加载
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOAD_FINISH   = 2,    //H5背景加载完成
};

/**
 * 直线类型
 */
typedef NS_ENUM(NSInteger, TEduBoardLineType)
{
    TEDU_BOARD_LINE_TYPE_SOLID    = 1,    //实线
    TEDU_BOARD_LINE_TYPE_DOTTED   = 2,    //虚线
};

/**
 * 箭头方向
 */
typedef NS_ENUM(NSInteger, TEduBoardArrowType)
{
    TEDU_BOARD_ARROW_TYPE_NONE     = 1,    //无箭头
    TEDU_BOARD_ARROW_TYPE_NORMAL   = 2,    //普通箭头
    TEDU_BOARD_ARROW_TYPE_SOLID    = 3,    //实心箭头
};

/**
 * 椭圆绘制模式
 */
typedef NS_ENUM(NSInteger, TEduBoardOvalDrawMode)
{
    TEDU_BOARD_OVAL_DRAW_MODE_FIX_START     = 1,    //固定起始点，起始点和终点的中点为圆心
    TEDU_BOARD_OVAL_DRAW_MODE_FIX_CENTER    = 2,    //固定圆心，起始点为圆心
};

/**
 * 转码状态
 */
typedef NS_ENUM(NSInteger, TEduBoardFileTranscodeStatus)
{
    TEDU_BOARD_FILE_TRANSCODE_ERROR         = 1,    //转码错误
    TEDU_BOARD_FILE_TRANSCODE_UPLOADING     = 2,    //文件上传中
    TEDU_BOARD_FILE_TRANSCODE_CREATED       = 3,    //发起转码任务
    TEDU_BOARD_FILE_TRANSCODE_QUEUED        = 4,    //排队中
    TEDU_BOARD_FILE_TRANSCODE_PROCESSING    = 5,    //转码中
    TEDU_BOARD_FILE_TRANSCODE_FINISHED      = 6,    //转码完成
};


/**
 * 白板信息
 */
@interface TEduBoardInfo : NSObject
//白板ID
@property (nonatomic, strong) NSString *boardId;
//背景图或者背景H5页面的URL
@property (nonatomic, strong) NSString *backgroundUrl;
//白板背景色
@property (nonatomic, strong) TEColor *backgroundColor;
@end


/**
 * 文件信息
 */
@interface TEduBoardFileInfo : NSObject
//文件标识
@property (nonatomic, strong) NSString *fileId;
//文件名称
@property (nonatomic, strong) NSString *title;
//文件下载地址
@property (nonatomic, strong) NSString *downloadURL;
//当前页数
@property (nonatomic, assign) int pageIndex;
//页数
@property (nonatomic, assign) int pageCount;
//白板信息列表
@property (nonatomic, strong) NSArray<TEduBoardInfo *> *boardInfoList;
@end


@interface TEduBoardAuthParam : NSObject
//应用标识
@property (nonatomic, assign) int sdkAppId;
//用户标识
@property (nonatomic, strong) NSString *userId;
//签名
@property (nonatomic, strong) NSString *userSig;
@end

@interface TEduBoardInitParam : NSObject
//默认白板宽高比，可传格式如“4:3”、“16:9”的字符串，默认“16:9”
@property (nonatomic, strong) NSString *ratio;
//是否允许涂鸦，默认YES
@property (nonatomic, assign) BOOL drawEnable;
//全局背景色
@property (nonatomic, strong) TEColor *globalBackgroundColor;
//白板工具，默认TEDU_BOARD_TOOL_TYPE_PEN
@property (nonatomic, assign) TEduBoardToolType toolType;
//画笔颜色
@property (nonatomic, strong) TEColor *brushColor;
//画笔粗细，默认100
@property (nonatomic, assign) int brushThin;
//文本颜色
@property (nonatomic, strong) TEColor *textColor;
//文本粗细，默认320
@property (nonatomic, assign) int textSize;
//文本样式，默认TEDU_BOARD_TEXT_STYLE_NORMAL
@property (nonatomic, assign) TEduBoardTextStyle textStyle;
//是否使用腾讯云IMSDK进行实时数据同步，默认YES
@property (nonatomic, assign) BOOL timSync;
//是否启用数据同步，禁用后将导致本地白板操作不会被同步给远端
@property (nonatomic, assign) BOOL dataSyncEnable;
//图片预加载深度，默认值5，表示预加载当前页前后5页的图片
@property (nonatomic, assign) int preloadDepth;
//平滑系数，默认0.1，范围[0，1]
@property (nonatomic, assign) float smoothLevel;
//白板内容自适应模式，默认TEDU_BOARD_CONTENT_FIT_MODE_NONE
@property (nonatomic, assign) TEduBoardContentFitMode boardContentFitMode;

@end


@interface TEduBoardLineStyle : NSObject
//直线类型，默认TEDU_BOARD_LINE_TYPE_SOLID
@property (nonatomic, assign) TEduBoardLineType lineType;
//起点箭头类型，默认TEDU_BOARD_ARROW_TYPE_NONE
@property (nonatomic, assign) TEduBoardArrowType startArrowType;
//终点箭头类型，默认TEDU_BOARD_ARROW_TYPE_NONE
@property (nonatomic, assign) TEduBoardArrowType endArrowType;
@end


@interface TEduBoardTranscodeConfig : NSObject
//指定转码结果最小分辨率，可用于提高转码结果清晰度，如960x540，宽高分隔符为x
@property (nonatomic, strong) NSString *minResolution;
//指定对于PPT文件是否启用静态转码（转为静态图片），默认转为H5动画（转码耗时较长）
@property (nonatomic, assign) BOOL isStaticPPT;
//指定文件生成缩略图分辨率，默认不生成缩略图（生成缩略图增加额外转码消耗），如200x200，宽高分隔符为x
@property (nonatomic, strong) NSString *thumbnailResolution;
@end

@interface TEduBoardTranscodeFileResult : NSObject
//任务ID
@property (nonatomic, strong) NSString *taskId;
//转码状态
@property (nonatomic, assign) TEduBoardFileTranscodeStatus status;
//转码进度（百分比）
@property (nonatomic, assign) NSInteger progress;
//文件标题
@property (nonatomic, strong) NSString *title;
//文件分辨率，如@"1024x768"
@property (nonatomic, strong) NSString *resolution;
//文件总页数
@property (nonatomic, assign) NSInteger pages;
//转码结果URL
@property (nonatomic, strong) NSString *url;
//文件生成缩略图的分辨率，如@"200x200"
@property (nonatomic, strong) NSString *thumbnailResolution;
//文件生成缩略图URL
@property (nonatomic, strong) NSString *thumbnailUrl;
@end

@protocol TEduBoardDelegate <NSObject>
/*************************************************************************************************
 *
 *                                                一、基本流程回调
 *
 *************************************************************************************************/
/**
 * 白板错误回调
 * @param code      错误码，参见TEduBoardErrorCode定义
 * @param msg       错误信息
 */
- (void)onTEBError:(TEduBoardErrorCode)code msg:(NSString *)msg;
/**
 * 白板警告回调
 * @param code      错误码，参见TEduBoardWarningCode定义
 * @param msg       错误信息
 */
- (void)onTEBWarning:(TEduBoardWarningCode)code msg:(NSString *)msg;
/**
 * 白板初始化完成回调，收到该回调后表示白板已处于可正常工作状态
 */
- (void)onTEBInit;
/**
 * 白板历史数据同步完成回调
 */
- (void)onTEBHistroyDataSyncCompleted;
/**
 * 白板同步数据回调
 * @param data      白板同步数据（JSON格式字符串）
 * @brief 收到该回调时需要将回调数据通过信令通道发送给房间内其他人，接受者收到后调用AddSyncData接口将数据添加到白板以实现数据同步,该回调用于多个白板间的数据同步，使用内置IM作为信令通道时，不会收到该回调
 */
- (void)onTEBSyncData:(NSString *)data;
/**
 * 白板可撤销状态改变回调
 * @param canUndo       白板当前是否还能执行Undo操作
 */
- (void)onTEBUndoStatusChanged:(BOOL)canUndo;
/**
 * 白板可重做状态改变回调
 * @param canRedo       白板当前是否还能执行Redo操作
 */
- (void)onTEBRedoStatusChanged:(BOOL)canRedo;


/*************************************************************************************************
 *
 *                                            二、涂鸦相关回调
 *
 *************************************************************************************************/
/**
 * 白板图片状态改变回调
 * @param boardId       白板ID
 * @param url           白板图片URL
 * @param status        新的白板图片状态
 */
- (void)onTEBImageStatusChanged:(NSString *)boardId url:(NSString *)url status:(TEduBoardImageStatus)status;
/**
 * 设置白板背景图片回调
 * @param url           调用setBackgroundImage时传入的url
 * @brief 只有本地调用setBackgroundImage时会收到该回调，收到该回调表示背景图片已经上传或下载成功，并且显示出来
 */
- (void)onTEBSetBackgroundImage:(NSString *)url;
/**
 * 白板图片状态改变回调
 * @param boardId       白板ID
 * @param url           白板图片URL
 * @param status        新的白板图片状态
 */
- (void)onTEBBackgroundH5StatusChanged:(NSString *)boardId url:(NSString *)url status:(TEduBoardBackgroundH5Status)status;
/*************************************************************************************************
 *
 *                                            三、白板页操作回调
 *
 *************************************************************************************************/
/**
 * 增加白板页回调
 * @param boardIds      增加的白板页IDs
 * @param fileId        增加的白板页所属的文件ID
 */
- (void)onTEBAddBoard:(NSArray *)boardIds fileId:(NSString *)fileId;
/**
 * 删除白板页回调
 * @param boardIds       删除的白板页IDs
 * @param fileId        删除的白板页所属的文件ID
 */
- (void)onTEBDeleteBoard:(NSArray *)boardIds fileId:(NSString *)fileId;
/**
 * 跳转白板页回调
 * @param boardId       跳转到的白板页ID
 * @param fileId        跳转到的白板页所属的文件ID
 */
- (void)onTEBGotoBoard:(NSString *)boardId fileId:(NSString *)fileId;
/**
 * 白板页动画步数回调
 * @param currentStep    当前白板页动画步数
 * @param totalStep        当前白板页动画总步数
 */
- (void)onTEBGotoStep:(uint32_t)currentStep totalStep:(uint32_t)totalStep;
/*************************************************************************************************
 *
 *                                            四、文件操作回调
 *
 *************************************************************************************************/

/**
 * 文件转码进度回调
 * @param errorCode         文件转码错误码，无异常时为空字符串 ""
 * @param errorMsg          文件转码错误信息，无异常时为空字符串 ""
 * @param result            文件转码结果
 */
- (void)onTEBFileTranscodeProgress:(TEduBoardTranscodeFileResult *)result path:(NSString *)path errorCode:(NSString *)errorCode errorMsg:(NSString *)errorMsg;


/**
 * 增加转码文件回调
 * @param fileId        增加的文件ID
 * @brief 文件加载完成后才会触发该回调
 */
- (void)onTEBAddTranscodeFile:(NSString *)fileId;
/**
 * 删除文件回调
 * @param fileId        删除的文件ID
 */
- (void)onTEBDeleteFile:(NSString *)fileId;
/**
 * 切换文件回调
 * @param fileId        切换到的文件ID
 */
- (void)onTEBSwitchFile:(NSString *)fileId;
/**
 * 文件上传进度回调
 * @param fileId            文件Id
 * @param currentBytes      当前已上传大小，单位bytes
 * @param totalBytes        文件总大小，单位bytes
 * @param uploadSpeed       文件上传速度，单位bytes
 * @param percent           文件上传百分比，小数形式，如0.5
 */
- (void)onTEBFileUploadProgress:(NSString *)fileId
                currentBytes:(int)currentBytes
                  totalBytes:(int)totalBytes
                 uploadSpeed:(int)uploadSpeed
                    percent:(float)percent;
/**
 * 文件上传状态回调
 * @param fileId            文件Id
 * @param status            文件上传状态
 * @param errorCode         错误码
 * @param errorMsg          错误信息
 */
- (void)onTEBFileUploadStatus:(NSString *)fileId
                   status:(TEduBoardUploadStatus)status
                       errorCode:(int)errorCode
                    errorMsg:(NSString *)errorMsg;

@end
