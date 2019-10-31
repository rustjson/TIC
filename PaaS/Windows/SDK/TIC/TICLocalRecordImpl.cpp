#include "TICLocalRecordImpl.h"
#include "jsoncpp/json.h"

const std::string URL = "http://127.0.0.1:37604/localrecord/v1/";

TICLocalRecorderImpl::TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback) : mCallback(callback){

}

TICLocalRecorderImpl::~TICLocalRecorderImpl() {

}


int TICLocalRecorderImpl::init(TEduRecordAuthParam authParam) {

	Json::Value value;
	value["AppProc"] = authParam.appId;
	value["UserId"] = authParam.userId;
	value["UserSig"] = authParam.userSig;


	Json::FastWriter writer;
	std::string msg = writer.write(value);

	send("Init", msg);
	return 0;
}


int TICLocalRecorderImpl::startLocalRecord(const TEduRecordParam& para, const char * szRecordPath) {

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

		send("StartRecord", msg);
		return 0;
	}

	return -1;

}

int TICLocalRecorderImpl::stopLocalRecord() {
	send("StopRecord", std::string());
	return 0;
}

int TICLocalRecorderImpl::startPush(const TEduRecordParam& para, const char * url) {
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

		send("StartPush", msg);
		return 0;
	}
	return -1;
}

int TICLocalRecorderImpl::stopPush() {
	send("StopPush", std::string());
	return 0;
}

int TICLocalRecorderImpl::exit() {
	send("Exit", std::string());
	return 0;
}


void TICLocalRecorderImpl::send(const std::string& cmd, const std::string& reqBody) {
	if (!cmd.empty) {
		http.asynPost(HttpClient::a2w(URL + cmd), reqBody, [](int code, const HttpHeaders& rspHeaders, const std::string& rspBody) {
			
		});
	}
	
}

