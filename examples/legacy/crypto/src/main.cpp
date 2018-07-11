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

#include <AuroraFW/Core.h>
#include <AuroraFW/Crypto.h>
#include <AuroraFW/CLI.h>

using namespace AuroraFW;

Application *MyApp;

void slot_MyApp_on_open(Application* )
{
	byte_t k[32] = {0x1a, 0xaa};
	byte_t c[16] = {0xa1, 0x11};
	CLI::Output << c << CLI::EndLine;
	CLI::Output << AES::encrypt(k, 128, c) << CLI::EndLine;
	CLI::Output << AES::decrypt(k, 128, AES::encrypt(k, 128, c)) << CLI::EndLine;
	Application::ExitSuccess();
}

int main(int argc, char * argv[])
{
	MyApp = new Application(argc, argv, slot_MyApp_on_open);
	return 0;
}
