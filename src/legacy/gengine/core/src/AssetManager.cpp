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

#include <AuroraFW/GEngine/AssetManager.h>

namespace AuroraFW {
	namespace GEngine {
		AssetNotFoundException::AssetNotFoundException(const char* path)
			: _path(path) {}

		const char* AssetNotFoundException::what() const throw()
		{
			std::stringstream error;
			error << "The file " << _path << " couldn't be found/read!";
			return error.str().c_str();
		}


		const char* AssetTypeInvalidException::what() const throw()
		{
			return "The given AssetType is invalid!";
		}

		auto AssetManager::loadAsset(const char* path, const AssetType& type)
		{
			// Loads the file
			std::ifstream file;
			file.open(path, std::ios::binary);

			// If the file can't be found/read, stop right here
			if(file.fail())
				throw AssetNotFoundException(path);

			// Returns the object as intended
			switch (type)
			{
				case AssetType::Audio:
					// TODO: Implement AudioAsset
					break;
				case AssetType::Font:
					// TODO: Implement FontAsset
					break;
				case AssetType::GUI:
					// TODO: Implement GUIAsset
					break;
				case AssetType::Material:
					// TODO: Implement MaterialAsset
					break;
				case AssetType::Model:
					// TODO: Implement ModelAsset
					break;
				case AssetType::Terrain:
					// TODO: Implement TerrainAsset
					break;
				case AssetType::Texture:
					// TODO: Implement TextureAsset
					break;
				case AssetType::Shader:
					// TODO: Implement ShaderAsset
					break;
				default:
					throw AssetTypeInvalidException();
			}
		}
	}
}