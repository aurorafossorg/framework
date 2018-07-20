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