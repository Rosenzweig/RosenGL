#ifndef GLSL_HPP_INCLUDED
#define GLSL_HPP_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>

using std::string;
using std::ifstream;
using std::map;
using std::vector;

class GLSLProgram
{
public:
struct GLSLShader
{
        unsigned int id;
        string filename;
        string source;
};

GLSLProgram(const string& vertexShader, const string& fragmentShader)
{
        m_vertexShader.filename = vertexShader;
        m_fragmentShader.filename = fragmentShader;
};

virtual ~GLSLProgram()
{

};

void Unload()
{
    glDetachShader(m_programID, m_vertexShader.id);
    glDetachShader(m_programID, m_fragmentShader.id);
    glDeleteShader(m_vertexShader.id);
    glDeleteShader(m_fragmentShader.id);
    glDeleteShader(m_programID);
};

bool Initialize()
{
    m_programID = glCreateProgram();
    m_vertexShader.id = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader.id = glCreateShader(GL_FRAGMENT_SHADER);

    m_vertexShader.source = ReadFile(m_vertexShader.filename);
    m_fragmentShader.source = ReadFile(m_fragmentShader.filename);

    if (m_vertexShader.source.empty() || m_fragmentShader.source.empty())
    {
        return false;
    }

    const GLchar* tmp = static_cast<const GLchar*>(m_vertexShader.source.c_str());
    glShaderSource(m_vertexShader.id, 1, (const GLchar**)&tmp, NULL);

    tmp = static_cast<const GLchar*>(m_fragmentShader.source.c_str());
    glShaderSource(m_fragmentShader.id, 1, (const GLchar**)&tmp, NULL);

    if (!CompileShader(m_vertexShader) || !CompileShader(m_fragmentShader))
    {
        std::cerr << "Could not compile the shaders, they are invalid." << std::endl;
        return false;
    }

    glAttachShader(m_programID, m_vertexShader.id);
    glAttachShader(m_programID, m_fragmentShader.id);

    glLinkProgram(m_programID);
    return true;
};

void LinkProgram()
{
    glLinkProgram(m_programID);
};

GLuint GetUniformLocation(const string& name)
{
    map<string, GLuint>::iterator i = m_uniformMap.find(name);
    if (i == m_uniformMap.end())
    {
        GLuint location = glGetUniformLocation(m_programID, name.c_str());
        m_uniformMap.insert(std::make_pair(name, location));
        return location;
    }

    return (*i).second;
};

GLuint GetAttribLocation(const string& name)
{
    map<string, GLuint>::iterator i = m_attribMap.find(name);
    if (i == m_attribMap.end())
    {
        GLuint location = glGetAttribLocation(m_programID, name.c_str());
        m_attribMap.insert(std::make_pair(name, location));
        return location;
    }

    return (*i).second;
};

void SendUniform(const string& name, const float* matrix, bool transpose=false)
{
    GLuint location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, transpose, matrix);
};

void BindAttrib(unsigned int index, const string& attribName)
{
    glBindAttribLocation(m_programID, index, attribName.c_str());
};

void BindFragDataLocation(GLuint colorNumber, const string& fragName)
{
    glBindFragDataLocation(m_programID, colorNumber, fragName.c_str());
};

void BindShader()
{
    glUseProgram(m_programID);
};

private:
string ReadFile(const string& filename)
{
    ifstream fileIn(filename.c_str());

    if (!fileIn.good())
    {
        std::cerr << "Could not load shader: " << filename << std::endl;
        return string();
    }

    string stringBuffer(std::istreambuf_iterator<char>(fileIn), (std::istreambuf_iterator<char>()));
    return stringBuffer;
};

bool CompileShader(const GLSLShader& shader)
{
    glCompileShader(shader.id);
    GLint result = 0xDEADBEEF;
    glGetShaderiv(shader.id, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        std::cout << "Could not compile shader: " << shader.id << std::endl;
        OutputShaderLog(shader.id);
        return false;
    }

    return true;
};

void OutputShaderLog(unsigned int shaderID)
{
    vector<char> infoLog;
    GLint infoLen;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLen);
    infoLog.resize(infoLen);

    std::cerr << "GLSL Shader: Shader contains errors, please validate this shader!" << std::endl;
    glGetShaderInfoLog(shaderID, sizeof(infoLog), &infoLen, &infoLog[0]);

    std::cerr << string(infoLog.begin(), infoLog.end()) << std::endl;
};

GLSLShader m_vertexShader;
GLSLShader m_fragmentShader;
unsigned int m_programID;

map<string, GLuint> m_uniformMap;
map<string, GLuint> m_attribMap;
};

#endif
