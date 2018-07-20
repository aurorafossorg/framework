/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Intel Corporation.
** Copyright (C) 2017 Aurora Framework.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** NOTE: All products, services or anything associated to Intel is a
** trademark or registered trademarks of Intel Corporation or its
** subsidiaries in the U.S. and/or other countries. More info:
** https://www.intel.com/content/www/us/en/legal/trademarks.html. Other
** names and brands may be claimed as the property of others.
****************************************************************************/

/** @file AuroraFW/CoreLib/Target/Architecture.h
 * Detect target architecture
 * @note This file use the following syntax: AFW_TARGET_ARCH_FAMILY_VARIANT. Can
 *	also use revision instead of variant, e.g. ARM family processors:
 *	AFW_TARGET_ARCH_FAMILY_REVISION.
 *
 * @author Luís “ljmf00” Ferreira <contact@lsferreira.net>
 *
 * @todo Need to be documented
 */

#ifndef AURORAFW_CORELIB_TARGET_ARCHITECTURE_H
#define AURORAFW_CORELIB_TARGET_ARCHITECTURE_H

#include <AuroraFW/CoreLib/Target/Compiler.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

//Define ix86 processor architecture detection
#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
	//Define x86 processor wordsize
	#define AFW_TARGET_ARCH_X86_32

	#ifdef (_M_IX86)
		#define AFW_TARGET_ARCH_X86 (_M_IX86/100)
	#elif defined(__i686__) || defined(__athlon__) || defined(__SSE__) || defined(__pentiumpro__)
		#define AFW_TARGET_ARCH_X86 6
	#elif defined(__i586__) || defined(__k6__) || defined(__pentium__)
		#define AFW_TARGET_ARCH_X86 5
	#elif defined(__i486__) || defined(__80486__)
		#define AFW_TARGET_ARCH_X86 4
	#else
		#define AFW_TARGET_ARCH_X86 3
	#endif

//Define x86_64 processor architecture detection
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(__amd64__) || defined(_M_X64) \
	|| defined(_M_AMD64)

	//Define i686 as x86 processor version
	#define AFW_TARGET_ARCH_X86 6
	//Define x86_64 processor wordsize
	#define AFW_TARGET_ARCH_X86_64


#elif defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(_M_ARM) || defined(__aarch64__) || defined(__ARM64__)
	//Define ARM processor wordsize
	#if defined(__aarch64__) || defined(__ARM64__)
		#define AFW_TARGET_ARCH_ARM_64
	#else
		#define AFW_TARGET_ARCH_ARM_32
	#endif
	
	//Define ARM processor version
	#if defined(__ARM_ARCH) && __ARM_ARCH > 1
		#define AFW_TARGET_ARCH_ARM __ARM_ARCH
	#elif defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM > 1
		#define AFW_TARGET_ARCH_ARM __TARGET_ARCH_ARM
	#elif defined(_M_ARM) && _M_ARM > 1
		#define AFW_TARGET_ARCH_ARM _M_ARM
	#elif defined(__ARM64_ARCH_8__) || defined(__aarch64__) || defined(__ARMv8__) || defined(__ARMv8_A__)
		#define AFW_TARGET_ARCH_ARM 8
	#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) \
		|| defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || defined(_ARM_ARCH_7) || defined(__CORE_CORTEXA__)

		#define AFW_TARGET_ARCH_ARM 7
	#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6Z__) \
		|| defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6M__)

		#define AFW_TARGET_ARCH_ARM 6
	#elif defined(__ARM_ARCH_5TEJ__) || defined(__ARM_ARCH_5TE__)
		#define AFW_TARGET_ARCH_ARM 5
	#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
		#define AFW_TARGET_ARCH_ARM 4
	#elif defined(__ARM_ARCH_3M__) || defined(__ARM_ARCH_3__)
		#define AFW_TARGET_ARCH_ARM 3
	#elif defined(__ARM_ARCH_2__)
		#define AFW_TARGET_ARCH_ARM 2
	#else
		#define AFW_TARGET_ARCH_ARM 0
	#endif
	
	//ARM version alias
	#if AFW_TARGET_ARCH_ARM >= 8
		#define AFW_TARGET_ARCH_ARM_V8
	#endif
	#if AFW_TARGET_ARCH_ARM >= 7
		#define AFW_TARGET_ARCH_ARM_V7
	#endif
	#if AFW_TARGET_ARCH_ARM >= 6
		#define AFW_TARGET_ARCH_ARM_V6
	#endif
	#if AFW_TARGET_ARCH_ARM >= 5
		#define AFW_TARGET_ARCH_ARM_V5
	#endif
	#if AFW_TARGET_ARCH_ARM >= 4
		#define AFW_TARGET_ARCH_ARM_V4
	#endif
	#if AFW_TARGET_ARCH_ARM >= 3
		#define AFW_TARGET_ARCH_ARM_V3
	#endif
	#if AFW_TARGET_ARCH_ARM >= 2
		#define AFW_TARGET_ARCH_ARM_V2
	#else
		#warning "Unknown ARM architecture version"
	#endif

