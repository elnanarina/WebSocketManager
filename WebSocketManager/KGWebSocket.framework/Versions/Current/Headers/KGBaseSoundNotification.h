/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import "KGSoundNotification.h"

/**
 * KGBaseSoundNotification is a concrete class with ability to specify  
 * the sound file name that is to be played when the remote notification
 * is received from Apple Push Notification Service(APNS) by the device. 
 * The sound file name is included in the JSON payload that is sent to 
 * the APNS service. This class conforms to the KGSoundNotification protocol.
 * 
 * @see KGSoundNotification
 * @see KGNotificationPayload
 */
@interface KGBaseSoundNotification : NSObject<KGSoundNotification>

/**
 * Creates an instance of KGBaseSoundNotification class using the
 * sound filename.
 *
 * @param filename    NSString representing the sound file to be
 *                    played
 */
- (id) initWithFilename:(NSString *)filename;

@end
