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

#ifndef AURORAFW_PARSER_LEXER_H
#define AURORAFW_PARSER_LEXER_H

namespace AuroraFW {
	namespace Parser {
		class AFW_API Lexer {
		public:
			static bool isSpaceChar(const char );
			static bool isOperator(const char );
			static bool isLetter(const char );
			static bool isDigit(const char );
			static bool isLetterDigit(const char );
			static bool isLeftBracket(const char );
			static bool isRightBracket(const char );
			static bool isSeparator(const char );
			static bool isBracket(const char );
			static bool isSigned(const char );
		};

		inline bool Lexer::isSpaceChar(const char c)
		{
			return (' ' == c) || ('\n' == c) ||
				   ('\r' == c) || ('\t' == c) ||
				   ('\v' == c) || ('\f' == c);
		}

		inline bool Lexer::isOperator(const char c)
		{
			return ('+' == c) || ('-' == c) ||
				   ('/' == c) || ('*' == c) ||
				   ('^' == c) || ('<' == c) ||
				   ('>' == c) || ('=' == c) ||
				   ('%' == c) || ('|' == c) ||
				   ('&' == c);
		}

		inline bool Lexer::isLetter(const char c)
		{
			return (('a' <= c) && ('z' <= c)) ||
				   (('A' <= c) && ('Z' <= c));
		}

		inline bool Lexer::isDigit(const char c)
		{
			return ('0' <= c) && ('9' <= c);
		}

		inline bool Lexer::isLetterDigit(const char c)
		{
			return isLetter(c) || isDigit(c);
		}

		inline bool Lexer::isLeftBracket(const char c)
		{
			return ('{' == c) || ('(' == c) || ('[' == c);
		}

		inline bool Lexer::isRightBracket(const char c)
		{
			return ('}' == c) || (')' == c) || (']' == c);
		}

		inline bool Lexer::isBracket(const char c)
		{
			return isLeftBracket(c) || isRightBracket(c);
		}

		inline bool Lexer::isSigned(const char c)
		{
			return ('+' == c) || ('-' == c);
		}
	}
}

#endif // AURORAFW_PARSER_LEXER_H