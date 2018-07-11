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
using namespace ImageManager;

int width = 255, height = 255, bpp = 24;

Application *app;

Image *image1;
Image *image2;

void printRWInfo()
{
	AuroraFW::DebugManager::Log("The image \"output.jpg\" is read-only, (", image1->isReadOnly(),
							") and write-only. (", image1->isWriteOnly(), ")");

	AuroraFW::DebugManager::Log("Also, the image \"output.jpg\" is read-and-write. (", image1->isReadAndWrite(), ").");

	AuroraFW::DebugManager::Log("The image \"output.png\" is read-only, (", image2->isReadOnly(),
							") and write-only. (", image2->isWriteOnly(), ")");

	AuroraFW::DebugManager::Log("Also, the image \"output.png\" is read-and-write. (", image2->isReadAndWrite(), ").");
}

void appMainFunction(Application* )
{
	try {
		// Opens two images (one for reading and the other for editing)
		CLI::Log(CLI::Information, "Opening output.jpg as read-only.");
		image1 = new Image(FIF_JPEG, "output.jpg", ImageFlags::Read);
		CLI::Log(CLI::Information, "Opening output.png as write-only.");
		image2 = new Image(FIF_PNG, "output.png", ImageFlags::Write, width, height, bpp);

		// Prints wheter they are read/write
		printRWInfo();

		// Closes image1
		delete image1;
		image1 = nullptr;

		// Creates the color for editing
		AuroraFW::DebugManager::Log("Creating color");
		Color color(0, 0, 0);

		// BPP was specified to be 24, so tests converting it to 32
		image2->convertTo32Bits();
		CLI::Log(CLI::Information, "Converted the image to 32-bit.");

		// Prepares to edit image2
		CLI::Log(CLI::Information, "Preparing to edit image2.");
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
				color.setRed((uint8_t)Math::clamp(y-x, 0, height));
				color.setGreen((uint8_t)abs(y-height));
				color.setBlue((uint8_t)x);

				// DEBUG purposes
				color.setAlpha((uint8_t)128);

				image2->drawPixel(x, y, color);
			}
		}

		CLI::Log(CLI::Information, "The image was drawn, saving it...");
		image2->saveImage();
		CLI::Log(CLI::Information, "The image was saved to \"output.png\"");
	} catch(ImageNotFoundException& e1) {
		CLI::Log(CLI::Error, e1.what());
	} catch(ImageAllocationFailedException& e2) {
		CLI::Log(CLI::Error, e2.what());
	}

	return;
}

int main(int argc, char *argv[])
{
	app = new Application(argc, argv, appMainFunction);

	delete app;
	delete image2;
	image2 = nullptr;

	return EXIT_SUCCESS;
}
