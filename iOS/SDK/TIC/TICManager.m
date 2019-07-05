//
//  TICManager.m
//  TICDemo
//
//  Created by kennethmiao on 2019/3/27.
//  Copyright © 2019年 Tencent. All rights reserved.
//

#import "TICManager.h"
#if TARGET_OS_IPHONE
#import <TXLiteAVSDK_TRTC/TXLiteAVSDK.h>
#import <ImSDK/ImSDK.h>
#else
#import <TXLiteAVSDK_Mac/TXLiteAVSDK.h>
#import <ImSDKForMac/ImSDK.h>
#endif
#import "TICRecorder.h"

typedef id(^WeakRefBlock)(void);
typedef id(^MakeWeakRefBlock)(id);
id makeWeakRef (id object) {
    __weak id weakref = object;
    WeakRefBlock block = ^(){
        return weakref;
    };
    return block();
}

@interface TICManager () <TIMUserStatusListener, TIMMessageListener, TRTCCloudDelegate, TEduBoardDelegate>
@property (nonatomic, assign) int sdkAppId;
@property (nonatomic, strong) TICClassroomOption *option;
@property (nonatomic, strong) NSString *userId;
@property (nonatomic, strong) NSString *userSig;

@property (nonatomic, strong) NSMutableArray<id<TICMessageListener>> *messageListeners;
@property (nonatomic, strong) NSMutableArray<id<TICEventListener>> *eventListeners;
@property (nonatomic, strong) NSMutableArray<id<TICStatusListener>> *statusListeners;

@property (nonatomic, assign) BOOL isEnterRoom;
@property (nonatomic, strong) TICCallback enterCallback;

@property (nonatomic, strong) TEduBoardController *boardController;
@property (nonatomic, strong) TICRecorder *recorder;
@end

@implementation TICManager


+ (instancetype)sharedInstance
{
    static TICManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[TICManager alloc] init];;
        instance.messageListeners = [NSMutableArray array];
        instance.eventListeners = [NSMutableArray array];
        instance.statusListeners = [NSMutableArray array];
    });
    return instance;
}

- (void)init:(int)sdkAppId callback:(TICCallback)callback;
{
    _sdkAppId = sdkAppId;
    //初始化IMSDK
    TIMSdkConfig *config = [[TIMSdkConfig alloc] init];
    config.sdkAppId = sdkAppId;
    int ret = [[TIMManager sharedInstance] initSdk:config];
    if(ret == 0){
        [[TIMManager sharedInstance] addMessageListener:self];
        TIMUserConfig *userConfig = [[TIMUserConfig alloc] init];
        userConfig.userStatusListener = self;
        userConfig.disableAutoReport = NO;
        [[TIMManager sharedInstance] setUserConfig:userConfig];
    }
    TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, ret, nil);
}

- (void)unInit
{
    
}

- (void)login:(NSString *)userId userSig:(NSString *)userSig callback:(TICCallback)callback
{
    _userId = userId;
    _userSig = userSig;
    TIMLoginParam *loginParam = [TIMLoginParam new];
    loginParam.identifier = userId;
    loginParam.userSig = userSig;
    loginParam.appidAt3rd = [@(_sdkAppId) stringValue];
    int ret = [[TIMManager sharedInstance] login:loginParam succ:^{
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil);
    } fail:^(int code, NSString *msg) {
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
    }];
    if(ret != 0){
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, ret, nil);
    }
}

- (void)logout:(TICCallback)callback
{
    int ret = [[TIMManager sharedInstance] logout:^{
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil);
    } fail:^(int code, NSString *msg) {
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
    }];
    if(ret != 0){
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, ret, nil);
    }
};


