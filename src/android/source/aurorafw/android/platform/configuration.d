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

module aurorafw.android.platform.configuration;

/**
 * @addtogroup Configuration
 * @{
 */

/**
 * @file aurorafw/android/platform/configuration.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/* nothing */

struct AConfiguration;
/**
 * {@link AConfiguration} is an opaque type used to get and set
 * various subsystem configurations.
 *
 * A {@link AConfiguration} pointer can be obtained using:
 * - AConfiguration_new()
 * - AConfiguration_fromAssetManager()
 */

/**
 * Define flags and constants for various subsystem configurations.
 */
enum
{
	/** Orientation: not specified. */
	ACONFIGURATION_ORIENTATION_ANY = 0,
	/**
	 * Orientation: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#OrientationQualifier">port</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_ORIENTATION_PORT = 1,
	/**
	 * Orientation: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#OrientationQualifier">land</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_ORIENTATION_LAND = 2,
	/** @deprecated Not currently supported or used. */
	ACONFIGURATION_ORIENTATION_SQUARE = 3,

	/** Touchscreen: not specified. */
	ACONFIGURATION_TOUCHSCREEN_ANY = 0,
	/**
	 * Touchscreen: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#TouchscreenQualifier">notouch</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_TOUCHSCREEN_NOTOUCH = 1,
	/** @deprecated Not currently supported or used. */
	ACONFIGURATION_TOUCHSCREEN_STYLUS = 2,
	/**
	 * Touchscreen: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#TouchscreenQualifier">finger</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_TOUCHSCREEN_FINGER = 3,

	/** Density: default density. */
	ACONFIGURATION_DENSITY_DEFAULT = 0,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">ldpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_LOW = 120,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">mdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_MEDIUM = 160,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">tvdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_TV = 213,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">hdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_HIGH = 240,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">xhdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_XHIGH = 320,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">xxhdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_XXHIGH = 480,
	/**
	 * Density: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">xxxhdpi</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_DENSITY_XXXHIGH = 640,
	/** Density: any density. */
	ACONFIGURATION_DENSITY_ANY = 65534,
	/** Density: no density specified. */
	ACONFIGURATION_DENSITY_NONE = 65535,

	/** Keyboard: not specified. */
	ACONFIGURATION_KEYBOARD_ANY = 0,
	/**
	 * Keyboard: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ImeQualifier">nokeys</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYBOARD_NOKEYS = 1,
	/**
	 * Keyboard: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ImeQualifier">qwerty</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYBOARD_QWERTY = 2,
	/**
	 * Keyboard: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ImeQualifier">12key</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYBOARD_12KEY = 3,

	/** Navigation: not specified. */
	ACONFIGURATION_NAVIGATION_ANY = 0,
	/**
	 * Navigation: value corresponding to the
	 * <a href="@@dacRoot/guide/topics/resources/providing-resources.html#NavigationQualifier">nonav</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVIGATION_NONAV = 1,
	/**
	 * Navigation: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavigationQualifier">dpad</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVIGATION_DPAD = 2,
	/**
	 * Navigation: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavigationQualifier">trackball</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVIGATION_TRACKBALL = 3,
	/**
	 * Navigation: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavigationQualifier">wheel</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVIGATION_WHEEL = 4,

	/** Keyboard availability: not specified. */
	ACONFIGURATION_KEYSHIDDEN_ANY = 0,
	/**
	 * Keyboard availability: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#KeyboardAvailQualifier">keysexposed</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYSHIDDEN_NO = 1,
	/**
	 * Keyboard availability: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#KeyboardAvailQualifier">keyshidden</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYSHIDDEN_YES = 2,
	/**
	 * Keyboard availability: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#KeyboardAvailQualifier">keyssoft</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_KEYSHIDDEN_SOFT = 3,

	/** Navigation availability: not specified. */
	ACONFIGURATION_NAVHIDDEN_ANY = 0,
	/**
	 * Navigation availability: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavAvailQualifier">navexposed</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVHIDDEN_NO = 1,
	/**
	 * Navigation availability: value corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavAvailQualifier">navhidden</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_NAVHIDDEN_YES = 2,

	/** Screen size: not specified. */
	ACONFIGURATION_SCREENSIZE_ANY = 0,
	/**
	 * Screen size: value indicating the screen is at least
	 * approximately 320x426 dp units, corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenSizeQualifier">small</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENSIZE_SMALL = 1,
	/**
	 * Screen size: value indicating the screen is at least
	 * approximately 320x470 dp units, corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenSizeQualifier">normal</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENSIZE_NORMAL = 2,
	/**
	 * Screen size: value indicating the screen is at least
	 * approximately 480x640 dp units, corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenSizeQualifier">large</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENSIZE_LARGE = 3,
	/**
	 * Screen size: value indicating the screen is at least
	 * approximately 720x960 dp units, corresponding to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenSizeQualifier">xlarge</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENSIZE_XLARGE = 4,

	/** Screen layout: not specified. */
	ACONFIGURATION_SCREENLONG_ANY = 0,
	/**
	 * Screen layout: value that corresponds to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenAspectQualifier">notlong</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENLONG_NO = 1,
	/**
	 * Screen layout: value that corresponds to the
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenAspectQualifier">long</a>
	 * resource qualifier.
	 */
	ACONFIGURATION_SCREENLONG_YES = 2,

