/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2010 The Android Open Source Project.
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

This file has bindings for an existing code, part of The Android Open Source
Project implementation. Check it out at android.googlesource.com .
*/

module aurorafw.android.platform.sensor;

/**
 * @addtogroup Sensor
 * @{
 */

/**
 * @file aurorafw/android/platform/sensor.d
 */

import core.stdc.math;
import core.sys.posix.sys.types;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/******************************************************************
 *
 * IMPORTANT NOTICE:
 *
 *   This file is part of Android's set of stable system headers
 *   exposed by the Android NDK (Native Development Kit).
 *
 *   Third-party source AND binary code relies on the definitions
 *   here to be FROZEN ON ALL UPCOMING PLATFORM RELEASES.
 *
 *   - DO NOT MODIFY ENUMS (EXCEPT IF YOU ADD NEW 32-BIT VALUES)
 *   - DO NOT MODIFY CONSTANTS OR FUNCTIONAL MACROS
 *   - DO NOT CHANGE THE SIGNATURE OF FUNCTIONS IN ANY WAY
 *   - DO NOT CHANGE THE LAYOUT OR SIZE OF STRUCTURES
 */

/**
 * Structures and functions to receive and process sensor events in
 * native code.
 *
 */

struct AHardwareBuffer;

enum ASENSOR_RESOLUTION_INVALID = nanf("");
enum ASENSOR_FIFO_COUNT_INVALID = -1;
enum ASENSOR_DELAY_INVALID = INT32_MIN;

/* (Keep in sync with hardware/sensors-base.h and Sensor.java.) */

/**
 * Sensor types.
 *
 * See
 * [android.hardware.SensorEvent#values](https://developer.android.com/reference/android/hardware/SensorEvent.html#values)
 * for detailed explanations of the data returned for each of these types.
 */