/*
	Define Intel Itanium processor architecture (IA-64) family
	NOTE: No revisions or variants
*/
#elif defined(__ia64) || defined(__ia64__) || defined(__itanium__) || defined(_M_IA64)
	#define AFW_TARGET_ARCH_IA64
	//Alias macro
	#define AFW_TARGET_ARCH_ITANIUM

//Define MIPS processor architecture family
#elif defined(__mips) || defined(__mips__) || defined(_M_MRX000)
	#define AFW_TARGET_ARCH_MIPS
	#if defined(_MIPS_ARCH_MIPS1) || (defined(__mips) && __mips - 0 >= 1) || defined(_MIPS_ISA_MIPS1) \
		|| defined(_R3000)

		#define AFW_TARGET_ARCH_MIPS_1
	#endif
	#if defined(_MIPS_ARCH_MIPS2) || (defined(__mips) && __mips - 0 >= 2) || defined(_MIPS_ISA_MIPS2) \
		|| defined(__MIPS_ISA2__)

		#define AFW_TARGET_ARCH_MIPS_2
	#endif
	#if defined(_MIPS_ARCH_MIPS3) || (defined(__mips) && __mips - 0 >= 3) || defined(_MIPS_ISA_MIPS3) \
		|| defined(__MIPS_ISA3__)

		#define AFW_TARGET_ARCH_MIPS_3
	#endif
	#if defined(_MIPS_ARCH_MIPS4) || (defined(__mips) && __mips - 0 >= 4) || defined(_MIPS_ISA_MIPS4) \
		|| defined(__MIPS_ISA4__)

		#define AFW_TARGET_ARCH_MIPS_4
	#endif
	#if defined(_MIPS_ARCH_MIPS5) || (defined(__mips) && __mips - 0 >= 5)
		#define AFW_TARGET_ARCH_MIPS_5
	#endif
	#if defined(_MIPS_ARCH_MIPS32) || defined(__mips32) || (defined(__mips) && __mips - 0 >= 32)
		#define AFW_TARGET_ARCH_MIPS_32
	#endif
	#if defined(_MIPS_ARCH_MIPS64) || defined(__mips64)
		#define AFW_TARGET_ARCH_MIPS_64
# endif

//Define PowerPC processor architecture family
#elif defined(__ppc__) || defined(__ppc) || defined(__powerpc__) || defined(_ARCH_COM) || defined(_ARCH_PWR) \
	|| defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(_M_MPPC) || defined(_M_PPC) || defined(__ppc64__) \
	|| defined(__PPC__) || defined(__PPC64_) || defined(__powerpc64__) || defined(__POWERPC__)

	#ifdef _ARCH_440
		#define AFW_TARGET_ARCH_POWERPC 440
	#elif _ARCH_450
		#define AFW_TARGET_ARCH_POWERPC 450
	#elif (_M_PPC == 601) || defined(__ppc601__) || defined(_ARCH_601)
		#define AFW_TARGET_ARCH_POWERPC 601
	#elif (_M_PPC == 603) || defined(__ppc603__) || defined(_ARCH_603)
		#define AFW_TARGET_ARCH_POWERPC 603
	#elif (_M_PPC == 604) || defined(__ppc604__) || defined(_ARCH_604)
		#define AFW_TARGET_ARCH_POWERPC 604
	#elif (_M_PPC == 620)
		#define AFW_TARGET_ARCH_POWERPC 620
	#else
		#define AFW_TARGET_ARCH_POWERPC
	#endif

	#if defined(__ppc64__) || defined(__powerpc64__) || defined(__64BIT__)
		#define AFW_TARGET_ARCH_POWERPC_64
	#else
		#define AFW_TARGET_ARCH_POWERPC_32
	#endif

