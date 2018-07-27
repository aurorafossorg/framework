/*****************************************************************************
**                                    / _|
**   __ _ _   _ _ __ ___  _ __ __ _  | |_ ___  ___ ___
**  / _` | | | | '__/ _ \| '__/ _` | |  _/ _ \/ __/ __|
** | (_| | |_| | | | (_) | | | (_| | | || (_) \__ \__ \
**  \__,_|\__,_|_|  \___/|_|  \__,_| |_| \___/|___/___/
**
** Copyright (C) 2018 Aurora Free Open Source Software.
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

#ifndef AURORAFW_CORELIB_CALLBACK_H
#define AURORAFW_CORELIB_CALLBACK_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/CoreLib/TypeTraits.h>

//#include <type_traits>
#include <functional>

namespace AuroraFW {
	template<typename T, size_t n, typename CallerType>
	struct Callback;

	template<typename Ret, typename ... Params, size_t n,typename CallerType>
	struct AFW_API Callback<Ret(Params...), n,CallerType>
	{
		typedef Ret (*ret_cb)(Params...);
		
		template<typename ... Args>
		static Ret callback(Args ... args)
		{
			func(args...);
		}

		static ret_cb getCallback(std::function<Ret(Params...)> fn)
		{
			func = fn;
			return static_cast<ret_cb>(Callback<Ret(Params...), n,CallerType>::callback);
		}

		static std::function<Ret(Params...)> func;
	};

	template<typename Ret, typename ... Params, size_t n,typename CallerType>
	std::function<Ret(Params...)> Callback<Ret(Params...), n,CallerType>::func;

	template<typename T, typename... U>
	AFW_FORCE_INLINE auto getCallbackPtr(std::function<T(U...)> f) {
		return f.template target<T(*)(U...)>();
	}
}

#define AFW_CALLBACK(ptype,ctype) AuroraFW::Callback<AuroraFW::ActualType<ptype>::type,__COUNTER__,ctype>::getCallback
typedef void(*afw_callback_t)();

#endif // AURORAFW_CORELIB_CALLBACK_H