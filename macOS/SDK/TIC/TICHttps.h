//
//  TICHttps.h
//  TAISDK
//
//  Created by kennethmiao on 2018/11/28.
//  Copyright © 2018年 kennethmiao. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^TICHttpsCallback)(NSInteger code, NSString *desc, NSDictionary *dic);

@interface TICHttpsDelegate : NSObject <NSURLSessionTaskDelegate>
@end

@interface TICHttpsParam : NSObject
@property (nonatomic, strong) NSString *url;
@property (nonatomic, strong) NSString *method;
@property (nonatomic, strong) NSData *body;
@property (nonatomic, strong) NSDictionary *header;
@property (nonatomic, assign) NSInteger timeout;
@end

@interface TICHttps : NSObject
+ (id)shareInstance;
- (void)request:(TICHttpsParam *)param callback:(TICHttpsCallback)callback;
@end
