function TICWebRTC(accountModel, webRTCOptionModel) {
  this.accountModel = accountModel;
  this.webRTCOptionModel = webRTCOptionModel;
  this.RTC = null;
}

TICWebRTC.prototype.getInstance = function () {
  return this.RTC;
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

  this.RTC.on('onKickout', () => {
    this.statusListener.fireEvent('onTICForceOffline');
  });
}

TICWebRTC.prototype.setStatusListener = function (listener) {
  this.statusListener = listener;
}

export default TICWebRTC;