//
//  SKManager.h
//  blukiiSK.framework
//
//  Created by Kevin Rombach on 11.02.15.
//
//  Copyright (c) 2015 Steinbeis-Transferzentrum Institute of Signal
//  Processing and embedded Systems  (ISPES).
//  All rights reserved.


#ifndef SK_MANAGER
#define SK_MANAGER

#import <Foundation/Foundation.h>
#import "SKCommon.h"
#import "SmartKey.h"



/**
 *  Status codes relating to the state of the SKManagers.
 */
typedef NS_ENUM(NSInteger,SKManagerStates){
    /**
     * The SKManager is ready.
     */
    SKManagerStatesReady,
    /**
     * The iOS bluetooth needs to be turned on.
     */
    SKManagerStatesNeedsBluetooth
};


/**
 *  Reasons for a disconnect from the linked SmartKey
 *
 */
typedef NS_ENUM(NSInteger,SKManagerDisconnectReasons){
    /**
     *  Connection lost unexpected. There are lots of reasons why this can occur.
     *  For example: Battery level too low, unusual large distance between the SmartKey and the iOS-Device
     *  or reflexions/packet loss on the bluetooth transmission path.
     */
    SKManagerConnectionLost,
    /**
     *  The connected SmartKey has canceled the connection.
     */
    SKManagerSmartKeyCanceledConnection,
    /**
     *  The iOS-Device canceled the connection due to the call of [SKManager disconnectFromSmartKey]
     */
    SKManageriOSCanceledConnection,
};


/**
 *  Status codes for some methods in the SKManager class
 */
typedef NS_ENUM(NSInteger,SKManagerStatusCodes){
    /**
     *  A operation succeded
     */
    SKManagerStatusCodesSuccess,
    /**
     *  No SmartKey linked, but the requested operation needs a linked SmartKey
     */
    SKManagerStatusCodesNoSmartKeyLinked,
    /**
     *  The linked SmartKey is out of range
     */
    SKManagerStatusCodesLinkedSmartKeyNotLocated,
    /**
     *  The linked SmartKey has been found in the range of the iOS-Device but its not connected
     */
    SKManagerStatusCodesLinkedSmartKeyNotConnected,
    /**
     *  The linked SmartKey is connected, but not ready yet for communication
     */
    SKManagerStatusCodesLinkedSmartKeyNotReady,
    /**
     *  The linked SmartKey is connected, correct configurated and ready for communication
     */
    SKManagerStatusCodesLinkedSmartKeyReady,
    /**
     *  The linked SmartKey's firmware version is out of date. 
     */
    SKManagerStatusCodesLinkedSmartNeedsUpdate,
    /**
     *  Indicates that the requested operation has failed.
     */
    SKManagerStatusCodesOperationFailed,
    /**
     * Another operation which is blocking the SKManager for further oprations
     * is still in progress.
     */
    SKManagerStatusCodesIsBusy,
};


/**
 *  Status codes relating to the authentication process in the SKManager class.
 */
typedef NS_ENUM(NSInteger,SKManagerAuthenticationStates){
    /**
     * The authentication with the SmartKey succeeded
     */
    SKManagerAuthenticationSuccessful,
    /**
     * The pairing which has been triggered during the authentication process
     * failed.
     */
    SKManagerAuthenticationPairingFailed,
    /**
     * The authentication with the SmartKey failed! You should think about 
     * resetting the security settings to protect the app against a potential attacker
     */
    SKManagerAuthenticationFailed
};

/**
 *  The SKManagerDelegate protocol defines methods that a delegate of the global
 *  available SKManager object can optionally implement to handle the
 *  communication with a blukiiSmartKey and some other generall processes of 
 *  the SKManager.
 */
@protocol SKManagerDelegate<NSObject>

@optional


/**---------------------------------------------------------------------------------------
 * @name Generall
 *  ---------------------------------------------------------------------------------------
 */

/**
 * Invoked due to the change of the iOS bluetooth availability.
 *
 * @param state The new state of the SKManager.
 */
-(void)SKManagerDidUpdateState:(SKManagerStates)state;

/**
 * Invoked due to the execution of a reset security settings request or if any 
 * internal security dependent operation has failed.
 *
 * @see [SKManager resetSecuritySettings]
 */
-(void)SKManagerDidResetSecuritySettings;

