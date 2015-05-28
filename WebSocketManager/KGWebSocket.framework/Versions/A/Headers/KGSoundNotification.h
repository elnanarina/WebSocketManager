/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * KGSoundNotification protocol provides the ability to create JSON
 * sound payload that can be sent to Apple Push Notification 
 * Service(APNS). The sound gets played when the notification is
 * eventually delivered to the device by APNS.
 * 
 * @see KGNotificationPayload
 */
@protocol KGSoundNotification <NSObject>

/**
 * Returns the sound filename.
 * 
 * @return NSString representing the sound filename.
 */
- (NSString *) fileName;

/**
 * Sets the specified sound filename.
 *
 * @param fname    NSString representing the sound filename
 */
- (void) setFileName:(NSString *)fname;

/**
 * Returns the JSON sound payload that is included in the overall
 * payload to be sent to APNS.
 * 
 * @return NSString  representing JSON sound payload
 */
- (NSString *) toJSON;

@end
