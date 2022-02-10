#pragma once

#include <string>
#include <unordered_map>

/// <summary>
/// Base Shader Class.
/// </summary>
class BaseShader
{
public:
	virtual ~BaseShader();
protected:
	//By default this function does nothing.
	//Override the function for custom behaviour.
	virtual void Bind() const = 0;
	//By default this function does nothing.
	//Override the function for custom behaviour.
	virtual void UnBind() const = 0;

	//By default this function creates shader and returns the id.
	//Override the function for custom behaviour.
	virtual unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	//By default this function internally caches uniform(s) if they are atleast fetched once.
	//Override the function for custom behaviour.
	virtual int GetUniformLocation(const std::string& name) const;

	BaseShader();

	unsigned int m_RendererID;
private:
	unsigned int CompileShader(unsigned int type, const std::string& source);

	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};