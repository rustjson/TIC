import IMHandler from './ImHandler';
import LogReport from '../log/LogReport'
import Constant from '../constant/Constant';

function TICWebIM() {
  this.accountModel = null;
  this.classModel = null;
  this.imListener = null;
  this.boardNotifyCallback = null;
  this.imHandler = null;
}

TICWebIM.prototype.setLog = function (log) {
  this.log = log;
}

TICWebIM.prototype.login = function (accountModel, classModel) {
  this.accountModel = accountModel;
  this.classModel = classModel;
  this.listeners = this.initEvent();
  return new Promise((resolve, reject) => {
    webim.login({
      'sdkAppID': accountModel.sdkAppId + '', //用户所属应用id,必填
      'appIDAt3rd': accountModel.sdkAppId + '', //用户所属应用id，必填
      'accountType': accountModel.accountType || 1, //用户所属应用帐号类型，必填
      'identifier': accountModel.userId, //当前用户ID,必须是否字符串类型，选填
      'identifierNick': accountModel.userNick || accountModel.userId, //当前用户昵称，选填
      'userSig': accountModel.userSig
    }, this.listeners, {
      isAccessFormalEnv: true,
      isLogOn: false
    }, (res) => {
      this.imHandler = new IMHandler(accountModel, classModel);
      resolve(res);
    }, reject);
  });
}

TICWebIM.prototype.logout = function () {
  return new Promise((resolve, reject) => {
    webim.logout(resolve, reject);
  });
}

TICWebIM.prototype.initEvent = function () {
  var self = this;
  return {
    // 用于监听用户连接状态变化的函数，选填
    onConnNotify(resp) {},

    // 监听新消息(直播聊天室)事件，直播场景下必填
    onBigGroupMsgNotify(msgs) {
      self.messageHandler(msgs);
    },

    // 监听新消息函数，必填
    onMsgNotify(msgs) {
      self.messageHandler(msgs);
    },


    // 监听（多终端同步）群系统消息事件，必填
    onGroupSystemNotifys: {
      // //申请加群请求（只有管理员会收到）
      // "1": (notify) => {
      // },

      // //申请加群被同意（只有申请人能够收到）
      // "2": (notify) => {
      // },

      // //申请加群被拒绝（只有申请人能够收到）
      // "3": (notify) => {
      // },

      //被管理员踢出群(只有被踢者接收到)
      "4": (notify) => {
        self.eventListener.fireEvent('onTICMemberQuit', [self.accountModel.userId]);
      },

      //群被解散(全员接收)
      "5": (notify) => {
        self.eventListener.fireEvent('onTICClassroomDestroy');
      },

      // //创建群(创建者接收)
      // "6": (notify) => {
      // },

      // //邀请加群(被邀请者接收)
      // "7": (notify) => {
      // },

      // //主动退群(主动退出者接收)
      // "8": (notify) => {

      // },

      // //设置管理员(被设置者接收)
      // "9": (notify) => {
      // },

      // //取消管理员(被取消者接收)
      // "10": (notify) => {
      // },

      // //群已被回收(全员接收)
      "11": (notify) => {
        self.eventListener.fireEvent('onTICClassroomDestroy');
      },

      // //用户自定义通知(默认全员接收)
      // "255": (notify) => {
      // }
    },

    // 监听群资料变化事件，选填
    onGroupInfoChangeNotify(groupInfo) {},

    // 被踢下线的回调
    onKickedEventCall() {
      // 被强制下线
      self.log.report(LogReport.EVENT_NAME.ONFORCEOFFLINE, {
        errorCode: 0,
        errorDesc: '',
        timeCost: 0,
        data: '',
        ext: 'im onKickedEventCall'
      });

      self.statusListener.fireEvent('onTICForceOffline');
    },

    // 监听 C2C 消息通道的处理
    onC2cEventNotifys: {
      // 多终端互踢
      "96": (notify) => {
        // 被强制下线
        self.log.report(LogReport.EVENT_NAME.ONFORCEOFFLINE, {
          errorCode: 0,
          errorDesc: '',
          timeCost: 0,
          data: '',
          ext: 'im onC2cEventNotifys-96'
        });
        self.statusListener.fireEvent('onTICForceOffline');
      }
    }
  }
}

