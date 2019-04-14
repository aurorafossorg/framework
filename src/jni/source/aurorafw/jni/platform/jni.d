/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 1996 Netscape Communications Corporation.
Copyright (C) 1996, 2013, Oracle and/or its affiliates.
Copyright (C) 2006 The Android Open Source Project.
Copyright (C) 2018-2019 Aurora Free Open Source Software.

This file is part of the Aurora Free Open Source Software. This
organization promote free and open source software that you can
redistribute and/or modify under the terms of the GNU Lesser General
Public License Version 3 as published by the Free Software Foundation or
(at your option) any later version approved by the Aurora Free Open Source
Software Organization. The license is available in the package root path
as 'LICENSE' file. Please review the following information to ensure the
GNU Lesser General Public License version 3 requirements will be met:
https://www.gnu.org/licenses/lgpl.html .

Alternatively, this file may be used under the terms of the GNU General
Public License version 3 or later as published by the Free Software
Foundation. Please review the following information to ensure the GNU
General Public License requirements will be met:
https://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .

This file has bindings for an existing code, part of Netscape's Java Runtime
Interface implementation, Java Native Interface implementation, from Oracle
Corporation and/or The Android Open Source Project implementation.

More information about The Android Open Source Project at
android.googlesource.com .
 */

module aurorafw.jni.platform.jni;

/// TODO: add documentation from android source

import core.stdc.stdarg;

extern (C):
@system:
nothrow:
@nogc:

/*
 * JNI Types
 */

alias int jint;
alias byte jbyte;
alias long jlong;

alias ubyte jboolean;
alias ushort jchar;
alias short jshort;
alias float jfloat;
alias double jdouble;

alias jint jsize;

class _jobject {}
class _jclass : _jobject {}
class _jthrowable : _jobject {}
class _jstring : _jobject {}
class _jarray : _jobject {}
class _jbooleanArray : _jarray {}
class _jbyteArray : _jarray {}
class _jcharArray : _jarray {}
class _jshortArray : _jarray {}
class _jintArray : _jarray {}
class _jlongArray : _jarray {}
class _jfloatArray : _jarray {}
class _jdoubleArray : _jarray {}
class _jobjectArray : _jarray {}

alias _jobject jobject;
alias _jclass jclass;
alias _jthrowable jthrowable;
alias _jstring jstring;
alias _jarray jarray;
alias _jbooleanArray jbooleanArray;
alias _jbyteArray jbyteArray;
alias _jcharArray jcharArray;
alias _jshortArray jshortArray;
alias _jintArray jintArray;
alias _jlongArray jlongArray;
alias _jfloatArray jfloatArray;
alias _jdoubleArray jdoubleArray;
alias _jobjectArray jobjectArray;

alias jobject jweak;

union jvalue
{
	jboolean z;
	jbyte b;
	jchar c;
	jshort s;
	jint i;
	jlong j;
	jfloat f;
	jdouble d;
	jobject l;
}

struct _jfieldID;
alias _jfieldID* jfieldID;

struct _jmethodID;
alias _jmethodID* jmethodID;

/* Return values from jobjectRefType */
enum _jobjectType
{
	JNIInvalidRefType,
	JNILocalRefType,
	JNIGlobalRefType,
	JNIWeakGlobalRefType
}

alias _jobjectType jobjectRefType;

/*
 * jboolean constants
 */

enum
{
	JNI_FALSE,
	JNI_TRUE
}

/*
 * possible return values for JNI functions.
 */

enum JNI_OK = 0; /* success */
enum JNI_ERR = -1; /* unknown error */
enum JNI_EDETACHED = -2; /* thread detached from the VM */
enum JNI_EVERSION = -3; /* JNI version error */
enum JNI_ENOMEM = -4; /* not enough memory */
enum JNI_EEXIST = -5; /* VM already created */
enum JNI_EINVAL = -6; /* invalid arguments */

/*
 * used in ReleaseScalarArrayElements
 */
enum JNI_COMMIT = 1; /* copy content, do not free buffer */
enum JNI_ABORT = 2; /* free buffer w/o copying back */

/*
 * used in RegisterNatives to describe native method name, signature,
 * and function pointer.
 */

struct JNINativeMethod
{
	const(char)* name;
	const(char)* signature;
	void* fnPtr;
}

/*
 * JNI Native Method Interface.
 */

alias JNIEnv_ JNIEnv;
alias JavaVM_ JavaVM;

