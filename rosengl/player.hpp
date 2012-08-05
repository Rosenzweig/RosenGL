#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "glsl.hpp"

class Player
{
public:
//enum Buffers
//{
//   VERTEX_BUFFER = 0,
//    INDEX_BUFFER,
//    LAST_BUFFER
//};

Player();
bool Initialize(GLSLProgram* prog);
void Render();

private:
GLSLProgram* m_shader;

float player_vertices[12];
GLuint player_indices[6];
float player_colors[3];

GLuint player_vertexBuffer;
GLuint player_indexBuffer;
GLuint player_colorBuffer;

void InitVertexBuffer();
void InitColorBuffer();
};


#endif
