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

#include <AuroraFW/Image/Image.h>

namespace AuroraFW {
	namespace ImageManager {

		bool Image::_freeImageInitialised = false;

		ImageNotFoundException::ImageNotFoundException(const char *path)
			: _path(std::string("The file " + std::string(path) + " couldn't be"
			"found/read!")) {}

		const char* ImageNotFoundException::what() const throw()
		{
			return _path.c_str();
		}

		ImageAllocationFailedException::ImageAllocationFailedException(const char *path)
			: _path(std::string("The allocation for the image " + std::string(path) +
			" failed.")) {}

		const char* ImageAllocationFailedException::what() const throw()
		{
			return _path.c_str();
		}

		const char* ImageIsReadOnlyException::what() const throw()
		{
			return "There was an attempt to edit a read-only image!";
		}
		
		const char* ImageIsWriteOnlyException::what() const throw()
		{
			return "There was an attempt to read a write-only image!";
		}

		Image::Image(FREE_IMAGE_FORMAT fif, const char* path , ImageFlags flags , int width , int height, int bpp)
			: _fif(fif), _path(path), _flags(flags), _width(width), _height(height), _bpp(bpp)
		{
			// Initializes FreeImage
			if(!_freeImageInitialised) {
				FreeImage_Initialise();
				CLI::Log(CLI::Information, "FreeImage was initialized.");
				_freeImageInitialised = true;
			}

			_image = FreeImage_Load(fif, path, 0);

			if(_flags & ImageFlags::Read) {
				// The user wants to read the file.
				AuroraFW::DebugManager::Log("Read flag.");
				if(!_image) {
					throw ImageNotFoundException(path);
				}
				_bpp = FreeImage_GetBPP(_image);
			}

			if(_flags & ImageFlags::Write) {
				if(!_image) {
					_image = FreeImage_Allocate(_width, _height, _bpp);
					if(!_image) {
						throw ImageAllocationFailedException(path);
					}
					AuroraFW::DebugManager::Log("Write flag: image didn't exist, space was allocated.");
				} else {
					AuroraFW::DebugManager::Log("Write flag: image existed.");
				}
			}
		}

		Image::~Image()
		{
			FreeImage_Unload(_image);
			AuroraFW::DebugManager::Log("The image was deleted from memory.");
		}

		void Image::convertTo32Bits()
		{
			if(_bpp != 32) {
				FIBITMAP *_bitmap32 = FreeImage_ConvertTo32Bits(_image);
				FreeImage_Unload(_image);
				_image = FreeImage_Clone(_bitmap32);
				FreeImage_Unload(_bitmap32);
				_bpp = 32;
			}
		}

		void Image::setReadOnly()
		{
			_flags = _flags & ~ImageFlags::Write;
			_flags = _flags | ImageFlags::Read;
		}

		void Image::setWriteOnly()
		{
			_flags = _flags & ~ImageFlags::Read;
			_flags = _flags | ImageFlags::Write;
		}

		void Image::setReadAndWrite()
		{
			_flags = _flags | (ImageFlags::Read | ImageFlags::Write);
		}

		void Image::setClearPixelColor(const Color& color)
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void Image::clearPixel(int x, int y)
		{
			#pragma message ("TODO: Need to be implemented")
		}

		void Image::clearImage()
		{
			#pragma message ("TODO: Need to be implemented")
		}

		bool Image::drawPixel(int x, int y, const Color& color)
		{
			if(isReadOnly())
				throw ImageIsReadOnlyException();
			
			_color.rgbRed = color.red();
			_color.rgbGreen = color.green();
			_color.rgbBlue = color.blue();

			if(color.alpha() != 255 && !is32Bit()) {
				CLI::Log(CLI::Warning, "There are alpha values in the supplied color, however the image is not 32-bit.",
				"The alpha information will be lost. If you want to use alpha, first convert the image to 32-bit.");
				_color.rgbReserved = 255;
			} else {
				_color.rgbReserved = color.alpha();
			}

			return FreeImage_SetPixelColor(_image, x, y, &_color);
		}

		bool Image::saveImage()
		{
			if(isReadOnly())
				throw ImageIsReadOnlyException();
			
			return FreeImage_Save(_fif, _image, _path, 0);
		}
	}
}