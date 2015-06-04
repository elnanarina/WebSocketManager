//
//  ViewController.m
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 26/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import "ViewController.h"
#import "DataManager.h"
#import "Packet.h"
#import <KGWebSocket/WebSocket.h>
#import "Reachability.h"

NSString *const ReceivedMessageDidChangeNotification = @"ReceivedMessageDidChangeNotification";
NSString *const ReceivedMessageUserInfoKey = @"ReceivedMessageUserInfoKey";

static NSString* types[] = {@"XML", @"JSON", @"BINARY"};

@interface ViewController () {
    Reachability *_reachabilityInfo;
}

@property (retain, nonatomic) KGWebSocket *webSocket;
@property (retain, nonatomic) KGWebSocketFactory *factory;
@property (retain, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (assign, nonatomic) BOOL reconnect;
@property (assign, nonatomic) BOOL isConnected;

@end

@implementation ViewController


#pragma mark - Setter

- (void)setReceivedMessage:(id)receivedMessage {
    _receivedMessage = receivedMessage;
    
    NSDictionary *userInfo = [NSDictionary dictionaryWithObject:receivedMessage
                                                         forKey:ReceivedMessageUserInfoKey];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:ReceivedMessageDidChangeNotification
                                                        object:nil
                                                      userInfo:userInfo];
}

#pragma mark - Getter
- (NSManagedObjectContext *)managedObjectContext {
    
    if (!_managedObjectContext) {
        _managedObjectContext = [[DataManager sharedManager]managedObjectContext];
    }
    return _managedObjectContext;
}

#pragma mark -

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    [self updateUI:NO];
    
    
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    
    [nc addObserver:self
           selector:@selector(contextObjectsChangedNotification:)
               name:NSManagedObjectContextDidSaveNotification
             object:self.managedObjectContext];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reachabilityChanged:)
                                                 name:kReachabilityChangedNotification
                                               object:_reachabilityInfo];
    [_reachabilityInfo startNotifier];
}

- (void)dealloc {
    [_reachabilityInfo release];
    [_receivedMessage release];
    [_webSocket release];
    [_factory release];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

#pragma mark - Actions
- (IBAction)send:(id)sender {
    
    Packet *packet = [NSEntityDescription insertNewObjectForEntityForName:@"Packet"
                                                   inManagedObjectContext:self.managedObjectContext];
    packet.dataString = self.messageTextField.text;
    packet.booleanSwitch = [NSNumber numberWithBool:self.booleanSwitch.on];
    packet.type = types[self.segmentedControl.selectedSegmentIndex];
    
    [[DataManager sharedManager] insertObject:packet];
}


- (IBAction)switchOn:(UISwitch *)sender {
    
    if([sender isOn]){
        // Switch is ON
        self.booleanSwitch.on = YES;
    } else{
        // Switch is OFF
        self.booleanSwitch.on = NO;
    }
}

- (IBAction)connectionButton:(id)sender {
    
    if ([self.connectionButton.titleLabel.text  isEqual: @"Connect"]) {
        NSString *url = self.urlTextField.text;
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self createAndEstablishwebSocketConnection:url];
                [self updateUI:YES];
            });
    } else {
        [self log:@"CLOSE"];
        @try {
            [_webSocket close];
            [self updateUI:NO];
        }
        @catch (NSException *exception) {
            [self log:[exception reason]];
        }
    }
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    if (textField == self.messageTextField || textField == self.urlTextField) {
        [textField resignFirstResponder];
    }
    return YES;
}

#pragma mark - Public Methods

- (void)applicationDidEnterBackground {
    // when application moves to background,
    // close the open webSocket connection, set reconnect to true
    if (self.webSocket != nil && [self.webSocket readyState] == KGReadyState_OPEN) {
        [self.webSocket close];
        self.reconnect = YES;
    }
    else {
        self.reconnect = NO;
    }
}

