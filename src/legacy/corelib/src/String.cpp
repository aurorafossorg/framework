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

#include <AuroraFW/CoreLib/String.h>
#include <AuroraFW/STDL/LibC/Assert.h>

#ifdef AFW_TARGET_CXX
	namespace AuroraFW
	{

		// @brief blank constructor for new string.
		template<class charT>
		string<charT>::string()
			:	buf(), len() {}

		/**
		** @brief        private constructor for temporary buffer.
		** @param cstr array of characters (string)
		*/
		template<class charT>
		string<charT>::string(size_t n)
			:	buf(new charT[n + 1]),
				len(n)
		{
			//buf = new charT[n + 1];
			//len = n;
		}

		/**
		** @brief        constructor for new string.
		** @param cstr array of characters (string)
		*/
		template<>
		string<char>::string(const char* cstr)
			:	buf(new char[size() + 1]),
				len(strlen(cstr))
		{
			// len = strlen(cstr);
			// buf = new char[size() + 1];
			memcpy(buf, cstr, (size() + 1) * sizeof(char));
		}
		template<>
		string<wchar_t>::string(const wchar_t* cstr)
			:	buf(new wchar_t[size() + 1]),
				len(wcslen(cstr))
		{
			// len = wcslen(cstr);
			// buf = new wchar_t[size() + 1];
			memcpy(buf, cstr, (size() + 1) * sizeof(wchar_t));
		}
		/**
		** @brief        constructor for new string by copy.
		** @param &str string object (for copy purpose).
		*/
		template<class charT>
		string<charT>::string(const string<charT> &str)
			:	buf(new charT[size() + 1]),
				len(str.size())
		{
			// len  = str.size();
			// buf = new charT[size() + 1];
			memcpy(buf, str.buf, (size() + 1) * sizeof(charT));
		}

		/**
		** @brief function to find a strings inside the string buffer
		** @return pos of first char of search query
		*/
		template<class charT>
		int string<charT>::find(const string<charT>& needle, const size_t pos) const
		{
			assert(pos+needle.length()+1<=len);
			for(size_t i = pos; i+1<=len-needle.length(); i++)
			{
				size_t j = 0;
				while(j+1 < needle.length() && buf[i+j] == needle[j]) j++;
				if(j+1 == needle.length()) return i;
			}
			return -1;
		}

		/**
		** @brief function to find a array of chars inside the string buffer
		** @return pos of first char of search query
		*/
		template<>
		int string<char>::find(const char* needle, const size_t pos) const
		{
			size_t tmp_len = strlen(needle);
			assert(pos+tmp_len+1<=len);
			for(size_t i = pos; i+1<=len-tmp_len; i++)
			{
				size_t j = 0;
				while(j+1 < tmp_len && buf[i+j] == needle[j]) j++;
				if(j+1 == tmp_len) return i;
			}
			return -1;
		}
		template<>
		int string<wchar_t>::find(const wchar_t* needle, const size_t pos) const
		{
		 	size_t tmp_len = wcslen(needle);
			assert(pos+tmp_len+1<=len);
			for(size_t i = pos; i+1<=len-tmp_len; i++)
			{
				size_t j = 0;
				while(j+1 < tmp_len && buf[i+j] == needle[j]) j++;
				if(j+1 == tmp_len) return i;
			}
			return -1;
		}

		/**
		** @brief function to find a array of chars inside the string buffer with a specific counter
		** @return pos of first char of search query
		*/
		template<>
		int string<char>::find(const char* needle, size_t pos, const size_t count) const
		{
			for(size_t tmp_count = 1; tmp_count <= count; tmp_count++)
			{
				pos += find(needle, pos)+strlen(needle);
			}
			return pos;
		}
		template<>
		int string<wchar_t>::find(const wchar_t* needle, size_t pos, const size_t count) const
		{
			for(size_t tmp_count = 1; tmp_count <= count; tmp_count++)
			{
				pos += find(needle, pos)+wcslen(needle);
			}
			return pos;
		}

		/**
		** @brief function to find a char inside the string buffer
		** @return pos of char of search query
		*/
		template<class charT>
		int string<charT>::find(const charT needle, size_t pos) const
		{
			assert(pos+2<=len);
			for(size_t i = pos; i+1<=len-1; i++)
			{
				if(buf[i] == needle) return i;
			}
			return -1;
		}

		/**
		** @brief        string operator = from another string
		** @param &str string object
		** @return       string (string with the same character type)
		*/
		template<class charT>
		string<charT>& string<charT>::operator = (const string<charT> str)
		{
			len = str.size();
			buf = new charT[size() + 1];
			memcpy(buf, str.buf, (size() + 1) * sizeof(charT) );
			return *this;
		}

		/**
		** @breif		 string operator + from a char ptr
		** @param &str char ptr
		** @return		 string (default string + char ptr)
		*/
		template<>
		string<char> string<char>::operator + (const char* str)
		{
			string<char> temp(size() + strlen(str));
			memcpy(temp.buf, buf, size() * sizeof(char));
			strcat(temp.buf, str);
			return temp;
		}
		template<>
		string<wchar_t> string<wchar_t>::operator + (const wchar_t* str)
		{
			string<wchar_t> temp(size() + wcslen(str));
			memcpy(temp.buf, buf, size() * sizeof(wchar_t));
			wcscat(temp.buf, str);
			return temp;
		}
		/**
		** @brief        string operator + from another string
		** @param &str string object
		** @return       string (string with the same character type)
		*/
		template<>
		string<char> string<char>::operator + (const string<char> str)
		{
			string<char> temp(size() + str.size());
			memcpy(temp.buf, buf, size() * sizeof(char));
			strcat(temp.buf, str.buf);
			return temp;
		}
		template<>
		string<wchar_t> string<wchar_t>::operator + (const string<wchar_t> str)
		{
			string<wchar_t> temp(size() + str.size());
			memcpy(temp.buf, buf, size() * sizeof(wchar_t));
			wcscat(temp.buf, str.buf);
			return temp;
		}

		/**
		** @brief        string operator += from another string
		** @param &str string object
		** @return       string (string with the same character type)
		*/
		template<>
		string<char>& string<char>::operator += (const string<char> str)
		{
			len += str.size();
			strcat(buf, str.buf);
			return *this;
		}
		template<>
		string<wchar_t>& string<wchar_t>::operator += (const string<wchar_t> str)
		{
			len += str.size();
			wcscat(buf, str.buf);
			return *this;
		}

		/**
		** @brief        string operator += from a char ptr
		** @param &str char pointer
		** @return       string (string with the same character type)
		*/
		template<>
		string<char>& string<char>::operator += (const char* str)
		{
			len += strlen(str);
			strcat(buf, str);
			return *this;
		}
		template<>
		string<wchar_t>& string<wchar_t>::operator += (const wchar_t* str)
		{
			len += wcslen(str);
			wcscat(buf, str);
			return *this;
		}

		/**
		** @brief       function to write on the input stream (std::istream)
		** @param &in istream object (input stream)
		**
		** bytes 	    2097152 <----- *
		** kilobits 	16384
		** kilobytes 	2048
		** megabits 	16
		** megabytes    2 <-----
		*/
		template<>
		void string<char>::input (std::istream &in)
		{
			char *tempbuf = new char[(AFW_STRING_MAX_INPUT_SIZE / sizeof(char))];
			in >> tempbuf;
			len = strlen(tempbuf);
			buf = new char[size() + 1];
			memcpy(buf, tempbuf, size() + 1);
			delete [] tempbuf;
		}
		template<>
		void string<wchar_t>::input (std::wistream &win)
		{
			wchar_t *tempbuf = new wchar_t[(AFW_STRING_MAX_INPUT_SIZE / sizeof(wchar_t))];
			win >> tempbuf;
			len = wcslen(tempbuf);
			buf = new wchar_t[size() + 1];
			memcpy(buf, tempbuf, size() + 1);
			delete [] tempbuf;
		}

		// string
		template class string<char>;
		template class string<wchar_t>;

		// stream operators
		/**
		** @brief        output stream (std::ostream) operator << from String
		**        (string).
		** @param &_out stream object (output stream)
		** @param &str String object (string object)
		*/
		std::ostream & operator << (std::ostream& out, String &str)
		{
			str.output(out);
			return out;
		}

		/**
		** @brief        input stream (std::istream) operator >> from String
		**        (string).
		** @param &_in   stream object (input stream)
		** @param &str String object (string object)
		*/
		std::istream & operator >> (std::istream& in, String &str)
		{
			str.input(in);
			return in;
		}
		// for wide characters
		/**
		** @brief        output stream (std::wostream) operator << from wString
		**        (wide string).
		** @param &_wout  stream object (output stream for wide characters)
		** @param &wstr wString object (string object for wide characters)
		*/
		std::wostream & operator << (std::wostream& wout, wString &wstr)
		{
			wstr.output(wout);
			return wout;
		}

		/**
		** @brief         input stream (std::wistream) operator >> from wString
		**        (wide string).
		** @param &_win   wstream object (input stream for wide characters)
		** @param &wstr wString object (string object for wide characters)
		*/
		std::wistream & operator >> (std::wistream& win, wString &wstr)
		{
			wstr.input(win);
			return win;
		}
	}
#endif /// AFW_TARGET_CXX