/**---------------------------------------------------------------------------------------
 * @name Searching for SmartKeys
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Invoked when a SmartKey search request from the SKManager has been completed
 *
 *  @param keys Array with the located SmartKey's. They are represented as 
 *  objects from the SmartKey class. If no SmartKey has been located during the 
 *  last request interval the array will be empty.
 *
 *  @see [SKManager requestSmartKeysWithTimeout:repeated:]
 *  @see [SKManager linkSmartKey:]:
 *  @see SKManagerDidFoundLinkedSmartKey:
 *
 *  @discussion The SKManager invokes this method when the related request 
 *  interval is done. If a SmartKey is already linked as personal SmartKey due
 *  to the call of linkSmartKey:, it will no longer be available in the keys 
 *  array.
 */
-(void)SKManagerDidReceiveSmartKeys:(NSArray*)keys;
/**
 *  Invoked when a the SmartKey that is linked as personal SmartKey has been
 *  found during a request interval.
 *
 *  @param linkedKey The linked SmartKey representation.
 *
 *  @see [SKManager requestSmartKeysWithTimeout:repeated:]
 *  @see [SKManager linkSmartKey:]:
 *
 *  @discussion This method indicates if the personal SmartKey was found during
 *  the search interval which is triggered by 
 *  [SKManager requestSmartKeysWithTimeout:repeated:].
 */
-(void)SKManagerDidFindLinkedSmartKey:(SmartKey*)linkedKey;

/**---------------------------------------------------------------------------------------
 * @name Communicaton state
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Invoked due to the execution of a connection request.
 *
 *  @param successful true: The connection is established successful.
 *  false: The connection could not be established.
 * 
 *  @see [SKManager connectToSmartKey:]
 */
-(void)SKManagerDidConnectToSmartKey:(BOOL)successful;
/**
 *  Invoked when the connection to the SmartKey has been disconnected or
 *  interrupted.
 *
 *  @param reason The reason for the disconnect as SKManagerDisconnectReasons 
 *  value
 *
 *  @see [SKManager disconnectFromSmartKey]
 */
-(void)SKManagerDidDisconnectFromSmartKey:(SKManagerDisconnectReasons)reason;
/**
 *  Invoked when the linked SmartKey is connected and ready for further 
 *  communication.
 *
 * @see [SKManager connectToSmartKey:]
 * @see [SKManager linkSmartKey:]
 *
 * @discussion When this method is invoked, the linked SmartKey will be ready for
 *              further communication. Its recommended to wait for the invocation
 *              of this method after a call of the connectToSmartKey: Method.
 */
-(void)SKManagerLinkedSmartKeyReady;

/**
 *  Invoked due to the execution of SmartKey configuration reset request.
 *
 *  @param successful Indicate whether the reset has been done successfully or
 *  not. If it is succeeded the value will be true. If the reset fails the value
 *  will be false.
 *
 *  @see [SKManager resetConfig]
 *
 *  @discussion Resetting the SmartKey configuration is only possible when 
 *  the reset config command is sent  within the <b><u>first 30 seconds after
 *  a power on reset </u></b> of the
 *  SmartKey. (e.g. due to a battery replacement).
 */
-(void)SKManagerDidResetSmartKeyConfig:(BOOL)successful;

/**---------------------------------------------------------------------------------------
 * @name Update values
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Invoked due to the execution of a read config request.
 *
 *  @param config The config state of the linked SmartKey as SmartKeyConfigStates
 *  value
 *
 *  @see [SKManager readConfigState]
 */
-(void)SKManagerDidUpdateConfigState:(SmartKeyConfigStates)config;

/**
 *  Invoked due to the execution of a read battery level request.
 *
 *  @param level The battery level of the linked SmartKey represented as a
 *  uint8_t value: 0% - 100%
 *
 *  @see [SKManager readBatteryLevel]
 */
-(void)SKManagerDidUpdateBatteryLevel:(uint8_t)level;


/**---------------------------------------------------------------------------------------
 * @name Configuration
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Invoked when the configuration which has been triggered by the invocation
 *  of one of the configuration methods is done.
 *
 *  @param successful Indicates whether the configuration has been done successfully or
 *  not. If its succeeded the value is true otherwise, if the configuration has failed,
 *  the value will be false.
 *
 *  @see [SKManager configurateConvenienceMode]
 *  @see [SKManager configuratePairingModeWithPairingKey:]
 *  @see [SKManager configurateSecureModeWithPairingKey:]
 */
