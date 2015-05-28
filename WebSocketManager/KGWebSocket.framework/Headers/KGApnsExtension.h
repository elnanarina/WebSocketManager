/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import "KGWebSocketExtension.h"

/**
 * KGApnsExtension class represents WebSocket extension "x-kaazing-apns-notify" 
 * that is used ONLY if the application wishesto receive out-of-band remote 
 * notifications from the Apple Push Notification service(APNs).
 * 
 * In order to receive out-of-band notifications, the application developer
 * should enable this extension by adding it to the set of enabled extensions 
 * and set it either using method [KGWebSocketFactory setDefaultEnabledExtensions:] 
 * or method [KGWebSocket setEnabledExtensions:].
 *
 * The KGApnsExtension defines the following extension parameters:
 * 
 * - bundleId
 * - deviceToken
 * 
 * *For Example*
 *
 *  *In order to enable extension on the KGWebSocket created from KGWebSocketFactory*
 *      <pre><code>
 *      NSString *apnsExtensionName = [[KGApnsExtension apnsExtension] name];
 *      NSArray  *enabledExtensions = [NSArray arrayWithObjects:apnsExtensionName, nil];
 *      [webSocket setEnabledExtensions:enabledExtensions];
 *      </pre></code>
 *  *In order to enable extension on the KGWebSocketFactory*
 *      <pre><code>
 *      NSString *apnsExtensionName = [[KGApnsExtension apnsExtension] name];
 *      NSArray  *enabledExtensions = [NSArray arrayWithObjects:apnsExtensionName, nil];
 *      [webSocketFactory setDefaultEnabledExtensions:enabledExtensions];
 *      </pre></code>
 * It is the responsibility of the application developer to specify the required 
 * parameters of this extension - bundleId and deviceToken.
 *
 * *For example*
 *
 *  *In order to set value of deviceToken and bundleId using KGWebSocket instance created from KGWebSocketFactory*
 *      <pre><code>
 *      // assuming device token and bundle id are stored in variables deviceToken and 
 *      // bundleId respectively
 *      [webSocket setEnabledParameter:[KGApnsExtension deviceToken] value:deviceToken];
 *      [webSocket setEnabledParameter:[KGApnsExtension bundleId] value:bundleId];
 *      </pre></code>
 *  *It can also be set at the KGWebSocketFactory which will be inherited by all KGWebSocket
 *   instances created from the factory. If APNs extension is enabled at the factory level and the
 *   value of the parameters are set at the factory as shown below, all the KGWebSocket instance created 
 *   from the factory will inherit the enabled extension as well as parameter values.*
 *      <pre><code>
 *      [webSocketFactory setDefaultParameter:[KGApnsExtension deviceToken] value:deviceToken];
 *      [webSocketFactory setDefaultParameter:[KGApnsExtension bundleId] value:bundleId];
 *      </pre></code>
 */
@interface KGApnsExtension : KGWebSocketExtension

/**
 * Returns the instance of KGApnsExtension. It is a definition object which 
 * the application developer does not need to initialize. 
 * It is initialize implicitly for use.
 */
+ (KGApnsExtension *) apnsExtension;

#pragma mark Extension Parameters
/**
 * Returns the KGwebSocketParameter instance that represents the Bundle Id. It is a 
 * definition object which is initialized implictly.
 *
 * If the KGApnsExtension is enabled, the application developer should provide the value 
 * of this parameter.
 *
 * @warning *Important:* The value of this parameter set using method [KGWebSocket setEnabledParameter:value:] or
 *                       [KGWebSocketFactory setDefaultParameter:value:] should be of type NSString
 *
 */
+ (KGWebSocketExtensionParameter *) bundleId;

/**
 * Returns the KGwebSocketParameter instance that represents the Device Token. It is a
 * definition object which is initialized implictly.
 *
 * If the KGApnsExtension is enabled, the application developer should provide the value
 * of this parameter.
 *
 * @warning *Important:* The value of this parameter set using method [KGWebSocket setEnabledParameter:value:] or
 *                       [KGWebSocketFactory setDefaultParameter:value:] should be of type NSData
 *
 */
+ (KGWebSocketExtensionParameter *) deviceToken;

@end