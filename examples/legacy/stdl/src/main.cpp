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
** the GNU General Public License version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3 requirements will be
** met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/

#include <AuroraFW/Aurora.h>

using namespace AuroraFW;

Application *MyApp;

void slot_MyApp_on_open(Application* )
{
	CLI::Output << sizeof(char) << CLI::EndLine;

	/*
	** @brief Creating a normal string - Procidual operations
	*/
	AuroraFW::DebugManager::Log("creating a string and output it...");
	String TestString("Test!");
	CLI::Output << TestString << CLI::EndLine;
	if(TestString.length() == 5)
		CLI::setColor(CLI::Color::Green, CLI::ColorType::Foreground);
	else
		CLI::setColor(CLI::Color::Red, CLI::ColorType::Foreground);
	CLI::Output << TestString.length() << CLI::EndLine;
	CLI::resetColor();

	AuroraFW::DebugManager::Log("done.");
	AuroraFW::DebugManager::Log("creating a wide string and output it...");
	wString wTestString(L"Test!");
	CLI::wOutput << wTestString << CLI::EndLine;
	CLI::wOutput << wTestString.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	/*
	** @brief String by Copy - Procidual operations
	*/
	AuroraFW::DebugManager::Log("creating a string by copy and output it...");
	String World = " World!";
	String CpWorld(World);
	CLI::Output << CpWorld << CLI::EndLine;
	CLI::Output << CpWorld.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");
	AuroraFW::DebugManager::Log("creating a wide string by copy and output it...");
	wString wWorld = L" World!";
	wString wCpWorld(wWorld);
	CLI::wOutput << wCpWorld << CLI::EndLine;
	CLI::wOutput << wCpWorld.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	/*
	** @brief Concatenation procidual operations
	*/
	AuroraFW::DebugManager::Log("creating two strings, try to contatenate them with operator+ and output the result...");
	String Hello = "Hello,";
	AuroraFW::DebugManager::Log("concatenation process...");
	String HelloWorld = Hello + World;
	CLI::Output << HelloWorld << CLI::EndLine;
	CLI::Output << HelloWorld.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");
	AuroraFW::DebugManager::Log("creating two wide strings, try to contatenate them with operator+ and output the result...");
	wString wHello = L"Hello,";
	AuroraFW::DebugManager::Log("concatenation process...");
	wString wHelloWorld = wHello + wWorld;
	CLI::wOutput << wHelloWorld << CLI::EndLine;
	CLI::wOutput << wHelloWorld.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	/*
	** @brief procidual operations for += operator (using char ptr)
	*/
	AuroraFW::DebugManager::Log("creating a string and try to use +=operator with a char pointer and output the result...");
	String SomeString = "Hello";
	SomeString += ", World";
	CLI::Output << SomeString << CLI::EndLine;
	CLI::Output << SomeString.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	/*
	** @brief Procidual operations for += operator (using two strings)
	*/
	AuroraFW::DebugManager::Log("creating a string and try to use +=operator with another string and output the result...");
	String SomeString2 = "Message: ";
	SomeString2 += SomeString;
	CLI::Output << SomeString2 << CLI::EndLine;
	CLI::Output << SomeString2.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	AuroraFW::DebugManager::Log("creating two strings and try to use conditional ==operator with another string and output the result...");
	String Check1Eq = "Hello";
	String Check2Eq = Check1Eq;
	bool checkEq = Check1Eq == Check2Eq;
	CLI::Log(CLI::Information, "the result need to be true");
	CLI::Output << checkEq << CLI::EndLine;
	checkEq = Check1Eq == "Hello";
	CLI::Log(CLI::Information, "the result need to be true");
	CLI::Output << checkEq << CLI::EndLine;
	AuroraFW::DebugManager::Log("try to use conditional !=operator and output the result...");
	checkEq = Check1Eq != Check2Eq;
	CLI::Log(CLI::Information, "the result need to be false");
	CLI::Output << checkEq << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");

	AuroraFW::DebugManager::Log("try to find a string inside an another string");
	String findStr = "World Hello!";
	String tmp_str = "Hello";
	CLI::Log(CLI::Information, "the result need to be 6");
	CLI::Output << findStr.find(tmp_str, 0) << CLI::EndLine;

	AuroraFW::DebugManager::Log("try to find an array of chars inside a string");
	String findStr2 = "World Hello!";
	CLI::Log(CLI::Information, "the result need to be 6");
	CLI::Output << findStr2.find("Hello", 0) << CLI::EndLine;

	AuroraFW::DebugManager::Log("try to find an array of chars inside a string with a specific counter");
	String findStr3 = "HHHH";
	CLI::Log(CLI::Information, "the result need to be 21");
	CLI::Output << findStr3.find("H", 0, 4) << CLI::EndLine;

	AuroraFW::DebugManager::Log("creating two strings and try to use conditional !=operator with another string and output the result...");
	String Check1NEq = "Hello";
	String Check2NEq = "World!";
	bool checkNEq =  Check1NEq != Check2NEq;
	CLI::Log(CLI::Information, "the result need to be true");
	CLI::Output << checkNEq << CLI::EndLine;
	checkNEq = Check1NEq != "World!";
	CLI::Log(CLI::Information, "the result need to be true");
	CLI::Output << checkNEq << CLI::EndLine;
	AuroraFW::DebugManager::Log("try to use conditional ==operator and output the result...");
	checkNEq =  Check1NEq == Check2NEq;
	CLI::Log(CLI::Information, "the result need to be false");
	CLI::Output << checkNEq << CLI::EndLine;

	AuroraFW::DebugManager::Log("testing operator>> and output the input...");
	CLI::Log(CLI::Information, "You need to input something in the shell...");
	String inputstr;
	CLI::Input >> inputstr;
	AuroraFW::DebugManager::Log("reading input...");
	CLI::Output << inputstr << CLI::EndLine;
	CLI::Output << inputstr.length() << CLI::EndLine;
	AuroraFW::DebugManager::Log("done.");
}

int main(int argc, char * argv[])
{
	MyApp = new Application(argc, argv, slot_MyApp_on_open);
	delete MyApp;
	return 0;
}