-(void)SKManagerDidFinishConfiguration:(BOOL)successful;

/**---------------------------------------------------------------------------------------
 * @name Authentication
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Invoked when the SKManager successfully authenticated with the linked SmartKey.
 *
 * @param state The new authentication state
 *
 * @discussion The authentication is different with the three security levels.
 *
 *  - Convenience-Mode: The authentication is successful when the SKManager located
 *                      the SmartKey as result of a requestSmartKey: search interval.
 *  - Pairing-Mode:     In this mode the authentication must be triggered by the SKManager
 *                      method initiateAuthenticationChallenge. If the authenticationChallenge
 *                      succeed the authentication will be granted here.
 *  - Secure-Mode:      In this mode the authentication is a process of multiple steps.
 *                      It must be triggered by the SKManager method initiateAuthenticationChallenge.
 *                      If the authenticationChallenge succeed the authentication will be granted here.
 *
 * @see [SKManager requestSmartKeysWithTimeout:repeated:]
 * @see [SKManager initiateAuthenticationChallenge]
 * @see [SKManager linkSmartKey:]
 * @see SKManagerAuthenticationStates
 */
-(void)SKManagerDidUpdateAuthenticationState:(SKManagerAuthenticationStates)state;

/**
 *  This method will be invoked when a SmartKey with wrong encryption keys 
 *  or other configuration flags like the linked one has been detected.
 *
 *  @param sk Representation of the modified SmartKeys
 *
 *  @discussion If this method is invoked the SKManager still has resetted all the
 *  security settings too through the invocation of [SKManager resetSecuritySettings]
 */
-(void)SKManagerDidDetectModifiedSmartKey:(SmartKey*)sk;

@end

/**
 *
 * The purpose of the SKManager class is to handle the communication with the 
 * blukii SmartKey's. It is impelemented according to the singelton design 
 * pattern and the application can get the shared object with the corresponding
 * method [SKManager sharedManager]. Its highly recommended to implement the 
 * SKManagerDelegate protocol for a class which uses the SKManager. Otherwise
 * that class will not get any feedback about the communication with the
 * SmartKey or anything else what is triggered by the SKManager.
 *
 */
@interface SKManager : NSObject

/**-----------------------------------------------------------------------------
 * @name Properties
 *  ----------------------------------------------------------------------------
 */
/** This is the delegate which receives the delegate method calls for the 
 * SKManagerDelegate protocol. 
 */
@property id <SKManagerDelegate> delegate;
/**
 * Represents the personal SmartKey, which is linked to the SKManager. nil if no
 * SmartKey is linked.
 *
 *@see SmartKey
 */
@property SmartKey * linkedKey;

/**-----------------------------------------------------------------------------
 * @name Get the SKManager Object
 *  ----------------------------------------------------------------------------
 */

/**
 * This method returns the shared SKManager object. At first call it will
 * instantiate and return the object which will be returned each repeated call.
 *
 */
+(id)sharedManager;

/**-----------------------------------------------------------------------------
 * @name Generall
 *  ----------------------------------------------------------------------------
 */

/**
 *  The invocation of this method forces a reset of the complete security 
 *  settings in the SKManager.
 *
 *  @discussion Its possible, in case of an security dependent error, that the 
 *  SKManager will invoke this method independent e.g. during a configuration process
 *  or if a modified SmartKey has been detected.
 *
 *  @see [SKManagerDelegate SKManagerDidResetSecuritySettings]
 */
-(void)resetSecuritySettings;


/**-----------------------------------------------------------------------------
 * @name Search and link
 *  ----------------------------------------------------------------------------
 */

/**
 *  Trigger a new SmartKey search request to search for near located SmartKey's.
 *
 *  @param ms  Interval in milliseconds which determines how long the
 *  search request will last.
 *
 *  @param repeat Indicates whether the request should repeat (true) or not 
 *  (false).
 *
 *  @discussion As a result of the request the SKManager will invoke
 *  SKManagerReceivedSmartKeys: when the time in ms is expired.
 *  Requesting SmartKey's is not possible when the SKManager has an activ
 *  connection to the linked SmartKey. In that case the invocation of
 *  requestSmartKeysWithTimeout:repeated: has no effect and the delegate method
 *  will not be called.
 *
 *  @return True if the request has been triggered, false if the SKManager has 
 *  an activ connection.
 *
 *  @see [SKManagerDelegate SKManagerDidReceiveSmartKeys:]
 *  @see [SKManagerDelegate SKManagerDidFindLinkedSmartKey:]
 *  @see cancleSmartKeyRequest
 */
