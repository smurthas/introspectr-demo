//
//  IRDetailViewController.h
//  IntrospectrTest
//
//  Created by Simon Murtha-Smith on 2/4/13.
//  Copyright (c) 2013 Simon Murtha-Smith. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface IRDetailViewController : UIViewController <UISplitViewControllerDelegate>

@property (strong, nonatomic) id detailItem;

@property (weak, nonatomic) IBOutlet UILabel *detailTitleLabel;
@property (weak, nonatomic) IBOutlet UILabel *detailDateLabel;
@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;

@end
