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