- (void)createClassroom:(int)classId callback:(TICCallback)callback
{
    TIMCreateGroupInfo *groupInfo = [[TIMCreateGroupInfo alloc] init];
    NSString *roomIdStr = [@(classId) stringValue];
    groupInfo.group = roomIdStr;
    groupInfo.groupName = roomIdStr;
    groupInfo.groupType = @"Public";
    groupInfo.setAddOpt = YES;
    groupInfo.addOpt = TIM_GROUP_ADD_ANY;
    [[TIMGroupManager sharedInstance] createGroup:groupInfo succ:^(NSString *groupId) {
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil);
    } fail:^(int code, NSString *msg) {
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
    }];
}

- (void)destroyClassroom:(int)classId callback:(TICCallback)callback
{
    __weak typeof(self) ws = self;
    [[TIMGroupManager sharedInstance] deleteGroup:[@(classId) stringValue] succ:^{
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil);
    } fail:^(int code, NSString *msg) {
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
    }];
}

- (void)joinClassroom:(TICClassroomOption *)option callback:(TICCallback)callback
{
    _option = option;
    _enterCallback = callback;
    
    //白板初始化
    __weak typeof(self) ws = self;
    void (^createBoard)(void) = ^(void){
        TEduBoardAuthParam *authParam = [[TEduBoardAuthParam alloc] init];
        authParam.sdkAppId = ws.sdkAppId;
        authParam.userId = ws.userId;
        authParam.userSig = ws.userSig;
        TEduBoardInitParam *initParam = option.boardInitParam;
        if(!initParam){
            initParam = [[TEduBoardInitParam alloc] init];
        }
        ws.boardController = [[TEduBoardController alloc] initWithAuthParam:authParam roomId:ws.option.classId initParam:initParam];
        [ws.boardController addDelegate:ws];
        if(option.boardDelegate){
            [ws.boardController addDelegate:option.boardDelegate];
        }
    };
    
    //IM进房
    [[TIMGroupManager sharedInstance] joinGroup:[@(_option.classId) stringValue] msg:nil succ:^{
        createBoard();
    } fail:^(int code, NSString *msg) {
        if(code == 10013){
            //已经在群中
            createBoard();
        }
        else{
            TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
        }
    }];
};

- (void)quitClassroom:(BOOL)clearBoard callback:(TICCallback)callback
{
    if(clearBoard){
        [self.boardController reset];
    }
    NSString *classId = [@(_option.classId) stringValue];
    [_boardController removeDelegate:self];
    if(_option.boardDelegate){
        [_boardController removeDelegate:_option.boardDelegate];
    }
    _isEnterRoom = NO;
    _option = nil;
    _boardController = nil;
    [[TRTCCloud sharedInstance] exitRoom];
    [[TIMGroupManager sharedInstance] quitGroup:classId succ:^{
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil)
    } fail:^(int code, NSString *msg) {
        if (code == 10009) {
            //群主退群失败
            TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil)
        }
        else{
            TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
        }
    }];
}

#pragma mark - manager
- (TEduBoardController *)getBoardController
{
    return _boardController;
}
 
- (TRTCCloud *)getTRTCCloud
{
    return [TRTCCloud sharedInstance];
}
#pragma mark - listener

- (void)addMessageListener:(id<TICMessageListener>)listener
{
    [_messageListeners addObject:makeWeakRef(listener)];
}

- (void)addEventListener:(id<TICEventListener>)listener
{
    [_eventListeners addObject:makeWeakRef(listener)];
}

- (void)addStatusListener:(id<TICStatusListener>)listener
{
    [_statusListeners addObject:makeWeakRef(listener)];
}

- (void)removeMessageListener:(id<TICMessageListener>)listener
{
    [_messageListeners removeObject:listener];
}

- (void)removeEventListener:(id<TICEventListener>)listener
{
    [_eventListeners removeObject:listener];
}

- (void)removeStatusListener:(id<TICStatusListener>)listener
{
    [_statusListeners removeObject:listener];
}

#pragma mark - im method
- (void)sendTextMessage:(NSString *)text toUserId:(NSString *)toUserId callback:(TICCallback)callback
{
    TIMTextElem *elem = [[TIMTextElem alloc] init];
    elem.text = text;
    [self sendMessageWithElem:elem type:TIM_C2C receiver:toUserId callback:callback];
}

