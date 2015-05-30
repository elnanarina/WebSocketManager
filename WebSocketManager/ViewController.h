//
//  ViewController.h
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 26/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString *const ReceivedMessageDidChangeNotification;
extern NSString *const ReceivedMessageUserInfoKey;

@interface ViewController : UIViewController <UITextFieldDelegate>

@property (assign, nonatomic) IBOutlet UITextField *urlTextField;
@property (assign, nonatomic) IBOutlet UITextField *messageTextField;
@property (assign, nonatomic) IBOutlet UIButton *connectionButton;
@property (assign, nonatomic) IBOutlet UIButton *sendButton;
@property (assign, nonatomic) IBOutlet UITextView *textView;
@property (assign, nonatomic) IBOutlet UISwitch *booleanSwitch;
@property (assign, nonatomic) IBOutlet UISegmentedControl *segmentedControl;
@property (retain, nonatomic) NSData *receivedMessage;

- (void)applicationDidEnterBackground;
- (void)applicationWillEnterForeground;

@end
