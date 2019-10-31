#ifndef _TIC_LOCAL_RECORD_IMPL_H_
#define _TIC_LOCAL_RECORD_IMPL_H_


#include <string>
#include <stdio.h>
#include <functional>
#include "TICLocalRecord.h"
#include "HttpClient.h"

class TICLocalRecorderImpl : public TICLocalRecorder, public std::enable_shared_from_this<TICLocalRecorderImpl> {
public:
	TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback);
	virtual ~TICLocalRecorderImpl();
	virtual int init(TEduRecordAuthParam authParam, TICCallback callback) override;
	virtual int startLocalRecord(const TEduRecordParam& para, const char * szRecordPath, TICCallback callback) override;
	virtual int stopLocalRecord(TICCallback callback) override;
	virtual int startPush(const TEduRecordParam& para, const char * url, TICCallback callback) override;
	virtual int stopPush(TICCallback callback) override;
	virtual int exit(TICCallback callback) override;

protected:
	void send(const std::string& cmd, const std::string& content, const TICCallback callback);

protected:
	HttpClient http;
	std::weak_ptr<TEduRecordCallback> mCallback;
};

#endif // !_TIC_LOCAL_RECORD_IMPL_H_


