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

/** @file AuroraFW/Image/Image.h
 * ImageManager header. This contains an Image class used to
 * handle images, and other things to complement said class
 * (such as ImageFlags, ImageExceptions, etc...)
 * @since snapshot20171022
 */

#ifndef AURORAFW_IMAGE_IMAGE_H
#define AURORAFW_IMAGE_IMAGE_H

#include <AuroraFW/Global.h>
#include <AuroraFW/CLI/Log.h>
#include <AuroraFW/STDL/STL/IOStream.h>
#include <AuroraFW/Image/BaseColor.h>

#include <exception>
#include <FreeImage.h>

namespace AuroraFW {
	namespace ImageManager {

		/**
		 * An enum to indicate read/write flags for the class Image.
		 * @since snapshot20171022
		 */
		enum ImageFlags {
			Read = 		(1<<0),	/**< Read flag. */
			Write =		(1<<1)	/**< Write flag. */
		};

		/**
		 * Operator defined internally to perform bitwise operations with ImageFlags.
		 * @since snapshot20171022
		 */
		inline ImageFlags operator|(ImageFlags a, ImageFlags b)
		{
			return static_cast<ImageFlags>(static_cast<int>(a) | static_cast<int>(b));
		}

		/**
		 * Operator defined internally to perform bitwise operations with ImageFlags.
		 * @since snapshot20171022
		 */
		inline ImageFlags operator&(ImageFlags a, ImageFlags b)
		{
			return static_cast<ImageFlags>(static_cast<int>(a) & static_cast<int>(b));
		}

		/**
		 * Operator defined internally to perform bitwise operations with ImageFlags.
		 * @since snapshot20171022
		 */
		inline ImageFlags operator~(ImageFlags a)
		{
			return static_cast<ImageFlags>(~static_cast<int>(a));
		}

		/**
		 * An exception to tell the user the given image couldn't be found
		 * @since snapshot20171022
		 */
		class ImageNotFoundException: public std::exception
		{
		private:
			const std::string _path;
		public:
			/**
			 * The constructor of the exception.
			 * @since snapshot20171022
			 */
			ImageNotFoundException(const char *);

			/**
			 * The exception's message:
			 * <em>The file <path> couldn't be found/read!</em>
			 * @since snapshot20171022
			 */
			virtual const char* what() const throw();
		};

		/**
		 * An exception to indicate it was not possible to allocate space for the intended image.
		 * @since snapshot20171022
		 */
		class ImageAllocationFailedException: public std::exception
		{
		private:
			const std::string _path;
		public:
			/**
			 * The constructor of the exception.
			 * @since snapshot20171022
			 */
			ImageAllocationFailedException(const char *);

			/**
			 * The exception's message:
			 * <em>The allocation for the image <path> failed.</em>
			 * @since snapshot20171022
			 */
			virtual const char* what() const throw();
		};

		/**
		 * An exception to indicate there was an attempt to edit a read-only image.
		 * @since snapshot20171022
		 */
		class ImageIsReadOnlyException: public std::exception
		{
		public:
			/**
			 * The constructor of the exception.
			 * @since snapshot20171022
			 */
			ImageIsReadOnlyException() {}

			/**
			 * The exception's message:
			 * <em>There was an attempt to edit a read-only image!</em>
			 * @since snapshot20171022
			 */
			virtual const char* what() const throw();
		};

		/**
		 * An exception to indicate there was an attempt to read a write-only image.
		 * @since snapshot20171022
		 */
		class ImageIsWriteOnlyException: public std::exception
		{
		public:
			/**
			 * The contructor of the exception.
			 * @since snapshot20171022
			 */
			ImageIsWriteOnlyException() {}

			/**
			 * The exception's message:
			 * <em>There was an attemp to read a write-only image!</em>
			 * @since snapshot20171022
			 */
			virtual const char* what() const throw();
		};

		/**
		 * A class representing an Image file. A class representing an Image file, allowing to read it's bytes
		 * and/or creating/editing them.
		 * @since snapshot20171022
		 */
		class AFW_API Image {
		public:
			/**
			 * Constructs an image depending on the flags given.
			 * @param fif The FREE_IMAGE_FORMAT (the image's extension) of the image.
			 * @param path The path of an existing image or where to create a new image.
			 * @param flags The ImageFlags intended for the image.
			 * @param width The width of the image <em>(if you want to create an image)</em>.
			 * @param height The height of the image <em>(if you want to create an image)</em>.
			 * @param bpp The BPP (bits per pixel) of the image <em>(if you want to create an image)</em>.
			 * @see ~Image()
			 * @since snapshot20171022
			 */
			Image(FREE_IMAGE_FORMAT , const char* , ImageFlags = (ImageFlags::Read | ImageFlags::Write),
			int = AFW_NULLVAL , int = AFW_NULLVAL , int = 32);

			/**
			 * Destructs an image.
			 * @see Image()
			 * @since snapshot20171022
			 */
			~Image();