- (void)sendCustomMessage:(NSData *)data toUserId:(NSString *)toUserId callback:(TICCallback)callback
{
    TIMCustomElem *elem = [[TIMCustomElem alloc] init];
    elem.data = data;
    [self sendMessageWithElem:elem type:TIM_C2C receiver:toUserId callback:callback];
}

- (void)sendMessage:(TIMMessage *)message toUserId:(NSString *)toUserId callback:(TICCallback)callback
{
    [self sendMessage:message type:TIM_C2C receiver:toUserId callback:callback];
}

- (void)sendGroupTextMessage:(NSString *)text groupId:(NSString *)groupId callback:(TICCallback)callback
{
    TIMTextElem *elem = [[TIMTextElem alloc] init];
    elem.text = text;
    [self sendMessageWithElem:elem type:TIM_GROUP receiver:groupId callback:callback];
}

- (void)sendGroupCustomMessage:(NSData *)data groupId:(NSString *)groupId callback:(TICCallback)callback
{
    TIMCustomElem *elem = [[TIMCustomElem alloc] init];
    elem.data = data;
    [self sendMessageWithElem:elem type:TIM_GROUP receiver:groupId callback:callback];
}

- (void)sendGroupMessage:(TIMMessage *)message groupId:(NSString *)groupId callback:(TICCallback)callback
{
    [self sendMessage:message type:TIM_GROUP receiver:groupId callback:callback];
}

- (void)sendMessageWithElem:(TIMElem *)elem type:(TIMConversationType)type receiver:(NSString *)receiver callback:(TICCallback)callback
{
    TIMMessage *message = [[TIMMessage alloc] init];
    [message addElem:elem];
    [self sendMessage:message type:type receiver:receiver callback:callback];
}

- (void)sendMessage:(TIMMessage *)message type:(TIMConversationType)type receiver:(NSString *)receiver callback:(TICCallback)callback
{
    TIMConversation *conversation = [[TIMManager sharedInstance] getConversation:type receiver:receiver];
    if(conversation){
        [conversation sendMessage:message succ:^{
            TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, 0, nil);
        } fail:^(int code, NSString *msg) {
            TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, code, msg);
        }];
    }
    else{
        TICBLOCK_SAFE_RUN(callback, TICMODULE_IMSDK, -1, @"conversation not exits!!");
    }
}



#pragma mark - trtc delegate
- (void)onError:(TXLiteAVError)errCode errMsg:(NSString *)errMsg extInfo:(NSDictionary *)extInfo
{
    if(errCode == ERR_ROOM_ENTER_FAIL
       || errCode == ERR_ENTER_ROOM_PARAM_NULL
       || errCode == ERR_SDK_APPID_INVALID
       || errCode == ERR_ROOM_ID_INVALID
       || errCode == ERR_USER_ID_INVALID
       || errCode == ERR_USER_SIG_INVALID){
        [[TRTCCloud sharedInstance] exitRoom];
        TICBLOCK_SAFE_RUN(self->_enterCallback, TICMODULE_TRTC, errCode, errMsg);
    }
    
    //TODO: 退房失败
}

- (void)onEnterRoom:(NSInteger)elapsed
{
    _isEnterRoom = YES;
    //录制对时
    [self sendOfflineRecordInfo];
    //群ID上报
    [_recorder reportGroupId:[@(_option.classId) stringValue] sdkAppId:_sdkAppId userId:_userId userSig:_userSig];
    //进房回调
    TICBLOCK_SAFE_RUN(self->_enterCallback, TICMODULE_TRTC, 0, nil);
    _enterCallback = nil;
}

- (void)onExitRoom:(NSInteger)reason
{
    [TRTCCloud destroySharedIntance];
}

