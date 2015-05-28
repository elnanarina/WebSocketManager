/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import "KGAlertNotification.h"

/**
 * KGSimpleAlertNotification is a concrete class that conforms to the
 * KGAlertNotification protocol. As the name indicates, it can be used
 * to create JSON payload for simple alert notifications that do not 
 * require localization. This class does provide the ability to 
 * localize the action button's label and the ability to render an 
 * image as part of the alert dialog.
 *
 * @see KGAlertNotification
 * @see KGNotificationPayload
 */
@interface KGSimpleAlertNotification : NSObject<KGAlertNotification>

/**
 * Creates an instance of KGSimpleAlertNotification with just the
 * body of the alert that includes the message. 
 *
 * @param  body    NSString representing the alert message
 * @return id   instance of KGSimpleAlertNotification class
 */
- (id) initWithBody:(NSString *)body;

/**
 * Creates an instance of KGSimpleAlertNotification with the
 * body of the alert and the resource key for the action button's 
 * label.
 *
 * @param  body            NSString representing the alert message
 * @param  actionLocKey    NSString representing the resource key
 *                         for the action button's label
 * @return id  instance of KGSimpleAlertNotification class
 */
- (id) initWithBody:(NSString *)body
          actionKey:(NSString *)actionLocKey;

/**
 * Creates an instance of KGSimpleAlertNotification with the
 * body of the alert, the resource key for the action button's 
 * label, and the image for the alert dialog.
 *
 * @param  body            NSString representing the alert message
 * @param  actionLocKey    NSString representing the resource key
 *                         for the action button's label
 * @param  filename        NSString representing image filename
 * @return id  instance of KGSimpleAlertNotification class
 */
- (id) initWithBody:(NSString *)body
          actionKey:(NSString *)actionLocKey 
              image:(NSString *)filename;

/**
 * Returns the body of the alert message.
 *
 * @return NSString representing the body of the message
 */
- (NSString *) body;

/**
 * Sets the body of the alert message.
 *
 * @param body    NSString representing the alert message
 */
- (void) setBody:(NSString *)body;

@end