			/**
			 * Returns if the image is read-only.
			 * @return <em>true</em> if the image is read-only. <em>false</em> otherwise.
			 * @see isWriteOnly()
			 * @see isReadAndWrite()
			 * @since snapshot20171022
			 */
			bool isReadOnly() const;

			/**
			 * Returns if the image is write-only.
			 * @return <em>true</em> if the image is write-only. <em>false</em> otherwise.
			 * @see isReadOnly()
			 * @see isReadAndWrite()
			 * @since snapshot20171022
			 */
			bool isWriteOnly() const;

			/**
			 * Returns if the image is bot read and write.
			 * @return <em>true</em> if the image is bot read and write. <em>false</em> otherwise.
			 * @see isReadOnly()
			 * @see isWriteOnly()
			 * @since snapshot20171022
			 */
			bool isReadAndWrite() const;

			/**
			 * Returns if the BPP's of the image are 32 <em>(has alpha channel)</em>.
			 * @return <em>true</em> if the image has 32 BPP. <em>false</em> otherwise.
			 * @since snapshot20171022
			 */
			bool is32Bit() const;

			/**
			 * Converts an image to 32 BPP <em>(adds an alpha channel)</em>.
			 * @throws ImageIsReadOnlyException In case the image is read-only.
			 * @since snapshot20171022
			 */
			void convertTo32Bits();

			/**
			 * Sets the ImageFlags of the image to the given flags.
			 * @param flags The ImageFlags to set this image to.
			 * @see setReadOnly()
			 * @see setWriteOnly()
			 * @see setReadAndWrite()
			 * @since snapshot20171022
			 */
			void setFlags(const ImageFlags );

			/**
			 * Sets the image to be read-only.
			 * @see setFlags(const ImageFlags )
			 * @see setWriteOnly()
			 * @see setReadAndWrite()
			 * @since snapshot20171022
			 */
			void setReadOnly();

			/**
			 * Sets the image to be write-only.
			 * @see setFlags(const ImageFlags )
			 * @see setReadOnly()
			 * @see setReadAndWrite()
			 * @since snapshot20171022
			 */
			void setWriteOnly();

			/**
			 * Sets the image to be read and write.
			 * @see setFlags(const ImageFlags )
			 * @see setReadOnly()
			 * @see setWriteOnly()
			 * @since snapshot20171022
			 */
			void setReadAndWrite();

			/**
			 * Sets the clear (background) pixel color.
			 * @param color The Color wanted.
			 * @see clearPixel(int , int )
			 * @see clearImage()
			 * @since snapshot20171022
			 */
			void setClearPixelColor(const Color& );

			/**
			 * Clears a pixel at the given coord's to the clear color.
			 * @param x The x coordinate <em>(from left to right)</em>
			 * @param y The y coordinate <em>(from bottom to top)</em>
			 * @throws ImageIsReadOnlyException In case the image is read-only.
			 * @see setClearPixelColor(const Color& )
			 * @see clearImage()
			 * @since snapshot20171022
			 */
			void clearPixel(int , int );

			/**
			 * Clears the whole image to the clear color.
			 * @throws ImageIsReadOnlyException In case the image is read-only.
			 * @see setClearPixelColor(const Color& )
			 * @see clearPixel(int , int )
			 * @since snapshot20171022
			 */
			void clearImage();

			/**
			 * Draws a pixel at the given coord's to the given color
			 * @param x The x coordinate <em>(from left to right)</em>
			 * @param y The y coordinate <em>(from bottom to top)</em>
			 * @param color The Color to draw the pixel to.
			 * @throws ImageIsReadOnlyException In case the image is read-only.
			 * @since snapshot20171022
			 */
			bool drawPixel(int , int , const Color& );

			/**
			 * Saves an image to the path given in the constructor.
			 * @throws ImageIsReadOnlyException In case the image is read-only.
			 * @since snapshot20171022
			 */
			bool saveImage();

		private:
			FREE_IMAGE_FORMAT _fif;
			const char *_path;
			ImageFlags _flags;
			int _width, _height, _bpp;

			static bool _freeImageInitialised;
			FIBITMAP *_image;
			Color _clearColor = Color(0xFFFFFF);
			RGBQUAD _color;
		};

		// Inline definitions
		inline bool Image::isReadOnly() const
		{
			return (_flags & ImageFlags::Read) == ImageFlags::Read;
		}

		inline bool Image::isWriteOnly() const
		{
			return (_flags & ImageFlags::Write) == ImageFlags::Write;
		}

		inline bool Image::isReadAndWrite() const
		{
			return (_flags & (ImageFlags::Read | ImageFlags::Write)) == (ImageFlags::Read | ImageFlags::Write);
		}

		inline bool Image::is32Bit() const
		{
			return _bpp == 32;
		}

		inline void Image::setFlags(const ImageFlags flags)
		{
			_flags = flags;
		}
	}
}

#endif	// AURORAFW_IMAGE_IMAGE_H
