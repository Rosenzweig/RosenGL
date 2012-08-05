#ifndef ROSENGL_HPP_INCLUDED
#define ROSENGL_HPP_INCLUDED

#include "player.hpp"

class RosenGL
{
public:
RosenGL();
virtual ~RosenGL();
bool Initialize();
void Render();
void Shutdown();

private:
Player m_player;
GLSLProgram* m_shader;
};

#endif // ROSENGL_HPP_INCLUDED