enum
{
	/**
	 * Invalid sensor type. Returned by {@link ASensor_getType} as error value.
	 */
	ASENSOR_TYPE_INVALID = -1,
	/**
	 * {@link ASENSOR_TYPE_ACCELEROMETER}
	 * reporting-mode: continuous
	 *
	 *  All values are in SI units (m/s^2) and measure the acceleration of the
	 *  device minus the force of gravity.
	 */
	ASENSOR_TYPE_ACCELEROMETER = 1,
	/**
	 * {@link ASENSOR_TYPE_MAGNETIC_FIELD}
	 * reporting-mode: continuous
	 *
	 *  All values are in micro-Tesla (uT) and measure the geomagnetic
	 *  field in the X, Y and Z axis.
	 */
	ASENSOR_TYPE_MAGNETIC_FIELD = 2,
	/**
	 * {@link ASENSOR_TYPE_GYROSCOPE}
	 * reporting-mode: continuous
	 *
	 *  All values are in radians/second and measure the rate of rotation
	 *  around the X, Y and Z axis.
	 */
	ASENSOR_TYPE_GYROSCOPE = 4,
	/**
	 * {@link ASENSOR_TYPE_LIGHT}
	 * reporting-mode: on-change
	 *
	 * The light sensor value is returned in SI lux units.
	 */
	ASENSOR_TYPE_LIGHT = 5,
	/**
	 * {@link ASENSOR_TYPE_PRESSURE}
	 *
	 * The pressure sensor value is returned in hPa (millibar).
	 */
	ASENSOR_TYPE_PRESSURE = 6,
	/**
	 * {@link ASENSOR_TYPE_PROXIMITY}
	 * reporting-mode: on-change
	 *
	 * The proximity sensor which turns the screen off and back on during calls is the
	 * wake-up proximity sensor. Implement wake-up proximity sensor before implementing
	 * a non wake-up proximity sensor. For the wake-up proximity sensor set the flag
	 * SENSOR_FLAG_WAKE_UP.
	 * The value corresponds to the distance to the nearest object in centimeters.
	 */
	ASENSOR_TYPE_PROXIMITY = 8,
	/**
	 * {@link ASENSOR_TYPE_GRAVITY}
	 *
	 * All values are in SI units (m/s^2) and measure the direction and
	 * magnitude of gravity. When the device is at rest, the output of
	 * the gravity sensor should be identical to that of the accelerometer.
	 */
	ASENSOR_TYPE_GRAVITY = 9,
	/**
	 * {@link ASENSOR_TYPE_LINEAR_ACCELERATION}
	 * reporting-mode: continuous
	 *
	 *  All values are in SI units (m/s^2) and measure the acceleration of the
	 *  device not including the force of gravity.
	 */
	ASENSOR_TYPE_LINEAR_ACCELERATION = 10,
	/**
	 * {@link ASENSOR_TYPE_ROTATION_VECTOR}
	 */
	ASENSOR_TYPE_ROTATION_VECTOR = 11,
	/**
	 * {@link ASENSOR_TYPE_RELATIVE_HUMIDITY}
	 *
	 * The relative humidity sensor value is returned in percent.
	 */
	ASENSOR_TYPE_RELATIVE_HUMIDITY = 12,
	/**
	 * {@link ASENSOR_TYPE_AMBIENT_TEMPERATURE}
	 *
	 * The ambient temperature sensor value is returned in Celcius.
	 */
	ASENSOR_TYPE_AMBIENT_TEMPERATURE = 13,
	/**
	 * {@link ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED}
	 */
	ASENSOR_TYPE_MAGNETIC_FIELD_UNCALIBRATED = 14,
	/**
	 * {@link ASENSOR_TYPE_GAME_ROTATION_VECTOR}
	 */
	ASENSOR_TYPE_GAME_ROTATION_VECTOR = 15,
	/**
	 * {@link ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED}
	 */
	ASENSOR_TYPE_GYROSCOPE_UNCALIBRATED = 16,
	/**
	 * {@link ASENSOR_TYPE_SIGNIFICANT_MOTION}
	 */
	ASENSOR_TYPE_SIGNIFICANT_MOTION = 17,
	/**
	 * {@link ASENSOR_TYPE_STEP_DETECTOR}
	 */
	ASENSOR_TYPE_STEP_DETECTOR = 18,
	/**
	 * {@link ASENSOR_TYPE_STEP_COUNTER}
	 */
	ASENSOR_TYPE_STEP_COUNTER = 19,
	/**
	 * {@link ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR}
	 */
	ASENSOR_TYPE_GEOMAGNETIC_ROTATION_VECTOR = 20,
	/**
	 * {@link ASENSOR_TYPE_HEART_RATE}
	 */
	ASENSOR_TYPE_HEART_RATE = 21,
	/**
	 * {@link ASENSOR_TYPE_POSE_6DOF}
	 */
	ASENSOR_TYPE_POSE_6DOF = 28,
	/**
	 * {@link ASENSOR_TYPE_STATIONARY_DETECT}
	 */
	ASENSOR_TYPE_STATIONARY_DETECT = 29,
	/**
	 * {@link ASENSOR_TYPE_MOTION_DETECT}
	 */
	ASENSOR_TYPE_MOTION_DETECT = 30,
	/**
	 * {@link ASENSOR_TYPE_HEART_BEAT}
	 */
	ASENSOR_TYPE_HEART_BEAT = 31,
	/**
	 * {@link ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT}
	 */
	ASENSOR_TYPE_LOW_LATENCY_OFFBODY_DETECT = 34,
	/**
	 * {@link ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED}
	 */
	ASENSOR_TYPE_ACCELEROMETER_UNCALIBRATED = 35
}

/**
 * Sensor accuracy measure.
 */
