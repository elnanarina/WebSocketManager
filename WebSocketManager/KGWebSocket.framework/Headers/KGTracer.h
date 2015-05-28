/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

/**
 * Set KGTracerDebug to YES to enable logging.
 */
extern BOOL KGTracerDebug;

@interface KGTracer : NSObject

/**
 * Logs messages when KGTracerDebug is set to true.
 *
 * @param message the message to log
 */
+ (void) trace:(NSString*)message;

@end
