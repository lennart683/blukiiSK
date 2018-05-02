//
//  SmartKey.h
//  blukiiSK.framework
//
//  Created by Kevin Rombach on 11.02.15.
//
//  Copyright (c) 2015 Steinbeis-Transferzentrum Institute of Signal
//  Processing and embedded Systems  (ISPES).
//  All rights reserved.

#ifndef blukiiSK_SmartKey_h
#define blukiiSK_SmartKey_h

/**
 *  blukii SmartKey's are available in different packages. Small round,
 *  large round or pen style. The values in SmartKeyPackages representing
 *  and the value stored in 'SmartKey.case' equates to the case of the SmartKey.
 */
typedef NS_ENUM(NSInteger,SmartKeyCaseTypes){
    /**
     *  Represents a SmartKey in the small round case
     */
    SmartKeyCaseTypeSmall,
    /**
     *  Represents a SmartKey in the tower
     */
    SmartKeyCaseTypeHigh,
    /**
     *  Represents a SmartKey in the pen case
     */
    SmartKeyCaseTypePen,
    /**
     *  Represents a SmartKey in the large round case
     */
    SmartKeyCaseTypeLarge,
    /**
     *  Represents a SmartKey in the maxi battery size case
     */
    SmartKeyCaseTypeMaxi,
    /**
     *  The case type is currently not available
     */
    SmartKeyCaseTypeNotAvailable,
};

/**
 *  Describes the SmartKey's different blukii hardware versions.
 */
typedef NS_ENUM(NSInteger,SmartKeyHardwareTypes){
    /**
     * blukii Hardware Version 1010-004
     */
    SmartKeyHardware_1010_004,
    /**
     * blukii Hardware Version 1011-005
     */
    SmartKeyHardware_1011_005,
    /**
     * blukii Hardware Version 1010-005
     */
    SmartKeyHardware_1010_005,
    /**
     * blukii Hardware Version 1011-006
     */
    SmartKeyHardware_1011_006,
    /**
     * blukii Hardware Version not available
     */
    SmartKeyHardware_NotAvailable = 0xFF
};

/**
 *  Configuration states which are possible for the linked SmartKey.
 */
typedef NS_ENUM(uint8_t,SmartKeyConfigStates){
    /**
     *  No configuration set.
     */
    SmartKeyConfigStatesNoConfig,
    /**
     *  Convenience-Mode configuration active.
     */
    SmartKeyConfigStatesConvenience,
    /**
     *  Pairing-Mode configuration active.
     */
    SmartKeyConfigStatesPairing,
    /**
     *  Secure-Mode configuration prepared. That's the case when the encrytion key
     *  is currently set and the write of the encrypted pairing key is expected.
     */
    SmartKeyConfigStatesSecurePrepared,
    /**
     *  Secure-Mode configuration active.
     */
    SmartKeyConfigStatesSecure,
};

/**
 *  Status codes relating to the authentication process in the SKManager class.
 */
typedef NS_ENUM(NSInteger,SmartKeyButtonStates){
    /**
     * The button has been released in secure mode while connected.
     */
    SmartKeySecureButtonReleased,
    /**
     * The button has been pressed in secure mode while connected.
     */
    SmartKeySecureButtonPressed,
    /**
     *  The button has been released in pairing mode while connected or in any mode
     *  during advertising.
     */
    SmartKeyButtonReleased,
    /**
     *  The button has been pressed in pairing mode while connected or in any mode
     *  during advertising.
     */
    SmartKeyButtonPressed,
    /**
     * The encrypted button data was invalid in secure mode.
     */
    SmartKeyButtonError,
    /**
     * The hardware of the SmartKey doesn't support the button functionality.
     */
    SmartKeyButtonNotAvailable = 0xFF
};



/** This class is the iOS representation of blukiiSmartKey's. There is no public method available for SmartKeys.
    Its only possible to get SmartKey object instances from the SKManager.
 */
@interface SmartKey : NSObject

/**---------------------------------------------------------------------------------------
 * @name SmartKey properties
 *  ---------------------------------------------------------------------------------------
 */

/** The firmware version of the SmartKey represented as Integer. Example: 6100 */
@property (readonly) NSInteger versionValue;

/** The firmware version of the SmartKey represented as String. Example: 6.1.0.0 */
@property (readonly) NSString * versionString;

/** The identifier of the SmartKey */
@property (readonly) NSString * ID;

/** Represents the last determined rssi value */
@property (readonly) int rssi;

/** The current battery level of the SmartKey */
@property (readonly) uint8_t batteryLevel;

/**
 *  SmartKey in  service mode. The SmartKey stays in this operating mode
 *  until during the first 30 seconds after a power on reset. In this mode
 *  its possible to reset the SmartKey's configuration and its also possible
 *  to initate a Firmware Update in this mode.
 */
@property (readonly) BOOL service;
 /**
 *Shows if the SmartKey is ready to use with the current framework version.
 *True if the SmartKey comply with the firmware version requirements, false if not 
*/
@property (readonly) BOOL supported;

/**
 Describes the case type of the SmartKey
 @see SmartKeyCaseTypes
 */
@property (readonly) SmartKeyCaseTypes caseType;

/**
 Describes the hardware type of the SmartKey
 @see SmartKeyHardwareTypes
 */
@property (readonly) SmartKeyHardwareTypes hardware;
/**
 Describes the hardware type of the SmartKey as String. Example: 1010-003
 @see SmartKeyHardwareTypes
 */
@property (readonly) NSString * hardwareString;

/**
 Describes the configuration state of the SmartKey.
 @see SmartKeyConfigStates
 */
@property (readonly) SmartKeyConfigStates config;

/**
 Represents the timestamp of the last received advertising data of 
 the linked SmartKey. If its not discovered since the last restart of the 
 application the timestamp will be nil.
 */
@property (readonly) NSDate * lastSeen;

@end


#endif