struct JNINativeInterface_
{
	void* reserved0;
	void* reserved1;
	void* reserved2;
	void* reserved3;
	jint function(JNIEnv*) GetVersion;
	jclass function(JNIEnv*, const(char)*, jobject, const(jbyte)*, jsize) DefineClass;
	jclass function(JNIEnv*, const(char)*) FindClass;
	jmethodID function(JNIEnv*, jobject) FromReflectedMethod;
	jfieldID function(JNIEnv*, jobject) FromReflectedField;
	jobject function(JNIEnv*, jclass, jmethodID, jboolean) ToReflectedMethod;
	jclass function(JNIEnv*, jclass) GetSuperclass;
	jboolean function(JNIEnv*, jclass, jclass) IsAssignableFrom;
	jobject function(JNIEnv*, jclass, jfieldID, jboolean) ToReflectedField;
	jint function(JNIEnv*, jthrowable) Throw;
	jint function(JNIEnv*, jclass, const(char)*) ThrowNew;
	jthrowable function(JNIEnv*) ExceptionOccurred;
	void function(JNIEnv*) ExceptionDescribe;
	void function(JNIEnv*) ExceptionClear;
	void function(JNIEnv*, const(char)*) FatalError;
	jint function(JNIEnv*, jint) PushLocalFrame;
	jobject function(JNIEnv*, jobject) PopLocalFrame;
	jobject function(JNIEnv*, jobject) NewGlobalRef;
	void function(JNIEnv*, jobject) DeleteGlobalRef;
	void function(JNIEnv*, jobject) DeleteLocalRef;
	jboolean function(JNIEnv*, jobject, jobject) IsSameObject;
	jobject function(JNIEnv*, jobject) NewLocalRef;
	jint function(JNIEnv*, jint) EnsureLocalCapacity;
	jobject function(JNIEnv*, jclass) AllocObject;
	jobject function(JNIEnv*, jclass, jmethodID, ...) NewObject;
	jobject function(JNIEnv*, jclass, jmethodID, va_list) NewObjectV;
	jobject function(JNIEnv*, jclass, jmethodID, const(jvalue*)) NewObjectA;
	jclass function(JNIEnv*, jobject) GetObjectClass;
	jboolean function(JNIEnv*, jobject, jclass) IsInstanceOf;
	jmethodID function(JNIEnv*, jclass, const(char)*, const(char)*) GetMethodID;
	jobject function(JNIEnv*, jobject, jmethodID, ...) CallObjectMethod;
	jobject function(JNIEnv*, jobject, jmethodID, va_list) CallObjectMethodV;
	jobject function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallObjectMethodA;
	jboolean function(JNIEnv*, jobject, jmethodID, ...) CallBooleanMethod;
	jboolean function(JNIEnv*, jobject, jmethodID, va_list) CallBooleanMethodV;
	jboolean function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallBooleanMethodA;
	jbyte function(JNIEnv*, jobject, jmethodID, ...) CallByteMethod;
	jbyte function(JNIEnv*, jobject, jmethodID, va_list) CallByteMethodV;
	jbyte function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallByteMethodA;
	jchar function(JNIEnv*, jobject, jmethodID, ...) CallCharMethod;
	jchar function(JNIEnv*, jobject, jmethodID, va_list) CallCharMethodV;
	jchar function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallCharMethodA;
	jshort function(JNIEnv*, jobject, jmethodID, ...) CallShortMethod;
	jshort function(JNIEnv*, jobject, jmethodID, va_list) CallShortMethodV;
	jshort function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallShortMethodA;
	jint function(JNIEnv*, jobject, jmethodID, ...) CallIntMethod;
	jint function(JNIEnv*, jobject, jmethodID, va_list) CallIntMethodV;
	jint function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallIntMethodA;
	jlong function(JNIEnv*, jobject, jmethodID, ...) CallLongMethod;
	jlong function(JNIEnv*, jobject, jmethodID, va_list) CallLongMethodV;
	jlong function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallLongMethodA;
	jfloat function(JNIEnv*, jobject, jmethodID, ...) CallFloatMethod;
	jfloat function(JNIEnv*, jobject, jmethodID, va_list) CallFloatMethodV;
	jfloat function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallFloatMethodA;
	jdouble function(JNIEnv*, jobject, jmethodID, ...) CallDoubleMethod;
	jdouble function(JNIEnv*, jobject, jmethodID, va_list) CallDoubleMethodV;
	jdouble function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallDoubleMethodA;
	void function(JNIEnv*, jobject, jmethodID, ...) CallVoidMethod;
	void function(JNIEnv*, jobject, jmethodID, va_list) CallVoidMethodV;
	void function(JNIEnv*, jobject, jmethodID, const(jvalue*)) CallVoidMethodA;
	jobject function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualObjectMethod;
	jobject function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualObjectMethodV;
	jobject function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualObjectMethodA;
	jboolean function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualBooleanMethod;
	jboolean function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualBooleanMethodV;
	jboolean function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualBooleanMethodA;
	jbyte function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualByteMethod;
	jbyte function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualByteMethodV;
	jbyte function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualByteMethodA;
	jchar function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualCharMethod;
	jchar function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualCharMethodV;
	jchar function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualCharMethodA;
	jshort function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualShortMethod;
	jshort function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualShortMethodV;
	jshort function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualShortMethodA;
	jint function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualIntMethod;
	jint function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualIntMethodV;
	jint function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualIntMethodA;
	jlong function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualLongMethod;
	jlong function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualLongMethodV;
	jlong function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualLongMethodA;
	jfloat function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualFloatMethod;
	jfloat function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualFloatMethodV;
	jfloat function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualFloatMethodA;
	jdouble function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualDoubleMethod;
	jdouble function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualDoubleMethodV;
	jdouble function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualDoubleMethodA;
	void function(JNIEnv*, jobject, jclass, jmethodID, ...) CallNonvirtualVoidMethod;
	void function(JNIEnv*, jobject, jclass, jmethodID, va_list) CallNonvirtualVoidMethodV;
	void function(JNIEnv*, jobject, jclass, jmethodID, const(jvalue*)) CallNonvirtualVoidMethodA;
	jfieldID function(JNIEnv*, jclass, const(char)*, const(char)*) GetFieldID;
	jobject function(JNIEnv*, jobject, jfieldID) GetObjectField;
	jboolean function(JNIEnv*, jobject, jfieldID) GetBooleanField;
	jbyte function(JNIEnv*, jobject, jfieldID) GetByteField;
	jchar function(JNIEnv*, jobject, jfieldID) GetCharField;
	jshort function(JNIEnv*, jobject, jfieldID) GetShortField;
	jint function(JNIEnv*, jobject, jfieldID) GetIntField;
	jlong function(JNIEnv*, jobject, jfieldID) GetLongField;
	jfloat function(JNIEnv*, jobject, jfieldID) GetFloatField;
	jdouble function(JNIEnv*, jobject, jfieldID) GetDoubleField;
	void function(JNIEnv*, jobject, jfieldID, jobject) SetObjectField;
	void function(JNIEnv*, jobject, jfieldID, jboolean) SetBooleanField;
	void function(JNIEnv*, jobject, jfieldID, jbyte) SetByteField;
	void function(JNIEnv*, jobject, jfieldID, jchar) SetCharField;
	void function(JNIEnv*, jobject, jfieldID, jshort) SetShortField;
	void function(JNIEnv*, jobject, jfieldID, jint) SetIntField;
	void function(JNIEnv*, jobject, jfieldID, jlong) SetLongField;
	void function(JNIEnv*, jobject, jfieldID, jfloat) SetFloatField;
	void function(JNIEnv*, jobject, jfieldID, jdouble) SetDoubleField;
	jmethodID function(JNIEnv*, jclass, const(char)*, const(char)*) GetStaticMethodID;
	jobject function(JNIEnv*, jclass, jmethodID, ...) CallStaticObjectMethod;
	jobject function(JNIEnv*, jclass, jmethodID, va_list) CallStaticObjectMethodV;
	jobject function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticObjectMethodA;
	jboolean function(JNIEnv*, jclass, jmethodID, ...) CallStaticBooleanMethod;
	jboolean function(JNIEnv*, jclass, jmethodID, va_list) CallStaticBooleanMethodV;
	jboolean function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticBooleanMethodA;
	jbyte function(JNIEnv*, jclass, jmethodID, ...) CallStaticByteMethod;
	jbyte function(JNIEnv*, jclass, jmethodID, va_list) CallStaticByteMethodV;
	jbyte function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticByteMethodA;
	jchar function(JNIEnv*, jclass, jmethodID, ...) CallStaticCharMethod;
	jchar function(JNIEnv*, jclass, jmethodID, va_list) CallStaticCharMethodV;
	jchar function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticCharMethodA;
	jshort function(JNIEnv*, jclass, jmethodID, ...) CallStaticShortMethod;
	jshort function(JNIEnv*, jclass, jmethodID, va_list) CallStaticShortMethodV;
	jshort function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticShortMethodA;
	jint function(JNIEnv*, jclass, jmethodID, ...) CallStaticIntMethod;
	jint function(JNIEnv*, jclass, jmethodID, va_list) CallStaticIntMethodV;
	jint function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticIntMethodA;
	jlong function(JNIEnv*, jclass, jmethodID, ...) CallStaticLongMethod;
	jlong function(JNIEnv*, jclass, jmethodID, va_list) CallStaticLongMethodV;
	jlong function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticLongMethodA;
	jfloat function(JNIEnv*, jclass, jmethodID, ...) CallStaticFloatMethod;
	jfloat function(JNIEnv*, jclass, jmethodID, va_list) CallStaticFloatMethodV;
	jfloat function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticFloatMethodA;
	jdouble function(JNIEnv*, jclass, jmethodID, ...) CallStaticDoubleMethod;
	jdouble function(JNIEnv*, jclass, jmethodID, va_list) CallStaticDoubleMethodV;
	jdouble function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticDoubleMethodA;
	void function(JNIEnv*, jclass, jmethodID, ...) CallStaticVoidMethod;
	void function(JNIEnv*, jclass, jmethodID, va_list) CallStaticVoidMethodV;
	void function(JNIEnv*, jclass, jmethodID, const(jvalue*)) CallStaticVoidMethodA;
	jfieldID function(JNIEnv*, jclass, const(char)*, const(char)*) GetStaticFieldID;
	jobject function(JNIEnv*, jclass, jfieldID) GetStaticObjectField;
	jboolean function(JNIEnv*, jclass, jfieldID) GetStaticBooleanField;
	jbyte function(JNIEnv*, jclass, jfieldID) GetStaticByteField;
	jchar function(JNIEnv*, jclass, jfieldID) GetStaticCharField;
	jshort function(JNIEnv*, jclass, jfieldID) GetStaticShortField;
	jint function(JNIEnv*, jclass, jfieldID) GetStaticIntField;
	jlong function(JNIEnv*, jclass, jfieldID) GetStaticLongField;
	jfloat function(JNIEnv*, jclass, jfieldID) GetStaticFloatField;
	jdouble function(JNIEnv*, jclass, jfieldID) GetStaticDoubleField;
	void function(JNIEnv*, jclass, jfieldID, jobject) SetStaticObjectField;
	void function(JNIEnv*, jclass, jfieldID, jboolean) SetStaticBooleanField;
	void function(JNIEnv*, jclass, jfieldID, jbyte) SetStaticByteField;
	void function(JNIEnv*, jclass, jfieldID, jchar) SetStaticCharField;
	void function(JNIEnv*, jclass, jfieldID, jshort) SetStaticShortField;
	void function(JNIEnv*, jclass, jfieldID, jint) SetStaticIntField;
	void function(JNIEnv*, jclass, jfieldID, jlong) SetStaticLongField;
	void function(JNIEnv*, jclass, jfieldID, jfloat) SetStaticFloatField;
	void function(JNIEnv*, jclass, jfieldID, jdouble) SetStaticDoubleField;
	jstring function(JNIEnv*, const(jchar)*, jsize) NewString;
	jsize function(JNIEnv*, jstring) GetStringLength;
	const(jchar)* function(JNIEnv*, jstring, jboolean*) GetStringChars;
	void function(JNIEnv*, jstring, const(jchar)*) ReleaseStringChars;
	jstring function(JNIEnv*, const(char)*) NewStringUTF;
	jsize function(JNIEnv*, jstring) GetStringUTFLength;
	const(char)* function(JNIEnv*, jstring, jboolean*) GetStringUTFChars;
	void function(JNIEnv*, jstring, const(char)*) ReleaseStringUTFChars;
	jsize function(JNIEnv*, jarray) GetArrayLength;
	jobjectArray function(JNIEnv*, jsize, jclass, jobject) NewObjectArray;
	jobject function(JNIEnv*, jobjectArray, jsize) GetObjectArrayElement;
	void function(JNIEnv*, jobjectArray, jsize, jobject) SetObjectArrayElement;
	jbooleanArray function(JNIEnv*, jsize) NewBooleanArray;
	jbyteArray function(JNIEnv*, jsize) NewByteArray;
	jcharArray function(JNIEnv*, jsize) NewCharArray;
	jshortArray function(JNIEnv*, jsize) NewShortArray;
	jintArray function(JNIEnv*, jsize) NewIntArray;
	jlongArray function(JNIEnv*, jsize) NewLongArray;
	jfloatArray function(JNIEnv*, jsize) NewFloatArray;
	jdoubleArray function(JNIEnv*, jsize) NewDoubleArray;
	jboolean* function(JNIEnv*, jbooleanArray, jboolean*) GetBooleanArrayElements;
	jbyte* function(JNIEnv*, jbyteArray, jboolean*) GetByteArrayElements;
	jchar* function(JNIEnv*, jcharArray, jboolean*) GetCharArrayElements;
	jshort* function(JNIEnv*, jshortArray, jboolean*) GetShortArrayElements;
	jint* function(JNIEnv*, jintArray, jboolean*) GetIntArrayElements;
	jlong* function(JNIEnv*, jlongArray, jboolean*) GetLongArrayElements;
	jfloat* function(JNIEnv*, jfloatArray, jboolean*) GetFloatArrayElements;
	jdouble* function(JNIEnv*, jdoubleArray, jboolean*) GetDoubleArrayElements;
	void function(JNIEnv*, jbooleanArray, jboolean*, jint) ReleaseBooleanArrayElements;
	void function(JNIEnv*, jbyteArray, jbyte*, jint) ReleaseByteArrayElements;
	void function(JNIEnv*, jcharArray, jchar*, jint) ReleaseCharArrayElements;
	void function(JNIEnv*, jshortArray, jshort*, jint) ReleaseShortArrayElements;
	void function(JNIEnv*, jintArray, jint*, jint) ReleaseIntArrayElements;
	void function(JNIEnv*, jlongArray, jlong*, jint) ReleaseLongArrayElements;
	void function(JNIEnv*, jfloatArray, jfloat*, jint) ReleaseFloatArrayElements;
	void function(JNIEnv*, jdoubleArray, jdouble*, jint) ReleaseDoubleArrayElements;
	void function(JNIEnv*, jbooleanArray, jsize, jsize, jboolean*) GetBooleanArrayRegion;
	void function(JNIEnv*, jbyteArray, jsize, jsize, jbyte*) GetByteArrayRegion;
	void function(JNIEnv*, jcharArray, jsize, jsize, jchar*) GetCharArrayRegion;
	void function(JNIEnv*, jshortArray, jsize, jsize, jshort*) GetShortArrayRegion;
	void function(JNIEnv*, jintArray, jsize, jsize, jint*) GetIntArrayRegion;
	void function(JNIEnv*, jlongArray, jsize, jsize, jlong*) GetLongArrayRegion;
	void function(JNIEnv*, jfloatArray, jsize, jsize, jfloat*) GetFloatArrayRegion;
	void function(JNIEnv*, jdoubleArray, jsize, jsize, jdouble*) GetDoubleArrayRegion;
	void function(JNIEnv*, jbooleanArray, jsize, jsize, const(jboolean)*) SetBooleanArrayRegion;
	void function(JNIEnv*, jbyteArray, jsize, jsize, const(jbyte)*) SetByteArrayRegion;
	void function(JNIEnv*, jcharArray, jsize, jsize, const(jchar)*) SetCharArrayRegion;
	void function(JNIEnv*, jshortArray, jsize, jsize, const(jshort)*) SetShortArrayRegion;
	void function(JNIEnv*, jintArray, jsize, jsize, const(jint)*) SetIntArrayRegion;
	void function(JNIEnv*, jlongArray, jsize, jsize, const(jlong)*) SetLongArrayRegion;
	void function(JNIEnv*, jfloatArray, jsize, jsize, const(jfloat)*) SetFloatArrayRegion;
	void function(JNIEnv*, jdoubleArray, jsize, jsize, const(jdouble)*) SetDoubleArrayRegion;
	jint function(JNIEnv*, jclass, const(JNINativeMethod)*, jint) RegisterNatives;
	jint function(JNIEnv*, jclass) UnregisterNatives;
	jint function(JNIEnv*, jobject) MonitorEnter;
	jint function(JNIEnv*, jobject) MonitorExit;
	jint function(JNIEnv*, JavaVM**) GetJavaVM;
	void function(JNIEnv*, jstring, jsize, jsize, jchar*) GetStringRegion;
	void function(JNIEnv*, jstring, jsize, jsize, char*) GetStringUTFRegion;
	void* function(JNIEnv*, jarray, jboolean*) GetPrimitiveArrayCritical;
	void function(JNIEnv*, jarray, void*, jint) ReleasePrimitiveArrayCritical;
	const(jchar)* function(JNIEnv*, jstring, jboolean*) GetStringCritical;
	void function(JNIEnv*, jstring, const(jchar)*) ReleaseStringCritical;
	jweak function(JNIEnv*, jobject) NewWeakGlobalRef;
	void function(JNIEnv*, jweak) DeleteWeakGlobalRef;
	jboolean function(JNIEnv*) ExceptionCheck;
	jobject function(JNIEnv*, void*, jlong) NewDirectByteBuffer;
	void* function(JNIEnv*, jobject) GetDirectBufferAddress;
	jlong function(JNIEnv*, jobject) GetDirectBufferCapacity;

