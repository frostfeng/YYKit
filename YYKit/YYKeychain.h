//
//  YYKeychainManager.h
//  YYKit
//
//  Created by ibireme on 14-10-15.
//  Copyright (c) 2014 ibireme. All rights reserved.
//

#import <Foundation/Foundation.h>

@class YYKeychainItem;

/**
 A wrapper for system keychain API.
 
 The idea is stolen from [SSKeychain](https://github.com/soffes/sskeychain) 😏
 */
@interface YYKeychain : NSObject

#pragma mark - Convenient method for keychain
///=============================================================================
/// @name Convenient method for keychain
///=============================================================================

/**
 Returns the password for a given account and service, or `nil` if not found or
 an error occurs.
 
 @param serviceName The service for which to return the corresponding password.
 This value must not be nil.
 
 @param account The account for which to return the corresponding password.
 This value must not be nil.
 
 @param error   On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information. 
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Password string, or nil when not found or error occurs.
 */
+ (NSString *)getPasswordForService:(NSString *)serviceName account:(NSString *)account error:(__autoreleasing NSError **)error;

/**
 Deletes a password from the Keychain.
 
 @param serviceName The service for which to return the corresponding password.
 This value must not be nil.
 
 @param account The account for which to return the corresponding password.
 This value must not be nil.
 
 @param error   On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Weather success.
 */
+ (BOOL)deletePasswordForService:(NSString *)serviceName account:(NSString *)account error:(__autoreleasing NSError **)error;

/**
 Insert or update the password for a given account and service.
 
 @param password    The new password.
 
 @param serviceName The service for which to return the corresponding password.
 This value must not be nil.
 
 @param account The account for which to return the corresponding password.
 This value must not be nil.
 
 @param error   On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Weather success.
 */
+ (BOOL)setPassword:(NSString *)password forService:(NSString *)serviceName account:(NSString *)account error:(__autoreleasing NSError **)error;


#pragma mark - Full query for keychain (SQL-like)
///=============================================================================
/// @name Full query for keychain (SQL-like)
///=============================================================================

/**
 Insert an item into keychain.
 
 @discussion The service,account,password is required. If there's item exist
 already, an error occurs and insert fail.
 
 @param item  The item to insert.
 
 @param error On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Weather success.
 */
+ (BOOL)insertItem:(YYKeychainItem *)item error:(__autoreleasing NSError **)error;

/**
 Update item in keychain.
 
 @discussion The service,account,password is required. If there's no item exist
 already, an error occurs and insert fail.
 
 @param item  The item to insert.
 
 @param error On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Weather success.
 */
+ (BOOL)updateItem:(YYKeychainItem *)item error:(__autoreleasing NSError **)error;

/**
 Delete items from keychain.
 
 @discussion The service,account,password is required. If there's item exist
 already, an error occurs and insert fail.
 
 @param item  The item to update.
 
 @param error On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return Weather success.
 */
+ (BOOL)deleteItem:(YYKeychainItem *)item error:(__autoreleasing NSError **)error;

/**
 Find an item from keychain.
 
 @discussion The service,account is optinal. It returns only one item if there
 exist multi.
 
 @param item  The item for query.
 
 @param error On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return An item or nil.
 */
+ (YYKeychainItem *)selectOneItem:(YYKeychainItem *)item error:(__autoreleasing NSError **)error;

/**
 Find all items matches the query.
 
 @discussion The service,account is optinal. It returns all item matches by the
 query.
 
 @param item  The item for query.
 
 @param error On input, a pointer to an error object. If an error occurs,
 this pointer is set to an actual error object containing the error information.
 You may specify nil for this parameter if you do not want the error information.
 See `YYKeychainErrorCode`.
 
 @return An array of YYKeychainItem.
 */
+ (NSArray *)selectItems:(YYKeychainItem *)item error:(__autoreleasing NSError **)error;
@end




#pragma mark - Const

/**
 Error code in YYKeychain API.
 */
typedef NS_ENUM (NSUInteger, YYKeychainErrorCode) {
    YYKeychainErrorUnimplemented = 1, ///< Function or operation not implemented.
    YYKeychainErrorIO, ///< I/O error (bummers)
    YYKeychainErrorOpWr, ///< File already open with with write permission.
    YYKeychainErrorParam, ///< One or more parameters passed to a function where not valid.
    YYKeychainErrorAllocate, ///< Failed to allocate memory.
    YYKeychainErrorUserCanceled, ///< User canceled the operation.
    YYKeychainErrorBadReq, ///< Bad parameter or invalid state for operation.
    YYKeychainErrorInternalComponent, ///< Internal...
    YYKeychainErrorNotAvailable, ///< No keychain is available. You may need to restart your computer.
    YYKeychainErrorDuplicateItem, ///< The specified item already exists in the keychain.
    YYKeychainErrorItemNotFound, ///< The specified item could not be found in the keychain.
    YYKeychainErrorInteractionNotAllowed, ///< User interaction is not allowed.
    YYKeychainErrorDecode, ///< Unable to decode the provided data.
    YYKeychainErrorAuthFailed, ///< The user name or passphrase you entered is not.
};


