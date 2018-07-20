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

#ifndef AURORAFW_CLI_LOG_H
#define AURORAFW_CLI_LOG_H

#include <AuroraFW/CoreLib/Target/System.h>
#include <AuroraFW/CLI/Output.h>
#include <AuroraFW/Core/DebugManager.h>

#ifndef AFW_LOGMESSAGE
	#ifdef AFW__NDEBUG
		#define AFW_LOGMESSAGE 0
	#else
		#define AFW_LOGMESSAGE 1
	#endif
#endif

#if AFW_LOGMESSAGE
	#define AFW_LOGMESSAGE_FILE __FILE__
	#define AFW_LOGMESSAGE_LINE __LINE__
	#define AFW_LOGMESSAGE_FUNC AFW_FUNC_INFO
#else
	#define AFW_LOGMESSAGE_FILE AFW_NULLPTR
	#define AFW_LOGMESSAGE_LINE 0
	#define AFW_LOGMESSAGE_FUNC AFW_NULLPTR
#endif

namespace AuroraFW {
	namespace CLI {
		enum MessageStatus
		{
			Error,
			Warning,
			Notice,
			Information,
			Debug
		};

		template <typename T>
		void __Log(const T& t)
		{
			Output << t;
		}

		template <typename T, typename... R>
		void __Log(const T& t, const R&... args)
		{
			Output << t;
			__Log(args...);
		}

		template <typename T, typename... R>
		void Log (const T& t, const R&... args)
		{
			// TODO: Windows ANSI integration
			//       Needs to be tested on Windows and Apple platforms
			if(t == Error)
			{
				#ifdef AFW_TARGET_ENVIRONMENT_UNIX
				Output << "\033[0m\033[1m[\033[1;31mERROR\033[0;1m] \033[0m";
				#else
				Output << "[ERROR] ";
				#endif
			}
			else if (t == Warning)
			{
				#ifdef AFW_TARGET_ENVIRONMENT_UNIX
				Output << "\033[0m\033[1m[\033[1;33mWARNING\033[0;1m] \033[0m";
				#else
				Output << "[WARNING] ";
				#endif
			}
			else if (t == Notice)
			{
				#ifdef AFW_TARGET_ENVIRONMENT_UNIX
				Output << "\033[0m\033[1m[\033[1;36mNOTICE\033[0;1m] \033[0m";
				#else
				Output << "[NOTICE] ";
				#endif
			}
			else if (t == Information)
			{
				#ifdef AFW_TARGET_ENVIRONMENT_UNIX
				Output << "\033[0m\033[1m[\033[1;32mINFORMATION\033[0;1m] \033[0m";
				#else
				Output << "[INFORMATION] ";
				#endif
			}
			else
			{
				__Log(t, args...);
				Output << EndLine;
				return;
			}
			__Log(args...);
			Output << EndLine;
		}

		class AFW_API Logger {
		public:
			//TODO: Implement logger
		};
	}
}

#define afwNoDebug while(false) AuroraFW::CLI::Logger().noDebug

#ifdef AFW__LOGGER_NDEBUG
	#define afwDebug afwNoDebug
#else
	#define afwDebug AuroraFW::CLI::Logger(AFW_LOGMESSAGE_FILE, AFW_LOGMESSAGE_LINE, AFW_LOGMESSAGE_FUNC).debug
#endif

#ifdef AFW__LOGGER_NINFO
	#define afwInfo afwNoDebug
#else
	#define afwInfo AuroraFW::CLI::Logger(AFW_LOGMESSAGE_FILE, AFW_LOGMESSAGE_LINE, AFW_LOGMESSAGE_FUNC).info
#endif

#ifdef AFW__LOGGER_NWARN
	#define afwWarning afwNoDebug
#else
	#define afwWarning AuroraFW::CLI::Logger(AFW_LOGMESSAGE_FILE, AFW_LOGMESSAGE_LINE, AFW_LOGMESSAGE_FUNC).warning
#endif

#define afwCritical AuroraFW::CLI::Logger(AFW_LOGMESSAGE_FILE, AFW_LOGMESSAGE_LINE, AFW_LOGMESSAGE_FUNC).critical
#define afwFatal AuroraFW::CLI::Logger(AFW_LOGMESSAGE_FILE, AFW_LOGMESSAGE_LINE, AFW_LOGMESSAGE_FUNC).fatal

#endif // AURORAFW_CLI_LOG_H
