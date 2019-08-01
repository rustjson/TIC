/**
 * 腾讯云白板SDK，Window、Linux平台头文件
 */

#pragma once

#if defined(WIN32) //Windows

#ifdef EDUSDK_EXPORTS
#define EDUSDK_API __declspec(dllexport)
#else
#define EDUSDK_API __declspec(dllimport)
#endif

#include <windows.h>

#undef DeleteFile

#define WINDOW_HANDLE HWND

#else //Unix

#define EDUSDK_API __attribute__ ((visibility("default")))

#if defined(__APPLE__) //macOS

#ifdef __cplusplus
#ifdef __OBJC__
@class NSView;
#else
struct NSView;
#endif
#define WINDOW_HANDLE NSView*
#else
#define WINDOW_HANDLE void*
#endif

#else //Linux

#define WINDOW_HANDLE unsigned long

#endif

#endif

#include <cstdint>

class TEduBoardController;


/*************************************************************************************************
 *
 * SDK导出接口
 *
 *************************************************************************************************/

extern "C" {
    /**
     * 创建白板控制类实例
     * @param disableCefInit                是否禁用CEF框架初始化，通常传默认值即可
     * @return 白板控制类实例指针
     * @warning 该接口必须在主线程调用
     * @info 由于SDK基于CEF框架(BSD-licensed)实现，若您的程序中也使用了CEF框架，可能会存在冲突。
     *       当 disableCefInit == true 时，将禁用掉SDK内部的CEF初始化，这可能有助于避免冲突。
     *       当您自行初始化CEF时，务必将 CefSettings::browser_subprocess_path 字段指向TEduBoardRender程序以保证SDK正常工作。
     */
    EDUSDK_API TEduBoardController *CreateTEduBoardController(bool disableCefInit = false);

    /**
     * 销毁白板控制类
     * @param ppBoardController	指向白板控制类指针
     * @param ppBoardController指针会被自动置空
     */
    EDUSDK_API void DestroyTEduBoardController(TEduBoardController **ppBoardController);

    /**
     * 启用白板离屏渲染
     * @return 启用离屏渲染是否成功
     * @info 启用离屏渲染时，SDK不再创建白板VIEW，而是通过onTEBOffscreenPaint回调接口将白板离屏渲染的像素数据抛出
     * @warning 该接口必须要在第一次调用CreateTEduBoardController之前调用才有效，否则将会失败
     */
    EDUSDK_API bool EnableTEduBoardOffscreenRender();

	/**
	 * 设置白板日志文件路径
	 * @param logFilePath					要设置的白板日志文件路径，包含文件名及文件后缀，UTF8编码，为空或nullptr表示使用默认路径
	 * @return 设置白板日志文件路径是否成功
	 * @warning 该接口必须要在第一次调用CreateTEduBoardController之前调用才有效，否则将会失败
	 * @info 默认路径，Windows下为：%AppData%\Local\TIC\teduboard.log
	 * @info 默认路径，Linux下为：~/TIC/teduboard.log
	 */
	EDUSDK_API bool SetTEduBoardLogFilePath(const char *logFilePath);

	/**
	 * 获取SDK版本号
	 * @return SDK版本号
	 * @info 返回值内存由SDK内部管理，用户不需要自己释放
	 */
	EDUSDK_API const char * GetTEduBoardVersion();
}


/*************************************************************************************************
 *
 * a. 参数枚举值
 *
 *************************************************************************************************/

/**
 * 白板错误码定义（严重）
 */
enum TEduBoardErrorCode {						//事件说明
	TEDU_BOARD_ERROR_INIT				= 1,	//初始化失败
	TEDU_BOARD_ERROR_AUTH				= 2, 	//服务鉴权失败，请先购买服务
    TEDU_BOARD_ERROR_LOAD				= 3,	//文件加载失败
	TEDU_BOARD_ERROR_TIM_INVALID    	= 5,    //腾讯云IMSDK不可用
	TEDU_BOARD_ERROR_HISTORYDATA		= 6,	//同步历史数据失败
	TEDU_BOARD_ERROR_RUNTIME			= 7,	//白板运行错误
};

/**
 * 白板错误码定义（警告）
 */
enum TEduBoardWarningCode {							//事件说明
	TEDU_BOARD_WARNING_SYNC_DATA_PARSE_FAILED       = 1,    //接收到其他端的同步数据解析错误
	TEDU_BOARD_WARNING_TIM_SEND_MSG_FAILED          = 2,    //腾讯云IMSDK发送消息失败
	TEDU_BOARD_WARNING_H5PPT_ALREADY_EXISTS			= 3,    //要添加的H5PPT已存在
	TEDU_BOARD_WARNING_BOARD_LOAD_FAILED			= 4,	//白板资源加载失败，正在内部重试
};