enum
{
	/** no contact */
	ASENSOR_STATUS_NO_CONTACT = -1,
	/** unreliable */
	ASENSOR_STATUS_UNRELIABLE = 0,
	/** low accuracy */
	ASENSOR_STATUS_ACCURACY_LOW = 1,
	/** medium accuracy */
	ASENSOR_STATUS_ACCURACY_MEDIUM = 2,
	/** high accuracy */
	ASENSOR_STATUS_ACCURACY_HIGH = 3
}

/**
 * Sensor Reporting Modes.
 */
enum
{
	/** invalid reporting mode */
	AREPORTING_MODE_INVALID = -1,
	/** continuous reporting */
	AREPORTING_MODE_CONTINUOUS = 0,
	/** reporting on change */
	AREPORTING_MODE_ON_CHANGE = 1,
	/** on shot reporting */
	AREPORTING_MODE_ONE_SHOT = 2,
	/** special trigger reporting */
	AREPORTING_MODE_SPECIAL_TRIGGER = 3
}

/**
 * Sensor Direct Report Rates.
 */
enum
{
	/** stopped */
	ASENSOR_DIRECT_RATE_STOP = 0,
	/** nominal 50Hz */
	ASENSOR_DIRECT_RATE_NORMAL = 1,
	/** nominal 200Hz */
	ASENSOR_DIRECT_RATE_FAST = 2,
	/** nominal 800Hz */
	ASENSOR_DIRECT_RATE_VERY_FAST = 3
}

/**
 * Sensor Direct Channel Type.
 */
enum
{
	/** shared memory created by ASharedMemory_create */
	ASENSOR_DIRECT_CHANNEL_TYPE_SHARED_MEMORY = 1,
	/** AHardwareBuffer */
	ASENSOR_DIRECT_CHANNEL_TYPE_HARDWARE_BUFFER = 2
}

/*
 * A few useful constants
 */

/** Earth's gravity in m/s^2 */
enum ASENSOR_STANDARD_GRAVITY = 9.80665f;
/** Maximum magnetic field on Earth's surface in uT */
enum ASENSOR_MAGNETIC_FIELD_EARTH_MAX = 60.0f;
/** Minimum magnetic field on Earth's surface in uT*/
enum ASENSOR_MAGNETIC_FIELD_EARTH_MIN = 30.0f;

/**
 * A sensor event.
 */

/* NOTE: changes to these structs have to be backward compatible */
struct ASensorVector
{
	union
	{
		float[3] v;

		struct
		{
			float x;
			float y;
			float z;
		}

		struct
		{
			float azimuth;
			float pitch;
			float roll;
		}
	}

	byte status;
	ubyte[3] reserved;
}

struct AMetaDataEvent
{
	int what;
	int sensor;
}

struct AUncalibratedEvent
{
	union
	{
		float[3] uncalib;

		struct
		{
			float x_uncalib;
			float y_uncalib;
			float z_uncalib;
		}
	}

	union
	{
		float[3] bias;

		struct
		{
			float x_bias;
			float y_bias;
			float z_bias;
		}
	}
}

struct AHeartRateEvent
{
	float bpm;
	byte status;
}

struct ADynamicSensorEvent
{
	int connected;
	int handle;
}

struct AAdditionalInfoEvent
{
	int type;
	int serial;

	union
	{
		int[14] data_int32;
		float[14] data_float;
	}
}

/* NOTE: changes to this struct has to be backward compatible */
struct ASensorEvent
{
	int version_; /* sizeof(struct ASensorEvent) */
	int sensor;
	int type;
	int reserved0;
	long timestamp;

	union
	{
		union
		{
			float[16] data;
			ASensorVector vector;
			ASensorVector acceleration;
			ASensorVector magnetic;
			float temperature;
			float distance;
			float light;
			float pressure;
			float relative_humidity;
			AUncalibratedEvent uncalibrated_gyro;
			AUncalibratedEvent uncalibrated_magnetic;
			AMetaDataEvent meta_data;
			AHeartRateEvent heart_rate;
			ADynamicSensorEvent dynamic_sensor_meta;
			AAdditionalInfoEvent additional_info;
		}

