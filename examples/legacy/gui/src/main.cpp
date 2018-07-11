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

void slot_MyGUIApp_on_open()
{
	GUI::Window window("Example Window");
	//GUI::Button TestButton(&FirstWindow, "TestButton");
	GUI::Label helloLbl(&window, "Hello World!");
	helloLbl.setText("Hello, World!");
	helloLbl.setSelectable(true);
	helloLbl.setWrap(true);
	helloLbl.setWrapMode(GUI::WrapMode::Word);
	helloLbl.setAlignment(GUI::AlignMode::BottomRight);
	//helloLbl.setAlignment(0.7, 0.8);
	CLI::Log(CLI::Information,"X: ", helloLbl.getXAlignment());
	CLI::Log(CLI::Information,"Y: ", helloLbl.getYAlignment());

	window.show();
}

int main(int argc, char * argv[])
{
	Application MyApp(argc, argv);
	GUI::Application MyGUIApp("org.aurora.example", GUI::Application::NoneFlag, slot_MyGUIApp_on_open);
	return MyGUIApp.getStatus();
}
