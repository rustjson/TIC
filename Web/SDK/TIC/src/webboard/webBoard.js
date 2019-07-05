function WebBoard(accountModel, boardOptionModel) {
  this.board = null;
  this.accountModel = accountModel;
  this.boardOptionModel = boardOptionModel;
}

WebBoard.prototype.getInstance = function () {
  return this.board;
}

WebBoard.prototype.render = function () {
  this.board = null;
  this.board = new TEduBoard(Object.assign({}, this.boardOptionModel, {
    classId: this.accountModel.classId,
    sdkAppId: this.accountModel.sdkAppId,
    userId: this.accountModel.userId + '',
    userSig: this.accountModel.userSig
  }));
}

WebBoard.prototype.addSyncDataEventCallback = function (callback) {
  this.board.on(TEduBoard.EVENT.TEB_SYNCDATA, data => {
    callback && callback(data);
  });
}

WebBoard.prototype.quit = function () {
  if (this.board) {
    this.board && this.board.off();
    this.board = null;
  }
}

// 清空课堂数据
WebBoard.prototype.clearAll = function () {
  if (this.board) {
    this.board && this.board.reset();
  }
}

export default WebBoard;