// Copyright 2025 The Lynx Authors. All rights reserved.
// Licensed under the Apache License Version 2.0 that can be found in the
// LICENSE file in the root directory of this source tree.

#import <LynxDevtool/LynxDebugInfoRecorderDelegate.h>

#pragma mark - LynxDebugInfoRecorderDelegate
@implementation LynxDebugInfoRecorderDelegate {
  NSMutableDictionary* debugInfoDict;
}

- (instancetype)init {
  self = [super init];
  if (self) {
    debugInfoDict = [NSMutableDictionary dictionary];
  }
  return self;
}

- (void)setDebugInfo:(NSString*)url debugInfo:(NSString*)debugInfo {
  [debugInfoDict setObject:debugInfo forKey:url];
}

- (NSString*)getDebugInfo:(NSString*)url {
  return debugInfoDict[url];
}

@end