TICWebIM.prototype.messageHandler = function (msgs) {
  let self = this;
  if (msgs.length) { // 如果有消息才处理
    msgs.forEach(msg => {
      var sess = msg.getSession();
      var msgType = sess.type();
      // 如果是群组消息
      if (msgType === webim.SESSION_TYPE.GROUP) {
        var groupid = sess.id();
        // 如果是信令群（如果不与saas同步，则同时也是聊天群）
        if (groupid == self.accountModel.classId) {
          var elems = msg.elems;
          if (elems.length) {
            // 白板消息
            if (elems[0].type === 'TIMCustomElem' && elems[0].content.ext === 'TXWhiteBoardExt') {
              if (msg.getFromAccount() != self.accountModel.userId) {
                self.boardNotifyCallback && self.boardNotifyCallback(msg)
              }
            } else if (elems[0].type === 'TIMFileElem' && elems[0].content.ext === 'TXWhiteBoardExt') { // 白板消息
              if (msg.getFromAccount() != self.accountModel.userId) {
                self.boardNotifyCallback && self.boardNotifyCallback(msg)
              }
            } else if (elems[0].type === 'TIMCustomElem' && elems[0].content.ext === 'TXConferenceExt') { // 对时消息过滤掉
            } else {
              self.resolveMessage(msg);
            }
          }
        } else if (groupid == self.accountModel.classChatId) { // 如果是聊天群
          self.resolveMessage(msg);
        } else {
          // 非本群通知，忽略
        }
      } else { // 如果是C2C消息
        self.resolveMessage(msg);
      }
    });
  }
}


TICWebIM.prototype.resolveMessage = function (msg) {
  var elems = msg.elems;
  this.messageListener.fireEvent('onTICRecvMessage', msg);
  elems.forEach(elem => {
    var content = elem.getContent();
    if (msg.getFromAccount() === '@TIM#SYSTEM') { // 接收到系统消息
      var opType = content.getOpType(); // 通知类型
      if (opType === webim.GROUP_TIP_TYPE.JOIN) { // 加群通知
        this.eventListener.fireEvent('onTICMemberJoin', elem.getContent().userIdList);
      } else if (opType === webim.GROUP_TIP_TYPE.QUIT) { // 退群通知
        this.eventListener.fireEvent('onTICMemberQuit', [elem.getContent().opUserId]);
      }
    } else { // 接收到群聊天/C2C消息
      var type = elem.getType();
      if (type === 'TIMTextElem') {
        var text = '';
        if (msg.getSession().type() === webim.SESSION_TYPE.GROUP) {
          text = elem.getContent().getText() || '';
          this.messageListener.fireEvent('onTICRecvGroupTextMessage', msg.getFromAccount(), text, text.length);
        } else {
          text = elem.getContent().getText() || '';
          this.messageListener.fireEvent('onTICRecvTextMessage', msg.getFromAccount(), text, text.length);
        }
      } else if (type === 'TIMCustomElem') {
        var data = '';
        if (msg.getSession().type() === webim.SESSION_TYPE.GROUP) {
          data = elem.getContent().getData() || '';
          this.messageListener.fireEvent('onTICRecvGroupCustomMessage', msg.getFromAccount(), data, data.length);
        } else {
          data = elem.getContent().getData() || '';
          this.messageListener.fireEvent('onTICRecvCustomMessage', msg.getFromAccount(), data, data.length);
        }
      }
    }
  });
}

/**
 * @classId 群组id
 * @scene 场景
 */
TICWebIM.prototype.createRoom = function (classId, scene) {
  classId = classId + '';
  scene = scene * 1;
  let groupType = scene === Constant.TICClassScene.TIC_CLASS_SCENE_VIDEO_CALL ? 'Public' : 'AVChatRoom';
  var options = {
    'GroupId': classId,
    'Owner_Account': String(this.accountModel.userId),
    'Type': groupType,
    'ApplyJoinOption': 'FreeAccess',
    'Name': classId,
    'Notification': "",
    'Introduction': "",
    'MemberList': [],
  };

  return new Promise((resolve, reject) => {
    webim.createGroup(
      options,
      function (resp) {
        resolve(resp);
      },
      function (err) {
        if (err.ErrorCode == 10025) {
          resolve(err);
        } else if (err.ErrorCode == 10021) {
          reject(err);
        } else {
          reject(err);
        }
      }
    );
  });
}

/**
 * 加入白板信令群
 */
TICWebIM.prototype.joinRoom = function () {
  // 先创建群，成功后加入群
  return new Promise((resolve, reject) => {
    var groupID = String(this.accountModel.classId);
    webim.applyJoinBigGroup({
        GroupId: groupID
      },
      (resp) => {
        //JoinedSuccess:加入成功; WaitAdminApproval:等待管理员审批
        if (resp.JoinedStatus && resp.JoinedStatus == 'JoinedSuccess') {
          this.imHandler.setIMBoardSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          // 如果不与saas互通
          if (!this.classModel.compatSaas) {
            this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          }
          resolve(resp);
        } else {
          reject(resp);
        }
      },

      (err) => {
        if (err.ErrorCode == 10013) { // 被邀请加入的用户已经是群成员,也表示成功
          this.imHandler.setIMBoardSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          // 如果不与saas互通
          if (!this.classModel.compatSaas) {
            this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          }
          resolve(err);
        } else if (err.ErrorCode == -12) { // Join Group succeed; But the type of group is not AVChatRoom
          this.imHandler.setIMBoardSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          // 如果不与saas互通
          if (!this.classModel.compatSaas) {
            this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          }
          resolve(err);
        } else {
          reject(err);
        }
      }
    );
  });
}

