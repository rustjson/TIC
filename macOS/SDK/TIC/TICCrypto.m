//
//  TICCrypto.m
//  TAISDK
//
//  Created by kennethmiao on 2018/11/28.
//  Copyright © 2018年 kennethmiao. All rights reserved.
//

#import "TICCrypto.h"
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonHMAC.h>

@implementation TICCrypto
+ (NSString *)sha256Hex:(NSString *)string
{
    const char *cstr = [string cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *data = [NSData dataWithBytes:cstr length:string.length];
    
    uint8_t digest[CC_SHA256_DIGEST_LENGTH];
    
    CC_SHA256(data.bytes, (CC_LONG)data.length, digest);
    
    NSMutableString* output = [NSMutableString stringWithCapacity:CC_SHA256_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_SHA256_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    
    return output;
}


+ (NSString *)hmacsha256Hex:(NSString *)value withKey:(NSData *)key
{
    const char *cKey  = key.bytes;
    const char *cData = [value cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned char cHMAC[CC_SHA256_DIGEST_LENGTH];
    CCHmac(kCCHmacAlgSHA256, cKey, [key length], cData, [value length], cHMAC);
    NSData *HMACData = [NSData dataWithBytes:cHMAC length:sizeof(cHMAC)];
    const unsigned char *buffer = (const unsigned char *)[HMACData bytes];
    NSMutableString *HMAC = [NSMutableString stringWithCapacity:HMACData.length * 2];
    for (int i = 0; i < HMACData.length; ++i){
        [HMAC appendFormat:@"%02x", buffer[i]];
    }
    return HMAC;
}

+ (NSData *)hmacsha256String:(NSString *)value withKey:(NSData *)key{
    const char *cKey  = key.bytes;
    const char *cData = [value cStringUsingEncoding:NSASCIIStringEncoding];
    unsigned char cHMAC[CC_SHA256_DIGEST_LENGTH];
    CCHmac(kCCHmacAlgSHA256, cKey, [key length], cData, [value length], cHMAC);
    NSData *HMACData = [NSData dataWithBytes:cHMAC length:sizeof(cHMAC)];
//    const unsigned char *buffer = (const unsigned char *)[HMACData bytes];
//    NSMutableString *HMAC = [NSMutableString stringWithCapacity:HMACData.length * 2];
//    for (int i = 0; i < HMACData.length; ++i){
//        H
//        [HMAC appendFormat:@"%c", buffer[i]];
//    }
    return HMACData;
}

+ (NSString *)md5:(NSString *)string {
    if (!string){
        return nil;
    }
    const char *cStr = string.UTF8String;
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5(cStr, (CC_LONG)strlen(cStr), result);
    NSMutableString *md5Str = [NSMutableString string];
    for (int i = 0; i < CC_MD5_DIGEST_LENGTH; ++i) {
        [md5Str appendFormat:@"%02x", result[i]];
    }
    return md5Str;
}
@end
