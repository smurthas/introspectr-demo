//
//  SinglySession.h
//  SinglySDK
//
//  Copyright (c) 2012-2013 Singly, Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>

@class SinglyService;

/*!
 *
 * Notification raised when a session's profiles have been updated.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString * const kSinglySessionProfilesUpdatedNotification = @"com.singly.notifications.SessionProfilesUpdatedNotification";

/*!
 *
 * Notification raised when a service has been applied to the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
static NSString * const kSinglyServiceAppliedNotification = @"com.singly.notifications.ServiceAppliedNotification";

/*!
 *
 * Notification raised when the device contacts have been synced with the
 * Singly API.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
 **/
static NSString * const kSinglyContactsSyncedNotification = @"com.singly.notifications.ContactsSyncedNotification";

/*!
 *
 * Manages the current session state.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@interface SinglySession : NSObject

/// ----------------------------------------------------------------------------
/// @name Accessing the Shared Session
/// ----------------------------------------------------------------------------

/*!
 *
 * Access the shared session object
 *
 * This is the preferred way to use the SinglySession and you should only create
 * a new instance if you must use multiple sessions inside one app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
+ (SinglySession *)sharedSession;

/// ----------------------------------------------------------------------------
/// @name Configuring the Session
/// ----------------------------------------------------------------------------

/*!
 *
 * The client ID to be used while authenticating against the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *clientID;

/*!
 *
 * The client secret to be used while authenticating against the Singly API.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *clientSecret;

/// ----------------------------------------------------------------------------
/// @name Managing the Session
/// ----------------------------------------------------------------------------

/*!
 *
 * The access token that will be used for all Singly API requests.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accessToken;

/*!
 *
 * Requests your Access Token from the Singly API for the given code. The code
 * is returned in the Redirect URI after you have successfully authenticated
 * with a service via Singly.
 *
 * @param code The code to use.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)requestAccessTokenWithCode:(NSString *)code;

/*!
 *
 * Requests your Access Token from the Singly API for the given code. The code
 * is returned in the Redirect URI after you have successfully authenticated
 * with a service via Singly. Once complete, the given completion handler will
 * be called.
 *
 * @param code The code to use.
 *
 * @param completionHandler The block to call once the operation has completed.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)requestAccessTokenWithCode:(NSString *)code
                        completion:(void (^)(NSString *accessToken, NSError *error))completionHandler;

/*!
 *
 * The account ID associated with the current access token.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (copy) NSString *accountID;

/*!
 *
 * Denotes whether or not the session is in a ready state (i.e. authorized and
 * valid).
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (readonly) BOOL isReady;

/*!
 *
 * Get the session in a state that is ready to make API calls.
 *
 * @param completionHandler  The block to run when the check is complete. It
 *                           will be passed a `BOOL` stating whether or not the
 *                           the session is ready.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)startSessionWithCompletion:(void (^)(BOOL))completionHandler;

/*!
 *
 * Get the session in a state that is ready to make API calls.
 *
 * @param completionHandler  The block to run when the check is complete. It
 *                           will be passed a `BOOL` stating whether or not the
 *                           the session is ready.
 *
 * @see startSessionWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)startSessionWithCompletionHandler:(void (^)(BOOL))completionHandler DEPRECATED_ATTRIBUTE;

/*!
 *
 * Resets the current session by clearing the access token, account id and
 * loaded profiles.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)resetSession;

/// ----------------------------------------------------------------------------
/// @name Managing Session Profiles
/// ----------------------------------------------------------------------------

/*!
 *
 * A combined profile for the user derived from normalized data from all of the
 * services to which they are connected.
 *
 * This property is populated while updating profiles.
 *
 * @see updateProfiles
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (readonly) NSDictionary *profile;

/*!
 *
 * Profiles of the services that the account has connected. Will return until
 * there is a valid session.
 *
 * This property is populated while updating profiles.
 *
 * @see updateProfiles
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
 * TODO Rename profiles to serviceProfiles
 *
**/
@property (readonly) NSDictionary *profiles;

/*!
 *
 * Updates the profiles by connecting to the Singly API and fetching the latest
 * version.
 *
 * A notification (`kSinglySessionProfilesUpdatedNotification`) is posted once
 * the update has completed.
 *
 * @see updateProfilesWithCompletion:
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)updateProfiles;

/*!
 *
 * Updates the profiles by connecting to the Singly API and fetching the latest
 * version and call the specified `completionHandler` once the update has
 * completed.
 *
 * In addition to calling the specified completion handler, a notification
 * (`kSinglySessionProfilesUpdatedNotification`) is posted once the update has
 * completed.
 *
 * @param completionHandler  The block to call once the profiles have been
 *                           updated.
 *
 * @see updateProfiles
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)updateProfilesWithCompletion:(void (^)(BOOL))completionHandler;

/// ----------------------------------------------------------------------------
/// @name Managing Services
/// ----------------------------------------------------------------------------

/*!
 *
 * Allows you to associate a service with an existing access token to the Singly
 * session.
 *
 * @param serviceIdentifier  The identifier of the service (e.g. "facebook",
 *                           "twitter", etc).
 *
 * @param token              The access token to associate with the session.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (void)applyService:(NSString *)serviceIdentifier withToken:(NSString *)token;

/// ----------------------------------------------------------------------------
/// @name Syncing Device Contacts
/// ----------------------------------------------------------------------------

/*!
 *
 * Denotes whether or not the device contacts are currently being synced with
 * the Singly API.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
@property (readonly) BOOL isSyncingDeviceContacts;

/*!
 *
 * Syncs the device contacts with the Singly API.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)syncDeviceContacts;

/*!
 *
 * Syncs the device contacts with the Singly API and calls the specified
 * `completionHandler` once the sync has completed.
 *
 * In addition to calling the specified completion handler, a notification
 * (`kSinglyContactsSyncedNotification`) is posted once the sync has completed.
 *
 * @param completionHandler  The block to call once the sync has been completed.
 *
 * @available Available in Singly iOS SDK 1.1.0 and later.
 *
**/
- (void)syncDeviceContactsWithCompletion:(void (^)(BOOL, NSArray *))completionHandler;

/// ----------------------------------------------------------------------------
/// @name Handling App Launches by URL
/// ----------------------------------------------------------------------------

/*!
 *
 * The service the is currently being authorized. This is necessary for
 * integration with 3rd party apps installed on the device so that we know which
 * service has been authorized after our app is relaunched by the authorizing
 * app.
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
@property (strong) SinglyService *authorizingService;

/*!
 *
 * Handles app launches by oauth redirection requests and maps them appropriately
 * based on the service.
 *
 * @param url The redirection URL that should be handled
 *
 * @available Available in Singly iOS SDK 1.0.0 and later.
 *
**/
- (BOOL)handleOpenURL:(NSURL *)url;

@end