/**
 * 加入Saas聊天群
 */
TICWebIM.prototype.joinSaasChatRoom = function () {
  // 先创建群，成功后加入群
  return new Promise((resolve, reject) => {
    var groupID = String(this.accountModel.classChatId);
    webim.applyJoinBigGroup({
        GroupId: groupID
      },
      (resp) => {
        //JoinedSuccess:加入成功; WaitAdminApproval:等待管理员审批
        if (resp.JoinedStatus && resp.JoinedStatus == 'JoinedSuccess') {
          this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          resolve(resp);
        } else {
          reject(resp);
        }
      },

      (err) => {
        if (err.ErrorCode == 10013) { // 被邀请加入的用户已经是群成员,也表示成功
          this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          resolve(err);
        } else if (err.ErrorCode == -12) { // Join Group succeed; But the type of group is not AVChatRoom
          this.imHandler.setIMChatSession(new webim.Session(webim.SESSION_TYPE.GROUP, groupID, groupID));
          resolve(err);
        } else {
          reject(err);
        }
      }
    );
  });
}

/**
 * 销毁群组
 */
TICWebIM.prototype.destroyGroup = function (groupID) {
  return new Promise((resolve, reject) => {
    webim.destroyGroup({
        GroupId: groupID + ''
      },
      function (resp) {
        resolve(resp);
      },
      function (err) {
        reject(err);
      }
    );
  });
}

/**
 * 退出群组
 */
TICWebIM.prototype.quitGroup = function () {
  var groupID = String(this.accountModel.classId);
  return new Promise((resolve, reject) => {
    webim.quitBigGroup({
        GroupId: groupID
      },
      function (resp) {
        resolve(resp);
      },
      (err) => {
        // 群主想退群,则也认为成功
        if (err.ErrorCode == 10009) {
          resolve();
          return;
        }
        reject(err);
      }
    );
  });
}

/**
 * 退出chat群组
 */
TICWebIM.prototype.quitChatGroup = function () {
  var groupID = String(this.accountModel.classChatId);
  return new Promise((resolve, reject) => {
    webim.quitBigGroup({
        GroupId: groupID
      },
      function (resp) {
        resolve(resp);
      },
      (err) => {
        // 群主想退群,则也认为成功
        if (err.ErrorCode == 10009) {
          resolve();
          return;
        }
        reject(err);
      }
    );
  });
}

TICWebIM.prototype.setReceiveBoardNotifyCallback = function (callback) {
  this.boardNotifyCallback = callback;
}

/**
 * 发送C2C文本消息
 */
TICWebIM.prototype.sendC2CTextMessage = function (userId, msg, succ, fail) {
  this.imHandler.sendTextMessage(webim.SESSION_TYPE.C2C, msg, userId, succ, fail);
}

/**
 * 发送C2C自定义消息
 */
TICWebIM.prototype.sendC2CCustomMessage = function (userId, msg, succ, fail) {
  this.imHandler.sendCustomMsg(webim.SESSION_TYPE.C2C, msg, userId, succ, fail);
}

/**
 * 发送群文本消息
 */
TICWebIM.prototype.sendGroupTextMessage = function (msg, succ, fail) {
  this.imHandler.sendTextMessage(webim.SESSION_TYPE.GROUP, msg, null, succ, fail);
}

/**
 * 发送群组自定义消息
 */
TICWebIM.prototype.sendGroupCustomMessage = function (msg, succ, fail) {
  this.imHandler.sendCustomMsg(webim.SESSION_TYPE.GROUP, msg, null, succ, fail);
}

// 发送白板数据
TICWebIM.prototype.sendBoardGroupCustomMessage = function (msg) {
  this.imHandler.sendBoardGroupCustomMessage(JSON.stringify(msg));
}

TICWebIM.prototype.setMessageListener = function (messageListener) {
  this.messageListener = messageListener;
}

TICWebIM.prototype.setEventListener = function (eventListener) {
  this.eventListener = eventListener;
}

TICWebIM.prototype.setStatusListener = function (statusListener) {
  this.statusListener = statusListener;
}

export default TICWebIM;