	ACONFIGURATION_SCREENROUND_ANY = 0,
	ACONFIGURATION_SCREENROUND_NO = 1,
	ACONFIGURATION_SCREENROUND_YES = 2,

	/** Wide color gamut: not specified. */
	ACONFIGURATION_WIDE_COLOR_GAMUT_ANY = 0,
	/**
	 * Wide color gamut: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#WideColorGamutQualifier">no
	 * nowidecg</a> resource qualifier specified.
	 */
	ACONFIGURATION_WIDE_COLOR_GAMUT_NO = 1,
	/**
	 * Wide color gamut: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#WideColorGamutQualifier">
	 * widecg</a> resource qualifier specified.
	 */
	ACONFIGURATION_WIDE_COLOR_GAMUT_YES = 2,

	/** HDR: not specified. */
	ACONFIGURATION_HDR_ANY = 0,
	/**
	 * HDR: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#HDRQualifier">
	 * lowdr</a> resource qualifier specified.
	 */
	ACONFIGURATION_HDR_NO = 1,
	/**
	 * HDR: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#HDRQualifier">
	 * highdr</a> resource qualifier specified.
	 */
	ACONFIGURATION_HDR_YES = 2,

	/** UI mode: not specified. */
	ACONFIGURATION_UI_MODE_TYPE_ANY = 0,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">no
	 * UI mode type</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_NORMAL = 1,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">desk</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_DESK = 2,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">car</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_CAR = 3,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">television</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_TELEVISION = 4,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">appliance</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_APPLIANCE = 5,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">watch</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_WATCH = 6,
	/**
	 * UI mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">vr</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_TYPE_VR_HEADSET = 7,

	/** UI night mode: not specified.*/
	ACONFIGURATION_UI_MODE_NIGHT_ANY = 0,
	/**
	 * UI night mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NightQualifier">notnight</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_NIGHT_NO = 1,
	/**
	 * UI night mode: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NightQualifier">night</a> resource qualifier specified.
	 */
	ACONFIGURATION_UI_MODE_NIGHT_YES = 2,

	/** Screen width DPI: not specified. */
	ACONFIGURATION_SCREEN_WIDTH_DP_ANY = 0,

	/** Screen height DPI: not specified. */
	ACONFIGURATION_SCREEN_HEIGHT_DP_ANY = 0,

	/** Smallest screen width DPI: not specified.*/
	ACONFIGURATION_SMALLEST_SCREEN_WIDTH_DP_ANY = 0,

