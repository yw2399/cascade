/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_cascade_Client */

#ifndef _Included_io_cascade_Client
#define _Included_io_cascade_Client
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_cascade_Client
 * Method:    closeClient
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_io_cascade_Client_closeClient
  (JNIEnv *, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    createClient
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_createClient
  (JNIEnv *, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    getMembers
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_io_cascade_Client_getMembers
  (JNIEnv *, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    getShardMembers
 * Signature: (Lio/cascade/ServiceType;JJ)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_io_cascade_Client_getShardMembers
  (JNIEnv *, jobject, jobject, jlong, jlong);

/*
 * Class:     io_cascade_Client
 * Method:    setMemberSelectionPolicy
 * Signature: (Lio/cascade/ServiceType;JJLio/cascade/ShardMemberSelectionPolicy;)V
 */
JNIEXPORT void JNICALL Java_io_cascade_Client_setMemberSelectionPolicy
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    getMemberSelectionPolicy
 * Signature: (Lio/cascade/ServiceType;JJ)Lio/cascade/ShardMemberSelectionPolicy;
 */
JNIEXPORT jobject JNICALL Java_io_cascade_Client_getMemberSelectionPolicy
  (JNIEnv *, jobject, jobject, jlong, jlong);

/*
 * Class:     io_cascade_Client
 * Method:    getNumberOfShards
 * Signature: (Lio/cascade/ServiceType;J)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_getNumberOfShards
  (JNIEnv *, jobject, jobject, jlong);

/*
 * Class:     io_cascade_Client
 * Method:    putInternal
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_putInternal
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    getInternal
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;JZ)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_getInternal
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject, jlong, jboolean);

/*
 * Class:     io_cascade_Client
 * Method:    getInternalByTime
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;JZ)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_getInternalByTime
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject, jlong, jboolean);

/*
 * Class:     io_cascade_Client
 * Method:    removeInternal
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_removeInternal
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    listKeysInternal
 * Signature: (Lio/cascade/ServiceType;JZJJ)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_listKeysInternal
  (JNIEnv *, jobject, jobject, jlong, jboolean, jlong, jlong);

/*
 * Class:     io_cascade_Client
 * Method:    listKeysByTimeInternal
 * Signature: (Lio/cascade/ServiceType;JZJJ)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_listKeysByTimeInternal
  (JNIEnv *, jobject, jobject, jlong, jboolean, jlong, jlong);

/*
 * Class:     io_cascade_Client
 * Method:    createObjectPoolInternal
 * Signature: (Ljava/lang/String;Lio/cascade/ServiceType;ILio/cascade/ShardingPolicy;Ljava/util/Map;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_createObjectPoolInternal
  (JNIEnv *, jobject, jstring, jobject, jint, jobject, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    listObjectPools
 * Signature: ()Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_io_cascade_Client_listObjectPools
  (JNIEnv *, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    putAndForgetInternal
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_putAndForgetInternal
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    multiGetInternal
 * Signature: (Lio/cascade/ServiceType;JJLjava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_multiGetInternal__Lio_cascade_ServiceType_2JJLjava_nio_ByteBuffer_2
  (JNIEnv *, jobject, jobject, jlong, jlong, jobject);

/*
 * Class:     io_cascade_Client
 * Method:    multiGetInternal
 * Signature: (Ljava/nio/ByteBuffer;)J
 */
JNIEXPORT jlong JNICALL Java_io_cascade_Client_multiGetInternal__Ljava_nio_ByteBuffer_2
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