		union _Anonymous_0
		{
			ulong[8] data;
			ulong step_counter;
		}

		_Anonymous_0 u64;
	}

	uint flags;
	int[3] reserved1;
}

struct ASensorManager;
/**
 * {@link ASensorManager} is an opaque type to manage sensors and
 * events queues.
 *
 * {@link ASensorManager} is a singleton that can be obtained using
 * ASensorManager_getInstance().
 *
 * This file provides a set of functions that uses {@link
 * ASensorManager} to access and list hardware sensors, and
 * create and destroy event queues:
 * - ASensorManager_getSensorList()
 * - ASensorManager_getDefaultSensor()
 * - ASensorManager_getDefaultSensorEx()
 * - ASensorManager_createEventQueue()
 * - ASensorManager_destroyEventQueue()
 */

struct ASensorEventQueue;
/**
 * {@link ASensorEventQueue} is an opaque type that provides access to
 * {@link ASensorEvent} from hardware sensors.
 *
 * A new {@link ASensorEventQueue} can be obtained using ASensorManager_createEventQueue().
 *
 * This file provides a set of functions to enable and disable
 * sensors, check and get events, and set event rates on a {@link
 * ASensorEventQueue}.
 * - ASensorEventQueue_enableSensor()
 * - ASensorEventQueue_disableSensor()
 * - ASensorEventQueue_hasEvents()
 * - ASensorEventQueue_getEvents()
 * - ASensorEventQueue_setEventRate()
 */

struct ASensor;
/**
 * {@link ASensor} is an opaque type that provides information about
 * an hardware sensors.
 *
 * A {@link ASensor} pointer can be obtained using
 * ASensorManager_getDefaultSensor(),
 * ASensorManager_getDefaultSensorEx() or from a {@link ASensorList}.
 *
 * This file provides a set of functions to access properties of a
 * {@link ASensor}:
 * - ASensor_getName()
 * - ASensor_getVendor()
 * - ASensor_getType()
 * - ASensor_getResolution()
 * - ASensor_getMinDelay()
 * - ASensor_getFifoMaxEventCount()
 * - ASensor_getFifoReservedEventCount()
 * - ASensor_getStringType()
 * - ASensor_getReportingMode()
 * - ASensor_isWakeUpSensor()
 */
/**
 * {@link ASensorRef} is a type for constant pointers to {@link ASensor}.
 *
 * This is used to define entry in {@link ASensorList} arrays.
 */
alias ASensorRef = const(ASensor)*;
/**
 * {@link ASensorList} is an array of reference to {@link ASensor}.
 *
 * A {@link ASensorList} can be initialized using ASensorManager_getSensorList().
 */
alias ASensorList = const(ASensor*)*;

/*****************************************************************************/

/**
 * Get a reference to the sensor manager. ASensorManager is a singleton
 * per package as different packages may have access to different sensors.
 *
 * Deprecated: Use ASensorManager_getInstanceForPackage(const char*) instead.
 *
 * Example:
 *
 *     ASensorManager* sensorManager = ASensorManager_getInstance();
 *
 */
ASensorManager* ASensorManager_getInstance ();

/**
 * Get a reference to the sensor manager. ASensorManager is a singleton
 * per package as different packages may have access to different sensors.
 *
 * Example:
 *
 *     ASensorManager* sensorManager = ASensorManager_getInstanceForPackage("foo.bar.baz");
 *
 */
ASensorManager* ASensorManager_getInstanceForPackage (const(char)* packageName);

/**
 * Returns the list of available sensors.
 */
int ASensorManager_getSensorList (ASensorManager* manager, ASensorList* list);

/**
 * Returns the default sensor for the given type, or NULL if no sensor
 * of that type exists.
 */
const(ASensor)* ASensorManager_getDefaultSensor (ASensorManager* manager, int type);

