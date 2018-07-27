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

#ifndef AURORAFW_CORELIB_STRING_H
#define AURORAFW_CORELIB_STRING_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/STDL/LibC/String.h>
#include <AuroraFW/STDL/LibC/WChar.h>

#define AFW_STRING_MAX_INPUT_SIZE 8192

#ifndef AFW_STRING_MAXSIZE
	#ifdef AFW_WORDSIZE
		#if AFW_WORDSIZE == 64
			#define AFW_STRING_MAXSIZE   9223372036854775807
		#elif AFW_
			#define AFW_STRING_MAXSIZE   2147483647
		#endif
	#endif /// AFW_WORDSIZE
#endif /// AFW_STRING_MAXSIZE

#ifdef AFW_TARGET_CXX
	extern "C"
	{
#endif /// AFW_TARGET_CXX
		// extern
#ifdef AFW_TARGET_CXX
	}
	#include <AuroraFW/STDL/STL/IStream.h>
	#include <AuroraFW/STDL/STL/OStream.h>

namespace AuroraFW
{
	template<class charT>
	class AFW_API string
	{
	public:
		string(); //Blank string
		string (const charT* ); // Normal string
		string (const string<charT>& ); // String by copy
		~string();

		//Operators
		string& operator = (const string<charT> );		// Operator: =
		string operator + (const string<charT> );         // Operator: + (string)
		string operator + (const charT* );                   // Operator: + (char ptr)
		string& operator += (const string<charT> );       // Operator: += (string)
		string& operator += (const charT* );					// Operator: += (char ptr)
		inline charT& operator [] (const size_t ) const;			// Operator: []
		inline bool operator == (const string<charT> );		// Operator: == (string)
		inline bool operator == (const charT );			// Operator: == (char ptr)
		inline bool operator != (const string<charT> );		// Operator: != (string)
		inline bool operator != (const charT* );			// Operator: != (char ptr)

		void add (size_t, const string<charT>& );
		void add (size_t, const charT* );
		void erase (const size_t ,const size_t );
		inline void output (std::ostream& );
		inline void output (std::wostream& );
		void input (std::istream& );
		void input (std::wistream& );
		int find (const string<charT>& , size_t = 0) const; // Search from another string
		int find (const charT* , const size_t  = 0) const; // Search from an array of char
		int find (const charT* , size_t , const size_t ) const; // Search from a buffer
		int find (const charT , const size_t = 0) const; // Search from a char
		inline size_t length() const; // Return String length
		inline size_t size() const; // Return String size
		inline charT* toCString() const;
		inline std::string toSTLString() const;

	private:
		string (size_t );
		charT* buf = NULL;
		size_t len;
	};
	typedef string<char> String;
	typedef string<wchar_t> wString;

	extern std::ostream& operator << (std::ostream& out, String &str);
	extern std::istream& operator >> (std::istream& in, String &str);

	//for wide characters
	extern std::wostream& operator << (std::wostream& wout, wString &wstr);
	extern std::wistream& operator >> (std::wistream& win, wString &wstr);

	/**
	** @brief destructor of string object: delete buffer ptr
	** (pointer).
	*/
	template<class charT>
	inline string<charT>::~string()
	{
		delete [] buf;
	}

	/**
		** @brief  function to get size of the string
		** @return size (size of buffer)
		*/
		template<class charT>
		inline size_t string<charT>::size() const
		{
			return len * sizeof(charT);
		}

		/**
		** @brief  function to get length of the string
		** @return length
		*/
		template<class charT>
		inline size_t string<charT>::length() const
		{
			return len;
		}

		/**
		** @brief      string operator [] from index of buffer
		** @param  i index of the buffer
		** @return     character from the specific index of the
		**  string / buffer.
		*/
		template<class charT>
		inline charT& string<charT>::operator [] (const size_t i) const
		{
			return buf[i];
		}

		/**
		** @brief			string conditional operator ==
		** @param &str	string object
		** @return			bool
		*/
		template<class charT>
		inline bool string<charT>::operator == (const string<charT> str)
		{
			return (size() == str.size()) && (memcmp(buf, str.buf, sizeof(charT)) == 0);
		}

		/**
		** @brief			string conditional operator ==
		** @param &str	char pointer
		** @return			bool
		*/
		template<>
		inline bool string<char>::operator == (const char str)
		{
			return (size() == strlen(&str)) && (memcmp(buf, &str, sizeof(char)) == 0);
		}
		template<>
		inline bool string<wchar_t>::operator == (const wchar_t str)
		{
			return (size() == wcslen(&str)) && (memcmp(buf, &str, sizeof(wchar_t)) == 0);
		}

		/**
		** @brief			string conditional operator !=
		** @param &str	string object
		** @return			bool
		*/
		template<class charT>
		inline bool string<charT>::operator != (const string<charT> str)
		{
			return (size() != str.size()) || (memcmp(buf, str.buf, sizeof(charT)) != 0);
		}

		/**
		** @brief			string conditional operator !=
		** @param &str	char pointer
		** @return			bool
		*/
		template<class charT>
		inline bool string<charT>::operator != (const charT* str)
		{
			return memcmp(buf, str, sizeof(charT));
		}

		template<class charT>
		// TODO: Delete unused compiler suppressors and define the body
		inline void string<charT>::erase(size_t pos __attribute__((unused)), size_t n __attribute__((unused)))
		{
			//for(int i = )
		}

		template<class charT>
		inline charT* string<charT>::toCString() const
		{
			return buf;
		}
		/**
		** @brief        function to write on the output stream (std::ostream)
		** @param &out ostream object (output stream)
		*/
		template<>
		inline void string<char>::output (std::ostream &out)
		{
			out << buf;
		}
		template<>
		inline void string<wchar_t>::output (std::wostream &wout)
		{
			wout << buf;
		}

}
#endif // AFW_TARGET_CXX
#endif // AURORAFW_STDL_STRING_H
