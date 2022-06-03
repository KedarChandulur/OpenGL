#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& path, bool flipVertsOnLoad);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	//Enables blends and applies the sfactor and dfactor to blend function.
	static void SetBlendFunction(GLenum sfactor, GLenum dfactor);
	static void SetFlipVerticallyOnLoad(bool value = true);
private:
	void SetFormat(const int& channels, GLenum& internalFormat, GLenum& dataFormat);

	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Channels;
};