/**
 * Returns the default sensor with the given type and wakeUp properties or NULL if no sensor
 * of this type and wakeUp properties exists.
 */
const(ASensor)* ASensorManager_getDefaultSensorEx (ASensorManager* manager, int type, bool wakeUp);

/**
 * Creates a new sensor event queue and associate it with a looper.
 *
 * "ident" is a identifier for the events that will be returned when
 * calling ALooper_pollOnce(). The identifier must be >= 0, or
 * ALOOPER_POLL_CALLBACK if providing a non-NULL callback.
 */
ASensorEventQueue* ASensorManager_createEventQueue (
	ASensorManager* manager,
	ALooper* looper,
	int ident,
	ALooper_callbackFunc callback,
	void* data);

/**
 * Destroys the event queue and free all resources associated to it.
 */
int ASensorManager_destroyEventQueue (ASensorManager* manager, ASensorEventQueue* queue);

/**
 * Create direct channel based on shared memory
 *
 * Create a direct channel of {@link ASENSOR_DIRECT_CHANNEL_TYPE_SHARED_MEMORY} to be used
 * for configuring sensor direct report.
 *
 * \param manager the {@link ASensorManager} instance obtained from
 *                {@link ASensorManager_getInstanceForPackage}.
 * \param fd      file descriptor representing a shared memory created by
 *                {@link ASharedMemory_create}
 * \param size    size to be used, must be less or equal to size of shared memory.
 *
 * \return a positive integer as a channel id to be used in
 *         {@link ASensorManager_destroyDirectChannel} and
 *         {@link ASensorManager_configureDirectReport}, or value less or equal to 0 for failures.
 */
int ASensorManager_createSharedMemoryDirectChannel (ASensorManager* manager, int fd, size_t size);

/**
 * Create direct channel based on AHardwareBuffer
 *
 * Create a direct channel of {@link ASENSOR_DIRECT_CHANNEL_TYPE_HARDWARE_BUFFER} type to be used
 * for configuring sensor direct report.
 *
 * \param manager the {@link ASensorManager} instance obtained from
 *                {@link ASensorManager_getInstanceForPackage}.
 * \param buffer  {@link AHardwareBuffer} instance created by {@link AHardwareBuffer_allocate}.
 * \param size    the intended size to be used, must be less or equal to size of buffer.
 *
 * \return a positive integer as a channel id to be used in
 *         {@link ASensorManager_destroyDirectChannel} and
 *         {@link ASensorManager_configureDirectReport}, or value less or equal to 0 for failures.
 */
int ASensorManager_createHardwareBufferDirectChannel (
	ASensorManager* manager,
	const(AHardwareBuffer)* buffer,
	size_t size);

/**
 * Destroy a direct channel
 *
 * Destroy a direct channel previously created using {@link ASensorManager_createDirectChannel}.
 * The buffer used for creating direct channel does not get destroyed with
 * {@link ASensorManager_destroy} and has to be close or released separately.
 *
 * \param manager the {@link ASensorManager} instance obtained from
 *                {@link ASensorManager_getInstanceForPackage}.
 * \param channelId channel id (a positive integer) returned from
 *                  {@link ASensorManager_createSharedMemoryDirectChannel} or
 *                  {@link ASensorManager_createHardwareBufferDirectChannel}.
 */
void ASensorManager_destroyDirectChannel (ASensorManager* manager, int channelId);