-(BOOL)requestSmartKeysWithTimeout:(int)ms repeated:(bool)repeat;

/**
 *  Immediately stop a pending SmartKey search request which has been started
 *  with requestSmartKeysWithTimeout:repeated:.
 *
 *  @see requestSmartKeysWithTimeout:repeated:
 */
-(void)cancleSmartKeyRequest;

/**
 *  This method links a SmartKey to the SKManager. That means that every 
 *  followed operation which needs a linked SmartKey and is triggered from the
 *  SKManager will use this SmartKey as personal SmartKey until 
 *  resetSecuritySettings has been called or until a security depented operation
 *  failed.
 *
 *  @param sk The SmartKey object which will be linked to the SKManager
 *
 *  @return There are the following possible SKManagerStatusCodes for the return
 *  value:
 *
 *  - SKManagerStatusCodesSuccess -> The SmartKey has become linked
 *  - SKManagerStatusCodesOperationFailed -> Another SmartKey is already linked
 *  to the SKManager. Its possible to delete the linked SmartKey through a
 *  security settings reset.
 *
 * @see resetSecuritySettings
 */
-(SKManagerStatusCodes)linkSmartKey:(SmartKey*)sk;


/**---------------------------------------------------------------------------------------
 * @name Communication
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Sends a connection request to the SmartKey.
 *
 *  @param powerSaving true: Power-Saving active, false: Power-Saving inactiv
 *
 *  @return There are the following possible SKManagerStatusCodes for the return
 *  value:
 *
 *  - SKManagerStatusCodesSuccess -> The connection request was successful
 *  - SKManagerStatusCodesOperationFailed -> The SmartKey is not connectable or
 *  not located currently
 *
 *  @discussion When the linked SmartKey doesn't accept the request within the
 *  next 5 seconds after the connection request is set, the connection delegate
 *  method will be invoked as failed.
 *
 *  @see [SKManagerDelegate SKManagerDidConnectToSmartKey:]
 */
-(SKManagerStatusCodes)connectToSmartKey:(BOOL)powerSaving;

/**
 *  Forces a reconnect if the linked SmartKey is currently connected.
 *
 *  @return If the reconnect has been initiated successfully the return value will
 *  be SKManagerStatusCodesSuccess. Otherwise it returns the correspondent
 *  SKManagerStatusCodes value
 *
 *  @see [SKManagerDelegate SKManagerDidDisconnectFromSmartKey:]
 *  @see [SKManagerDelegate SKManagerDidConnectToSmartKey:]
 */
-(SKManagerStatusCodes)reconnectSmartKey;

/**
 *  Forces a disconnect from the linked SmartKey.
 *
 *  @see [SKManagerDelegate SKManagerDidDisconnectFromSmartKey:]
 */
-(void)disconnectFromSmartKey;

/**
 *  Returns the current connection status of the linked SmartKey.
 *
 *  @return There are the following possible SKManagerStatusCodes for the return
 *  value:
 *
 *  - SKManagerStatusCodesNoSmartKeyLinked
 *  - SKManagerStatusCodesLinkedSmartKeyNotConnected
 *  - SKManagerStatusCodesLinkedSmartKeyNotReady
 *  - SKManagerStatusCodesLinkedSmartKeyReady
 */
-(SKManagerStatusCodes)connectionStatus;

/**
 *  Initiate a update for the config state of the linked SmartKey.
 *
 *  @return If the update request has been initiated successfully the return
 *  value will be SKManagerStatusCodesSuccess. Otherwise it returns the 
 *  correspondent SKManagerStatusCodes value
 *
 *  @see [SKManagerDelegate SKManagerDidUpdateConfigState:]
 */
-(SKManagerStatusCodes)readConfigState;

/**
 *  Initiate a update for the battery level of the linked SmartKey.
 *
 *  @return If the update request has been initiated successfully the return 
 *  value will be SKManagerStatusCodesSuccess. Otherwise it returns the 
 *  correspondent SKManagerStatusCodes value.
 *
 *  @see [SKManagerDelegate SKManagerDidUpdateBatteryLevel:]
 */
