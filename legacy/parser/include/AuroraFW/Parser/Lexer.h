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