/**
 * 白板工具定义
 */
enum TEduBoardToolType {						//工具名称
    TEDU_BOARD_TOOL_TYPE_MOUSE			= 0,	//鼠标
    TEDU_BOARD_TOOL_TYPE_PEN			= 1,	//画笔
	TEDU_BOARD_TOOL_TYPE_ERASER			= 2,	//橡皮擦
	TEDU_BOARD_TOOL_TYPE_LASER			= 3,	//激光笔
	TEDU_BOARD_TOOL_TYPE_LINE			= 4,	//直线
	TEDU_BOARD_TOOL_TYPE_OVAL			= 5,	//空心椭圆
	TEDU_BOARD_TOOL_TYPE_RECT			= 6,	//空心矩形
	TEDU_BOARD_TOOL_TYPE_OVAL_SOLID		= 7,	//实心椭圆
	TEDU_BOARD_TOOL_TYPE_RECT_SOLID		= 8,	//实心矩形
    TEDU_BOARD_TOOL_TYPE_POINT_SELECT	= 9,	//点选工具
	TEDU_BOARD_TOOL_TYPE_RECT_SELECT    = 10,	//框选工具
	TEDU_BOARD_TOOL_TYPE_TEXT			= 11,	//文本工具
	TEDU_BOARD_TOOL_TYPE_ZOOM_DRAG		= 12,	//缩放移动白板工具
};

/**
 * 白板图片填充对齐模式定义
 * @info 当以宽度基准等比例放大，则居左和居右同居中对齐效果一致；当以高度基准等比例放大，则居顶和居底同居中对齐效果一致
 */
enum TEduBoardImageFitMode {
	TEDU_BOARD_IMAGE_FIT_MODE_CENTER	= 0,	//以宽度或者高度为基准居中对齐等比例放大
	TEDU_BOARD_IMAGE_FIT_MODE_LEFT		= 4,	//以宽度或者高度为基准左对齐等比例放大
	TEDU_BOARD_IMAGE_FIT_MODE_TOP		= 5,	//以宽度或者高度为基准顶对齐等比例放大
	TEDU_BOARD_IMAGE_FIT_MODE_RIGHT		= 6,	//以宽度或者高度为基准右对齐等比例放大
	TEDU_BOARD_IMAGE_FIT_MODE_BOTTOM	= 7,	//以宽度或者高度为基准底对齐等比例放大
};

/**
 * 白板图片状态定义
 */
enum TEduBoardImageStatus {						//状态描述
	TEDU_BOARD_IMAGE_STATUS_LOADING		= 1,	//背景图片正在加载
	TEDU_BOARD_IMAGE_STATUS_LOAD_DONE	= 2,	//背景图片加载完成
	TEDU_BOARD_IMAGE_STATUS_LOAD_ABORT	= 3,	//背景图片加载中断
	TEDU_BOARD_IMAGE_STATUS_LOAD_ERROR	= 4,	//背景图片加载错误
};

/**
 * 白板文本样式
 */
enum TEduBoardTextStyle{
    TEDU_BOARD_TEXT_STYLE_NORMAL		= 0,	//常规样式
    TEDU_BOARD_TEXT_STYLE_BOLD			= 1,	//粗体样式
    TEDU_BOARD_TEXT_STYLE_ITALIC		= 2,	//斜体样式
    TEDU_BOARD_TEXT_STYLE_BOLD_ITALIC	= 3,	//粗斜体样式
};

/**
 * 白板上传状态
 */
enum TEduBoardUploadStatus{
    TEDU_BOARD_UPLOAD_STATUS_SUCCEED	= 1,	//上传成功
    TEDU_BOARD_UPLOAD_STATUS_FAILED		= 2,	//上传失败
};

/**
 * H5背景状态定义
 */
enum TEduBoardBackgroundH5Status{
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOADING        = 1,    //H5背景正在加载
    TEDU_BOARD_BACKGROUND_H5_STATUS_LOAD_FINISH    = 2,    //H5背景加载完成
};

/**
 * 白板内容自适应模式（内容包括图片、文件、PPT动画）
 */
enum TEduBoardContentFitMode {
	TEDU_BOARD_CONTENT_FIT_MODE_NONE = 0,				//不使用内容自适应，默认模式，不自动调整白板宽高比，内容等比例缩放居中显示，内容宽高<=白板宽高
	TEDU_BOARD_CONTENT_FIT_MODE_CENTER_INSIDE = 1,		//自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高<=容器宽高
	TEDU_BOARD_CONTENT_FIT_MODE_CENTER_COVER = 2,		//自动调整白板宽高比与内容一致，内容铺满白板，白板等比例缩放居中显示，白板宽高>=容器宽高
};


