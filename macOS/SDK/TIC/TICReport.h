//
//  TICReport.h
//  TICDemo_Mac
//
//  Created by 缪少豪 on 2019/7/5.
//  Copyright © 2019 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, TICReportEvent)
{
    TIC_INITSDK_START,
    TIC_INITSDK_END,
    TIC_LOGIN_START,
    TIC_LOGIN_END,
    
};

@interface TICReportParam : NSObject
@property (nonatomic, assign) int sdkAppId;
@property (nonatomic, strong) NSString *userId;
@property (nonatomic, strong) NSString *sdkVersion;
@property (nonatomic, strong) NSString *roomId;
@end

@interface TICReport : NSObject

@end

