#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	//Temporarly created for light vbo.
	const unsigned int& GetRendererID() const;
private:
	unsigned int m_RendererID;
};