/*************************************************************************************************
 *
 * b. 参数结构体
 *
 *************************************************************************************************/

/**
 * 授权参数
 */
struct TEduBoardAuthParam {
	uint32_t sdkAppId;
	const char * userId;
	const char * userSig;

    TEduBoardAuthParam()
            : sdkAppId(0)
            , userId(nullptr)
            , userSig(nullptr)
    {

    }

    TEduBoardAuthParam(uint32_t sdkAppId, const char * userId, const char * userSig)
            : sdkAppId(sdkAppId)
            , userId(userId)
            , userSig(userSig)
    {

    }
};

/**
 * 颜色参数（若语言自带有类似类型定义，可使用语言内置类型）
 */
struct TEduBoardColor {
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint8_t alpha = 0;

    TEduBoardColor()
            : red(0)
            , green(0)
            , blue(0)
            , alpha(0)
    {

    }

    TEduBoardColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            : red(red)
            , green(green)
            , blue(blue)
            , alpha(alpha)
    {

    }
};

/**
 * 白板初始化参数
 */
struct TEduBoardInitParam{
	bool progressEnable;					//是否启用SDK内置Loading图标
    const char * ratio;                     //默认白板宽高比（可传格式如“4:3”、“16:9”的字符串）
    bool drawEnable;                        //是否允许涂鸦
    TEduBoardColor globalBackgroundColor;   //全局背景色
    TEduBoardToolType toolType;			    //白板工具
    TEduBoardColor brushColor;              //画笔颜色
    uint32_t brushThin;						//画笔粗细
    TEduBoardColor textColor;               //文本颜色
    uint32_t textSize;                      //文本粗细
    TEduBoardTextStyle textStyle;           //文本样式
    const char * textFamily;                //文本字体
    bool timSync;                           //是否使用腾讯云IMSDK进行实时数据同步
	bool dataSyncEnable;					//是否启用数据同步，禁用后将导致本地白板操作不会被同步给远端
	uint32_t preloadDepth;					//图片预加载深度，默认值5，表示预加载当前页前后5页的图片
	double smoothLevel;						//笔迹平滑系数，默认0.1，范围 [0，1]
	TEduBoardContentFitMode contentFitMode; //内容自适应模式
	const char * experimental;				//实验性参数集，字典类型JSON串

    TEduBoardInitParam()
            : progressEnable(false)
			, ratio("16:9")
            , drawEnable(true)
            , globalBackgroundColor(255, 255, 255, 255)
            , toolType(TEDU_BOARD_TOOL_TYPE_MOUSE)
            , brushColor(255, 0, 0, 255)
            , brushThin(100)
            , textColor(0, 0, 0, 255)
            , textSize(320)
            , textStyle(TEDU_BOARD_TEXT_STYLE_NORMAL)
            , textFamily("sans-serif,serif,monospace")
            , timSync(true)
			, dataSyncEnable(true)
			, preloadDepth(5)
			, smoothLevel(0.1)
			, contentFitMode(TEDU_BOARD_CONTENT_FIT_MODE_NONE)
			, experimental(nullptr)
    {

    }
};

/**
 * 白板信息
 */
struct TEduBoardInfo {
    const char * boardId;		        //白板ID
    const char * backgroundUrl;		    //白板背景图或者背景H5页面的URL
    TEduBoardColor backgroundColor;     //白板背景色

    TEduBoardInfo()
            : boardId(nullptr)
            , backgroundUrl(nullptr)
    {

    }

    TEduBoardInfo(const char * boardId, const char * backgroundUrl, TEduBoardColor backgroundColor)
            : boardId(boardId)
            , backgroundUrl(backgroundUrl)
            , backgroundColor(backgroundColor)
    {

    }
};

/**
 * 白板信息列表
 */
class TEduBoardInfoList {
protected:
    virtual ~TEduBoardInfoList() {};

public:
    /**
     * @return 白板信息个数
     */
    virtual uint32_t GetCount() const = 0;

    /**
     * @return 白板信息
     */
    virtual TEduBoardInfo GetBoardInfo(uint32_t index) const = 0;
};

/**
 * 文件信息
 */
struct TEduBoardFileInfo {
	const char * fileId;						//文件ID
	const char * title;							//文件名
	const char * downloadUrl; 					//文件下载地址
    uint32_t pageIndex;							//文件当前显示的页数
    uint32_t pageCount;							//文件页数
	const TEduBoardInfoList *boardInfoList;		//白板信息列表

    TEduBoardFileInfo()
            : fileId(nullptr)
            , title(nullptr)
            , downloadUrl(nullptr)
            , pageIndex(0)
            , pageCount(0)
            , boardInfoList(nullptr)
    {

    }

