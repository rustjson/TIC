//
//  TICHttps.m
//  TAISDK
//
//  Created by kennethmiao on 2018/11/28.
//  Copyright © 2018年 kennethmiao. All rights reserved.
//

#import "TICHttps.h"

@implementation TICHttpsDelegate

- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition, NSURLCredential * _Nullable))completionHandler
{
    //1)获取trust object
    SecTrustRef trust = challenge.protectionSpace.serverTrust;
    SecTrustResultType result;
    
    NSString *host = [[task currentRequest] valueForHTTPHeaderField:@"host"];
    if (host.length > 0) {
        //指定域名
        SecPolicyRef policyOverride = SecPolicyCreateSSL(true, (__bridge CFStringRef)host);
        NSMutableArray *policies = [NSMutableArray array];
        [policies addObject:(__bridge_transfer id)policyOverride];
        SecTrustSetPolicies(trust, (__bridge CFArrayRef)policies);
    }
    
    //2)SecTrustEvaluate对trust进行验证
    OSStatus status = SecTrustEvaluate(trust, &result);
    if (status == errSecSuccess &&
        (result == kSecTrustResultProceed ||
         result == kSecTrustResultUnspecified)) {
            
            //3)验证成功，生成NSURLCredential凭证cred，告知challenge的sender使用这个凭证来继续连接
            NSURLCredential *cred = [NSURLCredential credentialForTrust:trust];
            //        [challenge.sender useCredential:cred forAuthenticationChallenge:challenge];
            completionHandler(NSURLSessionAuthChallengeUseCredential, cred);
        } else {
            
            //5)验证失败，取消这次验证流程
            //        [challenge.sender cancelAuthenticationChallenge:challenge];
            completionHandler(NSURLSessionAuthChallengeUseCredential, nil);
        }
}

@end



@implementation TICHttpsParam
@end

@interface TICHttps ()
@property (nonatomic, strong) NSURLSession *session;
@end

@implementation TICHttps

+ (id)shareInstance
{
    static TICHttps *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[TICHttps alloc] init];
        NSURLSessionConfiguration *config = [NSURLSessionConfiguration defaultSessionConfiguration];
        [config setRequestCachePolicy:NSURLRequestReloadIgnoringLocalCacheData];
        instance.session = [NSURLSession sessionWithConfiguration:config delegate:[[TICHttpsDelegate alloc] init] delegateQueue:nil];
    });
    return instance;
}

- (void)request:(TICHttpsParam *)param callback:(TICHttpsCallback)callback
{
    [_session.configuration setTimeoutIntervalForRequest:param.timeout];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:param.url]];
    request.HTTPMethod = param.method;
    request.HTTPBody = param.body;
    for(NSString *key in param.header){
        [request addValue:[param.header objectForKey:key] forHTTPHeaderField:key];
    }
    NSURLSessionDataTask *task = [_session dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse *)response;
        NSInteger code = 0;
        NSString *desc = nil;
        if(error || httpResponse.statusCode != 200 || data == nil){
            if(error){
                code = error.code;
                desc = [NSString stringWithFormat:@"server error %ld", (long)code];
            }
            else{
                code = httpResponse.statusCode;
                desc = [NSString stringWithFormat:@"https error %ld", (long)code];
            }
            callback(code, desc, nil);
            return;
        }
        NSError * jsonErr = nil;
        NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&jsonErr];
        if (jsonErr || ![dict isKindOfClass:[NSDictionary class]]) {
            code = jsonErr.code;
            desc = [NSString stringWithFormat:@"json error %ld", code];
            callback(code, desc, nil);
            return;
        }
        callback(0, nil, dict);
    }];
    [task resume];
}
@end
