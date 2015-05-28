/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import "KGAlertNotification.h"

/**
 * KGLocalizedAlertNotification is a concrete class that implements
 * KGAlertNotification protocol. Using KGLocalizedAlertNotification
 * class, an application developer can create sophisticated payloads
 * involving resource keys that are agnostic of the device locale.
 * When the notification is received by the device, iOS will
 * automatically resolve the resource key to a specific string from
 * the appropriate resource-bundle based on the device locale and 
 * format the parameters.
 */
@interface KGLocalizedAlertNotification : NSObject<KGAlertNotification>

/**
 * Creates an instance of KGLocalizedAlertNotification with resource
 * key for the alert message.
 *
 * @param locKey    NSString representing the resource key for the
 *                  alert message
 * @return id for the newly created instance of 
 *         KGLocalizedAlertNotification class
 */
- (id) initWithLocalizationKey:(NSString *)locKey;

/**
 * Creates an instance of KGLocalizedAlertNotification with resource
 * key for the alert message which includes type specifiers for 
 * formatting.
 *
 * @param locKey    NSString representing the resource key for the
 *                  alert message
 * @param locArgs   NSArray representing the resource keys to be
 *                  used to format the alert message
 * @return id for the newly created instance of 
 *         KGLocalizedAlertNotification class
 */
- (id) initWithLocalizationKey:(NSString *)locKey 
              localizationArgs:(NSArray *)locArgs;

/**
 * Creates an instance of KGLocalizedAlertNotification with resource
 * key for the alert message which includes type specifiers for 
 * formatting.
 *
 * @param locKey    NSString representing the resource key for the
 *                  alert message
 * @param locArgs   NSArray representing the resource keys to be
 *                  used to format the alert message
 * @param actionKey NSString representing the resource key for the
 *                  action button
 * @return id for the newly created instance of 
 *         KGLocalizedAlertNotification class
 */
- (id) initWithLocalizationKey:(NSString *)locKey 
              localizationArgs:(NSArray *)locArgs
                     actionKey:(NSString *)actionKey;

/**
 * Creates an instance of KGLocalizedAlertNotification with resource
 * key for the alert message which includes type specifiers for 
 * formatting.
 *
 * @param locKey    NSString representing the resource key for the
 *                  alert message
 * @param locArgs   NSArray representing the resource keys to be
 *                  used to format the alert message
 * @param actionKey NSString representing the resource key for the
 *                  action button
 * @param filename  NSString representing the image file name
 *
 * @return id for the newly created instance of 
 *         KGLocalizedAlertNotification class
 */
- (id) initWithLocalizationKey:(NSString *)locKey 
              localizationArgs:(NSArray *)locArgs
                     actionKey:(NSString *)actionKey 
                         image:(NSString *)filename;

/**
 * Returns the localization key of the alert message that will be
 * rendered when the remote notification is received from APNS
 * based on the device locale.
 * 
 * @return the resource key for the alert message
 */
- (NSString *) localizationKey;

/**
 * Sets the localization key of the alert message that will be
 * rendered when the notification is received from APNS based 
 * based on the device locale.
 *
 * @param key    NSString representing the resource key for the
 *               alert message
 */
- (void) setLocalizationKey:(NSString *)key;

/**
 * Returns NSArray of NSString objects representing the
 * names of the properties that the Gateway will use to
 * patch the payload.
 *
 * @return NSArray contain the resource keys for the properties
 *         that will be used to format the alert message
 */
- (NSArray *) localizationArgs;

/** 
 * Sets the NSArray of NSString objects representing the
 * names of the properties that the Gateway will use to
 * patch the payload before sending the payload to
 * to APNS.
 *
 * @param args    NSArray containing the resource keys for
 *                the properties that will be used to format
 *                the alert message
 */
- (void) setLocalizationArgs:(NSArray *)args;

@end
