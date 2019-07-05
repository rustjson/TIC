//
//  AppDelegate.m
//  TICDemo_Mac
//
//  Created by jameskhdeng(邓凯辉) on 2018/10/23.
//  Copyright © 2018年 Tencent. All rights reserved.
//

#import "AppDelegate.h"
#import "TICManager.h"
#import "ViewController.h"
#import <AVFoundation/AVFoundation.h>

@interface AppDelegate () 

@property (nonatomic, strong) ViewController *loginVC;     //!< 登录控制器



@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [[TICManager sharedInstance] init:1400127140 callback:^(TICModule module, int code, NSString *desc) {

    }];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
