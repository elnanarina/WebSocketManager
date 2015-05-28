/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * KGAlertNotification provides APIs to construct JSON alert
 * payload to be sent to the Apple Push Notification Service(APNS)
 * from an application. The application developers can use this
 * class to create notifications that cater to their specific
 * needs.
 */
@protocol KGAlertNotification <NSObject>

/**
 * Returns the resource-bundle key for the action button
 * in the alert notification. Returns nil if the key is
 * not set. If the resource-bundle key is not set, 
 * the action button is rendered with "View" label.
 *
 * @return NSString representing the resource-bundle key for
 *                  the action button
 */
- (NSString *) actionKey;

/** 
 * Sets the resource-bundle key for the action button
 * in the alert notification.
 *
 * @param actionKey   NSString representing the resource-bundle
 *                    key for the action button
 */
- (void) setActionKey:(NSString *)actionKey;

/**
 * Returns the image file name that will be used as part of
 * the alert notification. Returns nil if the image file name 
 * is not specified.
 * 
 * @return NSString representing the image file name
 */
- (NSString *) launchImage;

/**
 * Sets the image file name to be used as part of the alert
 * notification.
 *
 * @param filename    NSString representing the image filename
 */
- (void) setLaunchImage:(NSString *)filename;

/**
 * Returns JSON formatted payload for the alert notification to
 * be sent to the APNS service.
 * 
 * @return NSString representing the JSON payload
 */
- (NSString *) toJSON;
@end
