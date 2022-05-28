#include "stb_image/stb_image.h"
#include "Texture.h"
#include "Renderer.h"

//Texture::Texture(const std::string& path)
//	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_Channels(0)
//{
//	SetFlipVerticallyOnLoad(true);
//	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
//
//	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
//
//	//Used for settings formats based on the numbers of channels returned in "m_Channels".
//	GLenum internalFormat = 0, dataFormat = 0;
//
//	SetFormat(m_Channels, internalFormat, dataFormat);
//
//	GLCall(glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height));
//
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // Magnification filter doesn't use mip maps, because mipmaps are primarily used for when textures get downscaled.
//
//	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
//	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
//	//float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
//	//GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
//
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//	GLCall(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));
//	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
//	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
//
//	if (m_LocalBuffer)
//		stbi_image_free(m_LocalBuffer);
//}

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_Channels(0)
{
	SetFlipVerticallyOnLoad(true);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	GLCall(glGenTextures(1, &m_RendererID));

	//Used for settings formats based on the numbers of channels returned in "m_Channels".
	GLenum internalFormat = 0, dataFormat = 0;

	SetFormat(m_Channels, internalFormat, dataFormat);

	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	#pragma region LightMapCode

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	#pragma endregion

	#pragma region PreviousCode

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // Magnification filter doesn't use mip maps, because mipmaps are primarily used for when textures get downscaled.
	
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	#pragma endregion
	
	#pragma region TestingCode

	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	//float borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

	#pragma endregion

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	//if (m_LocalBuffer)
		//stbi_image_free(m_LocalBuffer);

	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetBlendFunction(GLenum sfactor, GLenum dfactor)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(sfactor, dfactor));
}

void Texture::SetFlipVerticallyOnLoad(bool value)
{
	stbi_set_flip_vertically_on_load(value);
}

void Texture::SetFormat(const int& channels, GLenum& internalFormat, GLenum& dataFormat)
{
	switch (channels)
	{
	case 4:
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
		break;
	case 3:
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
		break;
	default:
		break;
	}
}