/**
 * Configure direct report on channel
 *
 * Configure sensor direct report on a direct channel: set rate to value other than
 * {@link ASENSOR_DIRECT_RATE_STOP} so that sensor event can be directly
 * written into the shared memory region used for creating the buffer. It returns a positive token
 * which can be used for identify sensor events from different sensors on success. Calling with rate
 * {@link ASENSOR_DIRECT_RATE_STOP} will stop direct report of the sensor specified in the channel.
 *
 * To stop all active sensor direct report configured to a channel, set sensor to NULL and rate to
 * {@link ASENSOR_DIRECT_RATE_STOP}.
 *
 * In order to successfully configure a direct report, the sensor has to support the specified rate
 * and the channel type, which can be checked by {@link ASensor_getHighestDirectReportRateLevel} and
 * {@link ASensor_isDirectChannelTypeSupported}, respectively.
 *
 * Example:
 *
 *     ASensorManager *manager = ...;
 *     ASensor *sensor = ...;
 *     int channelId = ...;
 *
 *     ASensorManager_configureDirectReport(manager, sensor, channel_id, ASENSOR_DIRECT_RATE_FAST);
 *
 * \param manager   the {@link ASensorManager} instance obtained from
 *                  {@link ASensorManager_getInstanceForPackage}.
 * \param sensor    a {@link ASensor} to denote which sensor to be operate. It can be NULL if rate
 *                  is {@link ASENSOR_DIRECT_RATE_STOP}, denoting stopping of all active sensor
 *                  direct report.
 * \param channelId channel id (a positive integer) returned from
 *                  {@link ASensorManager_createSharedMemoryDirectChannel} or
 *                  {@link ASensorManager_createHardwareBufferDirectChannel}.
 *
 * \return positive token for success or negative error code.
 */
int ASensorManager_configureDirectReport (
	ASensorManager* manager,
	const(ASensor)* sensor,
	int channelId,
	int rate);
/* __ANDROID_API__ >= 26 */

/*****************************************************************************/

/**
 * Enable the selected sensor with sampling and report parameters
 *
 * Enable the selected sensor at a specified sampling period and max batch report latency.
 * To disable  sensor, use {@link ASensorEventQueue_disableSensor}.
 *
 * \param queue {@link ASensorEventQueue} for sensor event to be report to.
 * \param sensor {@link ASensor} to be enabled.
 * \param samplingPeriodUs sampling period of sensor in microseconds.
 * \param maxBatchReportLatencyus maximum time interval between two batch of sensor events are
 *                                delievered in microseconds. For sensor streaming, set to 0.
 * \return 0 on success or a negative error code on failure.
 */
int ASensorEventQueue_registerSensor (
	ASensorEventQueue* queue,
	const(ASensor)* sensor,
	int samplingPeriodUs,
	long maxBatchReportLatencyUs);

/**
 * Enable the selected sensor at default sampling rate.
 *
 * Start event reports of a sensor to specified sensor event queue at a default rate.
 *
 * \param queue {@link ASensorEventQueue} for sensor event to be report to.
 * \param sensor {@link ASensor} to be enabled.
 *
 * \return 0 on success or a negative error code on failure.
 */
int ASensorEventQueue_enableSensor (ASensorEventQueue* queue, const(ASensor)* sensor);

/**
 * Disable the selected sensor.
 *
 * Stop event reports from the sensor to specified sensor event queue.
 *
 * \param queue {@link ASensorEventQueue} to be changed
 * \param sensor {@link ASensor} to be disabled
 * \return 0 on success or a negative error code on failure.
 */
int ASensorEventQueue_disableSensor (ASensorEventQueue* queue, const(ASensor)* sensor);

/**
 * Sets the delivery rate of events in microseconds for the given sensor.
 *
 * This function has to be called after {@link ASensorEventQueue_enableSensor}.
 * Note that this is a hint only, generally event will arrive at a higher
 * rate. It is an error to set a rate inferior to the value returned by
 * ASensor_getMinDelay().
 *
 * \param queue {@link ASensorEventQueue} to which sensor event is delivered.
 * \param sensor {@link ASensor} of which sampling rate to be updated.
 * \param usec sensor sampling period (1/sampling rate) in microseconds
 * \return 0 on sucess or a negative error code on failure.
 */
int ASensorEventQueue_setEventRate (ASensorEventQueue* queue, const(ASensor)* sensor, int usec);