- (void)applicationWillEnterForeground {
    //if reconnect equals to true, reconect the webSocket
    if (self.webSocket != nil && [self.webSocket readyState] == KGReadyState_OPEN) {
        [self updateUI:YES];
    }
    else {
        [self updateUI:NO];
        if (self.reconnect) {
            NSString *url = self.urlTextField.text;
            
            //connection was open when application enter background, reconnect!
            [self createAndEstablishwebSocketConnection:url];
        }
    }
}

#pragma mark - Private Methods

- (void) createAndEstablishwebSocketConnection:(NSString *)location {
    @try {
        Reachability *reachability = [Reachability reachabilityForInternetConnection];
        NetworkStatus internetStatus = [reachability currentReachabilityStatus];
        
        if (internetStatus != NotReachable) {
            [self log:@"CONNECTING"];
            
            // Create KGwebSocketFactory
            self.factory = [KGWebSocketFactory createWebSocketFactory];
            
            // Create KGwebSocket from the KGwebSocketFactory
            NSURL   *url = [NSURL URLWithString:location];
            self.webSocket = [self.factory createWebSocket:url];
            
            // Setup webSocket events callbacks
            // The application developer can use a delegate based approach as well.
            [self setupwebSocketListeners];
            [self.webSocket connect];
            
            [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
            
            NSLog(@"True connection");
        } else {
            NSLog(@"Warning: No internet connection");
            //there-is-no-connection warning
        }
    }
    @catch (NSException *exception) {
        [self log:[exception reason]];
        [self updateUI:NO];
    }
}

-(void) setupwebSocketListeners {
    
    ViewController* ref = self;
    
    // Attach a block to execute when webSocket connection is established.
    // This indicates that the connection is ready to send and receive data.
    self.webSocket.didOpen = ^(KGWebSocket* webSocket) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [ref log:@"CONNECTED"];
            
            NSFetchRequest *request = [[NSFetchRequest alloc] initWithEntityName:@"Packet"];
            
            NSError *requestError = nil;
            NSArray *packets = [ref.managedObjectContext executeFetchRequest:request error:&requestError];
            
            for (Packet *packet in packets) {
                if ([packet.status  isEqual: @NO]) {
                    
                    // Message is sent
                    [ref sendMessage:packet];
                    
                    [packet setValue:@YES forKey:@"status"];
                }
            }
            
            [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
            ref.isConnected = YES;
            [ref updateUI:YES];
            
            // Save the context
            NSError *error = nil;
            if (![ref.managedObjectContext save:&error]) {
                NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
            }
            [request release];
        });
    };
    
    // The block to execute when a message is received from the server.
    // The data 'is' either UTF8-String (type: NSString) or binary (type: NSData)
    self.webSocket.didReceiveMessage = ^(KGWebSocket* webSocket, id data) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [ref log:[NSString stringWithFormat:@"RECEIVED MESSAGE: %@", data]];
            ref.receivedMessage = data;
        });
    };
    
    // The block to execute when an error occurs.
    self.webSocket.didReceiveError = ^(KGWebSocket* webSocket, NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [ref log:[NSString stringWithFormat:@"ERROR: %@", [error localizedFailureReason]]];
            
            [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
            ref.isConnected = NO;
        });
    };
    
    // The block to execute when the connection is closed
    self.webSocket.didClose = ^(KGWebSocket* webSocket, NSInteger code, NSString* reason, BOOL wasClean) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [ref log:[@"CLOSED" stringByAppendingFormat:@"(%u): Reason: %@", code, reason]];
            ref.isConnected = NO;
            [ref updateUI:NO];
        });
    };
}


