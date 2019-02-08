/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

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
http://www.gnu.org/licenses/gpl-3.0.html.

NOTE: All products, services or anything associated to trademarks and
service marks used or referenced on this file are the property of their
respective companies/owners or its subsidiaries. Other names and brands
may be claimed as the property of others.

For more info about intellectual property visit: aurorafoss.org or
directly send an email to: contact (at) aurorafoss.org .
*/

module aurorafw.graphics.platform.opengl.egl;

// types
import core.stdc.stdint : intptr_t;

alias EGLConfig = void*;
alias EGLClientBuffer = void*;
alias EGLNativeFileDescriptorKHR = int;
alias EGLuint64KHR = ulong;
alias EGLTimeKHR = ulong;
alias EGLOutputLayerEXT = void*;
alias EGLsizeiANDROID = ptrdiff_t;
alias EGLBoolean = uint;
alias EGLAttribKHR = intptr_t;
alias EGLDisplay = void*;
alias EGLint = int;
alias EGLSyncKHR = void*;
alias EGLTimeNV = ulong;
alias EGLDeviceEXT = void*;
alias EGLImageKHR = void*;
alias EGLSurface = void*;
alias __eglMustCastToProperFunctionPointerType = void function();
alias EGLAttrib = intptr_t;
alias EGLContext = void*;
alias EGLuint64MESA = ulong;
alias EGLenum = uint;
alias EGLImage = void*;
alias EGLSyncNV = void*;
alias EGLStreamKHR = void*;
alias EGLSync = void*;
alias EGLOutputPortEXT = void*;
alias EGLuint64NV = ulong;
alias EGLTime = ulong;

// Thanks to @jpf91 (github) for these declarations
version(Windows) {
	import core.sys.windows.windows;
	alias EGLNativeDisplayType = HDC;
	alias EGLNativePixmapType = HBITMAP;
	alias EGLNativeWindowType = HWND;
} else version(Symbian) {
	alias EGLNativeDisplayType = int;
	alias EGLNativeWindowType = void*;
	alias EGLNativePixmapType = void*;
} else version(Android) {
	//import android.native_window;
	//struct egl_native_pixmap_t;
	struct _egl_native_pixmap_t; alias egl_native_pixmap_t = _egl_native_pixmap_t*;

	//alias ANativeWindow*           EGLNativeWindowType;
	//alias egl_native_pixmap_t*     EGLNativePixmapType;
	alias EGLNativeWindowType = void*;
	alias EGLNativePixmapType = void*;
	alias EGLNativeDisplayType = void*;
} else version(linux) {
	alias EGLNativeDisplayType = void*;
	alias EGLNativePixmapType = uint;
	alias EGLNativeWindowType = uint;
}
alias EGLObjectKHR = void*;
alias EGLLabelKHR = void*;

extern(System) {
alias EGLSetBlobFuncANDROID = void function(const(void)*, EGLsizeiANDROID, const(void)*, EGLsizeiANDROID);
alias EGLGetBlobFuncANDROID = EGLsizeiANDROID function(const(void)*, EGLsizeiANDROID, const(void)* EGLsizeiANDROID);
struct EGLClientPixmapHI {
	void  *pData;
	EGLint iWidth;
	EGLint iHeight;
	EGLint iStride;
}
alias EGLDEBUGPROCKHR = void function(EGLenum error,const char *command,EGLint messageType,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,const char* message);
}
extern(System) {
struct __cl_event; alias _cl_event = __cl_event*;
}

import aurorafw.graphics.platform.khr.khrplatform;
alias EGLnsecsANDROID = khronos_stime_nanoseconds_t;

