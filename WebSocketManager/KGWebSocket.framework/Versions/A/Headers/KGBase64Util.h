/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

@interface KGBase64Util : NSObject

+ (NSString*) encode:(NSData*)decoded;

+ (NSData*) decode:(NSString*)encoded;

@end
