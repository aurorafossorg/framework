/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

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