//Define SPARC processor architecture family
#elif defined(__sparc) || defined(__sparc__)
	#define AFW_TARGET_ARCH_SPARC
	#ifdef __sparc_v9__
		#define AFW_TARGET_ARCH_SPARC_V9
	#endif
	#ifdef __sparc64__
		#define AFW_TARGET_ARCH_SPARC_64
	#endif

//Define s390 processor architecture family
#elif defined(__s390__)
	#define AFW_TARGET_ARCH_S390
	#ifdef __s390x__
		#define AFW_TARGET_ARCH_S390_X
	#endif

/*
	Define DEC Alpha processor architecture family
	NOTE: DEC, formally known as Digital Equipment Corporation
*/
#elif defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA) || defined(__alpha__ev4__) || defined(__alpha__ev5__) \
	|| defined(__alpha__ev6__)

	#define AFW_TARGET_ARCH_ALPHA
	#ifdef __alpha_ev4__
		#define AFW_TARGET_ARCH_ALPHA_EV4
	#endif
	#ifdef __alpha_ev5__
		#define AFW_TARGET_ARCH_ALPHA_EV5
	#endif
	#ifdef __alpha_ev6__
		#define AFW_TARGET_ARCH_ALPHA_EV6
	#endif
#elif defined(__bfin) || defined(__BFIN__)
	#define AFW_TARGET_ARCH_BLACKFIN
#elif defined(__convex__) || defined(__convex_c1__) || defined(__convex_c2__) || defined(__convex_c32__) \
	|| defined(__convex_c34__) || defined(__convex_c38__)

	#define AFW_TARGET_ARCH_CONVEX
	#ifdef __convex_c1__
		#define AFW_TARGET_ARCH_CONVEX_C1
	#endif
	#ifdef __convex_c2__
		#define AFW_TARGET_ARCH_CONVEX_C2
	#endif
	#ifdef __convex_c32__
		#define AFW_TARGET_ARCH_CONVEX_C32
	#endif
	#ifdef __convex_c34__
		#define AFW_TARGET_ARCH_CONVEX_C34
	#endif
	#ifdef __convex_c38__
		#define AFW_TARGET_ARCH_CONVEX_C38
	#endif
#elif defined(__epiphany__)
	#define AFW_TARGET_ARCH_EPIPHANY
#elif defined(__hppa__) || defined(__HPPA__) || defined(__hppa) || defined(_PA_RISC1_0) || defined(_PA_RISC1_1) \
	|| defined(__HPPA11__) || defined(__PA7100__) || defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) \
	|| defined(__PA8000__)

	#define AFW_TARGET_ARCH_PA_RISC
	#ifdef _PA_RISC1_0
		#define AFW_TARGET_ARCH_PA_RISC_1_0
	#endif
	#if defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__)
		#define AFW_TARGET_ARCH_PA_RISC_1_1
	#endif
	#if defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__)
		#define AFW_TARGET_ARCH_PA_RISC_2_0
	#endif
#elif defined(__m68k__) || defined(M68000) || defined(__MC68K__) || defined(__mc68000__) || defined(__MC68000__) \
	|| defined(__mc68010__) || defined(__mc68020__) || defined(__MC68020__) || defined(__mc68030__) || defined(__MC68030__) \
	|| defined(__mc68040__) || defined(__mc68060__)

	#if defined(__mc68000__) || defined(__MC68000__)
		#define AFW_TARGET_ARCH_MC68K 68000
	#elif defined(__mc68010__)
		#define AFW_TARGET_ARCH_MC68K 68010
	#elif defined(__mc68020__) || defined(__MC68020__)
		#define AFW_TARGET_ARCH_MC68K 68020
	#elif defined(__mc68030__) || defined(__MC68030__)
		#define AFW_TARGET_ARCH_MC68K 68030
	#elif defined(__mc68040__)
		#define AFW_TARGET_ARCH_MC68K 68040
	#elif defined(__mc68060__)
		#define AFW_TARGET_ARCH_MC68K 68060
	#else
		#define AFW_TARGET_ARCH_MC68K
	#endif