	TEduBoardFileInfo(const char * fileId, const char * title, const char * downloadUrl, uint32_t pageIndex, uint32_t pageCount, TEduBoardInfoList *boardInfoList)
		    : fileId(fileId)
		    , title(title)
		    , downloadUrl(downloadUrl)
		    , pageIndex(pageIndex)
		    , pageCount(pageCount)
		    , boardInfoList(boardInfoList)
	{

	}
};

/**
 * 文件信息列表
 */
class TEduBoardFileInfoList {
protected:
	virtual ~TEduBoardFileInfoList() {};

public:
	/**
	 * @return 文件信息个数
	 */
	virtual uint32_t GetCount() const = 0;

	/**
	 * @return 文件信息
	 */
	virtual TEduBoardFileInfo GetFileInfo(uint32_t index) const = 0;

	/**
	 * 释放文件信息列表
	 * @warning 文件信息列表使用完之后，务必调用该接口以释放内存
	 */
	virtual void Release() = 0;
};

/**
 * 白板ID列表
 */
class TEduBoardList {
protected:
	virtual ~TEduBoardList() {};

public:
	/**
	 * @return 白板个数
	 */
	virtual uint32_t GetCount() const = 0;

	/**
	 * @return 白板ID
	 * @info 返回值内存由SDK内部管理，不需要用户自行释放
	 */
	virtual const char * GetBoard(uint32_t index) const = 0;

	/**
	 * 释放白板ID列表
	 * @warning 白板ID列表使用完之后，务必调用该接口以释放内存
	 */
	virtual void Release() = 0;
};


/*************************************************************************************************
 *
 * c. 事件回调接口
 *
 *************************************************************************************************/
struct TEduBoardCallback {
	/*********************************************************************************************
	 *
	 *										一、基本流程回调
	 *
	 *********************************************************************************************/
	 /**
	  * 白板错误回调
	  * @param code				错误码，参见TEduBoardErrorCode定义
	  * @param msg				错误信息，编码格式为UTF8
	  */
	virtual void onTEBError(TEduBoardErrorCode code, const char *msg) = 0;

	/**
	 * 白板警告回调
	 * @param code				错误码，参见TEduBoardWarningCode定义
	 * @param msg				错误信息，编码格式为UTF8
	 */
	virtual void onTEBWarning(TEduBoardWarningCode code, const char *msg) = 0;

	/**
	 * 白板初始化完成回调，收到该回调后表示白板已处于可正常工作状态（此时白板为空白白板，历史数据尚未拉取到）
	 */
	virtual void onTEBInit() = 0;

	/**
	 * 白板历史数据同步完成回调
	 */
	virtual void onTEBHistroyDataSyncCompleted() {};

	/**
	 * 白板同步数据回调
	 * @param data				白板同步数据（JSON格式字符串）
	 * @info 收到该回调时需要将回调数据通过信令通道发送给房间内其他人，接受者收到后调用AddSyncData接口将数据添加到白板以实现数据同步
	 * @info 该回调用于多个白板间的数据同步，使用腾讯云IMSDK进行实时数据同步时，不会收到该回调
	 */
	virtual void onTEBSyncData(const char *data) {};

	/**
	 * 白板可撤销状态改变回调
	 * @param canUndo			白板当前是否还能执行Undo操作
	 */
	virtual void onTEBUndoStatusChanged(bool canUndo) {};

	/**
	 * 白板可重做状态改变回调
	 * @param canRedo			白板当前是否还能执行Redo操作
	 */
	virtual void onTEBRedoStatusChanged(bool canRedo) {};

	/**
	 * 白板离屏渲染回调
	 * @param buffer            白板像素数据，大小为width * height * 4，像素以白板左上方为原点从左到右从上到下按BGRA排列
	 * @param width             白板像素数据的宽度
	 * @param height            白板像素数据的高度
	 * @info 该回调只有在启用离屏渲染时才会被触发
	 */
	virtual void onTEBOffscreenPaint(const void* buffer, uint32_t width, uint32_t height) {};


	/*********************************************************************************************
	 *
	 *										二、涂鸦相关回调
	 *
	 *********************************************************************************************/
	 /**
	  * 白板图片状态改变回调
	  * @param boardId			白板ID
	  * @param url				白板图片URL
	  * @param status			新的白板图片状态
	  */
	virtual void onTEBImageStatusChanged(const char *boardId, const char *url, TEduBoardImageStatus status) {};

