import Constant from './constant/Constant';
import WebIM from './webim/WebIM';
import WebBoard from './webboard/webBoard';
import WebRTC from './webrtc/WebRTC';
import MessageListener from './event/MessageListener';
import EventListener from './event/EventListener';
import StatusListener from './event/StatusListener';
import AccountModel from './model/AccountModel';
import BoardOptionModel from './model/BoardOptionModel';
import WebRTCOptionModel from './model/WebRTCOptionModel';
import Config from './config/Config'
import LogReport from './log/LogReport'

function TIC() {
  this.accountModel = new AccountModel();
  this.boardOptionModel = new BoardOptionModel();
  this.webRTCOptionModel = new WebRTCOptionModel();

  this.messageListener = new MessageListener();
  this.eventListener = new EventListener();
  this.statusListener = new StatusListener();

  this.ticVersion = Config.version;
  console.log('tic version:', this.ticVersion);
  this.log = new LogReport();
  this.log.setSdkVersion(Config.version);
}

/** @constant {string} */
TIC.CONSTANT = Constant;

TIC.prototype = {

  /**
   * 初始化;
   * @param sdkAppId			在腾讯云申请的sdkAppId
   * @param callback			回调
   * @return 错误码, 0表示成功
   */
  init(sdkAppId, callback) {
    this.log.setSdkAppId(sdkAppId);
    let startTime = Date.now();

    // 初始化开始
    this.log.report(LogReport.EVENT_NAME.INITSDK_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: '',
      ext: '',
    });

    if (sdkAppId) {
      this.accountModel.sdkAppId = sdkAppId;
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      });

      // 初始化完成
      this.log.report(LogReport.EVENT_NAME.INITSDK_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

    } else {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: -7,
        desc: 'sdkAppId is illegal'
      });
      // 初始化
      this.log.report(LogReport.EVENT_NAME.INITSDK_END, {
        errorCode: -7,
        errorDesc: 'sdkAppId is illegal',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });
    }
  },

  // 保留接口
  uninit() {

  },

  /**
   * 登录
   * @param loginConfig		userid, usersig鉴权信息
   * @param callback			回调
   */
  login(loginConfig, callback) {
    let startTime = Date.now();

    this.accountModel.userId = loginConfig.userId;
    this.accountModel.userSig = loginConfig.userSig;
    this.ticWebIm = new WebIM();
    this.ticWebIm.setLog(this.log);
    
    this.log.setUserId(loginConfig.userId);

    // 登录-start
    this.log.report(LogReport.EVENT_NAME.LOGIN_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: '',
      ext: '',
    });

    this.ticWebIm.login(this.accountModel).then((res) => {

      this.ticWebIm.setMessageListener(this.messageListener);
      this.ticWebIm.setEventListener(this.eventListener);
      this.ticWebIm.setStatusListener(this.statusListener);

      this.addTICStatusListener({
        // 监听被踢下线
        onTICForceOffline: () => {
          this.ticWebRTC && this.ticWebRTC.quit();
          this.ticBoard && this.ticBoard.quit();
          this.removeTICEventListener();
          this.removeTICMessageListener();
          this.removeTICStatusListener();
        }
      });

      // 登录- end
      this.log.report(LogReport.EVENT_NAME.LOGIN_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }, error => {

      // 登录- end
      this.log.report(LogReport.EVENT_NAME.LOGIN_END, {
        errorCode: error.ErrorCode,
        errorDesc: error.ErrorInfo,
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      });
    });
  },

  /**
   * 登出
   * @param callback			回调
   */
  logout(callback) {
    let startTime = Date.now();

    // 登出-start
    this.log.report(LogReport.EVENT_NAME.LOGOUT_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: '',
      ext: '',
    });

    this.ticWebIm.logout().then((res) => {
      // 登出-end
      this.log.report(LogReport.EVENT_NAME.LOGOUT_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }).catch((error) => {

      // 登出-end
      this.log.report(LogReport.EVENT_NAME.LOGOUT_END, {
        errorCode: error.ErrorCode,
        errorDesc: error.ErrorInfo,
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      });
    });
  },

  /**
   * 创建课堂
   * @param classId			课堂ID，由业务生成和维护
   * @param callback			回调
   */
  createClassroom(classId, callback) {
    let startTime = Date.now();

    // 创建课堂-start
    this.log.report(LogReport.EVENT_NAME.CREATEGROUP_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: classId + '',
      ext: '',
    });

    // WebIM加入聊天房间
    this.ticWebIm.createRoom(classId).then(res => {
      // 创建课堂-end
      this.log.report(LogReport.EVENT_NAME.CREATEGROUP_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: classId + '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      });
    }, error => {
      // 创建课堂-end
      this.log.report(LogReport.EVENT_NAME.CREATEGROUP_END, {
        errorCode: error.ErrorCode,
        errorDesc: error.ErrorInfo,
        timeCost: Date.now() - startTime,
        data: classId + '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      });
    });
  },

  /**
   * 加入课堂
   * @param classId		课堂ID
   * @param webRTCOption		WebRTC相关参数
   * @param boardOption	白板相关参数
   * @param callback			回调
   */
  joinClassroom(classId, webRTCOption, boardOption, callback) {
    this.log.setRoomId(classId);

    let startTime = Date.now();

    // 加入课堂-start
    this.log.report(LogReport.EVENT_NAME.JOINGROUP_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: JSON.stringify(webRTCOption || {}),
      ext: JSON.stringify(boardOption || {}),
    });

    this.accountModel.classId = classId;
    this.webRTCOptionModel.setData(webRTCOption);

    this.ticWebIm.joinRoom().then(res => {

      // 加入课堂-end
      this.log.report(LogReport.EVENT_NAME.JOINGROUP_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      this.ticWebIm.setReceiveBoardNotifyCallback(msg => {
        if (this.ticBoard && this.ticBoard.getInstance()) {
          var elems = msg.elems;
          elems.forEach(elem => {
            if (elem.type === 'TIMCustomElem' && elem.content.ext === 'TXWhiteBoardExt') {
              this.ticBoard.getInstance().addSyncData(JSON.parse(elem.content.data));
            }
          });
        }
      });

      // 加入AV房间-start
      this.log.report(LogReport.EVENT_NAME.ENTERROOM_START, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      this.ticWebRTC = new WebRTC(this.accountModel, this.webRTCOptionModel);
      this.ticWebRTC.setLog(this.log);

      this.ticWebRTC.joinAvRoom(() => {
        // 加入AV房间-end
        this.log.report(LogReport.EVENT_NAME.ENTERROOM_END, {
          errorCode: 0,
          errorDesc: '',
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        this.ticWebRTC.setStatusListener(this.statusListener);

        // 白板初始化
        this.log.report(LogReport.EVENT_NAME.INITBOARD_START, {
          errorCode: 0,
          errorDesc: '',
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        this.boardOptionModel.setData(boardOption);
        this.ticBoard = new WebBoard(this.accountModel, this.boardOptionModel);
        this.ticBoard.setLog(this.log);
        this.ticBoard.render();

        // 白板初始化
        this.log.report(LogReport.EVENT_NAME.INITBOARD_END, {
          errorCode: 0,
          errorDesc: '',
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        // 设置白板的监听回调
        this.ticBoard.addSyncDataEventCallback((data) => {
          this.ticWebIm.sendBoardGroupCustomMessage(data);
        });

        callback && callback({
          module: Constant.TICModule.TICMODULE_IMSDK,
          code: 0
        });
      }, (error) => {
        // 加入AV房间-end
        this.log.report(LogReport.EVENT_NAME.ENTERROOM_END, {
          errorCode: error.errorCode,
          errorDesc: JSON.stringify(error),
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        callback && callback({
          module: Constant.TICModule.TICMODULE_TRTC,
          code: error.errorCode,
          desc: JSON.stringify(error)
        });
      });
    }, error => {

      // 加入课堂-end
      this.log.report(LogReport.EVENT_NAME.JOINGROUP_END, {
        errorCode: error.ErrorCode,
        errorDesc: error.ErrorInfo,
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      });
    });
  },

  /**
   * 退出课堂
   * @param callback			回调
   */
  quitClassroom(callback) {
    let startTime = Date.now();

    // 退出课堂-start
    this.log.report(LogReport.EVENT_NAME.QUITGROUP_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: '',
      ext: '',
    });

    this.ticWebIm.quitGroup().then(() => {
      this.ticWebRTC.quit();
      this.ticBoard.quit();

      this.removeTICEventListener();
      this.removeTICMessageListener();
      this.removeTICStatusListener();


      // 退出课堂-end
      this.log.report(LogReport.EVENT_NAME.QUITGROUP_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: '',
        ext: '',
      });

      // 退出成功
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      });
    }).catch((error) => {
      // 群不存在 或者 不在群里了 或者 群id不合法（一般这种情况是课堂销毁了groupId被重置后发生）(都认为成功)
      if (error.ErrorCode === 10010 || error.ErrorCode === 10007 || error.ErrorCode === 10015) {
        this.ticWebRTC.quit();
        this.ticBoard.quit();

        this.removeTICEventListener();
        this.removeTICMessageListener();
        this.removeTICStatusListener();

        // 退出课堂-end
        this.log.report(LogReport.EVENT_NAME.QUITGROUP_END, {
          errorCode: 0,
          errorDesc: '',
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        // 退出成功
        callback && callback({
          module: Constant.TICModule.TICMODULE_IMSDK,
          code: 0
        });
      } else {

        // 退出课堂-end
        this.log.report(LogReport.EVENT_NAME.QUITGROUP_END, {
          errorCode: error.ErrorCode,
          errorDesc: error.ErrorInfo,
          timeCost: Date.now() - startTime,
          data: '',
          ext: '',
        });

        // 退出失败
        callback && callback({
          module: Constant.TICModule.TICMODULE_IMSDK,
          code: error.ErrorCode,
          desc: error.ErrorInfo
        });
      }
    });
  },

  /**
   * 销毁课堂
   * @param classId			课堂ID，由业务生成和维护
   * @param callback			回调
   */
  destroyClassroom(classId, callback) {
    let startTime = Date.now();

    // 销毁课堂-start
    this.log.report(LogReport.EVENT_NAME.DELETEGROUP_START, {
      errorCode: 0,
      errorDesc: '',
      timeCost: Date.now() - startTime,
      data: classId + '',
      ext: '',
    });

    this.ticWebIm.destroyGroup(classId).then(data => {
      this.ticWebRTC.quit();
      this.ticBoard.clearAll();
      this.ticBoard.quit();

      this.removeTICEventListener();
      this.removeTICMessageListener();
      this.removeTICStatusListener();

      // 销毁课堂-start
      this.log.report(LogReport.EVENT_NAME.DELETEGROUP_END, {
        errorCode: 0,
        errorDesc: '',
        timeCost: Date.now() - startTime,
        data: classId + '',
        ext: '',
      });

      // 销毁成功
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      });
    }).catch(error => {
      // 销毁课堂-end
      this.log.report(LogReport.EVENT_NAME.DELETEGROUP_END, {
        errorCode: error.ErrorCode,
        errorDesc: error.ErrorInfo,
        timeCost: Date.now() - startTime,
        data: classId + '',
        ext: '',
      });

      // 销毁失败
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      });
    });
  },

  /**
   * 发送C2C文本消息
   * @param userId			消息接收者
   * @param text				文本消息内容
   * @param callback			回调
   */
  sendTextMessage(userId, text, callback) {
    this.ticWebIm.sendC2CTextMessage(userId, text, () => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }, error => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      })
    });
  },

  /**
   * 发送C2C自定义消息
   * @param userId			消息接收者
   * @param data				自定义消息内容
   * @param callback			回调
   */
  sendCustomMessage(userId, data, callback) {
    this.ticWebIm.sendC2CCustomMessage(userId, data, () => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }, error => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      })
    });
  },

  /**
   * 发送群文本消息
   * @param text				文本消息内容
   * @param callback			回调
   */
  sendGroupTextMessage(text, callback) {
    this.ticWebIm.sendGroupTextMessage(text, () => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }, error => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      })
    });
  },


  /**
   * 发送群自定义消息
   * @param data				自定义消息内容
   * @param callback			回调
   */
  sendGroupCustomMessage(text, callback) {
    this.ticWebIm.sendGroupCustomMessage(text, () => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: 0
      })
    }, error => {
      callback && callback({
        module: Constant.TICModule.TICMODULE_IMSDK,
        code: error.ErrorCode,
        desc: error.ErrorInfo
      })
    });
  },

  /**
   * @desc 获取白板实例
   * @return {Board} board 返回白板实例
   */
  getBoardInstance() {
    return this.ticBoard.getInstance();
  },

  /**
   * @desc 获取IM实例, 初始化TICKSDK后即可获得IM实例
   * @return {webim} im 返回IM实例
   */
  getImInstance() {
    return webim;
  },


  /**
   * @desc 获取WebRTC实例
   * @return {WebRTC} cos 返回WebRTC实例
   */
  getWebRTCInstance() {
    return this.ticWebRTC.getInstance();
  },

  /**
   * 添加IM消息监听回调
   * @param listener			回调
   */
  addTICMessageListener(listener) {
    this.messageListener.addTICMessageListener(listener);
  },

  /**
   * 移除IM消息监听回调
   * @param listener			回调
   */
  removeTICMessageListener(listener) {
    this.messageListener.removeTICMessageListener(listener);
  },

  /**
   * 添加事件监听回调
   * @param listener			回调
   */
  addTICEventListener(listener) {
    this.eventListener.addTICEventListener(listener);
  },

  /**
   * 移除事件监听回调
   * @param listener			回调
   */
  removeTICEventListener(listener) {
    this.eventListener.removeTICEventListener(listener);
  },

  /**
   * 添加IM状态监听回调
   * @param listener			回调
   */
  addTICStatusListener(listener) {
    this.statusListener.addTICStatusListener(listener);
  },

  /**
   * 移除IM状态监听回调
   * @param listener			回调
   */
  removeTICStatusListener(listener) {
    this.statusListener.removeTICStatusListener(listener);
  }
};

export default TIC