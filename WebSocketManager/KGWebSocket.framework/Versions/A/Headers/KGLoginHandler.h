/**
 * Copyright (c) 2007-2013, Kaazing Corporation. All rights reserved.
 */

#import <Foundation/Foundation.h>

/**
 * A login handler is responsible for obtaining credentials from an arbitrary source.
 *
 * Login Handlers can be associated with one or more KGChallengeHandler
 * objects, to ensure that when a Challenge Handler requires credentials for a KGChallengeResponse,
 * the work is delegated to a KGLoginHandler.
 *
 * At client configuration time, a KGLoginHandler can be associated with a KGChallengeHandler as follows:
 
      `MyLoginHandler* loginHandler = [[MyLoginHandler alloc] init];
       KGBasicChallengeHandler* challengeHandler = [KGBasicChallengeHandler create];
       [challengeHandler setLoginHandler:loginHandler];
 
       @interface MyLoginHandler : KGLoginHandler
       @end
 
       @implementation MyLoginHandler {
           int counter;
       }
 
       - (id)init {
           NSLog(@"[MyLoginHandler init]");
           self = [super init];
           if (self) {
               counter = 0;
           }
           return self;
       }
 
       -(NSURLCredential*) credentials {
           NSLog(@"providing incorrect credential");
           if (counter++ < 3) {
               return [[NSURLCredential alloc] initWithUser:@"joe" password:@"NOT - welcome"
                      persistence:NSURLCredentialPersistenceNone];
           }
          else {
              counter = 0;
              return nil;
           }
       }
       @end`
 
 */
@interface KGLoginHandler : NSObject

/**
 * Gets the password authentication credentials from an arbitrary source.
 *
 * @return the password authentication obtained.
 */
- (NSURLCredential*)credentials;

@end