- (void)onUserExit:(NSString *)userId reason:(NSInteger)reason
{
    [self onUserAudioAvailable:userId available:NO];
    [self onUserVideoAvailable:userId available:NO];
    [self onUserSubStreamAvailable:userId available:NO];
}

- (void)onUserVideoAvailable:(NSString *)userId available:(BOOL)available
{
    for (id<TICEventListener> listener in _eventListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICUserVideoAvailable:available:)]){
            [listener onTICUserVideoAvailable:userId available:available];
        }
    }
}

- (void)onUserSubStreamAvailable:(NSString *)userId available:(BOOL)available
{
    for (id<TICEventListener> listener in _eventListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICUserSubStreamAvailable:available:)]){
            [listener onTICUserSubStreamAvailable:userId available:available];
        }
    }
}

- (void)onUserAudioAvailable:(NSString *)userId available:(BOOL)available
{
    for (id<TICEventListener> listener in _eventListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICUserAudioAvailable:available:)]){
            [listener onTICUserAudioAvailable:userId available:available];
        }
    }
}

#if !TARGET_OS_IPHONE
- (void)onDevice:(NSString *)deviceId type:(TRTCMediaDeviceType)deviceType stateChanged:(NSInteger)state
{
    for (id<TICEventListener> listener in _eventListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICDevice:type:stateChanged:)]){
            [listener onTICDevice:deviceId type:deviceType stateChanged:state];
        }
    }
}
#endif

#pragma mark - board method

- (BOOL)isBoardMessage:(TIMMessage *)message
{
    TIMOfflinePushInfo *info = message.getOfflinePushInfo;
    return [info.ext hasPrefix:kTICEduBoardCmd];
}

- (BOOL)isBoardMessageElem:(TIMElem *)elem
{
    if ([elem isKindOfClass:[TIMCustomElem class]]) {
        TIMCustomElem *cusElem = (TIMCustomElem *)elem;
        return [cusElem.ext hasPrefix:kTICEduBoardCmd];
    }
    else if ([elem isKindOfClass:[TIMFileElem class]]) {
        TIMFileElem *fileElem = (TIMFileElem *)elem;
        return [fileElem.filename hasPrefix:kTICEduBoardCmd];
    }
    return NO;
}

- (BOOL)isRecordMessageElem:(TIMElem *)elem
{
    if ([elem isKindOfClass:[TIMCustomElem class]]) {
        TIMCustomElem *cusElem = (TIMCustomElem *)elem;
        return [cusElem.ext hasPrefix:kTICEduRecordCmd];
    }
    return NO;
}

#pragma mark - board delegate
- (void)onTEBInit
{
    TRTCParams *params = [[TRTCParams alloc] init];
    params.sdkAppId = _sdkAppId;
    params.userId = _userId;
    params.userSig = _userSig;
    params.roomId = _option.classId;
    [[TRTCCloud sharedInstance] setDelegate:self];
    [[TRTCCloud sharedInstance] enterRoom:params appScene:TRTCAppSceneVideoCall];
#if TARGET_OS_IPHONE
    if(_option.bOpenCamera && _option.renderView){
        [[TRTCCloud sharedInstance] startLocalPreview:_option.bFrontCamera view:_option.renderView];
    }
    if(_option.bOpenMic){
        [[TRTCCloud sharedInstance] startLocalAudio];
    }
#else
    if(_option.cameraId.length != 0){
        [[TRTCCloud sharedInstance] setCurrentCameraDevice:_option.cameraId];
    }
    if(_option.bOpenCamera && _option.renderView){
        [[TRTCCloud sharedInstance] startLocalPreview:_option.renderView];
    }
    if(_option.micId.length != 0){
        [[TRTCCloud sharedInstance] setCurrentMicDevice:_option.micId];
    }
    if(_option.bOpenMic){
        [[TRTCCloud sharedInstance] startLocalAudio];
    }
#endif
}

