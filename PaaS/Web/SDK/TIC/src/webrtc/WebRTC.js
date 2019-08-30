import LogReport from '../log/LogReport'

function TICWebRTC(accountModel, webRTCOptionModel) {
  this.accountModel = accountModel;
  this.webRTCOptionModel = webRTCOptionModel;
  this.RTC = null;
}

TICWebRTC.prototype.getInstance = function () {
  return this.RTC;
}

TICWebRTC.prototype.setLog = function (log) {
  return this.log = log;
}

TICWebRTC.prototype.quit = function (succ, fail) {
  if (this.RTC) {
    this.RTC.quit(succ, fail);
    this.RTC.unlisten();
    this.RTC = null;
  }
}

TICWebRTC.prototype.joinAvRoom = function (succ = function () {}, fail = function () {}) {
  this.RTC = new WebRTCAPI({
    "userId": this.accountModel.userId,
    "userSig": this.accountModel.userSig,
    "sdkAppId": this.accountModel.sdkAppId,
    "peerAddNotify": this.webRTCOptionModel.peerAddNotify,
    "debug": this.webRTCOptionModel.debug
  });

  this.RTC.enterRoom({
    roomid: this.accountModel.classId * 1,
    privateMapKey: this.webRTCOptionModel.privateMapKey,
    role: this.webRTCOptionModel.role, //画面设定的配置集名 （见控制台 - 画面设定 )
    pureAudioPushMod: this.webRTCOptionModel.pureAudioPushMod, // 纯音频推流模式，需要旁路直播和录制时需要带上此参数 1 => 本次是纯音频推流,不需要录制mp3文件 2 => 本次是纯音频推流,录制文件为mp3
    recordId: this.webRTCOptionModel.recordId
  }, succ, fail);



  this.RTC.on('onLocalStreamAdd', (data) => {
    // 本地视频流
    this.log.report('onLocalStreamAdd', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onRemoteStreamUpdate', (data) => {
    // 本地视频流
    this.log.report('onRemoteStreamUpdate', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onRemoteStreamRemove', (data) => {
    // 本地视频流
    this.log.report('onRemoteStreamRemove', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onWebSocketClose', (data) => {
    // 本地视频流
    this.log.report('onWebSocketClose', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onRelayTimeout', (data) => {
    // 本地视频流
    this.log.report('onRelayTimeout', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onKickout', (data) => {
    // 本地视频流
    this.log.report('onKickout', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });

    // 本地视频流
    this.log.report(LogReport.EVENT_NAME.ONFORCEOFFLINE, {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: JSON.stringify(data),
      ext: 'webrtc'
    });

    this.statusListener.fireEvent('onTICForceOffline');
  });

  this.RTC.on('onMuteAudio', (data) => {
    // 本地视频流
    this.log.report('onMuteAudio', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onUnmuteAudio', (data) => {
    // 本地视频流
    this.log.report('onUnmuteAudio', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onMuteVideo', (data) => {
    // 本地视频流
    this.log.report('onMuteVideo', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onUnmuteVideo', (data) => {
    // 本地视频流
    this.log.report('onUnmuteVideo', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });



  this.RTC.on('onStreamNotify', (data) => {
    // 本地视频流
    this.log.report('onStreamNotify', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onErrorNotify', (data) => {
    // 本地视频流
    this.log.report('onErrorNotify', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onWebSocketNotify', (data) => {
    // 本地视频流
    this.log.report('onWebSocketNotify', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });

  this.RTC.on('onWebsocketNotify', (data) => {
    // 本地视频流
    this.log.report('onWebsocketNotify', {
      errorCode: 0,
      errorDesc: '',
      timeCost: 0,
      data: '',
      ext: JSON.stringify(data),
    });
  });
}

TICWebRTC.prototype.setStatusListener = function (listener) {
  this.statusListener = listener;
}

export default TICWebRTC;