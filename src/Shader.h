#pragma once

#include "BaseShader.h"
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

/// <summary>
/// Shader class which accepts direct file path variable to vertex and fragment shader(if both shader are in same file)
/// Shader class which accepts multiple file path variables to vertex and fragment shader(if both shader are in different files)
/// Note: BaseShader is already Inherited.
/// </summary>
class Shader : public BaseShader
{
public:
	Shader(const std::string& filepath);
	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	virtual ~Shader();

	void Bind() const override;
	void UnBind() const override;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformMat4fp(const std::string& name, const float* value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	ShaderProgramSource ParseShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
};