	/**
	 * 设置白板背景图片回调
	 * @param url				调用SetBackgroundImage时传入的URL
	 * @info 只有本地调用SetBackgroundImage时会收到该回调
	 * @info 收到该回调表示背景图片已经上传或下载成功，并且显示出来
	 */
	virtual void onTEBSetBackgroundImage(const char *url) {};

	/**
	 * 设置白板背景H5状态改变回调
	 * @param boardId           白板ID
	 * @param url               白板图片URL
	 * @param status            新的白板图片状态
	 */
	virtual void onTEBBackgroundH5StatusChanged(const char *boardId, const char *url, TEduBoardBackgroundH5Status status) {};


	/*********************************************************************************************
	 *
	 *										三、白板页操作回调
	 *
	 *********************************************************************************************/
	 /**
	  * 增加白板页回调
	  * @param boardList		增加的白板页ID列表（使用后不需要自行调用Release方法释放，SDK内部自动释放）
	  * @param fileId			增加的白板页所属的文件ID（目前版本只可能为#DEFAULT）
	  */
	virtual void onTEBAddBoard(const TEduBoardList *boardList, const char *fileId) {};

	/**
	 * 删除白板页回调
	 * @param boardList			删除的白板页ID（使用后不需要自行调用Release方法释放，SDK内部自动释放）
	 * @param fileId			删除的白板页所属的文件ID（目前版本只可能为#DEFAULT）
	 */
	virtual void onTEBDeleteBoard(const TEduBoardList *boardList, const char *fileId) {};

	/**
	 * 跳转白板页回调
	 * @param boardId			跳转到的白板页ID
	 * @param fileId			跳转到的白板页所属的文件ID
	 */
	virtual void onTEBGotoBoard(const char *boardId, const char *fileId) {};


	/*********************************************************************************************
	 *
	 *										四、文件操作回调
	 *
	 *********************************************************************************************/
	 /**
	  * 增加文件回调
	  * @param fileId			增加的文件ID
	  * @info 文件上传完成后才会触发该回调
	  */
	virtual void onTEBAddFile(const char *fileId) {};

	/**
	 * 增加H5动画PPT文件回调
	 * @param fileId			增加的文件ID
	 * @info 文件加载完成后才会触发该回调
	 */
	virtual void onTEBAddH5PPTFile(const char *fileId) {};

	/**
	 * 删除文件回调
	 * @param fileId			删除的文件ID
	 */
	virtual void onTEBDeleteFile(const char *fileId) {};

	/**
	 * 切换文件回调
	 * @param fileId			切换到的文件ID
	 */
	virtual void onTEBSwitchFile(const char *fileId) {};

	/**
	 * 文件上传进度回调
	 * @param fileId            正在上传的文件ID
	 * @param currentBytes      当前已上传大小，单位bytes
	 * @param totalBytes        文件总大小，单位bytes
	 * @param uploadSpeed       文件上传速度，单位bytes
	 * @param percent			文件上传进度，取值范围 [0, 1]
	 */
	virtual void onTEBFileUploadProgress(const char *fileId, int currentBytes, int totalBytes, int uploadSpeed, double percent) {};

	/**
	 * 文件上传状态回调
	 * @param fileId            正在上传的文件ID
	 * @param status            文件上传状态
	 * @param errorCode			文件上传错误码
	 * @param errorMsg			文件上传错误信息
	 */
	virtual void onTEBFileUploadStatus(const char *fileId, TEduBoardUploadStatus status, int errorCode, const char *errorMsg) {};

};


/*************************************************************************************************
 *
 * d. 白板控制器
 *
 *************************************************************************************************/
class TEduBoardController {
protected:
	/**
	 * 析构函数
	 */
	virtual ~TEduBoardController() {};

public:
    /*********************************************************************************************
     *
     *										一、基本流程接口
     *
     *********************************************************************************************/

	/**
	 * 设置事件回调监听
	 * @param callback 			事件回调监听
	 * @warning 建议在Init之前调用该方法以支持错误处理
	 */
	virtual void AddCallback(TEduBoardCallback * callback) = 0;

	/**
	 * 删除事件回调监听
	 * @param callback 			事件回调监听
	 */
	virtual void RemoveCallback(TEduBoardCallback *callback) = 0;

    /**
     * 初始化白板
     * @param authParam 		授权参数
     * @param roomId 			课堂ID
     * @param initParam	 	 	可选参数，指定用于初始化白板的一系列属性值
     * @info 可用 initParam.timSync 指定是否使用腾讯云IMSDK进行实时数据同步
     * @info initParam.timSync == true 时，会尝试反射调用腾讯云IMSDK作为信令通道进行实时数据收发（只实现消息收发，初始化、进房等操作需要用户自行实现），目前仅支持IMSDK 4.3.118及以上版本
     * @warning 使用腾讯云IMSDK进行实时数据同步时，只支持一个白板实例，创建多个白板实例可能导致涂鸦状态异常
     */
	virtual void Init(const TEduBoardAuthParam & authParam, uint32_t roomId, const TEduBoardInitParam &initParam = TEduBoardInitParam()) = 0;

