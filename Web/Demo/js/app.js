Vue.use(Toasted);
window.app = new Vue({
  el: '#app_box',
  data() {
    return {
      step: 'first',
      pushModel: purl().param('auto') * 1 || 0, // 1  自动推流 0 手动推流
      account: purl().param('userid') || localStorage.getItem('IIC_USERID') || TEST_ACCOUNT.users[0]['userId'],
      userID: sessionStorage.getItem('IIC_USERNAME'),
      sdkAppId: TEST_ACCOUNT.sdkappid,
      userSig: '',
      nickName: sessionStorage.getItem('IIC_NICKNAME'),
      roomInfo: '',
      roomID: purl().param('roomid') * 1 || null,
      isTeacher: purl().param('isteacher') * 1 || 0,
      enableCamera: true,
      enableMic: true,
      users: TEST_ACCOUNT.users,
      msgs: [],
      isPushing: 0, // 是否正在推流
      isPushCamera: 0, // 是否推摄像头流
      devices: {
        camera: [],
        mic: []
      },

      cameraIndex: 0,
      micIndex: 0,

      imMsg: {
        common: {},
        custom: {}
      },

      boardData: {
        data: {
          current: null,
          list: []
        },
        page: {
          current: 0,
          total: 0
        }
      },

      remoteVideos: {},
      boardFileGroup: [], // 白板文件组
      currentFile: null, // 当前文件
    }
  },

  mounted() {

  },

  methods: {
    // 创建或者进入课堂
    start() {
      if (!this.roomID) {
        this.showErrorTip('房间号不能为空');
        return;
      }
      this.step = 'second';
      this.init();
    },

    // 初始化业务数据
    initData() {
      this.msgs = [];
      this.isPushing = 0; // 是否正在推流
      this.isPushCamera = 0; // 是否推摄像头流

      this.devices = {
        camera: [],
        mic: []
      };

      this.cameraIndex = 0;
      this.micIndex = 0;

      this.imMsg = {
        common: {
          data: '',
          toUser: ''
        },
        custom: {
          data: '',
          toUser: ''
        }
      };

      localStorage.setItem('IIC_USERID', this.account);

      this.enableCamera = true;
      this.enableMic = true;
      this.remoteVideos = {};
      this.boardFileGroup = []; // 白板文件组
      this.currentFile = null; // 当前文件
    },

    // 初始化SDK
    init() {
      this.initData();
      this.tic = null;
      this.tic = new TIC({});
      this.tic.init(this.sdkAppId, res => {
        if (res.code) {
          this.showErrorTip('初始化失败，code:' + res.code + ' msg:' + res.desc);
        } else {
          this.login();
        }
      });
    },

    // 登录
    login() {
      this.tic.login({
        userId: this.account,
        userSig: this.findUserSig(this.account)
      }, (res) => {
        if (res.code) {
          this.showErrorTip('登录失败');
          console.error(res);
        } else {
          this.showTip('登录成功');

          // 增加事件监听
          this.addTICMessageListener();
          this.addTICEventListener();
          this.addTICStatusListener();

          if (this.isTeacher) {
            // 老师就创建课堂
            this.createClassroom();
          } else { // 如果是学生
            // 有了课堂后就直接加入
            this.joinClassroom();
          }
        }
      });
    },

    // 创建房间
    createClassroom() {
      this.tic.createClassroom(this.roomID, (res) => {
        if (res.code) {
          this.showErrorTip('创建课堂失败');
          console.error(res);
          this.step = 'first';
        } else {
          this.showTip('创建课堂成功');
          // 如果是老师
          if (this.isTeacher) {
            this.joinClassroom()
          }
        }
      });
    },

    // 进入房间
    joinClassroom() {
      this.roomID && this.tic.joinClassroom(this.roomID, {}, {
        id: 'paint_box',
        boardContentFitMode: 2
      }, res => {
        if (res.code) {
          this.showErrorTip('加入课堂失败');
          console.error(res);
          this.step = 'first';
        } else {
          this.showTip('加入课堂成功');
          window.teduBoard = this.teduBoard = this.tic.getBoardInstance();
          this.initBoardEvent();

          window.TRTC = this.TRTC = this.tic.getWebRTCInstance();
          this.initTRTCEvent();

          // 如果是主动推流
          if (this.pushModel === 1) {
            this.startRTC();
          }
        }
      });
    },

    // 监听白板事件（按需监听）
    initBoardEvent() {
      var teduBoard = this.teduBoard;
      // 撤销状态改变
      teduBoard.on(TEduBoard.EVENT.TEB_OPERATE_CANUNDO_STATUS_CHANGED, (enable) => {
        console.log('======================:  ', 'TEB_OPERATE_CANUNDO_STATUS_CHANGED', enable ? '可撤销' : '不可撤销');
      });

      // 重做状态改变
      teduBoard.on(TEduBoard.EVENT.TEB_OPERATE_CANREDO_STATUS_CHANGED, (enable) => {
        console.log('======================:  ', 'TEB_OPERATE_CANREDO_STATUS_CHANGED', enable ? '可恢复' : '不可恢复');
      });

      // 新增白板
      teduBoard.on(TEduBoard.EVENT.TEB_ADDBOARD, (boardId, fid) => {
        console.log('======================:  ', 'TEB_ADDBOARD', ' boardId:', boardId, ' fid:', fid);
        this.proBoardData();
      });

      // 白板同步数据回调(收到该回调时需要将回调数据通过信令通道发送给房间内其他人，接受者收到后调用AddSyncData接口将数据添加到白板以实现数据同步)
      // TIC已经处理好了，可忽略该事件
      teduBoard.on(TEduBoard.EVENT.TEB_SYNCDATA, (data) => {
        console.log('======================:  ', 'TEB_SYNCDATA');
      });

      // 收到白板初始化完成事件后，表示白板已处于正常工作状态（此时白板为空白白板，历史数据尚未拉取完成）
      teduBoard.on(TEduBoard.EVENT.TEB_INIT, () => {
        console.log('======================:  ', 'TEB_INIT');
      });

      teduBoard.on(TEduBoard.EVENT.TEB_HISTROYDATA_SYNCCOMPLETED, () => {
        console.log('======================:  ', 'TEB_HISTROYDATA_SYNCCOMPLETED');
      });

      // 白板错误回调
      teduBoard.on(TEduBoard.EVENT.TEB_ERROR, (code, msg) => {
        console.log('======================:  ', 'TEB_ERROR', ' code:', code, ' msg:', msg);
      });

      // 白板警告回调
      teduBoard.on(TEduBoard.EVENT.TEB_WARNING, (code, msg) => {
        console.log('======================:  ', 'TEB_WARNING', ' code:', code, ' msg:', msg);
      });

      // 图片状态加载回调
      teduBoard.on(TEduBoard.EVENT.TEB_IMAGE_STATUS_CHANGED, (status, data) => {
        console.log('======================:  ', 'TEB_IMAGE_STATUS_CHANGED', ' status:', status, ' data:', data);
      });

      // 删除白板页回调
      teduBoard.on(TEduBoard.EVENT.TEB_DELETEBOARD, (boardId, fid) => {
        console.log('======================:  ', 'TEB_DELETEBOARD', ' boardId:', boardId, ' fid:', fid);
        this.proBoardData();
      });

      // 跳转白板页回调
      teduBoard.on(TEduBoard.EVENT.TEB_GOTOBOARD, (boardId, fid) => {
        console.log('======================:  ', 'TEB_GOTOBOARD', ' boardId:', boardId, ' fid:', fid);
        this.proBoardData();
      });

      // 增加H5动画PPT文件回调
      teduBoard.on(TEduBoard.EVENT.TEB_ADDH5PPTFILE, (fid) => {
        console.log('======================:  ', 'TEB_ADDH5PPTFILE', ' fid:', fid);
        this.proBoardData();
      });

      // 增加文件回调
      teduBoard.on(TEduBoard.EVENT.TEB_ADDFILE, (fid) => {
        console.log('======================:  ', 'TEB_ADDFILE', ' fid:', fid);
        this.proBoardData();
      });

      // 删除文件回调
      teduBoard.on(TEduBoard.EVENT.TEB_DELETEFILE, (fid) => {
        console.log('======================:  ', 'TEB_DELETEFILE', ' fid:', fid);
        this.proBoardData();
      });

      // 文件上传状态
      teduBoard.on(TEduBoard.EVENT.TEB_FILEUPLOADSTATUS, (status, data) => {
        console.log('======================:  ', 'TEB_FILEUPLOADSTATUS', status, data);
        if (status === 1) {
          this.showTip('上传成功');
        } else {
          this.showTip('上传失败');
        }
        document.getElementById('file_input').value = '';
      });

      // 切换文件回调
      teduBoard.on(TEduBoard.EVENT.TEB_SWITCHFILE, (fid) => {
        console.log('======================:  ', 'TEB_SWITCHFILE', ' fid:', fid);
        this.proBoardData();
      });

      // 上传背景图片的回调
      teduBoard.on(TEduBoard.EVENT.TEB_SETBACKGROUNDIMAGE, (fileName, fileUrl, userData) => {
        console.log('======================:  ', 'TEB_SETBACKGROUNDIMAGE', '  fileName:', fileName, '  fileUrl:', fileUrl, ' userData:', userData);
      });

      // 文件上传进度
      teduBoard.on(TEduBoard.EVENT.TEB_FILEUPLOADPROGRESS, (data) => {
        console.log('======================:  ', 'TEB_FILEUPLOADPROGRESS:: ', data);
        this.showTip('上传进度:' + parseInt(data.percent * 100) + '%');
      });

      // H5背景加载状态
      teduBoard.on(TEduBoard.EVENT.TEB_H5BACKGROUND_STATUS_CHANGED, (status, data) => {
        console.log('======================:  ', 'TEB_H5BACKGROUND_STATUS_CHANGED:: status:', status, '  data:', data);
      });
    },

    // TRTC事件
    initTRTCEvent() {
      this.TRTC.on('onLocalStreamAdd', (data) => {
        if (data && data.stream) {
          var localVideoEl = document.getElementById('local_video');
          if (!localVideoEl) {
            localVideoEl = document.createElement('video');
            localVideoEl.id = 'local_video';
            localVideoEl.class = "col-md-1";
            document.querySelector("#video_wrap").insertBefore(localVideoEl, null);
          }
          localVideoEl.muted = true;
          localVideoEl.autoplay = true;
          localVideoEl.playsinline = true
          localVideoEl.srcObject = data.stream;
          this.isPushing = 1; // 正在推流
          this.showTip('WebRTC接收到本地流');
        }
      })

      this.TRTC.on('onRemoteStreamUpdate', (data) => {
        var userVideoEl = document.getElementById(data.videoId);
        if (!userVideoEl) {
          userVideoEl = document.createElement('video');
          userVideoEl.id = data.videoId;
          userVideoEl.class = "col-md-1";
          document.querySelector("#video_wrap").appendChild(userVideoEl);
        }
        userVideoEl.autoplay = true;
        userVideoEl.playsinline = true
        userVideoEl.srcObject = data.stream;

        this.showTip('WebRTC接收到远端流');
      })

      this.TRTC.on('onRemoteStreamRemove', (data) => {
        var userVideoEl = document.getElementById(data.videoId);
        if (userVideoEl) {
          userVideoEl.remove();
        }
        this.showTip('WebRTC 远端流断开');
      })

      this.TRTC.on('onWebSocketClose', (data) => {
        this.showTip('WebRTC WebSocket 断开');
      })

      this.TRTC.on('onRelayTimeout', (data) => {
        this.showTip('WebRTC 超时');
      })

      this.TRTC.on('onStreamNotify', (data) => {
        console.log('==================== onStreamNotify==', data);
      })
    },

    /**
     * 退出课堂
     */
    quitClassroom() {
      this.tic.quitClassroom(res => {
        if (res.code) {
          this.showErrorTip('退出课堂失败');
          console.error(res);
        } else {
          this.step = 'first';
          this.showTip('退出课堂成功');
        }
      });
    },

    /**
     * 销毁课堂
     */
    destroyClassroom() {
      this.tic.destroyClassroom(this.roomID, res => {
        if (res.code) {
          this.showErrorTip('销毁课堂失败');
          console.error(res);
        } else {
          this.step = 'first';
          this.showTip('销毁课堂成功');
        }
      });
    },

    /**
     * 增加IM消息监听回调
     */
    addTICMessageListener() {
      this.tic.addTICMessageListener({

        /**
         * 收到C2C文本消息
         * @param fromUserId		发送此消息的用户id
         * @param text				收到消息的内容
         * @param textLen			收到消息的长度
         */
        onTICRecvTextMessage: (fromUserId, text, textLen) => {
          this.msgs.push({
            send: fromUserId + '：',
            content: text
          });
        },

        /**
         * 收到C2C自定义消息
         * @param fromUserId		发送此消息的用户id
         * @param data				收到消息的内容
         * @param dataLen			收到消息的长度
         */
        onTICRecvCustomMessage: (fromUserId, data, textLen) => {
          this.msgs.push({
            send: fromUserId + '：',
            content: data
          });
        },

        /**
         * 收到群文本消息
         * @param fromUserId		发送此消息的用户id
         * @param text				收到消息的内容
         * @param textLen			收到消息的长度
         */
        onTICRecvGroupTextMessage: (fromUserId, text, textLen) => {
          this.msgs.push({
            send: fromUserId + '：',
            content: text
          });
        },

        /**
         * 收到群自定义消息
         * @param fromUserId		发送此消息的用户id
         * @param data				收到消息的内容
         * @param dataLen			收到消息的长度
         */
        onTICRecvGroupCustomMessage: (fromUserId, data, textLen) => {
          this.msgs.push({
            send: fromUserId + '：',
            content: data
          });
        },

        /**
         * 所有消息
         * @param msg	IM消息体
         * @note 所有收到的消息都会在此回调进行通知，包括前面已经封装的文本和自定义消息（白板信令消息除外）
         */
        onTICRecvMessage(msg) {

        }
      });
    },

    // 事件监听回调
    addTICEventListener() {
      this.tic.addTICEventListener({
        onTICMemberJoin: (members) => {
          this.msgs.push({
            send: '群消息提示：',
            content: members.join(',') + '进入课堂'
          });
        },

        onTICMemberQuit: (members) => {
          this.msgs.push({
            send: '群消息提示：',
            content: members.join(',') + '退出课堂'
          });
        },

        onTICClassroomDestroy: () => {
          if (!this.isTeacher) { // 学生处理
            this.quitClassroom();
            this.showTip(`老师解散了课堂`);
          }
        }
      });
    },

    // IM状态监听回调
    addTICStatusListener() {
      this.tic.addTICStatusListener({
        onTICForceOffline: () => {
          alert(`其他地方登录，被T了`);
          // this.step = 'first';
        }
      });
    },

    // 启动推流(推摄像头)
    startRTC() {
      // 获取webrtc实例
      var WebRTC = this.TRTC;
      WebRTC.getLocalStream({
        audio: true,
        video: true,
        attributes: {
          width: 640,
          height: 480
        }
      }, (data) => {
        this.isPushCamera = true;
        if (WebRTC.global.localStream && WebRTC.global.localStream.active) {
          WebRTC.updateStream({
            role: 'screen',
            stream: data.stream
          }, () => {
            // 成功
          }, (error) => {
            this.showErrorTip(`更新流失败，${error}`);
          });
        } else {
          WebRTC.startRTC({
            stream: data.stream,
            role: 'user'
          }, (data) => {
            // 成功
          }, (error) => {
            this.showErrorTip(`推流失败, ${error}`);
          });
        }
      }, (error) => {
        this.showErrorTip(`获取本地流失败, ${JSON.stringify(error)}`);
      });
    },

    stopPush() {
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.stopRTC({}, () => {
        this.isPushing = 0;
        document.querySelector('#local_video').srcObject = null;
      });
    },

    /**
     * 推屏幕分享
     */
    pushScreen() {
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.getLocalStream({
        screen: true,
        screenSources: 'tab',
        attributes: {
          width: 1920,
          height: 1080,
          frameRate: 10
        }
      }, (data) => {
        this.isPushCamera = false;
        if (WebRTC.global.localStream && WebRTC.global.localStream.active) {
          WebRTC.updateStream({
            role: 'screen',
            stream: data.stream
          }, () => {
            // 成功
          }, (error) => {
            this.showErrorTip(`更新流失败，${error}`);
          });
        } else {
          WebRTC.startRTC({
            stream: data.stream,
            role: 'user'
          }, (data) => {
            // 成功
          }, (error) => {
            this.showErrorTip(`推流失败, ${error}`);
          });
        }
      }, (error) => {
        this.showErrorTip(`获取本地流失败, ${error}`);
      });
    },

    /**
     * 摄像头开关
     */
    toggleCamera() {
      this.enableCamera = !this.enableCamera;
      var WebRTC = this.tic.getWebRTCInstance();
      this.enableCamera ? WebRTC.openVideo() : WebRTC.closeVideo();
    },

    /**
     * 麦克风开关
     */
    toggleMic() {
      this.enableMic = !this.enableMic
      var WebRTC = this.tic.getWebRTCInstance();
      this.enableMic ? WebRTC.openAudio() : WebRTC.closeAudio();
    },

    /**
     * 枚举摄像头
     */
    getCameraDevices() {
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.getVideoDevices(devices => {
        this.devices.camera = devices;
      });
    },

    /**
     * 切换摄像头
     */
    switchCamera() {
      if (this.cameraIndex < 0) {
        return;
      }
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.chooseVideoDevice(this.devices.camera[this.cameraIndex]);
    },

    /**
     * 枚举麦克风
     */
    getMicDevices() {
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.getAudioDevices(devices => {
        this.devices.mic = devices;
      });
    },

    /**
     * 切换麦克风
     */
    switchMic() {
      if (this.micIndex < 0) {
        return;
      }
      var WebRTC = this.tic.getWebRTCInstance();
      WebRTC.chooseAudioDevice(this.devices.mic[this.micIndex]);
    },

    /**
     * 发送普通文本消息
     */
    sendMsg() {
      if (!this.imMsg.common.data) {
        this.showErrorTip(`不能发送空消息`);
      }

      // C2C 文本
      if (this.imMsg.common.toUser) {
        this.tic.sendTextMessage(this.imMsg.common.toUser, this.imMsg.common.data, function (res) {
          console.log('===sendTextMessage:', res);
        });
      } else { // 群组 文本
        this.tic.sendGroupTextMessage(this.imMsg.common.data, function (res) {
          console.log('===sendTextMessage:', res);
        });
      }
    },

    /**
     * 发送自定义消息
     */
    sendCustomGroupMsg() {
      // 
      if (this.imMsg.common.toUser) { // C2C 自定义
        this.tic.sendCustomMessage(this.imMsg.common.toUser, this.imMsg.custom.data, function (res) {
          console.log('===sendCustomGroupMsg:', res);
        });
      } else { //群组 自定义
        this.tic.sendGroupCustomMessage(this.imMsg.custom.data, function (res) {
          console.log('===sendCustomGroupMsg:', res);
        });
      }
    },

    /**
     * 设置全局背景色
     * @param {*} color Hex 色值，如 #ff00ff
     */
    setGlobalColor(color) {
      this.teduBoard.setGlobalBackgroundColor(color);
    },

    /**
     * 设置当前页背景色
     * @param {*} color Hex 色值，如 #ff00ff
     */
    setBgColor(color) {
      this.teduBoard.setBackgroundColor(color);
    },

    /**
     * 设置涂鸦颜色
     * @param {*} color Hex 色值，如 #ff00ff
     */
    setColor(color) {
      this.teduBoard.setBrushColor(color);
    },

    setBackgroundH5() {
      this.teduBoard.setBackgroundH5('https://www.qq.com');
    },

    /**
     * 设置涂鸦类型
     * @param {*} type 
     */
    setType(type) {
      this.teduBoard.setToolType(type);
    },

    /**
     * 设置涂鸦粗细
     * @param {*} num 
     */
    setThin(num) {
      this.teduBoard.setBrushThin(num);
    },

    /**
     * 清空当前页涂鸦(保留背景色/图片)
     */
    clearDraws() {
      this.teduBoard.clear();
    },

    /**
     * 清空当前页涂鸦 + 背景色/图片
     */
    clear() {
      this.teduBoard.clear(true);
    },

    /**
     * 回退
     */
    revert() {
      this.teduBoard.undo();
    },

    /**
     * 恢复
     */
    process() {
      this.teduBoard.redo();
    },

    /**
     * 上传文件
     */
    uploadFile() {
      var file = document.getElementById('file_input').files[0];
      this.teduBoard.addFile({
        data: file,
        userData: 'hello'
      });
    },

    uploadH5File() {
      // this.teduBoard.addH5PPTFile('https://test04-1257240443.cos.ap-shanghai.myqcloud.com/0l5stagbd6b26khg59jb/index.html');
      this.teduBoard.addH5PPTFile('https://test04-1257240443.cos.ap-shanghai.myqcloud.com/2019-05-08-15-38-54/index.html');
    },

    uploadH5File2() {
      this.teduBoard.addH5PPTFile('https://test04-1257240443.cos.ap-shanghai.myqcloud.com/0o5stagbd6b264ei59jb/index.html');
    },

    // 动画上一步
    prevStep() {
      this.teduBoard.prevStep();
    },

    // 动画下一步
    nextStep() {
      this.teduBoard.nextStep();
    },

    /**
     * 上一页
     */
    prevBoard() {
      this.teduBoard.prevBoard();
    },

    /**
     * 下一页
     */
    nextBoard() {
      this.teduBoard.nextBoard();
    },

    /**
     * 新增一页
     */
    addBoard() {
      this.teduBoard.addBoard();
    },

    /**
     * 删除当前页
     */
    deleteBoard() {
      this.teduBoard.deleteBoard();
    },

    /**
     * 白板事件回调处理
     * @param {*} data 
     */
    proBoardData(data) {
      this.currentFile = this.teduBoard.getCurrentFile();
      this.boardFileGroup = this.teduBoard.getFileInfoList();
      var currentBoard = this.teduBoard.getCurrentBoard();

      var boards = this.teduBoard.getFileBoardList(this.currentFile);

      this.boardData.page = {
        current: boards.indexOf(currentBoard) + 1,
        total: boards.length
      }
    },

    showErrorTip(title, time) {
      this.$toasted.error(title, {
        position: "top-right",
        duration: time || 2000
      });
    },

    showTip(title, time) {
      this.$toasted.show(title, {
        position: "top-right",
        duration: time || 2000
      });
    },


    /**
     * 切换文件
     */
    switchFile(file) {
      this.teduBoard.switchFile(file.fid);
    },

    /**
     * 删除文件
     */
    deleteFile(file) {
      this.teduBoard.deleteFile(file.fid);
    },

    // 放大
    zoom() {
      var scale = this.teduBoard.getBoardScale();
      this.teduBoard.setBoardScale(scale + 50);
    },

    shrink() {
      var scale = this.teduBoard.getBoardScale();
      this.teduBoard.setBoardScale(scale - 50);
    },

    /**
     * 获取userSig
     */
    findUserSig() {
      var userSig = null;
      for (var i = 0, len = this.users.length; i < len; i++) {
        if (this.account === this.users[i].userId) {
          userSig = this.users[i].userToken;
          break;
        }
      }
      return userSig;
    }
  },

  beforeDestroy() {
    this.quitClassroom();
  }
});