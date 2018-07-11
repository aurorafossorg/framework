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

#include <AuroraFW/GEngine/GL/ImGui/Loader.h>

namespace AuroraFW {
	namespace GEngine {
		GLImGuiLoader::GLImGuiLoader()
		{}

		void GLImGuiLoader::_Unload()
		{}

		bool GLImGuiLoader::createDeviceObjects()
		{
			// Backup GL state
			GLint last_texture, last_array_buffer, last_vertex_array;
			GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture));
			GLCall(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer));
			GLCall(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array));

			const GLchar *vertex_shader =
				"#version 150\n"
				"uniform mat4 ProjMtx;\n"
				"in vec2 Position;\n"
				"in vec2 UV;\n"
				"in vec4 Color;\n"
				"out vec2 Frag_UV;\n"
				"out vec4 Frag_Color;\n"
				"void main()\n"
				"{\n"
				"	Frag_UV = UV;\n"
				"	Frag_Color = Color;\n"
				"	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
				"}\n";

			const GLchar* fragment_shader =
				"#version 150\n"
				"uniform sampler2D Texture;\n"
				"in vec2 Frag_UV;\n"
				"in vec4 Frag_Color;\n"
				"out vec4 Out_Color;\n"
				"void main()\n"
				"{\n"
				"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
				"}\n";

			GLCall(_shaderHandle = glCreateProgram());
			GLCall(_vertHandle = glCreateShader(GL_VERTEX_SHADER));
			GLCall(_fragHandle = glCreateShader(GL_FRAGMENT_SHADER));
			GLCall(glShaderSource(_vertHandle, 1, &vertex_shader, 0));
			GLCall(glShaderSource(_fragHandle, 1, &fragment_shader, 0));
			GLCall(glCompileShader(_vertHandle));
			GLCall(glCompileShader(_fragHandle));
			GLCall(glAttachShader(_shaderHandle, _vertHandle));
			GLCall(glAttachShader(_shaderHandle, _fragHandle));
			GLCall(glLinkProgram(_shaderHandle));

			GLCall(_attribLocationTex = glGetUniformLocation(_shaderHandle, "Texture"));
			GLCall(_attribLocationProjMtx = glGetUniformLocation(_shaderHandle, "ProjMtx"));
			GLCall(_attribLocationPosition = glGetAttribLocation(_shaderHandle, "Position"));
			GLCall(_attribLocationUV = glGetAttribLocation(_shaderHandle, "UV"));
			GLCall(_attribLocationColor = glGetAttribLocation(_shaderHandle, "Color"));

			GLCall(glGenBuffers(1, &_vboHandle));
			GLCall(glGenBuffers(1, &_elementsHandle));

			{
				// Build texture atlas
				ImGuiIO& io = ImGui::GetIO();
				unsigned char* pixels;
				int width, height;
				io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

				// Upload texture to graphics system
				GLint last_texture;
				GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture));
				GLCall(glGenTextures(1, &_fontTexture));
				GLCall(glBindTexture(GL_TEXTURE_2D, _fontTexture));
				GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GLCall(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));

				// Store our identifier
				io.Fonts->TexID = (void *)(intptr_t)_fontTexture;

				// Restore state
				GLCall(glBindTexture(GL_TEXTURE_2D, last_texture));
			}

			// Restore modified GL state
			GLCall(glBindTexture(GL_TEXTURE_2D, last_texture));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer));
			GLCall(glBindVertexArray(last_vertex_array));

			return true;
		}

		void GLImGuiLoader::invalidateDeviceObjects()
		{
			if (_vboHandle) { GLCall(glDeleteBuffers(1, &_vboHandle)); }
			if (_elementsHandle) { GLCall(glDeleteBuffers(1, &_elementsHandle)); }
			_vboHandle = _elementsHandle = 0;

			if (_shaderHandle && _vertHandle) { GLCall(glDetachShader(_shaderHandle, _vertHandle)); }
			if (_vertHandle) { GLCall(glDeleteShader(_vertHandle)); }
			_vertHandle = 0;

			if (_shaderHandle && _fragHandle) { GLCall(glDetachShader(_shaderHandle, _fragHandle)); }
			if (_fragHandle) { GLCall(glDeleteShader(_fragHandle)); }
			_fragHandle = 0;

			if (_shaderHandle) { GLCall(glDeleteProgram(_shaderHandle)); }
			_shaderHandle = 0;

			if (_fontTexture)
			{
				GLCall(glDeleteTextures(1, &_fontTexture));
				ImGui::GetIO().Fonts->TexID = 0;
				_fontTexture = 0;
			}
		}

		void GLImGuiLoader::renderDrawLists(ImDrawData* data)
		{
			// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
			ImGuiIO& io = ImGui::GetIO();
			int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
			int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
			if (fb_width == 0 || fb_height == 0)
				return;
			data->ScaleClipRects(io.DisplayFramebufferScale);

			// Backup GL state
			GLenum last_active_texture; GLCall(glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture));
			glActiveTexture(GL_TEXTURE0);
			GLint last_program; GLCall(glGetIntegerv(GL_CURRENT_PROGRAM, &last_program));
			GLint last_texture; GLCall(glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture));
			GLint last_sampler; GLCall(glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler));
			GLint last_array_buffer; GLCall(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer));
			GLint last_element_array_buffer; GLCall(glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer));
			GLint last_vertex_array; GLCall(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array));
			GLint last_polygon_mode[2]; GLCall(glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode));
			GLint last_viewport[4]; GLCall(glGetIntegerv(GL_VIEWPORT, last_viewport));
			GLint last_scissor_box[4]; GLCall(glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box));
			GLenum last_blend_src_rgb; GLCall(glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb));
			GLenum last_blend_dst_rgb; GLCall(glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb));
			GLenum last_blend_src_alpha; GLCall(glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha));
			GLenum last_blend_dst_alpha; GLCall(glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha));
			GLenum last_blend_equation_rgb; GLCall(glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb));
			GLenum last_blend_equation_alpha; GLCall(glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha));
			GLCall(GLboolean last_enable_blend = glIsEnabled(GL_BLEND));
			GLCall(GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE));
			GLCall(GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST));
			GLCall(GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST));

			// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendEquation(GL_FUNC_ADD));
			GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			GLCall(glDisable(GL_CULL_FACE));
			GLCall(glDisable(GL_DEPTH_TEST));
			GLCall(glEnable(GL_SCISSOR_TEST));
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

			// Setup viewport, orthographic projection matrix
			GLCall(glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height));
			const float ortho_projection[4][4] =
			{
				{ 2.0f/io.DisplaySize.x, 0.0f, 0.0f, 0.0f },
				{ 0.0f, 2.0f/-io.DisplaySize.y, 0.0f, 0.0f },
				{ 0.0f, 0.0f, -1.0f, 0.0f },
				{-1.0f, 1.0f, 0.0f, 1.0f },
			};
			GLCall(glUseProgram(_shaderHandle));
			GLCall(glUniform1i(_attribLocationTex, 0));
			GLCall(glUniformMatrix4fv(_attribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]));
			GLCall(glBindSampler(0, 0)); // Rely on combined texture/sampler state.

			// Recreate the VAO every time 
			// (This is to easily allow multiple GL contexts. VAO are not shared among GL contexts, and we don't track creation/deletion of windows so we don't have an obvious key to use to cache them.)
			GLuint vao_handle = 0;
			GLCall(glGenVertexArrays(1, &vao_handle));
			GLCall(glBindVertexArray(vao_handle));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vboHandle));
			GLCall(glEnableVertexAttribArray(_attribLocationPosition));
			GLCall(glEnableVertexAttribArray(_attribLocationUV));
			GLCall(glEnableVertexAttribArray(_attribLocationColor));
			GLCall(glVertexAttribPointer(_attribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos)));
			GLCall(glVertexAttribPointer(_attribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv)));
			GLCall(glVertexAttribPointer(_attribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col)));

			// Draw
			for (int n = 0; n < data->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = data->CmdLists[n];
				const ImDrawIdx* idx_buffer_offset = 0;

				GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vboHandle));
				GLCall(glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW));

				GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementsHandle));
				GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW));

				for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
				{
					const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
					if (pcmd->UserCallback)
					{
						pcmd->UserCallback(cmd_list, pcmd);
					}
					else
					{
						GLCall(glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId));
						GLCall(glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y)));
						GLCall(glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset));
					}
					idx_buffer_offset += pcmd->ElemCount;
				}
			}
			GLCall(glDeleteVertexArrays(1, &vao_handle));

			// Restore modified GL state
			GLCall(glUseProgram(last_program));
			GLCall(glBindTexture(GL_TEXTURE_2D, last_texture));
			GLCall(glBindSampler(0, last_sampler));
			GLCall(glActiveTexture(last_active_texture));
			GLCall(glBindVertexArray(last_vertex_array));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer));
			GLCall(glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha));
			GLCall(glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha));
			if (last_enable_blend) { GLCall(glEnable(GL_BLEND)); } else { GLCall(glDisable(GL_BLEND)); }
			if (last_enable_cull_face) { GLCall(glEnable(GL_CULL_FACE)); } else { GLCall(glDisable(GL_CULL_FACE)); }
			if (last_enable_depth_test) { GLCall(glEnable(GL_DEPTH_TEST)); } else { GLCall(glDisable(GL_DEPTH_TEST)); }
			if (last_enable_scissor_test) { GLCall(glEnable(GL_SCISSOR_TEST)); } else { GLCall(glDisable(GL_SCISSOR_TEST)); }
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, (GLenum)last_polygon_mode[0]));
			GLCall(glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]));
			GLCall(glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]));
		}
	}
}