#elif defined(__sh__)
	#define AFW_TARGET_ARCH_SUPERH
	#ifdef __sh1__
		#define AFW_TARGET_ARCH_SUPERH_1
	#endif
	#ifdef __sh2__
		#define AFW_TARGET_ARCH_SUPERH_2
	#endif
	#if defined(__sh3__) || defined(__SH3__)
		#define AFW_TARGET_ARCH_SUPERH_3
	#endif
	#ifdef __SH4__
		#define AFW_TARGET_ARCH_SUPERH_4
	#endif
	#ifdef __SH5__
		#define AFW_TARGET_ARCH_SUPERH_5
	#endif
#elif defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || defined(__TMS320C55X__) \
	|| defined(_TMS320C6X) || defined(__TMS320C6X__)

	#if defined(_TMS320C2XX) || defined(__TMS320C2000__)
		#define AFW_TARGET_ARCH_TMS320 2000
	#elif defined(_TMS320C5X) || defined(__TMS320C55X__)
		#define AFW_TARGET_ARCH_TMS320 5000
	#elif defined(_TMS320C6X) || defined(__TMS320C6X__)
		#define AFW_TARGET_ARCH_TMS320 6000
	#endif

	#if defined(_TMS320C28X)
		#define AFW_TARGET_ARCH_TMS320_C28XX
	#elif defined(_TMS320C5XX)
		#define AFW_TARGET_ARCH_TMS320_C54X
	#elif defined(__TMS320C55X__)
		#define AFW_TARGET_ARCH_TMS320_C55X
	#elif defined(_TMS320C6200)
		#define AFW_TARGET_ARCH_TMS320_C6200
	#elif defined(_TMS320C6400)
		#define AFW_TARGET_ARCH_TMS320_C6400
	#elif defined(_TMS320C6400_PLUS)
		#define AFW_TARGET_ARCH_TMS320_C6400_PLUS
	#elif defined(_TMS320C6600)
		#define AFW_TARGET_ARCH_TMS320_C6600
	#elif defined(_TMS320C6700)
		#define AFW_TARGET_ARCH_TMS320_C6700
	#elif defined(_TMS320C6700_PLUS)
		#define AFW_TARGET_ARCH_TMS320_C6700_PLUS
	#elif defined(_TMS320C6740)
		#define AFW_TARGET_ARCH_TMS320_C6740
	#endif
#elif defined(__TMS470__)
	#define AFW_TARGET_ARCH_TMS470
#else
	#error "Unknown CPU Architecture"
#endif

// Data type 	LP32 	ILP32 	LP64 	LLP64 	ILP64 	SILP64
// char 		8 		8 		8 		8 		8 		8
// short 		16 		16 		16 		16 		16 		64
// int 			16 		32 		32 		32 		64 		64
// long 		32 		32 		64 		32 		64 		64
// long long 	64 		64 		64 		64
// pointer 		32 		32 		64 		64 		64 		64

// _ILP32 		Defined by HP aCC and Sun Studio
// __ILP32__ 	Defined by GNU C
#if defined(__ILP32__) || defined(_ILP32)
	#define AFW_TARGET_DATAMODEL_ILP32

// _LP64 		Defined by HP aCC and Sun Studio
// __LP64__ 	Defined by GNU C
#elif defined(__LP64__) || defined(_LP64)
	#define AFW_TARGET_DATAMODEL_LP64
#endif

//Define wordsize
#if defined(AFW_TARGET_CPUARCH_86_64) && !defined(AFW_TARGET_DATAMODEL_ILP32)
	#define AFW_TARGET_WORDSIZE 64
#else
	#define AFW_TARGET_WORDSIZE 32
#endif

#endif // AURORAFW_CORELIB_TARGET_ARCHITECTURE_H
