/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2018 The Android Open Source Project.
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

module aurorafw.android.platform.data_space;

/**
 * @file aurorafw/android/platform/data_space.d
 */

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * ADataSpace.
 */
enum ADataSpace
{
    /**
     * Default-assumption data space, when not explicitly specified.
     *
     * It is safest to assume the buffer is an image with sRGB primaries and
     * encoding ranges, but the consumer and/or the producer of the data may
     * simply be using defaults. No automatic gamma transform should be
     * expected, except for a possible display gamma transform when drawn to a
     * screen.
     */
    ADATASPACE_UNKNOWN = 0,

    /**
     * scRGB linear encoding:
     *
     * The red, green, and blue components are stored in extended sRGB space,
     * but are linear, not gamma-encoded.
     * The RGB primaries and the white point are the same as BT.709.
     *
     * The values are floating point.
     * A pixel value of 1.0, 1.0, 1.0 corresponds to sRGB white (D65) at 80 nits.
     * Values beyond the range [0.0 - 1.0] would correspond to other colors
     * spaces and/or HDR content.
     */
    ADATASPACE_SCRGB_LINEAR = 406913024, // STANDARD_BT709 | TRANSFER_LINEAR | RANGE_EXTENDED

    /**
     * sRGB gamma encoding:
     *
     * The red, green and blue components are stored in sRGB space, and
     * converted to linear space when read, using the SRGB transfer function
     * for each of the R, G and B components. When written, the inverse
     * transformation is performed.
     *
     * The alpha component, if present, is always stored in linear space and
     * is left unmodified when read or written.
     *
     * Use full range and BT.709 standard.
     */
    ADATASPACE_SRGB = 142671872, // STANDARD_BT709 | TRANSFER_SRGB | RANGE_FULL

    /**
     * scRGB:
     *
     * The red, green, and blue components are stored in extended sRGB space,
     * but are linear, not gamma-encoded.
     * The RGB primaries and the white point are the same as BT.709.
     *
     * The values are floating point.
     * A pixel value of 1.0, 1.0, 1.0 corresponds to sRGB white (D65) at 80 nits.
     * Values beyond the range [0.0 - 1.0] would correspond to other colors
     * spaces and/or HDR content.
     */
    ADATASPACE_SCRGB = 411107328, // STANDARD_BT709 | TRANSFER_SRGB | RANGE_EXTENDED

    /**
     * Display P3
     *
     * Use same primaries and white-point as DCI-P3
     * but sRGB transfer function.
     */
    ADATASPACE_DISPLAY_P3 = 143261696, // STANDARD_DCI_P3 | TRANSFER_SRGB | RANGE_FULL

    /**
     * ITU-R Recommendation 2020 (BT.2020)
     *
     * Ultra High-definition television
     *
     * Use full range, SMPTE 2084 (PQ) transfer and BT2020 standard
     */
    ADATASPACE_BT2020_PQ = 163971072 // STANDARD_BT2020 | TRANSFER_ST2084 | RANGE_FULL
}

// ANDROID_DATA_SPACE_H
