/*****************************************************************************
**                                     __
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

#include <AuroraFW/Image/BaseColor.h>

namespace AuroraFW {
	template<> BaseColor<float>::BaseColor(int r, int g, int b, int a)
	: r(Math::clamp(r, 0, 255)/255.0f),
		g(Math::clamp(g, 0, 255)/255.0f),
		b(Math::clamp(b, 0, 255)/255.0f),
		a(Math::clamp(a, 0, 255)/255.0f)
	{}

	template<> BaseColor<float>::BaseColor(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{}

	template<> BaseColor<float>::BaseColor(uint32_t hex)
	{
		r = (hex >> 16)/255.0f;
		g = (hex >> 8)/255.0f;
		b = hex/255.0f;
	}

	template<> BaseColor<float>::BaseColor(CommonColor hex)
	{
		r = static_cast<byte_t>(static_cast<uint32_t>(hex) >> 16)/255.0f;
		g = static_cast<byte_t>(static_cast<uint32_t>(hex) >> 8)/255.0f;
		b = static_cast<byte_t>(hex)/255.0f;
	}

	template<> BaseColor<byte_t>::BaseColor(uint32_t hex)
	{
		r = static_cast<byte_t>(hex) >> 16;
		g = static_cast<byte_t>(hex) >> 8;
		b = static_cast<byte_t>(hex);
	}

	template<> BaseColor<byte_t>::BaseColor(CommonColor hex)
	{
		r = static_cast<byte_t>(static_cast<uint32_t>(hex) >> 16);
		g = static_cast<byte_t>(static_cast<uint32_t>(hex) >> 8);
		b = static_cast<byte_t>(hex);
	}

	template<> BaseColor<byte_t>::BaseColor(int r, int g, int b, int a)
		: r(r), g(g), b(b), a(a)
	{}

	template<> int BaseColor<float>::red() const
	{
		return r*255;
	}

	template<> int BaseColor<float>::green() const
	{
		return g*255;
	}

	template<> int BaseColor<float>::blue() const
	{
		return b*255;
	}

	template<> int BaseColor<float>::alpha() const
	{
		return a*255;
	}

	template<> float BaseColor<byte_t>::redF() const
	{
		return r/255.0f;
	}

	template<> float BaseColor<byte_t>::greenF() const
	{
		return g/255.0f;
	}

	template<> float BaseColor<byte_t>::blueF() const
	{
		return b/255.0f;
	}

	template<> float BaseColor<byte_t>::alphaF() const
	{
		return a/255.0f;
	}

	template<> void BaseColor<byte_t>::setRed(float _r)
	{
		r = _r*255;
	}

	template<> void BaseColor<byte_t>::setGreen(float _g)
	{
		g = _g*255;
	}

	template<> void BaseColor<byte_t>::setBlue(float _b)
	{
		b = _b*255;
	}

	template<> void BaseColor<byte_t>::setAlpha(float _a)
	{
		a = _a*255;
	}

	template<> void BaseColor<float>::setRed(int _r)
	{
		r = _r/255.0f;
	}

	template<> void BaseColor<float>::setGreen(int _g)
	{
		g = _g/255.0f;
	}

	template<> void BaseColor<float>::setBlue(int _b)
	{
		b = _b/255.0f;
	}

	template<> void BaseColor<float>::setAlpha(int _a)
	{
		a = _a/255.0f;
	}

	template struct BaseColor<float>;
	template struct BaseColor<byte_t>;
}