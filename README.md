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
        SinglyRequest *request = [SinglyRequest requestWithEndpoint:@"types/all_feed" andParameters:[[NSDictionary alloc] initWithObjectsAndKeys:text, @"q", nil]];

        [NSURLConnection sendAsynchronousRequest:request
                                           queue:[NSOperationQueue mainQueue]
                               completionHandler:^(NSURLResponse *response, NSData *data, NSError *error) {
                                   NSArray *all = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
                                   [self updateResults:all];
                                   [[self tableView] reloadData];
                               }];
    }

in the iterator of `updateResults` add:

    NSMutableDictionary *newObject = [[NSMutableDictionary alloc] init];
    NSDictionary *oembed = [object valueForKey:@"oembed"];
    id title = [oembed valueForKey:@"title"];
    [newObject setValue:title forKey:@"title"];

    id descr = [oembed valueForKey:@"text"];
    if (!descr) descr = [oembed valueForKey:@"description"];
    if (!descr) descr = [oembed valueForKey:@"url"];
    [newObject setValue:descr forKey:@"description"];

    [newObject setValue:[object valueForKey:@"at"] forKey:@"at"];

    [_objects addObject:newObject];

to `cellForRowAtIndexPath` add:

    NSDate *object = _objects[indexPath.row];

    cell.textLabel.text = [object valueForKey:@"title"];
    cell.detailTextLabel.text = [object valueForKey:@"description"];

to `searchBarSearchButtonClicked` add:

    [self doSearch:searchBar.text];

# IRDetailViewController

in `configureView` add:

    self.detailTitleLabel.text = [self.detailItem valueForKey:@"title"];
    self.detailDescriptionLabel.text = [self.detailItem valueForKey:@"description"];
    self.detailDateLabel.text = [formatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:([[self.detailItem valueForKey:@"at"] floatValue] / 1000)]];
