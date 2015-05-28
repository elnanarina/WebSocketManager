/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * An immutable object representing the challenge presented by the server when the client accessed
 * the URI represented by a location.
 * <p/>
 * According to [RFC 2617](http://tools.ietf.org/html/rfc2617#section-1.2),
 * <pre>
 *     challenge   = auth-scheme 1*SP 1#auth-param
 * </pre>
 * so we model the authentication scheme and parameters in this class.
 * <p/>
 * This class is also responsible for detecting and adapting the `Application Basic`
 * and `Application Negotiate` authentication schemes into their `Basic` and `Negotiate`
 * counterpart authentication schemes.
 */
@interface KGChallengeRequest : NSObject

/**
 * Constructor from the protected URI location triggering the challenge,
 * and an entire server-provided 'WWW-Authenticate:' string.
 *
 * @param location  the protected URI location triggering the challenge
 * @param challenge an entire server-provided 'WWW-Authenticate:' string
 */
- (id) initWithLocation:(NSString*)location challenge:(NSString*)challenge;

/**
 * Return the protected URI the access of which triggered this challenge as a `NSString*`.
 * <p/>
 * For some authentication schemes, the production of a response to the challenge may require
 * access to the location of the URI triggering the challenge.
 *
 * @return the protected URI the access of which triggered this challenge as a `NSString*`
 */
- (NSString *) location;

/**
 * Return the authentication scheme with which the server is challenging.
 *
 * @return the authentication scheme with which the server is challenging.
 */
- (NSString *) authenticationScheme;

/**
 * Return the string after the space separator, not including the authentication scheme nor the space itself,
 * or `nil` if no such string exists.
 *
 * @return the string after the space separator, not including the authentication scheme nor the space itself,
 * or `nil` if no such string exists.
 */
- (NSString *) authenticationParameters;

- (NSString *) description;

@end
