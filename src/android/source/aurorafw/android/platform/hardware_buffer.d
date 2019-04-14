/*
									__
									/ _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2017 The Android Open Source Project.
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

module aurorafw.android.platform.hardware_buffer;

/**
 * @addtogroup NativeActivity Native Activity
 * @{
 */

/**
 * @file aurorafw/android/platform/hardware_buffer.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * Buffer pixel formats.
 */
enum
{
	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_R8G8B8A8_UNORM
	 *   OpenGL ES: GL_RGBA8
	 */
	AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM = 1,

	/**
	 * 32 bits per pixel, 8 bits per channel format where alpha values are
	 * ignored (always opaque).
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_R8G8B8A8_UNORM
	 *   OpenGL ES: GL_RGB8
	 */
	AHARDWAREBUFFER_FORMAT_R8G8B8X8_UNORM = 2,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_R8G8B8_UNORM
	 *   OpenGL ES: GL_RGB8
	 */
	AHARDWAREBUFFER_FORMAT_R8G8B8_UNORM = 3,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_R5G6B5_UNORM_PACK16
	 *   OpenGL ES: GL_RGB565
	 */
	AHARDWAREBUFFER_FORMAT_R5G6B5_UNORM = 4,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_R16G16B16A16_SFLOAT
	 *   OpenGL ES: GL_RGBA16F
	 */
	AHARDWAREBUFFER_FORMAT_R16G16B16A16_FLOAT = 22,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_A2B10G10R10_UNORM_PACK32
	 *   OpenGL ES: GL_RGB10_A2
	 */
	AHARDWAREBUFFER_FORMAT_R10G10B10A2_UNORM = 43,

	/**
	 * An opaque binary blob format that must have height 1, with width equal to
	 * the buffer size in bytes.
	 */
	AHARDWAREBUFFER_FORMAT_BLOB = 33,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_D16_UNORM
	 *   OpenGL ES: GL_DEPTH_COMPONENT16
	 */
	AHARDWAREBUFFER_FORMAT_D16_UNORM = 48,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_X8_D24_UNORM_PACK32
	 *   OpenGL ES: GL_DEPTH_COMPONENT24
	 */
	AHARDWAREBUFFER_FORMAT_D24_UNORM = 49,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_D24_UNORM_S8_UINT
	 *   OpenGL ES: GL_DEPTH24_STENCIL8
	 */
	AHARDWAREBUFFER_FORMAT_D24_UNORM_S8_UINT = 50,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_D32_SFLOAT
	 *   OpenGL ES: GL_DEPTH_COMPONENT32F
	 */
	AHARDWAREBUFFER_FORMAT_D32_FLOAT = 51,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_D32_SFLOAT_S8_UINT
	 *   OpenGL ES: GL_DEPTH32F_STENCIL8
	 */
	AHARDWAREBUFFER_FORMAT_D32_FLOAT_S8_UINT = 52,

	/**
	 * Corresponding formats:
	 *   Vulkan: VK_FORMAT_S8_UINT
	 *   OpenGL ES: GL_STENCIL_INDEX8
	 */
	AHARDWAREBUFFER_FORMAT_S8_UINT = 53
}

/**
 * Buffer usage flags, specifying how the buffer will be accessed.
 */
enum
{
	/// The buffer will never be read by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_READ_NEVER = 0,
	/// The buffer will sometimes be read by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_READ_RARELY = 2,
	/// The buffer will often be read by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_READ_OFTEN = 3,
	/// CPU read value mask.
	AHARDWAREBUFFER_USAGE_CPU_READ_MASK = 15,

	/// The buffer will never be written by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_WRITE_NEVER = 0,
	/// The buffer will sometimes be written to by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_WRITE_RARELY = 32,
	/// The buffer will often be written to by the CPU.
	AHARDWAREBUFFER_USAGE_CPU_WRITE_OFTEN = 48,
	/// CPU write value mask.
	AHARDWAREBUFFER_USAGE_CPU_WRITE_MASK = 240,

