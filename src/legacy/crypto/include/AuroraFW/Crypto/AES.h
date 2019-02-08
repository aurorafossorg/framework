/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018-2019 Aurora Free Open Source Software.
**
** This file is part of the Aurora Free Open Source Software. This
** organization promote free and open source software that you can
** redistribute and/or modify under the terms of the GNU Lesser General
** Public License Version 3 as published by the Free Software Foundation or
** (at your option) any later version approved by the Aurora Free Open Source
** Software Organization. The license is available in the package root path
** as 'LICENSE' file. Please review the following information to ensure the
** GNU Lesser General Public License version 3 requirements will be met:
** https://www.gnu.org/licenses/lgpl.html .
**
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3 or later as published by the Free Software
** Foundation. Please review the following information to ensure the GNU
** General Public License requirements will be met:
** http://www.gnu.org/licenses/gpl-3.0.html.
**
** NOTE: All products, services or anything associated to trademarks and
** service marks used or referenced on this file are the property of their
** respective companies/owners or its subsidiaries. Other names and brands
** may be claimed as the property of others.
**
** For more info about intellectual property visit: aurorafoss.org or
** directly send an email to: contact (at) aurorafoss.org .
*****************************************************************************/

/**	@file AuroraFW/Crypto/AES.h
 * AES Encryption header. Contains a class used to
 * encrypt/decrypt AES ciphers.
 * @since snapshot20170930
 */

#ifndef AURORAFW_CRYPTO_AES_H
#define AURORAFW_CRYPTO_AES_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/LibC/String.h>

/*
 * The number of columns comprising a _s in AES.
 * This is a constant in AES. Value=4
 */
#define AFW_AES_NUM 4

// AFW_AES_TIME is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define AFW_AES_TIME(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// _AFW_AES_MULTI is a macro used to multiply numbers in the field GF(2^8)
#define AFW_AES_MULTI(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * AFW_AES_TIME(x)) ^ ((y>>2 & 1) * AFW_AES_TIME(AFW_AES_TIME(x))) ^ ((y>>3 & 1) * AFW_AES_TIME(AFW_AES_TIME(AFW_AES_TIME(x)))) ^ ((y>>4 & 1) * AFW_AES_TIME(AFW_AES_TIME(AFW_AES_TIME(AFW_AES_TIME(x))))))

namespace AuroraFW {

	/**
	 * A class used to encrypt/decrypt AES ciphers.
	 * @since 20170930
	 */
	class AFW_API AES {
	private:
		static int _nr, _nk;

		/* i - it is the array that holds the CipherText to be decrypted.
		** o - it is the array that holds the output of the for decryption.
		** s - the array that holds the intermediate results during decryption.
		*/
		static unsigned char _in[16], _out[16], _stt[4][4];

		// The array that stores the round keys.
		static unsigned char _rk[240];
		// The Key input to the AES Program
		static unsigned char _key[32];

		static int _getSBV(const int&);
		// Inverted getSBV
		static int _getISBV(const int&);

		// This function produces Nb(Nr+1) round keys. The round keys are used in each round to decrypt the states.
		static void _ke();
		/* This function adds the round key to state.
		* The round key is added to the state by an XOR function.
		*/
		static void _ark(const int& round);
		/* The SubBytes Function Substitutes the values in the
		* state matrix with values in an S-box.
		*/
		static void _sb();
		// Inverted sb
		static void _isb();

		/* The ShiftRows() function shifts the rows in the state to the left.
		* Each row is shifted with different offset.
		* Offset = Row number. So the first row is not shifted.
		*/
		static void _sr();
		// Inverted method of _sr
		static void _isr();

		// MixColumns function mixes the columns of the state matrix
		static void _mc();
		// Inverted method of _mc
		static void _imc();

		// Cipher is the main function that encrypts the input text
		static void _c();
		// Inverted Cipher
		static void _ic();
	public:
		// AES encrypt function
		static unsigned char* encrypt(const unsigned char*, const int&, unsigned char*);
		// AES decrypt functionx
		static unsigned char* decrypt(const unsigned char*, const int&, unsigned char*);
	};
}


#endif // AURORAFW_CRYPTO_AES_H