- (void)onTEBError:(TEduBoardErrorCode)code msg:(NSString *)msg
{
    if(code == TEDU_BOARD_ERROR_AUTH || code == TEDU_BOARD_ERROR_LOAD){
        TICBLOCK_SAFE_RUN(self->_enterCallback, TICMODULE_TRTC, code, msg);
        _enterCallback = nil;
    }
}

#pragma mark - im delegate
- (void)onNewMessage:(NSArray *)msgs
{
    for (TIMMessage *msg in msgs) {
        if ([msg elemCount] <= 0) {
            continue;
        }

        TIMConversation *conv = [msg getConversation];
        NSString *convId = [conv getReceiver];
        TIMConversationType type = [conv getType];
        if(type == TIM_GROUP && ![convId isEqualToString:[@(_option.classId) stringValue]]){
            //收到其他群消息
            continue;
        }
        if ([self isBoardMessage:msg]) {
            //白板消息
            continue;
        }

        for (id<TICMessageListener> listener in _messageListeners) {
            if (listener && [listener respondsToSelector:@selector(onTICRecvMessage:)]) {
                [listener onTICRecvMessage:msg];
            }
        }
        
        for (int index = 0; index < msg.elemCount; index++) {
            TIMElem *elem = [msg getElem:index];
            if([self isBoardMessageElem:elem] || [self isRecordMessageElem:elem]){
                continue;
            }
            if ([elem isKindOfClass:[TIMTextElem class]]) {
                TIMTextElem *textElem = (TIMTextElem *)elem;
                switch (type)
                {
                    case TIM_C2C:
                        for (id<TICMessageListener> listener in _messageListeners) {
                            if (listener && [listener respondsToSelector:@selector(onTICRecvTextMessage:fromUserId:)]){
                                [listener onTICRecvTextMessage:textElem.text fromUserId:msg.sender];
                            }
                        }
                        break;
                    case TIM_GROUP:
                        for (id<TICMessageListener> listener in _messageListeners) {
                            if (listener && [listener respondsToSelector:@selector(onTICRecvGroupTextMessage:groupId:fromUserId:)]){
                                NSString *convId = [conv getReceiver];
                                NSString *curGroupId = [@(_option.classId) stringValue];
                                if ([convId isEqualToString:curGroupId]){
                                    [listener onTICRecvGroupTextMessage:textElem.text groupId:convId fromUserId:msg.sender];
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            } else if ([elem isKindOfClass:[TIMCustomElem class]]) {
                TIMCustomElem *cusElem = (TIMCustomElem *)elem;
                switch (type)
                {
                    case TIM_C2C:
                        for (id<TICMessageListener> listener in _messageListeners) {
                            if (listener && [listener respondsToSelector:@selector(onTICRecvCustomMessage:fromUserId:)]){
                                [listener onTICRecvCustomMessage:cusElem.data fromUserId:msg.sender];
                            }
                        }
                        break;
                    case TIM_GROUP:
                    {
                        NSString *convId = [conv getReceiver];
                        NSString *curGroupId = [@(_option.classId) stringValue];
                        for (id<TICMessageListener> listener in _messageListeners) {
                            if([convId isEqualToString:curGroupId]
                               && listener
                               && [listener respondsToSelector:@selector(onTICRecvGroupCustomMessage:groupId:fromUserId:)]){
                                [listener onTICRecvGroupCustomMessage:cusElem.data groupId:convId fromUserId:msg.sender];
                            }
                        }
                    }
                        break;
                    default:
                        break;
                }
            }
            else if ([elem isKindOfClass:[TIMGroupTipsElem class]]) {
                TIMGroupTipsElem *tipElem = (TIMGroupTipsElem *)elem;
                switch (tipElem.type) {
                    case TIM_GROUP_TIPS_TYPE_INVITE: // 用户加入群
                    {
                        if([[@(_option.classId) stringValue] isEqualToString:tipElem.group]) {
                            for (id<TICEventListener> listener in _eventListeners) {
                                if (listener && [listener respondsToSelector:@selector(onTICMemberJoin:)]) {
                                    [listener onTICMemberJoin:tipElem.userList];
                                }
                            }
                        }
                    }
                        break;
                    case TIM_GROUP_TIPS_TYPE_QUIT_GRP: // 用户退出群
                    case TIM_GROUP_TIPS_TYPE_KICKED: // 用户被踢出群
                    {
                        if([[@(_option.classId) stringValue] isEqualToString:tipElem.group]) {
                            for (id<TICEventListener> listener in _eventListeners) {
                                if (listener && [listener respondsToSelector:@selector(onTICMemberQuit:)]) {
                                    NSArray *arr = tipElem.userList;
                                    if (tipElem.userList.count == 0) {
                                        arr = @[tipElem.opUser];
                                    }
                                    [listener onTICMemberQuit:arr];
                                }
                            }
                        }
                    }
                        break;
                    default:
                        break;
                }
            } else if ([elem isKindOfClass:[TIMGroupSystemElem class]]) {
                TIMGroupSystemElem *sysElem = (TIMGroupSystemElem *)elem;
                switch (sysElem.type) {
                    case TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE: // 群被解散
                    case TIM_GROUP_SYSTEM_REVOKE_GROUP_TYPE: // 群被回收
                    {
                        if ([[@(_option.classId) stringValue] isEqualToString:sysElem.group]) {
                            for (id<TICEventListener> listener in _eventListeners) {
                                if (listener && [listener respondsToSelector:@selector(onTICClassroomDestroy)]) {
                                    // 退出房间
                                    [self quitClassroom:YES callback:nil];
                                    // 触发回调
                                    [listener onTICClassroomDestroy];
                                }
                            }
                        }
                    }
                        break;
                    case TIM_GROUP_SYSTEM_KICK_OFF_FROM_GROUP_TYPE: // 用户被踢出群（只有被踢的人能收到）
                    {
                        if ([[@(_option.classId) stringValue] isEqualToString:sysElem.group]) {
                            for (id<TICEventListener> listener in _eventListeners) {
                                if (listener && [listener respondsToSelector:@selector(onTICMemberQuit:)]) {
                                    // 退出房间
                                    [self quitClassroom:NO callback:nil];
                                    // 触发回调
                                    [listener onTICMemberQuit:@[_userId]];
                                }
                            }
                        }
                    }
                        break;

                    default:
                        break;
                }
            }
        }
    }
}


- (void)onForceOffline
{
    if(_isEnterRoom){
        [[TRTCCloud sharedInstance] exitRoom];
        [_boardController removeDelegate:self];
        if(_option.boardDelegate){
            [_boardController removeDelegate:_option.boardDelegate];
        }
        _boardController = nil;
    }
    for (id<TICStatusListener> listener in _statusListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICForceOffline)]){
            [listener onTICForceOffline];
        }
    }
}

- (void)onUserSigExpired
{
    if(_isEnterRoom){
        [[TRTCCloud sharedInstance] exitRoom];
        [_boardController removeDelegate:self];
        if(_option.boardDelegate){
            [_boardController removeDelegate:_option.boardDelegate];
        }
        _boardController = nil;
    }
    for (id<TICStatusListener> listener in _statusListeners) {
        if(listener && [listener respondsToSelector:@selector(onTICUserSigExpired)]){
            [listener onTICUserSigExpired];
        }
    }
}

- (void)sendOfflineRecordInfo
{
    if(_recorder == nil){
        _recorder = [[TICRecorder alloc] init];
    }
    __weak typeof(self) ws = self;
    [_recorder sendOfflineRecordInfo:[@(_option.classId) stringValue] ntpServer:_option.ntpServer callback:^(TICModule module, int code, NSString *desc) {
        for (id<TICEventListener> listener in ws.eventListeners) {
            if (listener && [listener respondsToSelector:@selector(onTICSendOfflineRecordInfo:desc:)]) {
                [listener onTICSendOfflineRecordInfo:code desc:desc];
            }
        }
    }];
}
@end