	/// The buffer will be read from by the GPU as a texture.
	AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE = 256,
	/**
	 * The buffer will be written to by the GPU as a framebuffer attachment.
	 * Note that the name of this flag is somewhat misleading: it does not imply
	 * that the buffer contains a color format. A buffer with depth or stencil
	 * format that will be used as a framebuffer attachment should also have
	 * this flag.
	 */
	AHARDWAREBUFFER_USAGE_GPU_COLOR_OUTPUT = 512,
	/// The buffer must not be used outside of a protected hardware path.
	AHARDWAREBUFFER_USAGE_PROTECTED_CONTENT = 16384,
	/// The buffer will be read by a hardware video encoder.
	AHARDWAREBUFFER_USAGE_VIDEO_ENCODE = 65536,
	/// The buffer will be used for direct writes from sensors.
	AHARDWAREBUFFER_USAGE_SENSOR_DIRECT_DATA = 8388608,
	/// The buffer will be used as a shader storage or uniform buffer object.
	AHARDWAREBUFFER_USAGE_GPU_DATA_BUFFER = 16777216,
	/// The buffer will be used as a cube map texture.
	AHARDWAREBUFFER_USAGE_GPU_CUBE_MAP = 33554432,
	/// The buffer contains a complete mipmap hierarchy.
	AHARDWAREBUFFER_USAGE_GPU_MIPMAP_COMPLETE = 67108864,

	AHARDWAREBUFFER_USAGE_VENDOR_0 = 1UL << 28,
	AHARDWAREBUFFER_USAGE_VENDOR_1 = 1UL << 29,
	AHARDWAREBUFFER_USAGE_VENDOR_2 = 1UL << 30,
	AHARDWAREBUFFER_USAGE_VENDOR_3 = 1UL << 31,
	AHARDWAREBUFFER_USAGE_VENDOR_4 = 1UL << 48,
	AHARDWAREBUFFER_USAGE_VENDOR_5 = 1UL << 49,
	AHARDWAREBUFFER_USAGE_VENDOR_6 = 1UL << 50,
	AHARDWAREBUFFER_USAGE_VENDOR_7 = 1UL << 51,
	AHARDWAREBUFFER_USAGE_VENDOR_8 = 1UL << 52,
	AHARDWAREBUFFER_USAGE_VENDOR_9 = 1UL << 53,
	AHARDWAREBUFFER_USAGE_VENDOR_10 = 1UL << 54,
	AHARDWAREBUFFER_USAGE_VENDOR_11 = 1UL << 55,
	AHARDWAREBUFFER_USAGE_VENDOR_12 = 1UL << 56,
	AHARDWAREBUFFER_USAGE_VENDOR_13 = 1UL << 57,
	AHARDWAREBUFFER_USAGE_VENDOR_14 = 1UL << 58,
	AHARDWAREBUFFER_USAGE_VENDOR_15 = 1UL << 59,
	AHARDWAREBUFFER_USAGE_VENDOR_16 = 1UL << 60,
	AHARDWAREBUFFER_USAGE_VENDOR_17 = 1UL << 61,
	AHARDWAREBUFFER_USAGE_VENDOR_18 = 1UL << 62,
	AHARDWAREBUFFER_USAGE_VENDOR_19 = 1UL << 63
}

/**
 * Buffer description. Used for allocating new buffers and querying parameters
 * of existing ones.
 */
struct AHardwareBuffer_Desc
{
	uint width; ///< Width in pixels.
	uint height; ///< Height in pixels.
	uint layers; ///< Number of images in an image array.
	uint format; ///< One of AHARDWAREBUFFER_FORMAT_*
	ulong usage; ///< Combination of AHARDWAREBUFFER_USAGE_*
	uint stride; ///< Row stride in pixels, ignored for AHardwareBuffer_allocate()
	uint rfu0; ///< Initialize to zero, reserved for future use.
	ulong rfu1; ///< Initialize to zero, reserved for future use.
}

