//
//  SKCommon.h
//  blukiiSK.framework
//
//  Created by Kevin Rombach on 11.02.15.
//
//  Copyright (c) 2015 Steinbeis-Transferzentrum Institute of Signal
//  Processing and embedded Systems  (ISPES).
//  All rights reserved.


#ifndef blukiiSK_SKCommon_h
#define blukiiSK_SKCommon_h

/**
 *  Helper class for the configuration in secure mode.
 *
 *  It has no public properties or methods. To create a SKPairingKey
 *  look here: [SKCommon createPairingKey:]
 *
 */
@interface SKPairingKey : NSObject

@end

/**
 *  Some general methods which can help to use some of the SKManager methods 
 *  correctly.
 */
@interface SKCommon : NSObject

/**
 *  Create a PairingKey for the configuration of the SmartKey.
 *
 *  @param value A value in the range: 000000-999999
 *
 *  @return Returns nil if the value is outside of the allowed range, otherwise 
 *  it returns the SKPairingKey instance.
 */
+(SKPairingKey*)createPairingKey:(UInt32)value;


/**
 * Used to get the version string of the used blukiiSK.framework.
 *  @return The framework version as string
*/
+(NSString*)blukiiSKVersionString;

/**
 *  AES-Encrypt data with a given encryption key.
 *
 *  @param plain        The plain data which should be encrypted.
 *  @param hexStringKey The encryption key as Hex-String with at least 16Bytes 
 *  (32Characters)
 *
 *  @return The return value contains the encrypted data. If the hexStringKey is
 *  too short, or if it contains unpermitted characters the return value will be
 *  nil.
 */
+(NSData*)encryptData:(NSData *)plain withKey:(NSString *)hexStringKey;

/**
 *  AES-Decrypt data with a given encryption key.
 *
 *  @param enc          The encrypted data which should be decrypted.
 *  @param hexStringKey The decryption key as Hex-String with at least 16Bytes
 *  (32Characters)
 *
 *  @return The return value contains the dectypted data. If the hexStringKey is
 *  too short, or if it contains unpermitted characters the return value will be
 *  nil.
 */
+(NSData*)decryptData:(NSData *)enc withKey:(NSString *)hexStringKey;

/**
 *  Get n random bytes.
 *
 *  @param len          The number of random bytes
 *
 *  @return A NSData instance with len random bytes.
 */
+(NSData*)getRandomBytes:(UInt8)len;


@end

#endif