//enums
enum int EGL_DONT_CARE = -1;
enum int EGL_UNKNOWN = -1;
enum uint EGL_NO_NATIVE_FENCE_FD_ANDROID = -1;
enum uint EGL_DEPTH_ENCODING_NONE_NV = 0;
enum EGLContext EGL_NO_CONTEXT = cast(EGLContext)0;
enum EGLDeviceEXT EGL_NO_DEVICE_EXT = cast(EGLDeviceEXT)0;
enum EGLDisplay EGL_NO_DISPLAY = cast(EGLDisplay)0;
enum EGLImage EGL_NO_IMAGE = cast(EGLImage)0;
enum EGLImageKHR EGL_NO_IMAGE_KHR = cast(EGLImageKHR)0;
enum EGLNativeDisplayType EGL_DEFAULT_DISPLAY = cast(EGLNativeDisplayType)0;
enum EGLNativeFileDescriptorKHR EGL_NO_FILE_DESCRIPTOR_KHR = cast(EGLNativeFileDescriptorKHR)-1;
enum EGLOutputLayerEXT EGL_NO_OUTPUT_LAYER_EXT = cast(EGLOutputLayerEXT)0;
enum EGLOutputPortEXT EGL_NO_OUTPUT_PORT_EXT = cast(EGLOutputPortEXT)0;
enum EGLStreamKHR EGL_NO_STREAM_KHR = cast(EGLStreamKHR)0;
enum EGLSurface EGL_NO_SURFACE = cast(EGLSurface)0;
enum EGLSync EGL_NO_SYNC = cast(EGLSync)0;
enum EGLSyncKHR EGL_NO_SYNC_KHR = cast(EGLSyncKHR)0;
enum EGLSyncNV EGL_NO_SYNC_NV = cast(EGLSyncNV)0;
enum uint EGL_DISPLAY_SCALING = 10000;
enum ulong EGL_FOREVER = 0xFFFFFFFFFFFFFFFF;
enum ulong EGL_FOREVER_KHR = 0xFFFFFFFFFFFFFFFF;
enum ulong EGL_FOREVER_NV = 0xFFFFFFFFFFFFFFFF;
enum uint EGL_ALPHA_SIZE = 0x3021;
enum uint EGL_BAD_ACCESS = 0x3002;
enum uint EGL_BAD_ALLOC = 0x3003;
enum uint EGL_BAD_ATTRIBUTE = 0x3004;
enum uint EGL_BAD_CONFIG = 0x3005;
enum uint EGL_BAD_CONTEXT = 0x3006;
enum uint EGL_BAD_CURRENT_SURFACE = 0x3007;
enum uint EGL_BAD_DISPLAY = 0x3008;
enum uint EGL_BAD_MATCH = 0x3009;
enum uint EGL_BAD_NATIVE_PIXMAP = 0x300A;
enum uint EGL_BAD_NATIVE_WINDOW = 0x300B;
enum uint EGL_BAD_PARAMETER = 0x300C;
enum uint EGL_BAD_SURFACE = 0x300D;
enum uint EGL_BLUE_SIZE = 0x3022;
enum uint EGL_BUFFER_SIZE = 0x3020;
enum uint EGL_CONFIG_CAVEAT = 0x3027;
enum uint EGL_CONFIG_ID = 0x3028;
enum uint EGL_CORE_NATIVE_ENGINE = 0x305B;
enum uint EGL_DEPTH_SIZE = 0x3025;
enum uint EGL_DRAW = 0x3059;
enum uint EGL_EXTENSIONS = 0x3055;
enum uint EGL_FALSE = 0;
enum uint EGL_GREEN_SIZE = 0x3023;
enum uint EGL_HEIGHT = 0x3056;
enum uint EGL_LARGEST_PBUFFER = 0x3058;
enum uint EGL_LEVEL = 0x3029;
enum uint EGL_MAX_PBUFFER_HEIGHT = 0x302A;
enum uint EGL_MAX_PBUFFER_PIXELS = 0x302B;
enum uint EGL_MAX_PBUFFER_WIDTH = 0x302C;
enum uint EGL_NATIVE_RENDERABLE = 0x302D;
enum uint EGL_NATIVE_VISUAL_ID = 0x302E;
enum uint EGL_NATIVE_VISUAL_TYPE = 0x302F;
enum uint EGL_NONE = 0x3038;
enum uint EGL_NON_CONFORMANT_CONFIG = 0x3051;
enum uint EGL_NOT_INITIALIZED = 0x3001;
enum uint EGL_PBUFFER_BIT = 0x0001;
enum uint EGL_PIXMAP_BIT = 0x0002;
enum uint EGL_READ = 0x305A;
enum uint EGL_RED_SIZE = 0x3024;
enum uint EGL_SAMPLES = 0x3031;
enum uint EGL_SAMPLE_BUFFERS = 0x3032;
enum uint EGL_SLOW_CONFIG = 0x3050;
enum uint EGL_STENCIL_SIZE = 0x3026;
enum uint EGL_SUCCESS = 0x3000;
enum uint EGL_SURFACE_TYPE = 0x3033;
enum uint EGL_TRANSPARENT_BLUE_VALUE = 0x3035;
enum uint EGL_TRANSPARENT_GREEN_VALUE = 0x3036;
enum uint EGL_TRANSPARENT_RED_VALUE = 0x3037;
enum uint EGL_TRANSPARENT_RGB = 0x3052;
enum uint EGL_TRANSPARENT_TYPE = 0x3034;
enum uint EGL_TRUE = 1;
enum uint EGL_VENDOR = 0x3053;
enum uint EGL_VERSION = 0x3054;
enum uint EGL_WIDTH = 0x3057;
enum uint EGL_WINDOW_BIT = 0x0004;
enum uint EGL_BACK_BUFFER = 0x3084;
enum uint EGL_BIND_TO_TEXTURE_RGB = 0x3039;
enum uint EGL_BIND_TO_TEXTURE_RGBA = 0x303A;
enum uint EGL_CONTEXT_LOST = 0x300E;
enum uint EGL_MIN_SWAP_INTERVAL = 0x303B;
enum uint EGL_MAX_SWAP_INTERVAL = 0x303C;
enum uint EGL_MIPMAP_TEXTURE = 0x3082;
enum uint EGL_MIPMAP_LEVEL = 0x3083;
enum uint EGL_NO_TEXTURE = 0x305C;
enum uint EGL_TEXTURE_2D = 0x305F;
enum uint EGL_TEXTURE_FORMAT = 0x3080;
enum uint EGL_TEXTURE_RGB = 0x305D;
enum uint EGL_TEXTURE_RGBA = 0x305E;
enum uint EGL_TEXTURE_TARGET = 0x3081;
enum uint EGL_ALPHA_FORMAT = 0x3088;
enum uint EGL_ALPHA_FORMAT_NONPRE = 0x308B;
enum uint EGL_ALPHA_FORMAT_PRE = 0x308C;
enum uint EGL_ALPHA_MASK_SIZE = 0x303E;
enum uint EGL_BUFFER_PRESERVED = 0x3094;
enum uint EGL_BUFFER_DESTROYED = 0x3095;
enum uint EGL_CLIENT_APIS = 0x308D;
enum uint EGL_COLORSPACE = 0x3087;
enum uint EGL_COLORSPACE_sRGB = 0x3089;
enum uint EGL_COLORSPACE_LINEAR = 0x308A;
enum uint EGL_COLOR_BUFFER_TYPE = 0x303F;
enum uint EGL_CONTEXT_CLIENT_TYPE = 0x3097;
enum uint EGL_HORIZONTAL_RESOLUTION = 0x3090;
enum uint EGL_LUMINANCE_BUFFER = 0x308F;
enum uint EGL_LUMINANCE_SIZE = 0x303D;
enum uint EGL_OPENGL_ES_BIT = 0x0001;
enum uint EGL_OPENVG_BIT = 0x0002;
enum uint EGL_OPENGL_ES_API = 0x30A0;
enum uint EGL_OPENVG_API = 0x30A1;
enum uint EGL_OPENVG_IMAGE = 0x3096;
enum uint EGL_PIXEL_ASPECT_RATIO = 0x3092;
enum uint EGL_RENDERABLE_TYPE = 0x3040;
enum uint EGL_RENDER_BUFFER = 0x3086;
enum uint EGL_RGB_BUFFER = 0x308E;
enum uint EGL_SINGLE_BUFFER = 0x3085;
enum uint EGL_SWAP_BEHAVIOR = 0x3093;
enum uint EGL_VERTICAL_RESOLUTION = 0x3091;
enum uint EGL_CONFORMANT = 0x3042;
enum uint EGL_CONTEXT_CLIENT_VERSION = 0x3098;
enum uint EGL_MATCH_NATIVE_PIXMAP = 0x3041;
enum uint EGL_OPENGL_ES2_BIT = 0x0004;
enum uint EGL_VG_ALPHA_FORMAT = 0x3088;
enum uint EGL_VG_ALPHA_FORMAT_NONPRE = 0x308B;
enum uint EGL_VG_ALPHA_FORMAT_PRE = 0x308C;
enum uint EGL_VG_ALPHA_FORMAT_PRE_BIT = 0x0040;
enum uint EGL_VG_COLORSPACE = 0x3087;
enum uint EGL_VG_COLORSPACE_sRGB = 0x3089;
enum uint EGL_VG_COLORSPACE_LINEAR = 0x308A;
enum uint EGL_VG_COLORSPACE_LINEAR_BIT = 0x0020;
enum uint EGL_MULTISAMPLE_RESOLVE_BOX_BIT = 0x0200;
enum uint EGL_MULTISAMPLE_RESOLVE = 0x3099;
enum uint EGL_MULTISAMPLE_RESOLVE_DEFAULT = 0x309A;
enum uint EGL_MULTISAMPLE_RESOLVE_BOX = 0x309B;
enum uint EGL_OPENGL_API = 0x30A2;
enum uint EGL_OPENGL_BIT = 0x0008;
enum uint EGL_SWAP_BEHAVIOR_PRESERVED_BIT = 0x0400;
enum uint EGL_CONTEXT_MAJOR_VERSION = 0x3098;
enum uint EGL_CONTEXT_MINOR_VERSION = 0x30FB;
enum uint EGL_CONTEXT_OPENGL_PROFILE_MASK = 0x30FD;
enum uint EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY = 0x31BD;
enum uint EGL_NO_RESET_NOTIFICATION = 0x31BE;
enum uint EGL_LOSE_CONTEXT_ON_RESET = 0x31BF;
enum uint EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT = 0x00000001;
enum uint EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT = 0x00000002;
enum uint EGL_CONTEXT_OPENGL_DEBUG = 0x31B0;
enum uint EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE = 0x31B1;
enum uint EGL_CONTEXT_OPENGL_ROBUST_ACCESS = 0x31B2;
enum uint EGL_OPENGL_ES3_BIT = 0x00000040;
enum uint EGL_CL_EVENT_HANDLE = 0x309C;
enum uint EGL_SYNC_CL_EVENT = 0x30FE;
enum uint EGL_SYNC_CL_EVENT_COMPLETE = 0x30FF;
enum uint EGL_SYNC_PRIOR_COMMANDS_COMPLETE = 0x30F0;
enum uint EGL_SYNC_TYPE = 0x30F7;
enum uint EGL_SYNC_STATUS = 0x30F1;
enum uint EGL_SYNC_CONDITION = 0x30F8;
enum uint EGL_SIGNALED = 0x30F2;
enum uint EGL_UNSIGNALED = 0x30F3;
enum uint EGL_SYNC_FLUSH_COMMANDS_BIT = 0x0001;
enum uint EGL_TIMEOUT_EXPIRED = 0x30F5;
enum uint EGL_CONDITION_SATISFIED = 0x30F6;
enum uint EGL_SYNC_FENCE = 0x30F9;
enum uint EGL_GL_COLORSPACE = 0x309D;
enum uint EGL_GL_COLORSPACE_SRGB = 0x3089;
enum uint EGL_GL_COLORSPACE_LINEAR = 0x308A;
enum uint EGL_GL_RENDERBUFFER = 0x30B9;
enum uint EGL_GL_TEXTURE_2D = 0x30B1;
enum uint EGL_GL_TEXTURE_LEVEL = 0x30BC;
enum uint EGL_GL_TEXTURE_3D = 0x30B2;
enum uint EGL_GL_TEXTURE_ZOFFSET = 0x30BD;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x30B3;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x30B4;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x30B5;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x30B6;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x30B7;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x30B8;
enum uint EGL_IMAGE_PRESERVED = 0x30D2;
enum uint EGL_NATIVE_BUFFER_USAGE_ANDROID = 0x3143;
enum uint EGL_NATIVE_BUFFER_USAGE_PROTECTED_BIT_ANDROID = 0x00000001;
enum uint EGL_NATIVE_BUFFER_USAGE_RENDERBUFFER_BIT_ANDROID = 0x00000002;
enum uint EGL_NATIVE_BUFFER_USAGE_TEXTURE_BIT_ANDROID = 0x00000004;
enum uint EGL_FRAMEBUFFER_TARGET_ANDROID = 0x3147;
enum uint EGL_FRONT_BUFFER_AUTO_REFRESH_ANDROID = 0x314C;
enum uint EGL_TIMESTAMP_PENDING_ANDROID = cast(EGLnsecsANDROID)-2;
enum uint EGL_TIMESTAMP_INVALID_ANDROID = cast(EGLnsecsANDROID)-1;
enum uint EGL_TIMESTAMPS_ANDROID = 0x3430;
enum uint EGL_COMPOSITE_DEADLINE_ANDROID = 0x3431;
enum uint EGL_COMPOSITE_INTERVAL_ANDROID = 0x3432;
enum uint EGL_COMPOSITE_TO_PRESENT_LATENCY_ANDROID = 0x3433;
enum uint EGL_REQUESTED_PRESENT_TIME_ANDROID = 0x3434;
enum uint EGL_RENDERING_COMPLETE_TIME_ANDROID = 0x3435;
enum uint EGL_COMPOSITION_LATCH_TIME_ANDROID = 0x3436;
enum uint EGL_FIRST_COMPOSITION_START_TIME_ANDROID = 0x3437;
enum uint EGL_LAST_COMPOSITION_START_TIME_ANDROID = 0x3438;
enum uint EGL_FIRST_COMPOSITION_GPU_FINISHED_TIME_ANDROID = 0x3439;
enum uint EGL_DISPLAY_PRESENT_TIME_ANDROID = 0x343A;
enum uint EGL_DEQUEUE_READY_TIME_ANDROID = 0x343B;
enum uint EGL_READS_DONE_TIME_ANDROID = 0x343C;
enum uint EGL_NATIVE_BUFFER_ANDROID = 0x3140;
enum uint EGL_SYNC_NATIVE_FENCE_ANDROID = 0x3144;
enum uint EGL_SYNC_NATIVE_FENCE_FD_ANDROID = 0x3145;
enum uint EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID = 0x3146;
enum uint EGL_RECORDABLE_ANDROID = 0x3142;
enum uint EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE = 0x3200;
enum uint EGL_D3D9_DEVICE_ANGLE = 0x33A0;
enum uint EGL_D3D11_DEVICE_ANGLE = 0x33A1;
enum uint EGL_FIXED_SIZE_ANGLE = 0x3201;
enum uint EGL_SYNC_PRIOR_COMMANDS_IMPLICIT_EXTERNAL_ARM = 0x328A;
enum uint EGL_DISCARD_SAMPLES_ARM = 0x3286;
enum uint EGL_FRONT_BUFFER_EXT = 0x3464;
enum uint EGL_BUFFER_AGE_EXT = 0x313D;
enum uint EGL_SYNC_CLIENT_EXT = 0x3364;
enum uint EGL_SYNC_CLIENT_SIGNAL_EXT = 0x3365;
enum uint EGL_PRIMARY_COMPOSITOR_CONTEXT_EXT = 0x3460;
enum uint EGL_EXTERNAL_REF_ID_EXT = 0x3461;
enum uint EGL_COMPOSITOR_DROP_NEWEST_FRAME_EXT = 0x3462;
enum uint EGL_COMPOSITOR_KEEP_NEWEST_FRAME_EXT = 0x3463;
enum uint EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT = 0x30BF;
enum uint EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT = 0x3138;
enum uint EGL_NO_RESET_NOTIFICATION_EXT = 0x31BE;
enum uint EGL_LOSE_CONTEXT_ON_RESET_EXT = 0x31BF;
enum uint EGL_BAD_DEVICE_EXT = 0x322B;
enum uint EGL_DEVICE_EXT = 0x322C;
enum uint EGL_DRM_DEVICE_FILE_EXT = 0x3233;
enum uint EGL_DRM_MASTER_FD_EXT = 0x333C;
enum uint EGL_OPENWF_DEVICE_ID_EXT = 0x3237;
enum uint EGL_GL_COLORSPACE_BT2020_LINEAR_EXT = 0x333F;
enum uint EGL_GL_COLORSPACE_BT2020_PQ_EXT = 0x3340;
enum uint EGL_GL_COLORSPACE_DISPLAY_P3_EXT = 0x3363;
enum uint EGL_GL_COLORSPACE_DISPLAY_P3_LINEAR_EXT = 0x3362;
enum uint EGL_GL_COLORSPACE_SCRGB_EXT = 0x3351;
enum uint EGL_GL_COLORSPACE_SCRGB_LINEAR_EXT = 0x3350;
enum uint EGL_LINUX_DMA_BUF_EXT = 0x3270;
enum uint EGL_LINUX_DRM_FOURCC_EXT = 0x3271;
enum uint EGL_DMA_BUF_PLANE0_FD_EXT = 0x3272;
enum uint EGL_DMA_BUF_PLANE0_OFFSET_EXT = 0x3273;
enum uint EGL_DMA_BUF_PLANE0_PITCH_EXT = 0x3274;
enum uint EGL_DMA_BUF_PLANE1_FD_EXT = 0x3275;
enum uint EGL_DMA_BUF_PLANE1_OFFSET_EXT = 0x3276;
enum uint EGL_DMA_BUF_PLANE1_PITCH_EXT = 0x3277;
enum uint EGL_DMA_BUF_PLANE2_FD_EXT = 0x3278;
enum uint EGL_DMA_BUF_PLANE2_OFFSET_EXT = 0x3279;
enum uint EGL_DMA_BUF_PLANE2_PITCH_EXT = 0x327A;
enum uint EGL_YUV_COLOR_SPACE_HINT_EXT = 0x327B;
enum uint EGL_SAMPLE_RANGE_HINT_EXT = 0x327C;
enum uint EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT = 0x327D;
enum uint EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT = 0x327E;
enum uint EGL_ITU_REC601_EXT = 0x327F;
enum uint EGL_ITU_REC709_EXT = 0x3280;
enum uint EGL_ITU_REC2020_EXT = 0x3281;
enum uint EGL_YUV_FULL_RANGE_EXT = 0x3282;
enum uint EGL_YUV_NARROW_RANGE_EXT = 0x3283;
enum uint EGL_YUV_CHROMA_SITING_0_EXT = 0x3284;
enum uint EGL_YUV_CHROMA_SITING_0_5_EXT = 0x3285;
enum uint EGL_DMA_BUF_PLANE3_FD_EXT = 0x3440;
enum uint EGL_DMA_BUF_PLANE3_OFFSET_EXT = 0x3441;
enum uint EGL_DMA_BUF_PLANE3_PITCH_EXT = 0x3442;
enum uint EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT = 0x3443;
enum uint EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT = 0x3444;
enum uint EGL_DMA_BUF_PLANE1_MODIFIER_LO_EXT = 0x3445;
enum uint EGL_DMA_BUF_PLANE1_MODIFIER_HI_EXT = 0x3446;
enum uint EGL_DMA_BUF_PLANE2_MODIFIER_LO_EXT = 0x3447;
enum uint EGL_DMA_BUF_PLANE2_MODIFIER_HI_EXT = 0x3448;
enum uint EGL_DMA_BUF_PLANE3_MODIFIER_LO_EXT = 0x3449;
enum uint EGL_DMA_BUF_PLANE3_MODIFIER_HI_EXT = 0x344A;
enum uint EGL_GL_COLORSPACE_DEFAULT_EXT = 0x314D;
enum uint EGL_IMPORT_SYNC_TYPE_EXT = 0x3470;
enum uint EGL_IMPORT_IMPLICIT_SYNC_EXT = 0x3471;
enum uint EGL_IMPORT_EXPLICIT_SYNC_EXT = 0x3472;
enum uint EGL_MULTIVIEW_VIEW_COUNT_EXT = 0x3134;
enum uint EGL_BAD_OUTPUT_LAYER_EXT = 0x322D;
enum uint EGL_BAD_OUTPUT_PORT_EXT = 0x322E;
enum uint EGL_SWAP_INTERVAL_EXT = 0x322F;
enum uint EGL_DRM_CRTC_EXT = 0x3234;
enum uint EGL_DRM_PLANE_EXT = 0x3235;
enum uint EGL_DRM_CONNECTOR_EXT = 0x3236;
enum uint EGL_OPENWF_PIPELINE_ID_EXT = 0x3238;
enum uint EGL_OPENWF_PORT_ID_EXT = 0x3239;
enum uint EGL_COLOR_COMPONENT_TYPE_EXT = 0x3339;
enum uint EGL_COLOR_COMPONENT_TYPE_FIXED_EXT = 0x333A;
enum uint EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT = 0x333B;
enum uint EGL_PLATFORM_DEVICE_EXT = 0x313F;
enum uint EGL_PLATFORM_WAYLAND_EXT = 0x31D8;
enum uint EGL_PLATFORM_X11_EXT = 0x31D5;
enum uint EGL_PLATFORM_X11_SCREEN_EXT = 0x31D6;
enum uint EGL_PROTECTED_CONTENT_EXT = 0x32C0;
enum uint EGL_CTA861_3_MAX_CONTENT_LIGHT_LEVEL_EXT = 0x3360;
enum uint EGL_CTA861_3_MAX_FRAME_AVERAGE_LEVEL_EXT = 0x3361;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_RX_EXT = 0x3341;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_RY_EXT = 0x3342;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_GX_EXT = 0x3343;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_GY_EXT = 0x3344;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_BX_EXT = 0x3345;
enum uint EGL_SMPTE2086_DISPLAY_PRIMARY_BY_EXT = 0x3346;
enum uint EGL_SMPTE2086_WHITE_POINT_X_EXT = 0x3347;
enum uint EGL_SMPTE2086_WHITE_POINT_Y_EXT = 0x3348;
enum uint EGL_SMPTE2086_MAX_LUMINANCE_EXT = 0x3349;
enum uint EGL_SMPTE2086_MIN_LUMINANCE_EXT = 0x334A;
enum uint EGL_METADATA_SCALING_EXT = 50000;
enum uint EGL_YUV_ORDER_EXT = 0x3301;
enum uint EGL_YUV_NUMBER_OF_PLANES_EXT = 0x3311;
enum uint EGL_YUV_SUBSAMPLE_EXT = 0x3312;
enum uint EGL_YUV_DEPTH_RANGE_EXT = 0x3317;
enum uint EGL_YUV_CSC_STANDARD_EXT = 0x330A;
enum uint EGL_YUV_PLANE_BPP_EXT = 0x331A;
enum uint EGL_YUV_BUFFER_EXT = 0x3300;
enum uint EGL_YUV_ORDER_YUV_EXT = 0x3302;
enum uint EGL_YUV_ORDER_YVU_EXT = 0x3303;
enum uint EGL_YUV_ORDER_YUYV_EXT = 0x3304;
enum uint EGL_YUV_ORDER_UYVY_EXT = 0x3305;
enum uint EGL_YUV_ORDER_YVYU_EXT = 0x3306;
enum uint EGL_YUV_ORDER_VYUY_EXT = 0x3307;
enum uint EGL_YUV_ORDER_AYUV_EXT = 0x3308;
enum uint EGL_YUV_SUBSAMPLE_4_2_0_EXT = 0x3313;
enum uint EGL_YUV_SUBSAMPLE_4_2_2_EXT = 0x3314;
enum uint EGL_YUV_SUBSAMPLE_4_4_4_EXT = 0x3315;
enum uint EGL_YUV_DEPTH_RANGE_LIMITED_EXT = 0x3318;
enum uint EGL_YUV_DEPTH_RANGE_FULL_EXT = 0x3319;
enum uint EGL_YUV_CSC_STANDARD_601_EXT = 0x330B;
enum uint EGL_YUV_CSC_STANDARD_709_EXT = 0x330C;
enum uint EGL_YUV_CSC_STANDARD_2020_EXT = 0x330D;
enum uint EGL_YUV_PLANE_BPP_0_EXT = 0x331B;
enum uint EGL_YUV_PLANE_BPP_8_EXT = 0x331C;
enum uint EGL_YUV_PLANE_BPP_10_EXT = 0x331D;
enum uint EGL_CLIENT_PIXMAP_POINTER_HI = 0x8F74;
enum uint EGL_COLOR_FORMAT_HI = 0x8F70;
enum uint EGL_COLOR_RGB_HI = 0x8F71;
enum uint EGL_COLOR_RGBA_HI = 0x8F72;
enum uint EGL_COLOR_ARGB_HI = 0x8F73;
enum uint EGL_CONTEXT_PRIORITY_LEVEL_IMG = 0x3100;
enum uint EGL_CONTEXT_PRIORITY_HIGH_IMG = 0x3101;
enum uint EGL_CONTEXT_PRIORITY_MEDIUM_IMG = 0x3102;
enum uint EGL_CONTEXT_PRIORITY_LOW_IMG = 0x3103;
enum uint EGL_NATIVE_BUFFER_MULTIPLANE_SEPARATE_IMG = 0x3105;
enum uint EGL_NATIVE_BUFFER_PLANE_OFFSET_IMG = 0x3106;
enum uint EGL_CL_EVENT_HANDLE_KHR = 0x309C;
enum uint EGL_SYNC_CL_EVENT_KHR = 0x30FE;
enum uint EGL_SYNC_CL_EVENT_COMPLETE_KHR = 0x30FF;
enum uint EGL_CONFORMANT_KHR = 0x3042;
enum uint EGL_VG_COLORSPACE_LINEAR_BIT_KHR = 0x0020;
enum uint EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR = 0x0040;
enum uint EGL_CONTEXT_RELEASE_BEHAVIOR_NONE_KHR = 0;
enum uint EGL_CONTEXT_RELEASE_BEHAVIOR_KHR = 0x2097;
enum uint EGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR = 0x2098;
enum uint EGL_CONTEXT_MAJOR_VERSION_KHR = 0x3098;
enum uint EGL_CONTEXT_MINOR_VERSION_KHR = 0x30FB;
enum uint EGL_CONTEXT_FLAGS_KHR = 0x30FC;
enum uint EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR = 0x30FD;
enum uint EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR = 0x31BD;
enum uint EGL_NO_RESET_NOTIFICATION_KHR = 0x31BE;
enum uint EGL_LOSE_CONTEXT_ON_RESET_KHR = 0x31BF;
enum uint EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR = 0x00000001;
enum uint EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR = 0x00000002;
enum uint EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR = 0x00000004;
enum uint EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR = 0x00000001;
enum uint EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR = 0x00000002;
enum uint EGL_OPENGL_ES3_BIT_KHR = 0x00000040;
enum uint EGL_CONTEXT_OPENGL_NO_ERROR_KHR = 0x31B3;
enum uint EGL_OBJECT_THREAD_KHR = 0x33B0;
enum uint EGL_OBJECT_DISPLAY_KHR = 0x33B1;
enum uint EGL_OBJECT_CONTEXT_KHR = 0x33B2;
enum uint EGL_OBJECT_SURFACE_KHR = 0x33B3;
enum uint EGL_OBJECT_IMAGE_KHR = 0x33B4;
enum uint EGL_OBJECT_SYNC_KHR = 0x33B5;
enum uint EGL_OBJECT_STREAM_KHR = 0x33B6;
enum uint EGL_DEBUG_MSG_CRITICAL_KHR = 0x33B9;
enum uint EGL_DEBUG_MSG_ERROR_KHR = 0x33BA;
enum uint EGL_DEBUG_MSG_WARN_KHR = 0x33BB;
enum uint EGL_DEBUG_MSG_INFO_KHR = 0x33BC;
enum uint EGL_DEBUG_CALLBACK_KHR = 0x33B8;
enum uint EGL_TRACK_REFERENCES_KHR = 0x3352;
enum uint EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR = 0x30F0;
enum uint EGL_SYNC_CONDITION_KHR = 0x30F8;
enum uint EGL_SYNC_FENCE_KHR = 0x30F9;
enum uint EGL_GL_COLORSPACE_KHR = 0x309D;
enum uint EGL_GL_COLORSPACE_SRGB_KHR = 0x3089;
enum uint EGL_GL_COLORSPACE_LINEAR_KHR = 0x308A;
enum uint EGL_GL_RENDERBUFFER_KHR = 0x30B9;
enum uint EGL_GL_TEXTURE_2D_KHR = 0x30B1;
enum uint EGL_GL_TEXTURE_LEVEL_KHR = 0x30BC;
enum uint EGL_GL_TEXTURE_3D_KHR = 0x30B2;
enum uint EGL_GL_TEXTURE_ZOFFSET_KHR = 0x30BD;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR = 0x30B3;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR = 0x30B4;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR = 0x30B5;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR = 0x30B6;
enum uint EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR = 0x30B7;
enum uint EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR = 0x30B8;
enum uint EGL_NATIVE_PIXMAP_KHR = 0x30B0;
enum uint EGL_IMAGE_PRESERVED_KHR = 0x30D2;
enum uint EGL_READ_SURFACE_BIT_KHR = 0x0001;
enum uint EGL_WRITE_SURFACE_BIT_KHR = 0x0002;
enum uint EGL_LOCK_SURFACE_BIT_KHR = 0x0080;
enum uint EGL_OPTIMAL_FORMAT_BIT_KHR = 0x0100;
enum uint EGL_MATCH_FORMAT_KHR = 0x3043;
enum uint EGL_FORMAT_RGB_565_EXACT_KHR = 0x30C0;
enum uint EGL_FORMAT_RGB_565_KHR = 0x30C1;
enum uint EGL_FORMAT_RGBA_8888_EXACT_KHR = 0x30C2;
enum uint EGL_FORMAT_RGBA_8888_KHR = 0x30C3;
enum uint EGL_MAP_PRESERVE_PIXELS_KHR = 0x30C4;
enum uint EGL_LOCK_USAGE_HINT_KHR = 0x30C5;
enum uint EGL_BITMAP_POINTER_KHR = 0x30C6;
enum uint EGL_BITMAP_PITCH_KHR = 0x30C7;
enum uint EGL_BITMAP_ORIGIN_KHR = 0x30C8;
enum uint EGL_BITMAP_PIXEL_RED_OFFSET_KHR = 0x30C9;
enum uint EGL_BITMAP_PIXEL_GREEN_OFFSET_KHR = 0x30CA;
enum uint EGL_BITMAP_PIXEL_BLUE_OFFSET_KHR = 0x30CB;
enum uint EGL_BITMAP_PIXEL_ALPHA_OFFSET_KHR = 0x30CC;
enum uint EGL_BITMAP_PIXEL_LUMINANCE_OFFSET_KHR = 0x30CD;
enum uint EGL_LOWER_LEFT_KHR = 0x30CE;
enum uint EGL_UPPER_LEFT_KHR = 0x30CF;
enum uint EGL_BITMAP_PIXEL_SIZE_KHR = 0x3110;
enum uint EGL_MUTABLE_RENDER_BUFFER_BIT_KHR = 0x1000;
enum uint EGL_BUFFER_AGE_KHR = 0x313D;
enum uint EGL_PLATFORM_ANDROID_KHR = 0x3141;
enum uint EGL_PLATFORM_GBM_KHR = 0x31D7;
enum uint EGL_PLATFORM_WAYLAND_KHR = 0x31D8;
enum uint EGL_PLATFORM_X11_KHR = 0x31D5;
enum uint EGL_PLATFORM_X11_SCREEN_KHR = 0x31D6;
enum uint EGL_SYNC_STATUS_KHR = 0x30F1;
enum uint EGL_SIGNALED_KHR = 0x30F2;
enum uint EGL_UNSIGNALED_KHR = 0x30F3;
enum uint EGL_TIMEOUT_EXPIRED_KHR = 0x30F5;
enum uint EGL_CONDITION_SATISFIED_KHR = 0x30F6;
enum uint EGL_SYNC_TYPE_KHR = 0x30F7;
enum uint EGL_SYNC_REUSABLE_KHR = 0x30FA;
enum uint EGL_SYNC_FLUSH_COMMANDS_BIT_KHR = 0x0001;
enum uint EGL_CONSUMER_LATENCY_USEC_KHR = 0x3210;
enum uint EGL_PRODUCER_FRAME_KHR = 0x3212;
enum uint EGL_CONSUMER_FRAME_KHR = 0x3213;
enum uint EGL_STREAM_STATE_KHR = 0x3214;
enum uint EGL_STREAM_STATE_CREATED_KHR = 0x3215;
enum uint EGL_STREAM_STATE_CONNECTING_KHR = 0x3216;
enum uint EGL_STREAM_STATE_EMPTY_KHR = 0x3217;
enum uint EGL_STREAM_STATE_NEW_FRAME_AVAILABLE_KHR = 0x3218;
enum uint EGL_STREAM_STATE_OLD_FRAME_AVAILABLE_KHR = 0x3219;
enum uint EGL_STREAM_STATE_DISCONNECTED_KHR = 0x321A;
enum uint EGL_BAD_STREAM_KHR = 0x321B;
enum uint EGL_BAD_STATE_KHR = 0x321C;
enum uint EGL_CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR = 0x321E;
enum uint EGL_STREAM_FIFO_LENGTH_KHR = 0x31FC;
enum uint EGL_STREAM_TIME_NOW_KHR = 0x31FD;
enum uint EGL_STREAM_TIME_CONSUMER_KHR = 0x31FE;
enum uint EGL_STREAM_TIME_PRODUCER_KHR = 0x31FF;
enum uint EGL_STREAM_BIT_KHR = 0x0800;
enum uint EGL_VG_PARENT_IMAGE_KHR = 0x30BA;
enum uint EGL_DRM_BUFFER_FORMAT_MESA = 0x31D0;
enum uint EGL_DRM_BUFFER_USE_MESA = 0x31D1;
enum uint EGL_DRM_BUFFER_FORMAT_ARGB32_MESA = 0x31D2;
enum uint EGL_DRM_BUFFER_MESA = 0x31D3;
enum uint EGL_DRM_BUFFER_STRIDE_MESA = 0x31D4;
enum uint EGL_DRM_BUFFER_USE_SCANOUT_MESA = 0x00000001;
enum uint EGL_DRM_BUFFER_USE_SHARE_MESA = 0x00000002;
enum uint EGL_DRM_BUFFER_USE_CURSOR_MESA = 0x00000004;
enum uint EGL_PLATFORM_GBM_MESA = 0x31D7;
enum uint EGL_PLATFORM_SURFACELESS_MESA = 0x31DD;
enum uint EGL_Y_INVERTED_NOK = 0x307F;
enum uint EGL_AUTO_STEREO_NV = 0x3136;
enum uint EGL_CONTEXT_PRIORITY_REALTIME_NV = 0x3357;
enum uint EGL_COVERAGE_BUFFERS_NV = 0x30E0;
enum uint EGL_COVERAGE_SAMPLES_NV = 0x30E1;
enum uint EGL_COVERAGE_SAMPLE_RESOLVE_NV = 0x3131;
enum uint EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV = 0x3132;
enum uint EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV = 0x3133;
enum uint EGL_CUDA_EVENT_HANDLE_NV = 0x323B;
enum uint EGL_SYNC_CUDA_EVENT_NV = 0x323C;
enum uint EGL_SYNC_CUDA_EVENT_COMPLETE_NV = 0x323D;
enum uint EGL_DEPTH_ENCODING_NV = 0x30E2;
enum uint EGL_DEPTH_ENCODING_NONLINEAR_NV = 0x30E3;
enum uint EGL_CUDA_DEVICE_NV = 0x323A;
enum uint EGL_POST_SUB_BUFFER_SUPPORTED_NV = 0x30BE;
enum uint EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV = 0x334C;
enum uint EGL_YUV_PLANE0_TEXTURE_UNIT_NV = 0x332C;
enum uint EGL_YUV_PLANE1_TEXTURE_UNIT_NV = 0x332D;
enum uint EGL_YUV_PLANE2_TEXTURE_UNIT_NV = 0x332E;
enum uint EGL_STREAM_CROSS_DISPLAY_NV = 0x334E;
enum uint EGL_STREAM_CROSS_OBJECT_NV = 0x334D;
enum uint EGL_STREAM_CROSS_PARTITION_NV = 0x323F;
enum uint EGL_STREAM_CROSS_PROCESS_NV = 0x3245;
enum uint EGL_STREAM_CROSS_SYSTEM_NV = 0x334F;
enum uint EGL_PENDING_FRAME_NV = 0x3329;
enum uint EGL_STREAM_TIME_PENDING_NV = 0x332A;
enum uint EGL_STREAM_FIFO_SYNCHRONOUS_NV = 0x3336;
enum uint EGL_PRODUCER_MAX_FRAME_HINT_NV = 0x3337;
enum uint EGL_CONSUMER_MAX_FRAME_HINT_NV = 0x3338;
enum uint EGL_MAX_STREAM_METADATA_BLOCKS_NV = 0x3250;
enum uint EGL_MAX_STREAM_METADATA_BLOCK_SIZE_NV = 0x3251;
enum uint EGL_MAX_STREAM_METADATA_TOTAL_SIZE_NV = 0x3252;
enum uint EGL_PRODUCER_METADATA_NV = 0x3253;
enum uint EGL_CONSUMER_METADATA_NV = 0x3254;
enum uint EGL_PENDING_METADATA_NV = 0x3328;
enum uint EGL_METADATA0_SIZE_NV = 0x3255;
enum uint EGL_METADATA1_SIZE_NV = 0x3256;
enum uint EGL_METADATA2_SIZE_NV = 0x3257;
enum uint EGL_METADATA3_SIZE_NV = 0x3258;
enum uint EGL_METADATA0_TYPE_NV = 0x3259;
enum uint EGL_METADATA1_TYPE_NV = 0x325A;
enum uint EGL_METADATA2_TYPE_NV = 0x325B;
enum uint EGL_METADATA3_TYPE_NV = 0x325C;
enum uint EGL_STREAM_STATE_INITIALIZING_NV = 0x3240;
enum uint EGL_STREAM_TYPE_NV = 0x3241;
enum uint EGL_STREAM_PROTOCOL_NV = 0x3242;
enum uint EGL_STREAM_ENDPOINT_NV = 0x3243;
enum uint EGL_STREAM_LOCAL_NV = 0x3244;
enum uint EGL_STREAM_PRODUCER_NV = 0x3247;
enum uint EGL_STREAM_CONSUMER_NV = 0x3248;
enum uint EGL_STREAM_PROTOCOL_FD_NV = 0x3246;
enum uint EGL_SUPPORT_RESET_NV = 0x3334;
enum uint EGL_SUPPORT_REUSE_NV = 0x3335;
enum uint EGL_STREAM_PROTOCOL_SOCKET_NV = 0x324B;
enum uint EGL_SOCKET_HANDLE_NV = 0x324C;
enum uint EGL_SOCKET_TYPE_NV = 0x324D;
enum uint EGL_SOCKET_TYPE_INET_NV = 0x324F;
enum uint EGL_SOCKET_TYPE_UNIX_NV = 0x324E;
enum uint EGL_SYNC_NEW_FRAME_NV = 0x321F;
enum uint EGL_SYNC_PRIOR_COMMANDS_COMPLETE_NV = 0x30E6;
enum uint EGL_SYNC_STATUS_NV = 0x30E7;
enum uint EGL_SIGNALED_NV = 0x30E8;
enum uint EGL_UNSIGNALED_NV = 0x30E9;
enum uint EGL_SYNC_FLUSH_COMMANDS_BIT_NV = 0x0001;
enum uint EGL_ALREADY_SIGNALED_NV = 0x30EA;
enum uint EGL_TIMEOUT_EXPIRED_NV = 0x30EB;
enum uint EGL_CONDITION_SATISFIED_NV = 0x30EC;
enum uint EGL_SYNC_TYPE_NV = 0x30ED;
enum uint EGL_SYNC_CONDITION_NV = 0x30EE;
enum uint EGL_SYNC_FENCE_NV = 0x30EF;
enum uint EGL_NATIVE_BUFFER_TIZEN = 0x32A0;
enum uint EGL_NATIVE_SURFACE_TIZEN = 0x32A1;