/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "KGChallengeHandler.h"

@class KGChallengeHandler;

/**
 * A challenge response contains a character array representing the response to the server,
 * and a reference to the next challenge handler to handle any further challenges for the request.
 *
 */
@interface KGChallengeResponse : NSObject

/**
 * Constructor from a set of credentials to send to the server in an 'Authorization:' header
 * and the next challenge handler responsible for handling any further 401 challenges for the request.
 *
 * @param credentials a set of credentials to send to the server in an 'Authorization:' header
 * @param nextChallengeHandler the next challenge handler responsible for handling any further 401 challenges for the request.
 */
-(id) initWithCredentials:(NSString*) credentials nextChallengeHandler:(KGChallengeHandler *)nextChallengeHandler;

/**
 * Return a set of credentials to send to the server in an 'Authorization:' header.
 *
 * @return a set of credentials to send to the server in an 'Authorization:' header.
 */
-(NSString*) credentials;

/**
 * Establish the credentials for this response.
 *
 * @param credentials the credentials to be used for this challenge response.
 */
-(void) setCredentials:(NSString*) credentials;

/**
 * Return the next challenge handler responsible for handling any further 401 challenges for the request.
 *
 * @return the next challenge handler responsible for handling any further 401 challenges for the request.
 */
-(KGChallengeHandler *) nextChallengeHandler;

/**
 * Establish the next challenge handler responsible for handling any further 401 challenges for the request.
 *
 * @param nextChallengeHandler the next challenge handler responsible for handling any further 401 challenges for the request.
 */
-(void) setNextChallengeHandler:(KGChallengeHandler *) nextChallengeHandler;

/**
 * Clear the credentials of this response.
 * <p/>
 * Calling this method once the credentials have been communicated to the network layer
 * protects credentials in memory.
 */
-(void) clearCredentials;

@end
