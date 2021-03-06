#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "glsl.hpp"

class Player
{
public:
Player();
bool Initialize(GLSLProgram* prog);
void Render();

private:
GLSLProgram* m_shader;

float player_vertices[12];
GLuint player_indices[6];
float player_colors[12];

GLuint player_vertexBuffer;
GLuint player_indexBuffer;
GLuint player_colorBuffer;

void InitVertexBuffer();
void InitColorBuffer();
};


#endif
