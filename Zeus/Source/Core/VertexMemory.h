#pragma once

#include "Core/CoreLibrary.h"

class ZBufferObject
{
public:
    ZBufferObject(GLenum type = GL_ARRAY_BUFFER)
        : z_Type(type)
    {
    }

    void Generate()
    {
        glGenBuffers(1, &z_Val);
    }

    void Attach() const
    {
        glBindBuffer(z_Type, z_Val);
    }

    template<typename T>
    void SetData(GLuint noElements, T* data, GLenum usage)
    {
        glBufferData(z_Type, noElements * sizeof(T), data, usage);
    }

    template<typename T>
    void SetData(T& data, GLenum usage)
    {
        glBufferData(z_Type, sizeof(data), data, usage);
    }

    template<typename T>
    void UpdateData(GLintptr offset, GLuint noElements, T* data)
    {
        glBufferSubData(z_Type, offset, noElements * sizeof(T), data);
    }

    template<typename T>
    void SetAttPointer(GLuint idx, GLint size, GLenum type, GLuint stride, GLuint offset, GLuint divisor = 0)
    {
        glVertexAttribPointer(idx, size, type, GL_FALSE, stride * sizeof(T), (void*)(offset * sizeof(T)));
        glEnableVertexAttribArray(idx);
        if (divisor > 0)
        {
            glVertexAttribDivisor(idx, divisor);
        }
    }

    void Detach() const
    {
        glBindBuffer(z_Type, 0);
    }

    void Free() const
    {
        glDeleteBuffers(1, &z_Val);
    }

    GLuint z_Val;
    GLenum z_Type;
};

class ZArrayObject
{
public:
    ZBufferObject& operator[](const char* key)
    {
        return z_Buffers[key];
    }

    void Generate()
    {
        glGenVertexArrays(1, &z_Val);
    }

    void Attach() const
    {
        glBindVertexArray(z_Val);
    }

    void Render(GLenum mode, GLuint first, GLuint count) const
    {
        glDrawArrays(mode, first, count);
    }

    void Render(GLenum mode, GLuint first, GLuint count, const void* indices) const
    {
        glDrawElements(mode, first, count, indices);
    }

    void RenderArrays(GLenum mode, GLint first, GLsizei count, GLsizei iCount) const
    {
        glDrawArraysInstanced(mode, first, count, iCount);
    }

    void Render(GLenum mode, GLuint count, GLenum type, GLint indices, GLuint instancecount = 1) const
    {
        glDrawElementsInstanced(mode, count, type, (void*)indices, instancecount);
    }

    void Free()
    {
        glDeleteVertexArrays(1, &z_Val);
        for (auto& pair : z_Buffers)
        {
            pair.second.Free();
        }
    }

    static void Detach()
    {
        glBindVertexArray(0);
    }


    GLuint z_Val;

    std::map<const char*, ZBufferObject> z_Buffers;
};