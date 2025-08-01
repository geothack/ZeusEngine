#include "Core/CoreLibrary.h"
#include "UniformBuffer.h"
#include "Core/Error.h"

UniformBuffer& UniformBuffer::Get()
{
	if (!z_UniformBuffer)
	{
		z_UniformBuffer = new UniformBuffer();
	}

	return *z_UniformBuffer;
}

void UniformBuffer::Create(std::string_view handle, size_t size, GLuint bindingPoint)
{
	if (z_UniformCache.find(handle.data()) != z_UniformCache.end())
	{
		Error error("UBO already exists");
	}

	GLuint ubo;
	glGenBuffers(1, &ubo); 
	glBindBuffer(GL_UNIFORM_BUFFER, ubo); 
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); 
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, 0); 

	z_UniformCache[handle.data()] = {ubo, size, bindingPoint};
}

void UniformBuffer::Update(std::string_view handle, size_t offset, const void* data, size_t dataSize)
{
	if (z_UniformCache.find(handle.data()) == z_UniformCache.end())
	{
		Error error("UBO not found");
	}

	glBindBuffer(GL_UNIFORM_BUFFER, z_UniformCache[handle.data()].bufferID);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0); 
}

void UniformBuffer::Attach(std::string_view handle, GLuint shaderID, std::string_view uboName)
{
	if (z_UniformCache.find(handle.data()) == z_UniformCache.end())
	{
		Error error("UBO not found");
	}

	GLuint blockIndex = glGetUniformBlockIndex(shaderID, uboName.data());

	if (blockIndex == GL_INVALID_INDEX) 
	{
		Error error("UBO not found");
	}

	glUniformBlockBinding(shaderID, blockIndex, z_UniformCache[handle.data()].bindingPoint);
}

void UniformBuffer::Free()
{
	for (auto& [tag, uboData] : z_UniformCache)
	{
		glDeleteBuffers(1, &uboData.bufferID);
	}
	delete z_UniformBuffer;
}
