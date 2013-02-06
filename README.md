# Add the Singly SDK


# IRAppDelegate.m

    #import <SinglySDK/SinglySDK.h>

in `didFinishLaunchingWithOptions` add:

    SinglySession *session = [SinglySession sharedSession];
    session.clientID = @"762883abd63e45410d45b1a8ebf2d1f6";
    session.clientSecret = @"e2696129e1e9dd9219ea2e986c033906";

    [session startSessionWithCompletion:^(BOOL ready)  {
    }];


# IRMasterViewController.m:

add:

    #import <SinglySDK/SinglySDK.h>

and:

    - (void) doLogin:(NSString *)serviceName
    {
        SinglyService *service = [SinglyService serviceWithIdentifier:serviceName];
        service.delegate = self;
        [service requestAuthorizationFromViewController:self];
    }

to `dismissAndLogin` add:

    [self doLogin:[segue identifier]];

add:

    - (void)doSearch:(NSString *)text
    {
        SinglyRequest *request = [SinglyRequest requestWithEndpoint:@"types/photos" andParameters:[[NSDictionary alloc] initWithObjectsAndKeys:text, @"q", nil]];

        [NSURLConnection sendAsynchronousRequest:request
                                           queue:[NSOperationQueue mainQueue]
                               completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
                                   NSArray *all = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
                                   [self updateResults:all];
                                   [[self tableView] reloadData];
                               }];
    }

in the iterator of `updateResults` add:

    [_objects addObject:[object valueForKey:@"oembed"]];

to `cellForRowAtIndexPath` add:

    cell.textLabel.text = [_objects[indexPath.row] valueForKey:@"title"];

to `searchBarSearchButtonClicked` add:

    [self doSearch:searchBar.text];

# IRDetailViewController

in `configureView` add:

    self.detailTitleLabel.text = [self.detailItem valueForKey:@"title"];

    NSURL *url = [NSURL URLWithString:[self.detailItem valueForKey:@"url"]];
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    [self.image loadRequest:requestObj];
