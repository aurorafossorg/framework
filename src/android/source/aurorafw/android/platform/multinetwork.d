/*
                                    __
                                   / _|
  __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
 / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
| (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
 \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/

Copyright (C) 2015 The Android Open Source Project.
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

module aurorafw.android.platform.multinetwork;

/**
 * @addtogroup Networking
 * @{
 */

/**
 * @file aurorafw/android/platform/multinetwork.d
 */

import core.stdc.config;
import core.sys.posix.netdb;

version (Android):
extern (C):
@system:
nothrow:
@nogc:

/**
 * The corresponding C type for android.net.Network#getNetworkHandle() return
 * values.  The Java signed long value can be safely cast to a net_handle_t:
 *
 *     [C]    ((net_handle_t) java_long_network_handle)
 *     [C++]  static_cast<net_handle_t>(java_long_network_handle)
 *
 * as appropriate.
 */
alias net_handle_t = c_ulong;

/**
 * The value NETWORK_UNSPECIFIED indicates no specific network.
 *
 * For some functions (documented below), a previous binding may be cleared
 * by an invocation with NETWORK_UNSPECIFIED.
 *
 * Depending on the context it may indicate an error.  It is expressly
 * not used to indicate some notion of the "current default network".
 */
enum NETWORK_UNSPECIFIED = cast(net_handle_t) 0;

/**
 * All functions below that return an int return 0 on success or -1
 * on failure with an appropriate errno value set.
 */

/**
 * Set the network to be used by the given socket file descriptor.
 *
 * To clear a previous socket binding, invoke with NETWORK_UNSPECIFIED.
 *
 * This is the equivalent of: [android.net.Network#bindSocket()](https://developer.android.com/reference/android/net/Network.html#bindSocket(java.net.Socket))
 *
 */
int android_setsocknetwork (net_handle_t network, int fd);

/**
 * Binds the current process to |network|.  All sockets created in the future
 * (and not explicitly bound via android_setsocknetwork()) will be bound to
 * |network|.  All host name resolutions will be limited to |network| as well.
 * Note that if the network identified by |network| ever disconnects, all
 * sockets created in this way will cease to work and all host name
 * resolutions will fail.  This is by design so an application doesn't
 * accidentally use sockets it thinks are still bound to a particular network.
 *
 * To clear a previous process binding, invoke with NETWORK_UNSPECIFIED.
 *
 * This is the equivalent of: [android.net.ConnectivityManager#setProcessDefaultNetwork()](https://developer.android.com/reference/android/net/ConnectivityManager.html#setProcessDefaultNetwork(android.net.Network))
 *
 */
int android_setprocnetwork (net_handle_t network);

/**
 * Perform hostname resolution via the DNS servers associated with |network|.
 *
 * All arguments (apart from |network|) are used identically as those passed
 * to getaddrinfo(3).  Return and error values are identical to those of
 * getaddrinfo(3), and in particular gai_strerror(3) can be used as expected.
 * Similar to getaddrinfo(3):
 *     - |hints| may be NULL (in which case man page documented defaults apply)
 *     - either |node| or |service| may be NULL, but not both
 *     - |res| must not be NULL
 *
 * This is the equivalent of: [android.net.Network#getAllByName()](https://developer.android.com/reference/android/net/Network.html#getAllByName(java.lang.String))
 *
 */
int android_getaddrinfofornetwork (
	net_handle_t network,
	const(char)* node,
	const(char)* service,
	const(addrinfo)* hints,
	addrinfo** res);

/* __ANDROID_API__ >= 23 */

// ANDROID_MULTINETWORK_H

/** @} */