	/**
	 * 获取白板渲染View
	 * @param callback 			事件回调监听
	 * @warning 建议在Init之前调用该方法以支持错误处理
	 */
	virtual WINDOW_HANDLE GetBoardRenderView() = 0;

	/**
	 * 添加白板同步数据
	 * @param data 				接收到的房间内其他人发送的同步数据
	 * @info 该接口用于多个白板间的数据同步，使用内置IM作为信令通道时，不需要调用该接口
	 */
	virtual void AddSyncData(const char * data) = 0;

	/**
	 * 设置白板是否开启数据同步
	 * @param enable    是否开启
	 * @brief 白板创建后默认开启数据同步，关闭数据同步，本地的所有白板操作不会同步到远端和服务器
	 */
	virtual void SetDataSyncEnable(bool enable) = 0;

	/**
	 * 获取白板是否开启数据同步
	 * @return 是否开启数据同步，true 表示开启，false 表示关闭
	 */
	virtual bool IsDataSyncEnable() = 0;

    /**
     * 重置白板
     * @info 调用该接口后将会删除所有的白板页和文件
     */
    virtual void Reset() = 0;

    /**
     * 设置白板渲染View的位置和大小
     * @param x                 要设置的白板渲染View的位置X分量
     * @param y                 要设置的白板渲染View的位置Y分量
     * @param width             要设置的白板渲染View的宽度
     * @param height            要设置的白板渲染View的高度
     * @info 白板渲染View有父窗口时，(x, y) 指定相对其父窗口的位置
     */
    virtual void SetBoardRenderViewPos(int32_t x, int32_t y, uint32_t width, uint32_t height) = 0;

	/**
	 * 调用白板实验性接口
	 * @param apiExp			要执行的白板相关JS代码
	 * @return JS执行后的返回值转换而来的字符串
	 */
	virtual const char * CallExperimentalAPI(const char * apiExp) = 0;


    /*********************************************************************************************
     *
     *										二、涂鸦相关接口
     *
     *********************************************************************************************/

	 /**
	  * 设置白板是否允许涂鸦
	  * @param enable 			是否允许涂鸦，true 表示白板可以涂鸦，false 表示白板不能涂鸦
	  * @info 白板创建后默认为允许涂鸦状态
	  */
	virtual void SetDrawEnable(bool enable) = 0;

    /**
     * 获取白板是否允许涂鸦
     * @return 是否允许涂鸦，true 表示白板可以涂鸦，false 表示白板不能涂鸦
     */
    virtual bool IsDrawEnable() = 0;

    /**
     * 设置所有白板的背景色
     * @param color 			要设置的全局背景色
     * @info 调用该接口将导致所有白板的背景色发生改变
     * @info 新创建白板的默认背景色取全局背景色
     */
	virtual void SetGlobalBackgroundColor(const TEduBoardColor &color) = 0;

    /**
	 * 获取白板全局背景色
	 * @return 全局背景色
	 */
    virtual TEduBoardColor GetGlobalBackgroundColor() = 0;

	/**
	 * 设置当前白板页的背景色
	 * @param color 			要设置的背景色
	 * @info 白板页创建以后的默认背景色由SetDefaultBackgroundColor接口设定
	 */
	virtual void SetBackgroundColor(const TEduBoardColor & color) = 0;

    /**
     * 获取当前白板页的背景色
     * @return 当前白板页的背景色
     */
    virtual TEduBoardColor GetBackgroundColor() = 0;

	/**
	 * 设置要使用的白板工具
	 * @param type 				要设置的白板工具
	 */
	virtual void SetToolType(TEduBoardToolType type) = 0;

    /**
     * 获取正在使用的白板工具
     * @return 正在使用的白板工具
     */
    virtual TEduBoardToolType GetToolType() = 0;

	/**
	 * 设置画笔颜色
	 * @param color 			要设置的画笔颜色
	 * @info 画笔颜色用于所有涂鸦绘制
	 */
	virtual void SetBrushColor(const TEduBoardColor & color) = 0;

    /**
     * 获取画笔颜色
     * @return 画笔颜色
     */
    virtual TEduBoardColor GetBrushColor() = 0;

	/**
	 * 设置画笔粗细
	 * @param thin 				要设置的画笔粗细
	 * @info 画笔粗细用于所有涂鸦绘制，实际像素值取值(thin * 白板的高度 / 10000)px，如果结果小于1px，则涂鸦的线条会比较虚
	 */
	virtual void SetBrushThin(uint32_t thin) = 0;

