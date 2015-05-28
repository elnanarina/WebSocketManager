//
//  DataManager.h
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 27/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class Packet;

@interface DataManager : NSObject

@property (readonly, retain, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (readonly, retain, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, retain, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;

+ (DataManager *)sharedManager;
- (void)insertObject:(Packet *)packet;

- (void)saveContext;
- (NSURL *)applicationDocumentsDirectory;

@end