	/** Layout direction: not specified. */
	ACONFIGURATION_LAYOUTDIR_ANY = 0,
	/**
	 * Layout direction: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#LayoutDirectionQualifier">ldltr</a> resource qualifier specified.
	 */
	ACONFIGURATION_LAYOUTDIR_LTR = 1,
	/**
	 * Layout direction: value that corresponds to
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#LayoutDirectionQualifier">ldrtl</a> resource qualifier specified.
	 */
	ACONFIGURATION_LAYOUTDIR_RTL = 2,

	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#MccQualifier">mcc</a>
	 * configuration.
	 */
	ACONFIGURATION_MCC = 1,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#MccQualifier">mnc</a>
	 * configuration.
	 */
	ACONFIGURATION_MNC = 2,
	/**
	 * Bit mask for
	 * <a href="{@docRoot}guide/topics/resources/providing-resources.html#LocaleQualifier">locale</a>
	 * configuration.
	 */
	ACONFIGURATION_LOCALE = 4,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#TouchscreenQualifier">touchscreen</a>
	 * configuration.
	 */
	ACONFIGURATION_TOUCHSCREEN = 8,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ImeQualifier">keyboard</a>
	 * configuration.
	 */
	ACONFIGURATION_KEYBOARD = 16,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#KeyboardAvailQualifier">keyboardHidden</a>
	 * configuration.
	 */
	ACONFIGURATION_KEYBOARD_HIDDEN = 32,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#NavigationQualifier">navigation</a>
	 * configuration.
	 */
	ACONFIGURATION_NAVIGATION = 64,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#OrientationQualifier">orientation</a>
	 * configuration.
	 */
	ACONFIGURATION_ORIENTATION = 128,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#DensityQualifier">density</a>
	 * configuration.
	 */
	ACONFIGURATION_DENSITY = 256,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#ScreenSizeQualifier">screen size</a>
	 * configuration.
	 */
	ACONFIGURATION_SCREEN_SIZE = 512,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#VersionQualifier">platform version</a>
	 * configuration.
	 */
	ACONFIGURATION_VERSION = 1024,
	/**
	 * Bit mask for screen layout configuration.
	 */
	ACONFIGURATION_SCREEN_LAYOUT = 2048,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#UiModeQualifier">ui mode</a>
	 * configuration.
	 */
	ACONFIGURATION_UI_MODE = 4096,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#SmallestScreenWidthQualifier">smallest screen width</a>
	 * configuration.
	 */
	ACONFIGURATION_SMALLEST_SCREEN_SIZE = 8192,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#LayoutDirectionQualifier">layout direction</a>
	 * configuration.
	 */
	ACONFIGURATION_LAYOUTDIR = 16384,
	ACONFIGURATION_SCREEN_ROUND = 32768,
	/**
	 * Bit mask for
	 * <a href="@dacRoot/guide/topics/resources/providing-resources.html#WideColorGamutQualifier">wide color gamut</a>
	 * and <a href="@dacRoot/guide/topics/resources/providing-resources.html#HDRQualifier">HDR</a> configurations.
	 */
	ACONFIGURATION_COLOR_MODE = 65536,
	/**
	 * Constant used to to represent MNC (Mobile Network Code) zero.
	 * 0 cannot be used, since it is used to represent an undefined MNC.
	 */
	ACONFIGURATION_MNC_ZERO = 65535
}

/**
 * Create a new AConfiguration, initialized with no values set.
 */
AConfiguration* AConfiguration_new ();

/**
 * Free an AConfiguration that was previously created with
 * AConfiguration_new().
 */
void AConfiguration_delete (AConfiguration* config);

/**
 * Create and return a new AConfiguration based on the current configuration in
 * use in the given {@link AAssetManager}.
 */
void AConfiguration_fromAssetManager (AConfiguration* out_, AAssetManager* am);

/**
 * Copy the contents of 'src' to 'dest'.
 */
void AConfiguration_copy (AConfiguration* dest, AConfiguration* src);

