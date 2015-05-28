/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import "KGAlertNotification.h"
#import "KGSoundNotification.h"

/**
 * KGNotificationPayload represents a concrete class that is used
 * to create a JSON payload to be delivered to Apple Push Notification
 * Service(APNS). Currently, only alert and sound notifications are
 * supported.
 *
 * @see KGAlertNotification
 * @see KGSimpleAlertNotification
 * @see KGLocalizedAlertNotification
 * @see KGSoundNotification
 * @see KGBaseSoundNotification
 */
@interface KGNotificationPayload : NSObject

/**
 * Creates an instance of KGNotificationPayload which includes
 * an alert notification.
 *
 * @param alert    KGAlertNotification representing the alert to
 *                 be rendered when the notification is received
 * @return id  instance of KGNotificationPayload class
 */
- (id) initWithAlert:(id<KGAlertNotification>)alert;

/**
 * Creates an instance of KGNotificationPayload which includes
 * an alert notification with sound.
 *
 * @param alert    KGAlertNotification representing the alert to
 *                 be rendered when the notification is received
 * @param sound    KGSoundNotification representing the sound to
 *                 be played when the notification is received
 * @return id  instance of KGNotificationPayload class
 */
- (id) initWithAlert:(id<KGAlertNotification>)alert 
               sound:(id<KGSoundNotification>)sound;

/**
 * Returns the alert notification.
 *
 * @return KGAlertNotification object
 */
- (id<KGAlertNotification>) alertNotification;

/**
 * Sets the alert notification.
 *
 * @param alert    KGAlertNotification object representing an alert
 */
- (void) setAlertNotification:(id<KGAlertNotification>)alert;

/**
 * Returns the sound notification.
 *
 * @return KGSoundNotification object
 */
- (id<KGSoundNotification>) soundNotification;

/**
 * Sets the sound notification.
 *
 * @param sound    KGSoundNotification object representing a sound
 */
- (void) setSoundNotification:(id<KGSoundNotification>)sound;

- (NSString *) toJSON;

@end