    /**
     * 获取画笔粗细
     * @return 画笔粗细
     */
    virtual uint32_t GetBrushThin() = 0;

	/**
	 * 设置文本颜色
	 * @param color 			要设置的文本颜色
	 */
	virtual void SetTextColor(const TEduBoardColor & color) = 0;

    /**
     * 获取文本颜色
     * @return 文本颜色
     */
    virtual TEduBoardColor GetTextColor() = 0;

	/**
	 * 设置文本大小
	 * @param thin 				要设置的文本大小
	 * @info 实际像素值取值(size * 白板的高度 / 10000)px
	 */
	virtual void SetTextSize(uint32_t size) = 0;

    /**
     * 获取文本大小
     * @return 文本大小
     */
    virtual uint32_t GetTextSize() = 0;

    /**
     * 设置文本样式
     * @param style 				要设置的文本样式
     */
    virtual void SetTextStyle(TEduBoardTextStyle style) = 0;

    /**
     * 获取文本样式
     * @return 文本样式
     */
    virtual TEduBoardTextStyle GetTextStyle() = 0;

    /**
     * 设置文本字体
     * @param family 				要设置的文本字体
     */
    virtual void SetTextFamily(const char * family) = 0;

    /**
     * 获取文本字体
     * @return 文本字体
     */
    virtual const char * GetTextFamily() = 0;

	/**
	 * 清空当前白板页涂鸦
	 * @param clearBackground 	是否同时清空背景色以及背景图片
	 */
	virtual void Clear(bool clearBackground = false) = 0;

    /**
     * 设置当前白板页的背景图片
     * @param url 				要设置的背景图片URL，编码格式为UTF8
     * @param mode				要使用的图片填充对齐模式
     * @info 当URL是一个有效的本地文件地址时，该文件会被自动上传到COS
     */
    virtual void SetBackgroundImage(const char * url, TEduBoardImageFitMode mode) = 0;

    /**
	 * 设置当前白板页的背景H5页面
	 * @param url				要设置的背景H5页面URL
	 * @info 该接口与SetBackgroundImage接口互斥
     * @warning 目前版本该功能暂未实现
	 */
    virtual void SetBackgroundH5(const char * url) = 0;

	/**
	 * 撤销当前白板页上一次动作
	 */
	virtual void Undo() = 0;

	/**
	 * 重做当前白板页上一次撤销
	 */
	virtual void Redo() = 0;


    /*********************************************************************************************
     *
     *										三、白板页操作接口
     *
     *********************************************************************************************/
	 /**
	  * 增加一页白板
	  * @param url				要使用的背景图片URL，编码格式为UTF8，为nullptr表示不指定背景图片
	  * @return 白板ID
	  * @info 返回值内存由SDK内部管理，用户不需要自己释放
	  * @warning 白板页会被添加到默认文件（文件ID为#DEFAULT)，自行上传的文件无法添加白板页
	  */
	virtual const char * AddBoard(const char * url = nullptr) = 0;

	/**
	 * 删除一页白板
	 * @param boardId			要删除的白板ID，为nullptr表示删除当前页
	 * @warning 只允许删除默认文件（文件ID为#DEFAULT）内的白板页，且默认白板页（白板ID为#DEFAULT）无法删除
	 */
	virtual void DeleteBoard(const char * boardId = nullptr) = 0;

    /**
     * 上一步
     * @info 每个Step对应PPT的一个动画效果，若当前没有已展示的动画效果，则该接口调用会导致向前翻页
     */
    virtual void PrevStep() = 0;

    /**
     * 下一步
     * @info 每个Step对应PPT的一个动画效果，若当前没有未展示的动画效果，则该接口调用会导致向后翻页
     */
    virtual void NextStep() = 0;

	/**
	 * 向前翻页
	 * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
	 * @info 若当前白板页为当前文件的第一页，则该接口调用无效
	 */
	virtual void PrevBoard(bool resetStep = false) = 0;

	/**
	 * 向后翻页
	 * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
	 * @info 若当前白板页为当前文件的最后一页，则该接口调用无效
	 */
	virtual void NextBoard(bool resetStep = false) = 0;

	/**
	 * 跳转到指定白板页
	 * @param boardId			要跳转到的白板页ID
	 * @param resetStep			指定翻到指定页以后是否重置PPT动画步数
	 * @info 允许跳转到任意文件的白板页
	 */
	virtual void GotoBoard(const char * boardId, bool resetStep = false) = 0;

	/**
	 * 获取当前白板页ID
	 * @return 当前白板页ID
	 * @info 返回值内存由SDK内部管理，用户不需要自己释放
	 */
	virtual const char * GetCurrentBoard() = 0;