/**
 * Return the current MCC set in the configuration.  0 if not set.
 */
int AConfiguration_getMcc (AConfiguration* config);

/**
 * Set the current MCC in the configuration.  0 to clear.
 */
void AConfiguration_setMcc (AConfiguration* config, int mcc);

/**
 * Return the current MNC set in the configuration.  0 if not set.
 */
int AConfiguration_getMnc (AConfiguration* config);

/**
 * Set the current MNC in the configuration.  0 to clear.
 */
void AConfiguration_setMnc (AConfiguration* config, int mnc);

/**
 * Return the current language code set in the configuration.  The output will
 * be filled with an array of two characters.  They are not 0-terminated.  If
 * a language is not set, they will be 0.
 */
void AConfiguration_getLanguage (AConfiguration* config, char* outLanguage);

/**
 * Set the current language code in the configuration, from the first two
 * characters in the string.
 */
void AConfiguration_setLanguage (AConfiguration* config, const(char)* language);

/**
 * Return the current country code set in the configuration.  The output will
 * be filled with an array of two characters.  They are not 0-terminated.  If
 * a country is not set, they will be 0.
 */
void AConfiguration_getCountry (AConfiguration* config, char* outCountry);

/**
 * Set the current country code in the configuration, from the first two
 * characters in the string.
 */
void AConfiguration_setCountry (AConfiguration* config, const(char)* country);

/**
 * Return the current ACONFIGURATION_ORIENTATION_* set in the configuration.
 */
int AConfiguration_getOrientation (AConfiguration* config);

/**
 * Set the current orientation in the configuration.
 */
void AConfiguration_setOrientation (AConfiguration* config, int orientation);

/**
 * Return the current ACONFIGURATION_TOUCHSCREEN_* set in the configuration.
 */
int AConfiguration_getTouchscreen (AConfiguration* config);

/**
 * Set the current touchscreen in the configuration.
 */
void AConfiguration_setTouchscreen (AConfiguration* config, int touchscreen);

/**
 * Return the current ACONFIGURATION_DENSITY_* set in the configuration.
 */
int AConfiguration_getDensity (AConfiguration* config);

/**
 * Set the current density in the configuration.
 */
void AConfiguration_setDensity (AConfiguration* config, int density);

/**
 * Return the current ACONFIGURATION_KEYBOARD_* set in the configuration.
 */
int AConfiguration_getKeyboard (AConfiguration* config);

/**
 * Set the current keyboard in the configuration.
 */
void AConfiguration_setKeyboard (AConfiguration* config, int keyboard);

/**
 * Return the current ACONFIGURATION_NAVIGATION_* set in the configuration.
 */
int AConfiguration_getNavigation (AConfiguration* config);

/**
 * Set the current navigation in the configuration.
 */
void AConfiguration_setNavigation (AConfiguration* config, int navigation);

/**
 * Return the current ACONFIGURATION_KEYSHIDDEN_* set in the configuration.
 */
int AConfiguration_getKeysHidden (AConfiguration* config);

/**
 * Set the current keys hidden in the configuration.
 */
void AConfiguration_setKeysHidden (AConfiguration* config, int keysHidden);

/**
 * Return the current ACONFIGURATION_NAVHIDDEN_* set in the configuration.
 */
int AConfiguration_getNavHidden (AConfiguration* config);

/**
 * Set the current nav hidden in the configuration.
 */
void AConfiguration_setNavHidden (AConfiguration* config, int navHidden);

/**
 * Return the current SDK (API) version set in the configuration.
 */
int AConfiguration_getSdkVersion (AConfiguration* config);

/**
 * Set the current SDK version in the configuration.
 */
void AConfiguration_setSdkVersion (AConfiguration* config, int sdkVersion);

/**
 * Return the current ACONFIGURATION_SCREENSIZE_* set in the configuration.
 */
int AConfiguration_getScreenSize (AConfiguration* config);

/**
 * Set the current screen size in the configuration.
 */
void AConfiguration_setScreenSize (AConfiguration* config, int screenSize);

