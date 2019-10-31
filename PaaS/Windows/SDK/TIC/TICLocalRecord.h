#ifndef _TIC_LOCAL_RECORD_H_
#define _TIC_LOCAL_RECORD_H_

#include <stdio.h>
#include <string>
#include <functional>
#include "TICManager.h"


enum TEduRecordReslution {
	// 普屏 4:3
	TEDU_VIDEO_RESOLUTION_320x240 = 1,
	TEDU_VIDEO_RESOLUTION_480x360 = 2,
	TEDU_VIDEO_RESOLUTION_640x480 = 3,
	TEDU_VIDEO_RESOLUTION_960x720 = 4,
	TEDU_VIDEO_RESOLUTION_1280x960 = 5,

	// 宽屏16:9
	TEDU_VIDEO_RESOLUTION_320x180 = 101,
	TEDU_VIDEO_RESOLUTION_480x272 = 102,
	TEDU_VIDEO_RESOLUTION_640x360 = 103,
	TEDU_VIDEO_RESOLUTION_960x540 = 104,
	TEDU_VIDEO_RESOLUTION_1280x720 = 105,
	TEDU_VIDEO_RESOLUTION_1920x1080 = 106,
};

/**
 *  授权参数
 */
struct TEduRecordAuthParam {
	TEduRecordAuthParam(int appId, std::string userId, std::string userSig) {
		this->appId = appId;
		this->userId = userId;
		this->userSig = userSig;
	}

	int appId;
	std::string userId;
	std::string userSig;
};

/**
 *  视频参数
 */
struct TEduRecordParam {
	//【字段含义】 视频分辨率
	//【推荐取值】 - 视频通话建议选择360 × 640及以下分辨率，resMode 选择 Portrait。
	//           - 手机直播建议选择 540 × 960，resMode 选择 Portrait。
	//           - Window 和 iMac 建议选择 640 × 360 及以上分辨率，resMode 选择 Landscape。
	//【特别说明】 您在 TRTCVideoResolution 只能找到横屏模式的分辨率，例如：640 × 360 这样的分辨率。
	//             如果想要使用竖屏分辨率，请指定 resMode 为 Portrait，例如：640 × 360 + Portrait = 360 × 640。
	int videoResolution = TEDU_VIDEO_RESOLUTION_1280x720; //1280x720

	//【字段含义】视频采集帧率
	//【推荐取值】15fps 或 20fps，10fps 以下会有轻微卡顿感，5fps 以下卡顿感明显，20fps 以上的帧率则过于浪费（电影的帧率也只有 24fps）。
	int videoFps = 10;

	//【字段含义】视频发送码率
	int videoBps = 1000; //1000kpbs

	//【字段含义】视频录制窗口x位置
	int x = 0;

	//【字段含义】视频录制窗口Y
	int y = 0;

	//【字段含义】视频录制窗口宽度，0表示整个窗口宽度
	int width = 0;

	//【字段含义】视频录制窗口高度, 0表示整个窗口高度
	int Height = 0;

	//被录制进程名称
	std::string AppProc;  //如QQMusic.exe

	//被录制窗口wndId
	int Wnd = 0;

	//是否录制音频
	bool enableAudio = true;
};

/**
 * 录制事件回调接口
 */
class TEduRecordCallback {
public:
	virtual void onGotStatus(int state, const char* msg) = 0;
};

class TICLocalRecorder {
public:
	virtual ~TICLocalRecorder() {};

public:


	/**
	 * 获取TICLocalRecord单例对象
	 */
	static TICLocalRecorder* GetInstance();

	/**
	* 初始化
	 * @param authParam 		授权参数
	*/
	virtual int init(TEduRecordAuthParam authParam, TICCallback callback) = 0;

	/**
	* 视频本地录制, 支持不推流录制。
	* @param szRecordPath:视频录制后存储路径，目前传 flv和mp4 后缀文件。
	* @return
	*          0 成功；
	*          -1 路径非法
	*          -2 上次录制未结束，请先stopRecord
	*/
	virtual int startLocalRecord(const TEduRecordParam& para, const char * szRecordPath, TICCallback callback) = 0;

	/**
	* 结束录制短视频，停止推流后，如果视频还在录制中，SDK内部会自动结束录制
	* @return
	*       0 成功；
	*      -1 不存在录制任务；
	*/
	virtual int stopLocalRecord(TICCallback callback) = 0;

	/**
	* 启动推流 (在否则推送出去的数据流里只有音频)
	* @param url - 一个合法的推流地址，腾讯云的推流 URL 都要求带有 txSecret 和 txTime 防盗链签名，如果您发现推流推不上去，请检查这两个签名是否合法。
	* @return：成功 or 失败，内存分配、资源申请失败等原因可能会导致返回失败
	*/
	virtual int startPush(const TEduRecordParam& para, const char * url, TICCallback callback) = 0;

	/**
	* 停止推流，注意推流 url 有排他性，也就是一个推流 Url 同时只能有一个推流端向上推流
	*/
	virtual int stopPush(TICCallback callback) = 0;


	/**
	* 停止所有录制和推流并退出进程
	*/
	virtual int exit(TICCallback callback) = 0;

};



#endif //_TIC_LOCAL_RECORD_H_