/**
 When query to return the item's data, the error
 errSecInteractionNotAllowed will be returned if the item's data is not
 available until a device unlock occurs.
 */
typedef NS_ENUM (NSUInteger, YYKeychainAccessible) {
    YYKeychainAccessibleNone = 0, ///< no value
    
    /** Item data can only be accessed
     while the device is unlocked. This is recommended for items that only
     need be accesible while the application is in the foreground.  Items
     with this attribute will migrate to a new device when using encrypted
     backups. */
    YYKeychainAccessibleWhenUnlocked,
    
    /** Item data can only be
     accessed once the device has been unlocked after a restart.  This is
     recommended for items that need to be accesible by background
     applications. Items with this attribute will migrate to a new device
     when using encrypted backups.*/
    YYKeychainAccessibleAfterFirstUnlock,
    
    /** Item data can always be accessed
     regardless of the lock state of the device.  This is not recommended
     for anything except system use. Items with this attribute will migrate
     to a new device when using encrypted backups.*/
    YYKeychainAccessibleAlways,
    
    /** Item data can
     only be accessed while the device is unlocked. This class is only
     available if a passcode is set on the device. This is recommended for
     items that only need to be accessible while the application is in the
     foreground. Items with this attribute will never migrate to a new
     device, so after a backup is restored to a new device, these items
     will be missing. No items can be stored in this class on devices
     without a passcode. Disabling the device passcode will cause all
     items in this class to be deleted.*/
    YYKeychainAccessibleWhenPasscodeSetThisDeviceOnly,
    
    /** Item data can only
     be accessed while the device is unlocked. This is recommended for items
     that only need be accesible while the application is in the foreground.
     Items with this attribute will never migrate to a new device, so after
     a backup is restored to a new device, these items will be missing. */
    YYKeychainAccessibleWhenUnlockedThisDeviceOnly,
    
    /** Item data can
     only be accessed once the device has been unlocked after a restart.
     This is recommended for items that need to be accessible by background
     applications. Items with this attribute will never migrate to a new
     device, so after a backup is restored to a new device these items will
     be missing.*/
    YYKeychainAccessibleAfterFirstUnlockThisDeviceOnly,
    
    /** Item data can always
     be accessed regardless of the lock state of the device.  This option
     is not recommended for anything except system use. Items with this
     attribute will never migrate to a new device, so after a backup is
     restored to a new device, these items will be missing.*/
    YYKeychainAccessibleAlwaysThisDeviceOnly,
};

/**
 Whether the item in question can be synchronized.
 */
typedef NS_ENUM (NSUInteger, YYKeychainQuerySynchronizationMode) {
    
    /** Default, Don't care for synchonization  */
    YYKeychainQuerySynchronizationModeAny = 0,
    
    /** Do not synchronizable */
    YYKeychainQuerySynchronizationModeNo,
    
    /** To add a new item which can be synced to other devices, or to obtain 
     synchronizable results from a query*/
    YYKeychainQuerySynchronizationModeYes,
} NS_AVAILABLE_IOS (7_0);


#pragma mark - Item

/**
 Wrapper for keychain item/query.
 */
@interface YYKeychainItem : NSObject <NSCopying>

@property (nonatomic, copy) NSString *service; ///< kSecAttrService
@property (nonatomic, copy) NSString *account; ///< kSecAttrAccount
@property (nonatomic, copy) NSData *passwordData; ///< kSecValueData
@property (nonatomic, copy) NSString *password; ///< shortcut for `passwordData`
@property (nonatomic, copy) id <NSCoding> passwordObject; ///< shortcut for `passwordData`

@property (nonatomic, copy) NSString *label; ///< kSecAttrLabel
@property (nonatomic, copy) NSNumber *type; ///< kSecAttrType (FourCC)
@property (nonatomic, copy) NSNumber *creater; ///< kSecAttrCreator (FourCC)
@property (nonatomic, copy) NSString *comment; ///< kSecAttrComment
@property (nonatomic, copy) NSString *descr; ///< kSecAttrDescription
@property (nonatomic, readonly, copy) NSDate *modificationDate; ///< kSecAttrModificationDate
@property (nonatomic, readonly, copy) NSDate *creationDate; ///< kSecAttrCreationDate
@property (nonatomic, copy) NSString *accessGroup; ///< kSecAttrAccessGroup

@property (nonatomic, assign) YYKeychainAccessible accessible; ///< kSecAttrAccessible
@property (nonatomic, assign) YYKeychainQuerySynchronizationMode synchronizable NS_AVAILABLE_IOS(7_0); ///< kSecAttrSynchronizable

@end
