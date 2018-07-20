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

/**	@file AuroraFW/GEngine/AssetManager.h
 * AssetManager header. This contains a singleton of AssetManager
 * used to load any assets needed.
 * @since snapshot20170930
 */

#ifndef AURORAFW_GENGINE_ASSETMANAGER_H
#define AURORAFW_GENGINE_ASSETMANAGER_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <exception>
#include <fstream>
#include <sstream>

namespace AuroraFW {
	namespace GEngine {

		/**
		 * An enum to indicate the type of asset wanted.	
		 * @since snapshot20170930
		 */
		enum class AssetType {
			/**
			 * An AudioAsset.
			 */
			Audio,
			/**
			 * A FontAsset.
			 */	
			Font,
			/**
			 * A GUIAsset.
			 */
			GUI,
			/**
			 * A MaterialAsset.
			 */		
			Material,
			/**
			 * A ModelAsset.
			 */
			Model,
			/**
			 * A TerainAsset.
			 */
			Terrain,
			/**
			 * A TextureAsset.
			 */
			Texture,
			/**
			 * A ShaderAsset.
			 */
			Shader
		};

		/**
		 * An exception to indicate an asset was not found.
		 * @since snapshot20170930
		 */
		class AssetNotFoundException: public std::exception {
		private:
			const char *_path;
		public:
			/**
			 * The constructor of the exception.
			 * @since snapshot20170930
			 */
			AssetNotFoundException(const char* );

			/**
			 * The exception's message:
			 * <em>"The file <path> couldn't be found/read!"</em>
			 * @since snapshot20170930
			 */
			virtual const char* what() const throw();
		};

		/**
		 * An exception to indicate an invalid asset type (from the enum AssetType)
		 * @since snapshot20170930
		 */
		class AssetTypeInvalidException: public std::exception {
		public:
			/**
			 * The exception's message:
			 * <em>"The given AssetType is invalid!"</em>
			 * @since snapshot20170930
			 */
			virtual const char* what() const throw();
		};

		/**
		 * A singleton class used to load any assets needed. A singleton class
		 * with static methods for the sole purpose of loading assets.
		 * @since snapshot20170930
		 */
		class AFW_API AssetManager {
		private:
			static AssetManager *_instance;
			AssetManager() {}
		public:
			/**
			 * Returns the only instance of AssetManager. If it wasn't initialized yet, it default constructs it.
			 * @return Instance of AssetManager
			 * @since snapshot20170930
			 */
			static AssetManager& getInstance()
			{
				if(_instance == nullptr)
					_instance = new AssetManager();
				return *_instance;
			}

			/**
			 * Loads an asset of the type given by the variable type.
			 * @param path The relative path (to the executing program) to the asset, including extension
			 * @param type The type of asset (from the enum AssetType)
			 * @exception AssetNotFoundException the asset was not found.
			 * @exception AssetTypeInvalidException the asset type is invalid.
			 * @return The loaded asset with the type wanted
			 * @since snapshot20170930
			 */
			static auto loadAsset(const char* , const AssetType& );
		};
	}
}

#endif // AURORAFW_GENGINE_ASSETMANAGER_H