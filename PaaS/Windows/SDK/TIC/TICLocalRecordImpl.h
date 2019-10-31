#ifndef _TIC_LOCAL_RECORD_IMPL_H_
#define _TIC_LOCAL_RECORD_IMPL_H_


#include <string>
#include <stdio.h>
#include <functional>
#include "TICLocalRecord.h"
#include "HttpClient.h"

class TICLocalRecorderImpl : public TICLocalRecorder {
public:
	TICLocalRecorderImpl(std::weak_ptr<TEduRecordCallback>  callback);
	virtual ~TICLocalRecorderImpl();
	virtual int init(TEduRecordAuthParam authParam) override;
	virtual int startLocalRecord(const TEduRecordParam& para, const char * szRecordPath) override;
	virtual int stopLocalRecord() override;
	virtual int startPush(const TEduRecordParam& para, const char * url) override;
	virtual int stopPush() override;
	virtual int exit() override;

protected:
	void send(const std::string& cmd, const std::string& content);

protected:
	HttpClient http;
	std::weak_ptr<TEduRecordCallback> mCallback;
};

#endif // !_TIC_LOCAL_RECORD_IMPL_H_


