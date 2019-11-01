
#include<windows.h>
#include<stdio.h>
#include "TICLocalRecordImpl.h"
#include "jsoncpp/json.h"

const std::string RecordExe = "TXCloudRecord.exe";
const std::string URL = "http://127.0.0.1:37604/localrecord/v1/";

TICLocalRecorderImpl::TICLocalRecorderImpl() {

}

TICLocalRecorderImpl::TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback) : mCallback(callback){

}

TICLocalRecorderImpl::~TICLocalRecorderImpl() {

}


int TICLocalRecorderImpl::startService() {
	BOOL ret = FALSE;

	//ShellExecute(NULL, TEXT("open"), TEXT("C:\\Program Files\\Internet Explorer\\iexplore.exe"), NULL, NULL, SW_SHOWNORMAL);

	std::string cmd = "";


	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0;
	std::string path = szFilePath;
	path.append("\\..\\..\\SDK\\LocalRecord\\");
	path.append(RecordExe);
	//path.append("../");

	SHELLEXECUTEINFOA sei = { 0 };
	sei.cbSize = sizeof(SHELLEXECUTEINFOA);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.hwnd = NULL;
	sei.lpVerb = "open";
	sei.lpFile = path.c_str();
	sei.lpParameters = cmd.c_str();
	sei.lpDirectory = NULL;
	sei.nShow = SW_HIDE;
	sei.hInstApp = NULL;
	sei.lpIDList = NULL;
	sei.lpClass = NULL;
	sei.hkeyClass = NULL;
	sei.dwHotKey = NULL;
	sei.hIcon = NULL;
	sei.hProcess = NULL;

	ret = ::ShellExecuteExA(&sei);

	return ret;
}


int TICLocalRecorderImpl::init(TEduRecordAuthParam authParam, TICCallback callback) {

	startService();


	Json::Value value;
	value["SdkAppId"] = authParam.appId;
	value["UserId"] = authParam.userId;
	value["UserSig"] = authParam.userSig;


	Json::FastWriter writer;
	std::string msg = writer.write(value);

	send("Init", msg, callback);
	return 0;
}


int TICLocalRecorderImpl::startLocalRecord(const TEduRecordParam& para, const char * szRecordPath, TICCallback callback) {

	if (szRecordPath != NULL && strlen(szRecordPath) > 0) {
		Json::Value value;
		value["AppProc"] = para.AppProc;
		value["Wnd"] = para.Wnd;
		value["x"] = para.x;
		value["y"] = para.y;
		value["Width"] = para.width;
		value["Height"] = para.Height;
		value["VideoResolution"] = para.videoResolution;
		value["VideoFps"] = para.videoFps;
		value["VideoBps"] = para.videoBps;
		value["EnableAudio"] = para.enableAudio;
		value["DstPath"] = szRecordPath;

		Json::FastWriter writer;
		std::string msg = writer.write(value);

		send("StartRecord", msg, callback);
		return 0;
	}

	return -1;

}

int TICLocalRecorderImpl::stopLocalRecord(TICCallback callback) {
	send("StopRecord", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::startPush(const TEduRecordParam& para, const char * url, TICCallback callback) {
	if (url != NULL && strlen(url) > 0) {
		Json::Value value;
		value["AppProc"] = para.AppProc;
		value["Wnd"] = para.Wnd;
		value["x"] = para.x;
		value["y"] = para.y;
		value["Width"] = para.width;
		value["Height"] = para.Height;
		value["VideoResolution"] = para.videoResolution;
		value["VideoFps"] = para.videoFps;
		value["VideoBps"] = para.videoBps;
		value["EnableAudio"] = para.enableAudio;
		value["DstURL"] = url;

		
		Json::FastWriter writer;
		std::string msg = writer.write(value);

		send("StartPush", msg, callback);
		return 0;
	}
	return -1;
}

int TICLocalRecorderImpl::stopPush(TICCallback callback) {
	send("StopPush", std::string(), callback);
	return 0;
}

int TICLocalRecorderImpl::exit(TICCallback callback) {
	send("Exit", std::string(), callback);
	return 0;
}


void TICLocalRecorderImpl::send(const std::string& cmd, const std::string& reqBody, const TICCallback callback) {
	if (!cmd.empty()) {
		//std::weak_ptr<TICLocalRecorderImpl> weakThis = this->shared_from_this();
		http.asynPost(HttpClient::a2w(URL + cmd), reqBody, [=](int code, const HttpHeaders& rspHeaders, const std::string& rspBody) {
			//auto _this = weakThis.lock();
			//if (!_this) return;

			int result = code;
			std::string desc = rspBody;
			if (callback) {
				callback(TICMODULE_RECORD, result, desc.c_str());
			}
		});
	}
	
}

