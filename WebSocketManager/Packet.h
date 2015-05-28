//
//  Packet.h
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 26/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface Packet : NSManagedObject

@property (nonatomic, retain) NSString * dataString;
@property (nonatomic, retain) NSDate * timeStamp;
@property (nonatomic, retain) NSNumber * status;
@property (nonatomic, retain) NSString * type;
@property (nonatomic, retain) NSNumber * booleanSwitch;

@end