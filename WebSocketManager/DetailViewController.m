//
//  DetailViewController.m
//  WebSocketManager
//
//  Created by Eugeniya Pervushina on 27/5/15.
//  Copyright (c) 2015 Eugeniya Pervushina. All rights reserved.
//

#import "DetailViewController.h"
#import "ViewController.h"

@interface DetailViewController ()

@property (assign, nonatomic) IBOutlet UITextView *textView;

@end

@implementation DetailViewController

#pragma mark -

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:YES];
    
    NSString *header = @"RECEIVED MESSAGE:";
    self.textView.text = header;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    
    [nc addObserver:self
           selector:@selector(showReceivedMessage:)
               name:ReceivedMessageDidChangeNotification
             object:nil];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - Notifications

- (void)showReceivedMessage:(NSNotification *)notification {
    
    NSData *data = [notification.userInfo objectForKey:ReceivedMessageUserInfoKey];
    
    NSString *message = nil;
    message = [NSString stringWithFormat:@"%@", data];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.textView.text = [NSString stringWithFormat:@"%@\n%@", self.textView.text, message];
        [self.textView scrollRangeToVisible:self.textView.selectedRange];
    });
}

@end