	/* New JNI 1.6 Features */
	jobjectRefType function(JNIEnv*, jobject) GetObjectRefType;
}

struct JNIEnv_
{
	const(JNINativeInterface_)* functions;

	jint GetVersion()
	{
		return functions.GetVersion(&this);
	}

	jclass DefineClass(const(char)* name, jobject loader, const(jbyte)* buf, jsize len)
	{
		return functions.DefineClass(&this, name, loader, buf, len);
	}

	jclass FindClass(const(char)* name)
	{
		return functions.FindClass(&this, name);
	}

	jmethodID FromReflectedMethod(jobject method)
	{
		return functions.FromReflectedMethod(&this, method);
	}

	jfieldID FromReflectedField(jobject field)
	{
		return functions.FromReflectedField(&this, field);
	}

	jobject ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic)
	{
		return functions.ToReflectedMethod(&this, cls, methodID, isStatic);
	}

	jclass GetSuperclass(jclass sub)
	{
		return functions.GetSuperclass(&this, sub);
	}

	jboolean IsAssignableFrom(jclass sub, jclass sup)
	{
		return functions.IsAssignableFrom(&this, sub, sup);
	}

	jobject ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic)
	{
		return functions.ToReflectedField(&this, cls, fieldID, isStatic);
	}

	jint Throw(jthrowable obj)
	{
		return functions.Throw(&this, obj);
	}

	jint ThrowNew(jclass clazz, const(char)* msg)
	{
		return functions.ThrowNew(&this, clazz, msg);
	}

	jthrowable ExceptionOccurred()
	{
		return functions.ExceptionOccurred(&this);
	}

	void ExceptionDescribe()
	{
		functions.ExceptionDescribe(&this);
	}

	void ExceptionClear()
	{
		functions.ExceptionClear(&this);
	}

	void FatalError(const(char)* msg)
	{
		functions.FatalError(&this, msg);
	}

	jint PushLocalFrame(jint capacity)
	{
		return functions.PushLocalFrame(&this, capacity);
	}

	jobject PopLocalFrame(jobject result)
	{
		return functions.PopLocalFrame(&this, result);
	}

	jobject NewGlobalRef(jobject lobj)
	{
		return functions.NewGlobalRef(&this, lobj);
	}

	void DeleteGlobalRef(jobject gref)
	{
		functions.DeleteGlobalRef(&this, gref);
	}

	void DeleteLocalRef(jobject obj)
	{
		functions.DeleteLocalRef(&this, obj);
	}

	jboolean IsSameObject(jobject obj1, jobject obj2)
	{
		return functions.IsSameObject(&this, obj1, obj2);
	}

	jobject NewLocalRef(jobject _ref)
	{
		return functions.NewLocalRef(&this, _ref);
	}

	jint EnsureLocalCapacity(jint capacity)
	{
		return functions.EnsureLocalCapacity(&this, capacity);
	}

	jobject AllocObject(jclass clazz)
	{
		return functions.AllocObject(&this, clazz);
	}

	jobject NewObject(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jobject result;
		va_start(args, methodID);
		result = functions.NewObjectV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jobject NewObjectV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.NewObjectV(&this, clazz, methodID, args);
	}

	jobject NewObjectA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.NewObjectA(&this, clazz, methodID, args);
	}

	jclass GetObjectClass(jobject obj)
	{
		return functions.GetObjectClass(&this, obj);
	}

	jboolean IsInstanceOf(jobject obj, jclass clazz)
	{
		return functions.IsInstanceOf(&this, obj, clazz);
	}

	jmethodID GetMethodID(jclass clazz, const(char)* name, const(char)* sig)
	{
		return functions.GetMethodID(&this, clazz, name, sig);
	}

	jobject CallObjectMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jobject result;
		va_start(args, methodID);
		result = functions.CallObjectMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jobject CallObjectMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallObjectMethodV(&this, obj, methodID, args);
	}

	jobject CallObjectMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallObjectMethodA(&this, obj, methodID, args);
	}

	jboolean CallBooleanMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jboolean result;
		va_start(args, methodID);
		result = functions.CallBooleanMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jboolean CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallBooleanMethodV(&this, obj, methodID, args);
	}

	jboolean CallBooleanMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallBooleanMethodA(&this, obj, methodID, args);
	}

	jbyte CallByteMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jbyte result;
		va_start(args, methodID);
		result = functions.CallByteMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jbyte CallByteMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallByteMethodV(&this, obj, methodID, args);
	}

	jbyte CallByteMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallByteMethodA(&this, obj, methodID, args);
	}

	jchar CallCharMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jchar result;
		va_start(args, methodID);
		result = functions.CallCharMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jchar CallCharMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallCharMethodV(&this, obj, methodID, args);
	}

	jchar CallCharMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallCharMethodA(&this, obj, methodID, args);
	}

	jshort CallShortMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jshort result;
		va_start(args, methodID);
		result = functions.CallShortMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jshort CallShortMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallShortMethodV(&this, obj, methodID, args);
	}

	jshort CallShortMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallShortMethodA(&this, obj, methodID, args);
	}

	jint CallIntMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jint result;
		va_start(args, methodID);
		result = functions.CallIntMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jint CallIntMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallIntMethodV(&this, obj, methodID, args);
	}

	jint CallIntMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallIntMethodA(&this, obj, methodID, args);
	}

	jlong CallLongMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jlong result;
		va_start(args, methodID);
		result = functions.CallLongMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jlong CallLongMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallLongMethodV(&this, obj, methodID, args);
	}

	jlong CallLongMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallLongMethodA(&this, obj, methodID, args);
	}

	jfloat CallFloatMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jfloat result;
		va_start(args, methodID);
		result = functions.CallFloatMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jfloat CallFloatMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallFloatMethodV(&this, obj, methodID, args);
	}

	jfloat CallFloatMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallFloatMethodA(&this, obj, methodID, args);
	}

	jdouble CallDoubleMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		jdouble result;
		va_start(args, methodID);
		result = functions.CallDoubleMethodV(&this, obj, methodID, args);
		va_end(args);
		return result;
	}

	jdouble CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		return functions.CallDoubleMethodV(&this, obj, methodID, args);
	}

	jdouble CallDoubleMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallDoubleMethodA(&this, obj, methodID, args);
	}

	void CallVoidMethod(jobject obj, jmethodID methodID, ...)
	{
		va_list args;
		va_start(args, methodID);
		functions.CallVoidMethodV(&this, obj, methodID, args);
		va_end(args);
	}

	void CallVoidMethodV(jobject obj, jmethodID methodID, va_list args)
	{
		functions.CallVoidMethodV(&this, obj, methodID, args);
	}

	void CallVoidMethodA(jobject obj, jmethodID methodID, const(jvalue)* args)
	{
		functions.CallVoidMethodA(&this, obj, methodID, args);
	}

	jobject CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jobject result;
		va_start(args, methodID);
		result = functions.CallNonvirtualObjectMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jobject CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualObjectMethodV(&this, obj, clazz, methodID, args);
	}

	jobject CallNonvirtualObjectMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualObjectMethodA(&this, obj, clazz, methodID, args);
	}

	jboolean CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jboolean result;
		va_start(args, methodID);
		result = functions.CallNonvirtualBooleanMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jboolean CallNonvirtualBooleanMethodV(jobject obj, jclass clazz,
			jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualBooleanMethodV(&this, obj, clazz, methodID, args);
	}

	jboolean CallNonvirtualBooleanMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualBooleanMethodA(&this, obj, clazz, methodID, args);
	}

	jbyte CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jbyte result;
		va_start(args, methodID);
		result = functions.CallNonvirtualByteMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jbyte CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualByteMethodV(&this, obj, clazz, methodID, args);
	}

	jbyte CallNonvirtualByteMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualByteMethodA(&this, obj, clazz, methodID, args);
	}

	jchar CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jchar result;
		va_start(args, methodID);
		result = functions.CallNonvirtualCharMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jchar CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualCharMethodV(&this, obj, clazz, methodID, args);
	}

	jchar CallNonvirtualCharMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualCharMethodA(&this, obj, clazz, methodID, args);
	}

	jshort CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jshort result;
		va_start(args, methodID);
		result = functions.CallNonvirtualShortMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jshort CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualShortMethodV(&this, obj, clazz, methodID, args);
	}

	jshort CallNonvirtualShortMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualShortMethodA(&this, obj, clazz, methodID, args);
	}

	jint CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jint result;
		va_start(args, methodID);
		result = functions.CallNonvirtualIntMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jint CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualIntMethodV(&this, obj, clazz, methodID, args);
	}

	jint CallNonvirtualIntMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualIntMethodA(&this, obj, clazz, methodID, args);
	}

	jlong CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jlong result;
		va_start(args, methodID);
		result = functions.CallNonvirtualLongMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jlong CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualLongMethodV(&this, obj, clazz, methodID, args);
	}

	jlong CallNonvirtualLongMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualLongMethodA(&this, obj, clazz, methodID, args);
	}

	jfloat CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jfloat result;
		va_start(args, methodID);
		result = functions.CallNonvirtualFloatMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jfloat CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualFloatMethodV(&this, obj, clazz, methodID, args);
	}

	jfloat CallNonvirtualFloatMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualFloatMethodA(&this, obj, clazz, methodID, args);
	}

	jdouble CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jdouble result;
		va_start(args, methodID);
		result = functions.CallNonvirtualDoubleMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jdouble CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallNonvirtualDoubleMethodV(&this, obj, clazz, methodID, args);
	}

	jdouble CallNonvirtualDoubleMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallNonvirtualDoubleMethodA(&this, obj, clazz, methodID, args);
	}

	void CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		va_start(args, methodID);
		functions.CallNonvirtualVoidMethodV(&this, obj, clazz, methodID, args);
		va_end(args);
	}

	void CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
	{
		functions.CallNonvirtualVoidMethodV(&this, obj, clazz, methodID, args);
	}

	void CallNonvirtualVoidMethodA(jobject obj, jclass clazz,
			jmethodID methodID, const(jvalue)* args)
	{
		functions.CallNonvirtualVoidMethodA(&this, obj, clazz, methodID, args);
	}

	jfieldID GetFieldID(jclass clazz, const(char)* name, const(char)* sig)
	{
		return functions.GetFieldID(&this, clazz, name, sig);
	}

	jobject GetObjectField(jobject obj, jfieldID fieldID)
	{
		return functions.GetObjectField(&this, obj, fieldID);
	}

	jboolean GetBooleanField(jobject obj, jfieldID fieldID)
	{
		return functions.GetBooleanField(&this, obj, fieldID);
	}

	jbyte GetByteField(jobject obj, jfieldID fieldID)
	{
		return functions.GetByteField(&this, obj, fieldID);
	}

	jchar GetCharField(jobject obj, jfieldID fieldID)
	{
		return functions.GetCharField(&this, obj, fieldID);
	}

	jshort GetShortField(jobject obj, jfieldID fieldID)
	{
		return functions.GetShortField(&this, obj, fieldID);
	}

	jint GetIntField(jobject obj, jfieldID fieldID)
	{
		return functions.GetIntField(&this, obj, fieldID);
	}

	jlong GetLongField(jobject obj, jfieldID fieldID)
	{
		return functions.GetLongField(&this, obj, fieldID);
	}

	jfloat GetFloatField(jobject obj, jfieldID fieldID)
	{
		return functions.GetFloatField(&this, obj, fieldID);
	}

	jdouble GetDoubleField(jobject obj, jfieldID fieldID)
	{
		return functions.GetDoubleField(&this, obj, fieldID);
	}

	void SetObjectField(jobject obj, jfieldID fieldID, jobject val)
	{
		functions.SetObjectField(&this, obj, fieldID, val);
	}

	void SetBooleanField(jobject obj, jfieldID fieldID, jboolean val)
	{
		functions.SetBooleanField(&this, obj, fieldID, val);
	}

	void SetByteField(jobject obj, jfieldID fieldID, jbyte val)
	{
		functions.SetByteField(&this, obj, fieldID, val);
	}

	void SetCharField(jobject obj, jfieldID fieldID, jchar val)
	{
		functions.SetCharField(&this, obj, fieldID, val);
	}

	void SetShortField(jobject obj, jfieldID fieldID, jshort val)
	{
		functions.SetShortField(&this, obj, fieldID, val);
	}

	void SetIntField(jobject obj, jfieldID fieldID, jint val)
	{
		functions.SetIntField(&this, obj, fieldID, val);
	}

	void SetLongField(jobject obj, jfieldID fieldID, jlong val)
	{
		functions.SetLongField(&this, obj, fieldID, val);
	}

	void SetFloatField(jobject obj, jfieldID fieldID, jfloat val)
	{
		functions.SetFloatField(&this, obj, fieldID, val);
	}

	void SetDoubleField(jobject obj, jfieldID fieldID, jdouble val)
	{
		functions.SetDoubleField(&this, obj, fieldID, val);
	}

	jmethodID GetStaticMethodID(jclass clazz, const(char)* name, const(char)* sig)
	{
		return functions.GetStaticMethodID(&this, clazz, name, sig);
	}

	jobject CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jobject result;
		va_start(args, methodID);
		result = functions.CallStaticObjectMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jobject CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticObjectMethodV(&this, clazz, methodID, args);
	}

	jobject CallStaticObjectMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticObjectMethodA(&this, clazz, methodID, args);
	}

	jboolean CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jboolean result;
		va_start(args, methodID);
		result = functions.CallStaticBooleanMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jboolean CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticBooleanMethodV(&this, clazz, methodID, args);
	}

	jboolean CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticBooleanMethodA(&this, clazz, methodID, args);
	}

	jbyte CallStaticByteMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jbyte result;
		va_start(args, methodID);
		result = functions.CallStaticByteMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jbyte CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticByteMethodV(&this, clazz, methodID, args);
	}

	jbyte CallStaticByteMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticByteMethodA(&this, clazz, methodID, args);
	}

	jchar CallStaticCharMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jchar result;
		va_start(args, methodID);
		result = functions.CallStaticCharMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jchar CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticCharMethodV(&this, clazz, methodID, args);
	}

	jchar CallStaticCharMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticCharMethodA(&this, clazz, methodID, args);
	}

	jshort CallStaticShortMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jshort result;
		va_start(args, methodID);
		result = functions.CallStaticShortMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jshort CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticShortMethodV(&this, clazz, methodID, args);
	}

	jshort CallStaticShortMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticShortMethodA(&this, clazz, methodID, args);
	}

	jint CallStaticIntMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jint result;
		va_start(args, methodID);
		result = functions.CallStaticIntMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jint CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticIntMethodV(&this, clazz, methodID, args);
	}

	jint CallStaticIntMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticIntMethodA(&this, clazz, methodID, args);
	}

	jlong CallStaticLongMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jlong result;
		va_start(args, methodID);
		result = functions.CallStaticLongMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jlong CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticLongMethodV(&this, clazz, methodID, args);
	}

	jlong CallStaticLongMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticLongMethodA(&this, clazz, methodID, args);
	}

	jfloat CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jfloat result;
		va_start(args, methodID);
		result = functions.CallStaticFloatMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jfloat CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticFloatMethodV(&this, clazz, methodID, args);
	}

	jfloat CallStaticFloatMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticFloatMethodA(&this, clazz, methodID, args);
	}

	jdouble CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...)
	{
		va_list args;
		jdouble result;
		va_start(args, methodID);
		result = functions.CallStaticDoubleMethodV(&this, clazz, methodID, args);
		va_end(args);
		return result;
	}

	jdouble CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args)
	{
		return functions.CallStaticDoubleMethodV(&this, clazz, methodID, args);
	}

	jdouble CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, const(jvalue)* args)
	{
		return functions.CallStaticDoubleMethodA(&this, clazz, methodID, args);
	}

	void CallStaticVoidMethod(jclass cls, jmethodID methodID, ...)
	{
		va_list args;
		va_start(args, methodID);
		functions.CallStaticVoidMethodV(&this, cls, methodID, args);
		va_end(args);
	}

	void CallStaticVoidMethodV(jclass cls, jmethodID methodID, va_list args)
	{
		functions.CallStaticVoidMethodV(&this, cls, methodID, args);
	}

	void CallStaticVoidMethodA(jclass cls, jmethodID methodID, const(jvalue)* args)
	{
		functions.CallStaticVoidMethodA(&this, cls, methodID, args);
	}

	jfieldID GetStaticFieldID(jclass clazz, const(char)* name, const(char)* sig)
	{
		return functions.GetStaticFieldID(&this, clazz, name, sig);
	}

	jobject GetStaticObjectField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticObjectField(&this, clazz, fieldID);
	}

	jboolean GetStaticBooleanField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticBooleanField(&this, clazz, fieldID);
	}

	jbyte GetStaticByteField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticByteField(&this, clazz, fieldID);
	}

	jchar GetStaticCharField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticCharField(&this, clazz, fieldID);
	}

	jshort GetStaticShortField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticShortField(&this, clazz, fieldID);
	}

	jint GetStaticIntField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticIntField(&this, clazz, fieldID);
	}

	jlong GetStaticLongField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticLongField(&this, clazz, fieldID);
	}

	jfloat GetStaticFloatField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticFloatField(&this, clazz, fieldID);
	}

	jdouble GetStaticDoubleField(jclass clazz, jfieldID fieldID)
	{
		return functions.GetStaticDoubleField(&this, clazz, fieldID);
	}

	void SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value)
	{
		functions.SetStaticObjectField(&this, clazz, fieldID, value);
	}

	void SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value)
	{
		functions.SetStaticBooleanField(&this, clazz, fieldID, value);
	}

	void SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value)
	{
		functions.SetStaticByteField(&this, clazz, fieldID, value);
	}

	void SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value)
	{
		functions.SetStaticCharField(&this, clazz, fieldID, value);
	}

	void SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value)
	{
		functions.SetStaticShortField(&this, clazz, fieldID, value);
	}

	void SetStaticIntField(jclass clazz, jfieldID fieldID, jint value)
	{
		functions.SetStaticIntField(&this, clazz, fieldID, value);
	}

	void SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value)
	{
		functions.SetStaticLongField(&this, clazz, fieldID, value);
	}

	void SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value)
	{
		functions.SetStaticFloatField(&this, clazz, fieldID, value);
	}

	void SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value)
	{
		functions.SetStaticDoubleField(&this, clazz, fieldID, value);
	}

	jstring NewString(const(jchar)* unicode, jsize len)
	{
		return functions.NewString(&this, unicode, len);
	}

	jsize GetStringLength(jstring str)
	{
		return functions.GetStringLength(&this, str);
	}

	const(jchar)* GetStringChars(jstring str, jboolean* isCopy)
	{
		return functions.GetStringChars(&this, str, isCopy);
	}

	void ReleaseStringChars(jstring str, const(jchar)* chars)
	{
		functions.ReleaseStringChars(&this, str, chars);
	}

	jstring NewStringUTF(const(char)* utf)
	{
		return functions.NewStringUTF(&this, utf);
	}

	jsize GetStringUTFLength(jstring str)
	{
		return functions.GetStringUTFLength(&this, str);
	}

	const(char)* GetStringUTFChars(jstring str, jboolean* isCopy)
	{
		return functions.GetStringUTFChars(&this, str, isCopy);
	}

	void ReleaseStringUTFChars(jstring str, const(char)* chars)
	{
		functions.ReleaseStringUTFChars(&this, str, chars);
	}

	jsize GetArrayLength(jarray array)
	{
		return functions.GetArrayLength(&this, array);
	}

	jobjectArray NewObjectArray(jsize len, jclass clazz, jobject init)
	{
		return functions.NewObjectArray(&this, len, clazz, init);
	}

	jobject GetObjectArrayElement(jobjectArray array, jsize index)
	{
		return functions.GetObjectArrayElement(&this, array, index);
	}

	void SetObjectArrayElement(jobjectArray array, jsize index, jobject val)
	{
		functions.SetObjectArrayElement(&this, array, index, val);
	}

	jbooleanArray NewBooleanArray(jsize len)
	{
		return functions.NewBooleanArray(&this, len);
	}

	jbyteArray NewByteArray(jsize len)
	{
		return functions.NewByteArray(&this, len);
	}

	jcharArray NewCharArray(jsize len)
	{
		return functions.NewCharArray(&this, len);
	}

	jshortArray NewShortArray(jsize len)
	{
		return functions.NewShortArray(&this, len);
	}

	jintArray NewIntArray(jsize len)
	{
		return functions.NewIntArray(&this, len);
	}

	jlongArray NewLongArray(jsize len)
	{
		return functions.NewLongArray(&this, len);
	}

	jfloatArray NewFloatArray(jsize len)
	{
		return functions.NewFloatArray(&this, len);
	}

	jdoubleArray NewDoubleArray(jsize len)
	{
		return functions.NewDoubleArray(&this, len);
	}

	jboolean* GetBooleanArrayElements(jbooleanArray array, jboolean* isCopy)
	{
		return functions.GetBooleanArrayElements(&this, array, isCopy);
	}

	jbyte* GetByteArrayElements(jbyteArray array, jboolean* isCopy)
	{
		return functions.GetByteArrayElements(&this, array, isCopy);
	}

	jchar* GetCharArrayElements(jcharArray array, jboolean* isCopy)
	{
		return functions.GetCharArrayElements(&this, array, isCopy);
	}

	jshort* GetShortArrayElements(jshortArray array, jboolean* isCopy)
	{
		return functions.GetShortArrayElements(&this, array, isCopy);
	}

	jint* GetIntArrayElements(jintArray array, jboolean* isCopy)
	{
		return functions.GetIntArrayElements(&this, array, isCopy);
	}

	jlong* GetLongArrayElements(jlongArray array, jboolean* isCopy)
	{
		return functions.GetLongArrayElements(&this, array, isCopy);
	}

	jfloat* GetFloatArrayElements(jfloatArray array, jboolean* isCopy)
	{
		return functions.GetFloatArrayElements(&this, array, isCopy);
	}

	jdouble* GetDoubleArrayElements(jdoubleArray array, jboolean* isCopy)
	{
		return functions.GetDoubleArrayElements(&this, array, isCopy);
	}

	void ReleaseBooleanArrayElements(jbooleanArray array, jboolean* elems, jint mode)
	{
		functions.ReleaseBooleanArrayElements(&this, array, elems, mode);
	}

	void ReleaseByteArrayElements(jbyteArray array, jbyte* elems, jint mode)
	{
		functions.ReleaseByteArrayElements(&this, array, elems, mode);
	}

	void ReleaseCharArrayElements(jcharArray array, jchar* elems, jint mode)
	{
		functions.ReleaseCharArrayElements(&this, array, elems, mode);
	}

	void ReleaseShortArrayElements(jshortArray array, jshort* elems, jint mode)
	{
		functions.ReleaseShortArrayElements(&this, array, elems, mode);
	}

	void ReleaseIntArrayElements(jintArray array, jint* elems, jint mode)
	{
		functions.ReleaseIntArrayElements(&this, array, elems, mode);
	}

	void ReleaseLongArrayElements(jlongArray array, jlong* elems, jint mode)
	{
		functions.ReleaseLongArrayElements(&this, array, elems, mode);
	}

	void ReleaseFloatArrayElements(jfloatArray array, jfloat* elems, jint mode)
	{
		functions.ReleaseFloatArrayElements(&this, array, elems, mode);
	}

	void ReleaseDoubleArrayElements(jdoubleArray array, jdouble* elems, jint mode)
	{
		functions.ReleaseDoubleArrayElements(&this, array, elems, mode);
	}

	void GetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean* buf)
	{
		functions.GetBooleanArrayRegion(&this, array, start, len, buf);
	}

	void GetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte* buf)
	{
		functions.GetByteArrayRegion(&this, array, start, len, buf);
	}

	void GetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar* buf)
	{
		functions.GetCharArrayRegion(&this, array, start, len, buf);
	}

	void GetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort* buf)
	{
		functions.GetShortArrayRegion(&this, array, start, len, buf);
	}

	void GetIntArrayRegion(jintArray array, jsize start, jsize len, jint* buf)
	{
		functions.GetIntArrayRegion(&this, array, start, len, buf);
	}

	void GetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong* buf)
	{
		functions.GetLongArrayRegion(&this, array, start, len, buf);
	}

	void GetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat* buf)
	{
		functions.GetFloatArrayRegion(&this, array, start, len, buf);
	}

	void GetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble* buf)
	{
		functions.GetDoubleArrayRegion(&this, array, start, len, buf);
	}

	void SetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, const(jboolean)* buf)
	{
		functions.SetBooleanArrayRegion(&this, array, start, len, buf);
	}

	void SetByteArrayRegion(jbyteArray array, jsize start, jsize len, const(jbyte)* buf)
	{
		functions.SetByteArrayRegion(&this, array, start, len, buf);
	}

	void SetCharArrayRegion(jcharArray array, jsize start, jsize len, const(jchar)* buf)
	{
		functions.SetCharArrayRegion(&this, array, start, len, buf);
	}

	void SetShortArrayRegion(jshortArray array, jsize start, jsize len, const(jshort)* buf)
	{
		functions.SetShortArrayRegion(&this, array, start, len, buf);
	}

	void SetIntArrayRegion(jintArray array, jsize start, jsize len, const(jint)* buf)
	{
		functions.SetIntArrayRegion(&this, array, start, len, buf);
	}

	void SetLongArrayRegion(jlongArray array, jsize start, jsize len, const(jlong)* buf)
	{
		functions.SetLongArrayRegion(&this, array, start, len, buf);
	}

	void SetFloatArrayRegion(jfloatArray array, jsize start, jsize len, const(jfloat)* buf)
	{
		functions.SetFloatArrayRegion(&this, array, start, len, buf);
	}

	void SetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, const(jdouble)* buf)
	{
		functions.SetDoubleArrayRegion(&this, array, start, len, buf);
	}

	jint RegisterNatives(jclass clazz, const(JNINativeMethod)* methods, jint nMethods)
	{
		return functions.RegisterNatives(&this, clazz, methods, nMethods);
	}

	jint UnregisterNatives(jclass clazz)
	{
		return functions.UnregisterNatives(&this, clazz);
	}

	jint MonitorEnter(jobject obj)
	{
		return functions.MonitorEnter(&this, obj);
	}

	jint MonitorExit(jobject obj)
	{
		return functions.MonitorExit(&this, obj);
	}

	jint GetJavaVM(JavaVM** vm)
	{
		return functions.GetJavaVM(&this, vm);
	}

	void GetStringRegion(jstring str, jsize start, jsize len, jchar* buf)
	{
		functions.GetStringRegion(&this, str, start, len, buf);
	}

	void GetStringUTFRegion(jstring str, jsize start, jsize len, char* buf)
	{
		functions.GetStringUTFRegion(&this, str, start, len, buf);
	}

	void* GetPrimitiveArrayCritical(jarray array, jboolean* isCopy)
	{
		return functions.GetPrimitiveArrayCritical(&this, array, isCopy);
	}

	void ReleasePrimitiveArrayCritical(jarray array, void* carray, jint mode)
	{
		functions.ReleasePrimitiveArrayCritical(&this, array, carray, mode);
	}

	const(jchar)* GetStringCritical(jstring string, jboolean* isCopy)
	{
		return functions.GetStringCritical(&this, string, isCopy);
	}

	void ReleaseStringCritical(jstring string, const(jchar)* cstring)
	{
		functions.ReleaseStringCritical(&this, string, cstring);
	}

	jweak NewWeakGlobalRef(jobject obj)
	{
		return functions.NewWeakGlobalRef(&this, obj);
	}

	void DeleteWeakGlobalRef(jweak _ref)
	{
		functions.DeleteWeakGlobalRef(&this, _ref);
	}

	jboolean ExceptionCheck()
	{
		return functions.ExceptionCheck(&this);
	}

	jobject NewDirectByteBuffer(void* address, jlong capacity)
	{
		return functions.NewDirectByteBuffer(&this, address, capacity);
	}

	void* GetDirectBufferAddress(jobject buf)
	{
		return functions.GetDirectBufferAddress(&this, buf);
	}

	jlong GetDirectBufferCapacity(jobject buf)
	{
		return functions.GetDirectBufferCapacity(&this, buf);
	}

	jobjectRefType GetObjectRefType(jobject obj)
	{
		return functions.GetObjectRefType(&this, obj);
	}

}

