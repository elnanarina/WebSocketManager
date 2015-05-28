//
//  Packet.m
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 26/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import "Packet.h"


@implementation Packet

@dynamic dataString;
@dynamic timeStamp;
@dynamic status;
@dynamic type;
@dynamic booleanSwitch;

- (NSString *)description {
    return [NSString stringWithFormat:@"Packet type: %@, dataString: %@, switch: %@, date: %@, status: %@",
            self.type, self.dataString, self.booleanSwitch, self.timeStamp, self.status];
}

@end