	/**
	 * 获取所有文件的白板列表
	 * @return 所有文件的白板列表
	 * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
	 */
	virtual TEduBoardList *GetBoardList() = 0;

	/**
	 * 设置当前白板页宽高比
	 * @param ratio				要设置的白板宽高比
	 * @info 格式如: "4:3"、"16:9"
	 */
    virtual void SetBoardRatio(const char *ratio) = 0;

	/**
	 * 获取当前白板页宽高比
	 * @return 白板宽高比，格式与SetBoardRatio接口参数格式一致
	 */
	virtual const char * GetBoardRatio() = 0;

	/**
	 * 设置当前白板页缩放比例
	 * @param scale				要设置的白板缩放比例
	 * @info 支持范围: [100，300]，实际缩放比为: scale/100
	 */
	virtual void SetBoardScale(uint32_t scale) = 0;

	/**
	 * 获取当前白板页缩放比例
	 * @return 白板缩放比例，格式与SetBoardScale接口参数格式一致
	 */
	virtual uint32_t GetBoardScale() = 0;

	/**
	 * 设置白板内容自适应模式
	 * @param mode				要设置的白板内容自适应模式
	 * @info 设置自适应模式后会影响所有后续白板内容操作,受影响接口包括：AddFile、AddH5PPTFile
	 */
	virtual void SetBoardContentFitMode(TEduBoardContentFitMode mode) = 0;

	/**
	 * 获取白板内容自适应模式
	 * @return 白板内容自适应模式
	 */
	virtual TEduBoardContentFitMode GetBoardContentFitMode() = 0;


    /*********************************************************************************************
     *
     *										四、文件操作接口
     *
     *********************************************************************************************/
	 /**
	  * 增加文件
	  * @param path				要增加的文件路径，编码格式为UTF8
	  * @return 文件ID
	  * @info 支持 PPT、PDF、Word、Excel
	  * @info 当path指向一个有效的本地文件时，SDK会先将文件上传到COS后再执行后续操作，此时会触发文件上传相关回调
	  * @info 若path不是一个有效的本地文件路径，则会被当做URL处理，URL必须指向腾讯云COS文件路径，否则接口调用无效
	  * @info 文件添加完成后，将自动切换到该文件
	  * @warning 在收到对应的onTEBAddFile回调前，无法用返回的文件ID查询到文件信息
	  */
	virtual const char * AddFile(const char * path) = 0;

    /**
     * 增加H5动画PPT文件
     * @param url				要增加的H5动画PPT的URL
	 * @return 文件ID
     * @info 调用该接口后，SDK会在后台进行H5加载，期间用户可正常进行其它操作，加载成功或失败后会触发相应回调
     * @info H5加载成功后，将自动切换到该文件
     * @warning 当传入的URL重复时，文件ID返回为空字符串
	 * @warning 在收到对应的onTEBAddH5PPTFile回调前，无法用返回的文件ID查询到文件信息
     */
    virtual const char * AddH5PPTFile(const char * url) = 0;

	/**
	 * 删除文件
	 * @param fileId			要删除的文件ID
	 * @info 文件ID为nullptr时表示当前文件，默认文件无法删除
	 */
	virtual void DeleteFile(const char * fileId) = 0;

	/**
	 * 切换文件
	 * @param fileId			要切换到的文件ID
	 * @info 文件ID为必填项，为nullptr或空字符串将导致文件切换失败
	 */
	virtual void SwitchFile(const char * fileId) = 0;

    /**
     * 获取当前文件ID
     * @return 当前文件ID
     */
    virtual const char * GetCurrentFile() = 0;

	/**
	 * 获取白板中指定文件的文件信息
	 * @return 文件信息
	 * @warning 每次调用该接口的返回值内容都指向同一块内存，若需要保存返回信息，请在拿到返回值后及时拷贝走
	 */
	virtual TEduBoardFileInfo GetFileInfo(const char *fileId) = 0;

	/**
	 * 获取白板中上传的所有文件的文件信息列表
	 * @return 文件信息列表
	 * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
	 */
	virtual TEduBoardFileInfoList * GetFileInfoList() = 0;

	/**
	 * 获取指定文件的白板ID列表
	 * @param fileId			文件ID
	 * @return 白板ID列表
	 * @warning 返回值不再使用时不需要自行delete，但是务必调用其release方法以释放内存占用
	 */
	virtual TEduBoardList * GetFileBoardList(const char * fileId) = 0;

	/**
	 * 清空指定文件的所有白板涂鸦
	 * @param fileId			文件ID
	 */
	virtual void ClearFileDraws(const char * fileId) = 0;
};
