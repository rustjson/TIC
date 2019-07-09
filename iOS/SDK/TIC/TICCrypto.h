//
//  TICCrypto.h
//  TAISDK
//
//  Created by kennethmiao on 2018/11/28.
//  Copyright © 2018年 kennethmiao. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TICCrypto : NSObject
+ (NSString *)sha256Hex:(NSString *)string;
+ (NSString *)hmacsha256Hex:(NSString *)value withKey:(NSData *)key;
+ (NSData *)hmacsha256String:(NSString *)value withKey:(NSData *)key;
+ (NSString *)md5:(NSString *)string;
@end