- (void)sendMessage:(Packet *)packet {
    @try {
        id dataToSend;
        NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
        [dateFormat setDateFormat:@"HH:mm:ss"];
        
        NSDictionary *dictionary = @{@"dataString"  : packet.dataString,
                                     @"switch": packet.booleanSwitch,
                                     @"date"  : [dateFormat stringFromDate:packet.timeStamp],
                                     @"type"  : packet.type };
        
        if ([packet.type isEqualToString:@"XML"]) {
            NSData *data = [NSPropertyListSerialization dataWithPropertyList:dictionary
                                                                      format:NSPropertyListXMLFormat_v1_0
                                                                     options:0
                                                                       error:nil];
            NSString* xml = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];

            [self log:[NSString stringWithFormat:@"SEND MESSAGE: %@", xml]];
            dataToSend = xml;
            
//            xml = nil;
        } else if ([packet.type isEqualToString:@"JSON"]) {
            
            NSError* error;
            NSData* jsonData = [NSJSONSerialization dataWithJSONObject:dictionary
                                                               options:NSJSONWritingPrettyPrinted
                                                                 error:&error];
            
            NSString* json = [[[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding] autorelease];
            [self log:[NSString stringWithFormat:@"SEND MESSAGE: %@", json]];
            dataToSend = json;
            
//            json = nil;
        } else if ([packet.type isEqualToString:@"BINARY"]) {
            NSData *binaryData = [NSKeyedArchiver archivedDataWithRootObject:dictionary];
            [self log:[NSString stringWithFormat:@"SEND MESSAGE: %@", binaryData]];
            dataToSend = binaryData;
        }
        
        Reachability *reachability = [Reachability reachabilityForInternetConnection];
        NetworkStatus internetStatus = [reachability currentReachabilityStatus];
        
        if (internetStatus != NotReachable) {
            dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                [self.webSocket send:dataToSend];
            });
            
            NSLog(@"True connection");
        } else {
            NSLog(@"Warning: No internet connection");
            //there-is-no-connection warning
        }
        
        [dateFormat release];
    }
    @catch (NSException *exception) {
        [self log:[exception reason]];
    }
}

- (void) log:(NSString *)msg {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSString *text = msg;
        NSString *log = [self.textView text];
        
        if ((log != nil) && ([log length] > 0)) {
            
            text = [NSString stringWithFormat:@"%@\n%@", [self.textView text], msg];
        }
        
        if ([[self.textView text] length] > 5000) {
            text = [text substringFromIndex:3000];
        }
        
        [self.textView setText:text];
        [self.textView scrollRangeToVisible:NSMakeRange([self.textView.text length], 0)];
    });
}


- (void) updateUI:(BOOL)connectStatus {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (connectStatus) {
            [self.connectionButton setTitle:@"Disconnect" forState:UIControlStateNormal];
            self.urlTextField.enabled = NO;
            self.urlTextField.backgroundColor = [UIColor lightGrayColor];
            self.messageTextField.enabled = YES;
            self.messageTextField.backgroundColor = [UIColor whiteColor];
            self.sendButton.enabled = YES;
            self.sendButton.alpha = 1.0f;
            
        } else {
            [self.connectionButton setTitle:@"Connect" forState:UIControlStateNormal];
            self.urlTextField.enabled = YES;
            self.urlTextField.backgroundColor = [UIColor whiteColor];
            self.messageTextField.enabled = NO;
            self.messageTextField.backgroundColor = [UIColor lightGrayColor];
            self.sendButton.enabled = NO;
            self.sendButton.alpha = 0.5f;
        }
    });
}

#pragma mark - Notifications

- (void)contextObjectsChangedNotification:(NSNotification *)notification {
    
    NSSet *insertedObjects = [[notification userInfo] objectForKey:NSInsertedObjectsKey];
    
    if (self.isConnected) {
        for (Packet *packet in insertedObjects) {
            if ([packet.status  isEqual: @NO]) {
                
                // Message is sent
                [self sendMessage:packet];
                [packet setValue:@YES forKey:@"status"];
                
                // Save the context
                NSError *error = nil;
                if (![self.managedObjectContext save:&error]) {
                    NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
                }
            }
        }
    }
}

- (void)reachabilityChanged: (NSNotification* )note
{
    Reachability* curReach = [note object];
    NetworkStatus status = curReach.currentReachabilityStatus;
    
    switch (status) {
        case NotReachable:
            break;
        case ReachableViaWiFi:
            break;
        case ReachableViaWWAN:
            break;
    }
}

@end