struct AHardwareBuffer;

/**
 * Allocates a buffer that backs an AHardwareBuffer using the passed
 * AHardwareBuffer_Desc.
 *
 * \return 0 on success, or an error number of the allocation fails for
 * any reason. The returned buffer has a reference count of 1.
 */
int AHardwareBuffer_allocate (
	const(AHardwareBuffer_Desc)* desc,
	AHardwareBuffer** outBuffer);
/**
 * Acquire a reference on the given AHardwareBuffer object.  This prevents the
 * object from being deleted until the last reference is removed.
 */
void AHardwareBuffer_acquire (AHardwareBuffer* buffer);

/**
 * Remove a reference that was previously acquired with
 * AHardwareBuffer_acquire().
 */
void AHardwareBuffer_release (AHardwareBuffer* buffer);

/**
 * Return a description of the AHardwareBuffer in the passed
 * AHardwareBuffer_Desc struct.
 */
void AHardwareBuffer_describe (
	const(AHardwareBuffer)* buffer,
	AHardwareBuffer_Desc* outDesc);

/**
 * Lock the AHardwareBuffer for reading or writing, depending on the usage flags
 * passed.  This call may block if the hardware needs to finish rendering or if
 * CPU caches need to be synchronized, or possibly for other implementation-
 * specific reasons.  If fence is not negative, then it specifies a fence file
 * descriptor that will be signaled when the buffer is locked, otherwise the
 * caller will block until the buffer is available.
 *
 * If \a rect is not NULL, the caller promises to modify only data in the area
 * specified by rect. If rect is NULL, the caller may modify the contents of the
 * entire buffer.
 *
 * The content of the buffer outside of the specified rect is NOT modified
 * by this call.
 *
 * The \a usage parameter may only specify AHARDWAREBUFFER_USAGE_CPU_*. If set,
 * then outVirtualAddress is filled with the address of the buffer in virtual
 * memory.
 *
 * THREADING CONSIDERATIONS:
 *
 * It is legal for several different threads to lock a buffer for read access;
 * none of the threads are blocked.
 *
 * Locking a buffer simultaneously for write or read/write is undefined, but
 * will neither terminate the process nor block the caller; AHardwareBuffer_lock
 * may return an error or leave the buffer's content into an indeterminate
 * state.
 *
 * \return 0 on success, -EINVAL if \a buffer is NULL or if the usage
 * flags are not a combination of AHARDWAREBUFFER_USAGE_CPU_*, or an error
 * number of the lock fails for any reason.
 */
int AHardwareBuffer_lock (
	AHardwareBuffer* buffer,
	ulong usage,
	int fence,
	const(ARect)* rect,
	void** outVirtualAddress);

/**
 * Unlock the AHardwareBuffer; must be called after all changes to the buffer
 * are completed by the caller. If fence is not NULL then it will be set to a
 * file descriptor that is signaled when all pending work on the buffer is
 * completed. The caller is responsible for closing the fence when it is no
 * longer needed.
 *
 * \return 0 on success, -EINVAL if \a buffer is NULL, or an error
 * number if the unlock fails for any reason.
 */
int AHardwareBuffer_unlock (AHardwareBuffer* buffer, int* fence);

/**
 * Send the AHardwareBuffer to an AF_UNIX socket.
 *
 * \return 0 on success, -EINVAL if \a buffer is NULL, or an error
 * number if the operation fails for any reason.
 */
int AHardwareBuffer_sendHandleToUnixSocket (const(AHardwareBuffer)* buffer, int socketFd);

/**
 * Receive the AHardwareBuffer from an AF_UNIX socket.
 *
 * \return 0 on success, -EINVAL if \a outBuffer is NULL, or an error
 * number if the operation fails for any reason.
 */
int AHardwareBuffer_recvHandleFromUnixSocket (int socketFd, AHardwareBuffer** outBuffer);

// __ANDROID_API__ >= 26

// ANDROID_HARDWARE_BUFFER_H

/** @} */