struct JavaVMOption
{
	char* optionString;
	void* extraInfo;
}

struct JavaVMInitArgs
{
	jint _version;
	jint nOptions;
	JavaVMOption* options;
	jboolean ignoreUnrecognized;
}

struct JavaVMAttachArgs
{
	jint _version;
	char* name;
	jobject group;
}

struct JNIInvokeInterface_
{
	void* reserved0;
	void* reserved1;
	void* reserved2;
	jint function(JavaVM* vm) DestroyJavaVM;
	jint function(JavaVM* vm, void** penv, void* args) AttachCurrentThread;
	jint function(JavaVM* vm) DetachCurrentThread;
	jint function(JavaVM* vm, void** penv, jint _version) GetEnv;
	jint function(JavaVM* vm, void** penv, void* args) AttachCurrentThreadAsDaemon;
}

struct JavaVM_
{
	const(JNIInvokeInterface_)* functions;

	jint DestroyJavaVM()
	{
		return functions.DestroyJavaVM(&this);
	}

	jint AttachCurrentThread(void** penv, void* args)
	{
		return functions.AttachCurrentThread(&this, penv, args);
	}

	jint DetachCurrentThread()
	{
		return functions.DetachCurrentThread(&this);
	}

	jint GetEnv(void** penv, jint _version)
	{
		return functions.GetEnv(&this, penv, _version);
	}

	jint AttachCurrentThreadAsDaemon(void** penv, void* args)
	{
		return functions.AttachCurrentThreadAsDaemon(&this, penv, args);
	}
}

/* In practice, these are not exported by the NDK so don't declare them */
//jint JNI_GetDefaultJavaVMInitArgs(void* args);
//jint JNI_CreateJavaVM(JavaVM** pvm, void** penv, void* args);
//jint JNI_GetCreatedJavaVMs(JavaVM**, jsize, jsize*);

/* Defined by native libraries. */

/*
 * Prototypes for functions exported by loadable shared libs. These are
 * called by JNI, not provided by JNI.
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved);
void JNI_OnUnload(JavaVM* vm, void* reserved);

/*
 * Manifest constants.
 */
enum JNI_VERSION_1_1 = 0x00010001;
enum JNI_VERSION_1_2 = 0x00010002;
enum JNI_VERSION_1_4 = 0x00010004;
enum JNI_VERSION_1_6 = 0x00010006;
enum JNI_VERSION_1_8 = 0x00010008;