-(SKManagerStatusCodes)readBatteryLevel;

/**-----------------------------------------------------------------------------
 * @name Configuration
 *  ----------------------------------------------------------------------------
 */

/**
 *  This method tries to start a configuration process for the
 *  linked SmartKey. If the linked SmartKey is currently in the Service-Mode 
 *  it can be configured with this method as SmartKey with the security
 *  state: Convenience.
 *
 *  @return If the configuration has been initiated successfully the
 *  return value will be SKManagerStatusCodesSuccess. Otherwise it returns the 
 *  correspondent SKManagerStatusCodes value.
 *
 *  @discussion The SKManager will invoke SKManagerConfigurationDone: when the
 *  configuration process has been done successfully or if the timeout which is
 *  about 20 seconds will running out before.
 *
 *  @see [SKManagerDelegate SKManagerDidFinishConfiguration:]
 */
-(SKManagerStatusCodes)configurateConvenienceMode;

/**
 *  This method tries to start a configuration process for the linked
 *  SmartKey. If the linked SmartKey is currently in the Service-Mode 
 *  it can be configured with this method as SmartKey with the security state: Pairing.
 *
 *  @param key The pairing key which will be set on the SmartKey if the
 *  configuration process succeeds.
 *
 *  @discussion The SKManager will invoke the SKManagerConfigurationDone: method when the
 *  configuration process has been done successfully or if the timeout which is
 *  about 20 seconds will running out before.
 *
 *  @return If the configuration has been initiated successfully the
 *  return value will be SKManagerStatusCodesSuccess. Otherwise it returns the
 *  correspondent SKManagerStatusCodes value.
 *
 *  @see [SKManagerDelegate SKManagerDidFinishConfiguration:]
 *  @see [SKCommon createPairingKey:]
 */
-(SKManagerStatusCodes)configuratePairingModeWithPairingKey:(SKPairingKey*)key;

/**
 *  This method tries to start a configuration process for the linked
 *  SmartKey. If the linked SmartKey is currently in the Service-Mode it can 
 *  be configured with this method as SmartKey with the security state: Secure.
 *
 *  @param key The pairing key which will be set on the SmartKey if the
 *  configuration process succeeds.
 *
 *  @discussion The SKManager will invoke the SKManagerConfigurationDone: method when the
 *  configuration process has been done successfully or if the timeout which is 
 *  about 20 seconds will running out before.
 *
 *  @return If the configuration has been initiated successfully the
 *  return value will be SKManagerStatusCodesSuccess. Otherwise it returns the
 *  correspondent SKManagerStatusCodes value.
 *
 *  @see [SKManagerDelegate SKManagerDidFinishConfiguration:]
 *  @see [SKCommon createPairingKey:]
 */
-(SKManagerStatusCodes)configurateSecureModeWithPairingKey:(SKPairingKey*)key;

/**
 *  Try to send the command which forces a resets of the security configuration
 *  on the SmartKey.
 *
 *  @discussion Resetting the SmartKey's configuration is only possible
 *  if the resetConfig method will be sent within the <b><u>first 30 seconds
 *  after a power on reset</u></b> of the SmartKey.(e.g due to a battery replacement).
 *  After a succeeded reset the SmartKey needs a new configuration before it can 
 *  be used furthermore. The corresponding delegate method will inform about the
 *  result of the request.
 *
 *  @see [SKManagerDelegate SKManagerDidResetSmartKeyConfig:]
 *
 *  @return If the reset config request has been initiated successfully the
 *  return value will be SKManagerStatusCodesSuccess. Otherwise it returns the
 *  correspondent SKManagerStatusCodes value
 */
-(SKManagerStatusCodes)resetConfig;


/** ---------------------------------------------------------------------------------------
 * @name Authentication
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  This method tries to initiate a authentication challenge with the linked 
 *  SmartKey.
 *
 *  @discussion The authentication challenge can only be initiated if the linked
 *  SmartKey is configurated complete and correctly in secure mode.
 *
 *  @return If the initiation of the challenge is successful the return value 
 *  will be SKManagerStatusCodesSuccess. Otherwise it returns the correspondent 
 *  SKManagerStatusCodes value
 *
 *  @see [SKManagerDelegate SKManagerDidUpdateAuthenticationState:]
 */
-(SKManagerStatusCodes)initiateAuthenticationChallenge;

@end

#endif
