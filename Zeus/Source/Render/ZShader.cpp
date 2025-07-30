#include "Core/CoreLibrary.h"
#include "ZShader.h"
#include "Core/Error.h"

ZShader::ZShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		MakeShader(vertexShaderPath, fragShaderPath);
	}
	else
	{
		MakeShader(vertexShaderPath, fragShaderPath, geoShaderPath);
	}

	GLint uniformCount{};
	glGetProgramiv(z_Program, GL_ACTIVE_UNIFORMS, &uniformCount);

	if (uniformCount != 0)
	{
		GLint maxNameLength{};
		glGetProgramiv(z_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		GLsizei length{};
		GLsizei count{};
		GLenum type{};

		for (auto i = 0; i < uniformCount; i++)
		{
			//'\O'
			std::string name(maxNameLength, '\n');
			glGetActiveUniform(z_Program, i, maxNameLength, &length, &count, &type, name.data());

			name.resize(length);

			const auto location = glGetUniformLocation(z_Program, name.c_str());

			z_UniformCache[name] = location;
		}
	}
}

void ZShader::MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		Create(z_Vertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(z_Fragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		LinkShader();
	}
	else
	{
		Create(z_Vertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(z_Fragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		Create(z_Geometry, fragShaderPath.string().c_str(), GL_GEOMETRY_SHADER);
		LinkShader();
	}
}

void ZShader::Attach() const
{
	glUseProgram(z_Program);
}

void ZShader::SetVec3(std::string_view name, Vec3 value) const
{
	const auto uniform = z_UniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);

	if (uniform == std::ranges::cend(z_UniformCache))
	{
		Error error(string);
	}

	::glUniform3fv(uniform->second, 1, &value[0]);
}

void ZShader::SetMat4(std::string_view name, const Mat4& value) const
{
	const auto uniform = z_UniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);

	if (uniform == std::ranges::cend(z_UniformCache))
	{
		Error error(string);
	}

	::glUniformMatrix4fv(uniform->second, 1, GL_FALSE, glm::value_ptr(value));
}

void ZShader::SetInt(std::string_view name, int value) const
{
	const auto uniform = z_UniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);

	if (uniform == std::ranges::cend(z_UniformCache))
	{
		Error error(string);
	}

	::glUniform1i(uniform->second, value);
}

void ZShader::SetFloat(std::string_view name, float value) const
{
	const auto uniform = z_UniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);

	if (uniform == std::ranges::cend(z_UniformCache))
	{
		Error error(string);
	}

	::glUniform1f(uniform->second, value);
}

void ZShader::Create(uint32_t& shader, const char* path, uint32_t type)
{
	std::ifstream file;

	std::stringstream ssfile;

	std::string code;

	file.open(path);
	std::stringstream vShaderStream;
	ssfile << file.rdbuf();

	file.close();
	code = ssfile.str();
	const char* glShader = code.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &glShader, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &z_Success);

	glGetShaderInfoLog(shader, 512, NULL, z_InfoLog);
	std::string string = std::format("Failed to compile shader {}", z_InfoLog);

	if (z_Success == 0)
	{
		Error error(string);
	}

}

void ZShader::LinkShader()
{
	z_Program = glCreateProgram();
	glAttachShader(z_Program, z_Vertex);
	glAttachShader(z_Program, z_Fragment);
	glLinkProgram(z_Program);

	glGetProgramiv(z_Program, GL_LINK_STATUS, &z_Success);

	glGetProgramInfoLog(z_Program, 512, NULL, z_InfoLog);
	std::string string = std::format("Failed to link program {}", z_InfoLog);

	if (z_Success == 0)
	{
		Error error(string);
	}

	glDeleteShader(z_Vertex);
	glDeleteShader(z_Fragment);
}