/**
 * Determine if a sensor event queue has pending event to be processed.
 *
 * \param queue {@link ASensorEventQueue} to be queried
 * \return 1 if the queue has events; 0 if it does not have events;
 *         or a negative value if there is an error.
 */
int ASensorEventQueue_hasEvents (ASensorEventQueue* queue);

/**
 * Retrieve pending events in sensor event queue
 *
 * Retrieve next available events from the queue to a specified event array.
 *
 * \param queue {@link ASensorEventQueue} to get events from
 * \param events pointer to an array of {@link ASensorEvents}.
 * \param count max number of event that can be filled into array event.
 * \return number of events returned on success; negative error code when
 *         no events are pending or an error has occurred.
 *
 * Examples:
 *
 *     ASensorEvent event;
 *     ssize_t numEvent = ASensorEventQueue_getEvents(queue, &event, 1);
 *
 *     ASensorEvent eventBuffer[8];
 *     ssize_t numEvent = ASensorEventQueue_getEvents(queue, eventBuffer, 8);
 *
 */
ssize_t ASensorEventQueue_getEvents (ASensorEventQueue* queue, ASensorEvent* events, size_t count);

/*****************************************************************************/

/**
 * Returns this sensor's name (non localized)
 */
const(char)* ASensor_getName (const(ASensor)* sensor);

/**
 * Returns this sensor's vendor's name (non localized)
 */
const(char)* ASensor_getVendor (const(ASensor)* sensor);

/**
 * Return this sensor's type
 */
int ASensor_getType (const(ASensor)* sensor);

/**
 * Returns this sensors's resolution
 */
float ASensor_getResolution (const(ASensor)* sensor);

/**
 * Returns the minimum delay allowed between events in microseconds.
 * A value of zero means that this sensor doesn't report events at a
 * constant rate, but rather only when a new data is available.
 */
int ASensor_getMinDelay (const(ASensor)* sensor);

/**
 * Returns the maximum size of batches for this sensor. Batches will often be
 * smaller, as the hardware fifo might be used for other sensors.
 */
int ASensor_getFifoMaxEventCount (const(ASensor)* sensor);

/**
 * Returns the hardware batch fifo size reserved to this sensor.
 */
int ASensor_getFifoReservedEventCount (const(ASensor)* sensor);

/**
 * Returns this sensor's string type.
 */
const(char)* ASensor_getStringType (const(ASensor)* sensor);

/**
 * Returns the reporting mode for this sensor. One of AREPORTING_MODE_* constants.
 */
int ASensor_getReportingMode (const(ASensor)* sensor);

/**
 * Returns true if this is a wake up sensor, false otherwise.
 */
bool ASensor_isWakeUpSensor (const(ASensor)* sensor);
/* __ANDROID_API__ >= 21 */

/**
 * Test if sensor supports a certain type of direct channel.
 *
 * \param sensor  a {@link ASensor} to denote the sensor to be checked.
 * \param channelType  Channel type constant, either
 *                     {@ASENSOR_DIRECT_CHANNEL_TYPE_SHARED_MEMORY}
 *                     or {@link ASENSOR_DIRECT_CHANNEL_TYPE_HARDWARE_BUFFER}.
 * \returns true if sensor supports the specified direct channel type.
 */
bool ASensor_isDirectChannelTypeSupported (const(ASensor)* sensor, int channelType);

/**
 * Get the highest direct rate level that a sensor support.
 *
 * \param sensor  a {@link ASensor} to denote the sensor to be checked.
 *
 * \return a ASENSOR_DIRECT_RATE_... enum denoting the highest rate level supported by the sensor.
 *         If return value is {@link ASENSOR_DIRECT_RATE_STOP}, it means the sensor
 *         does not support direct report.
 */
int ASensor_getHighestDirectReportRateLevel (const(ASensor)* sensor);
/* __ANDROID_API__ >= 26 */

// ANDROID_SENSOR_H

/** @} */