/**
 * Return the current ACONFIGURATION_SCREENLONG_* set in the configuration.
 */
int AConfiguration_getScreenLong (AConfiguration* config);

/**
 * Set the current screen long in the configuration.
 */
void AConfiguration_setScreenLong (AConfiguration* config, int screenLong);

/**
 * Return the current ACONFIGURATION_SCREENROUND_* set in the configuration.
 */
int AConfiguration_getScreenRound (AConfiguration* config);

/**
 * Set the current screen round in the configuration.
 */
void AConfiguration_setScreenRound (AConfiguration* config, int screenRound);

/**
 * Return the current ACONFIGURATION_UI_MODE_TYPE_* set in the configuration.
 */
int AConfiguration_getUiModeType (AConfiguration* config);

/**
 * Set the current UI mode type in the configuration.
 */
void AConfiguration_setUiModeType (AConfiguration* config, int uiModeType);

/**
 * Return the current ACONFIGURATION_UI_MODE_NIGHT_* set in the configuration.
 */
int AConfiguration_getUiModeNight (AConfiguration* config);

/**
 * Set the current UI mode night in the configuration.
 */
void AConfiguration_setUiModeNight (AConfiguration* config, int uiModeNight);

/**
 * Return the current configuration screen width in dp units, or
 * ACONFIGURATION_SCREEN_WIDTH_DP_ANY if not set.
 */
int AConfiguration_getScreenWidthDp (AConfiguration* config);

/**
 * Set the configuration's current screen width in dp units.
 */
void AConfiguration_setScreenWidthDp (AConfiguration* config, int value);

/**
 * Return the current configuration screen height in dp units, or
 * ACONFIGURATION_SCREEN_HEIGHT_DP_ANY if not set.
 */
int AConfiguration_getScreenHeightDp (AConfiguration* config);

/**
 * Set the configuration's current screen width in dp units.
 */
void AConfiguration_setScreenHeightDp (AConfiguration* config, int value);

/**
 * Return the configuration's smallest screen width in dp units, or
 * ACONFIGURATION_SMALLEST_SCREEN_WIDTH_DP_ANY if not set.
 */
int AConfiguration_getSmallestScreenWidthDp (AConfiguration* config);

/**
 * Set the configuration's smallest screen width in dp units.
 */
void AConfiguration_setSmallestScreenWidthDp (AConfiguration* config, int value);
/* __ANDROID_API__ >= 13 */

/**
 * Return the configuration's layout direction, or
 * ACONFIGURATION_LAYOUTDIR_ANY if not set.
 */
int AConfiguration_getLayoutDirection (AConfiguration* config);

/**
 * Set the configuration's layout direction.
 */
void AConfiguration_setLayoutDirection (AConfiguration* config, int value);
/* __ANDROID_API__ >= 17 */

/**
 * Perform a diff between two configurations.  Returns a bit mask of
 * ACONFIGURATION_* constants, each bit set meaning that configuration element
 * is different between them.
 */
int AConfiguration_diff (AConfiguration* config1, AConfiguration* config2);

/**
 * Determine whether 'base' is a valid configuration for use within the
 * environment 'requested'.  Returns 0 if there are any values in 'base'
 * that conflict with 'requested'.  Returns 1 if it does not conflict.
 */
int AConfiguration_match (AConfiguration* base, AConfiguration* requested);

/**
 * Determine whether the configuration in 'test' is better than the existing
 * configuration in 'base'.  If 'requested' is non-NULL, this decision is based
 * on the overall configuration given there.  If it is NULL, this decision is
 * simply based on which configuration is more specific.  Returns non-0 if
 * 'test' is better than 'base'.
 *
 * This assumes you have already filtered the configurations with
 * AConfiguration_match().
 */
int AConfiguration_isBetterThan (
	AConfiguration* base,
	AConfiguration* test,
	AConfiguration* requested);

// ANDROID_CONFIGURATION_H

/** @} */
