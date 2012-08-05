#include "player.hpp"

Player::Player()
{
    m_shader = NULL;
}

void Player::InitVertexBuffer()
{
    player_vertices =
    {
        0.0f, 0.f, 0.f
       -0.5f, 0.f, 0.f,
       -0.5f, -0.5f, 0.f,
        0.0f, -0.5f, 0.f
    };

    player_indices =
    {
        0, 1, 2, 2, 3, 0
    };

    glGenBuffers(1, &player_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, player_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(player_vertices), player_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &player_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, player_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(player_indices), player_indices, GL_STATIC_DRAW);
}

void Player::InitColorBuffer()
{
    player_colors =
    {
        1.0f, 0.0f, 0.0f
    };

    glGenBuffers(1, &player_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, player_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(player_colors), player_colors, GL_STATIC_DRAW);
}


bool Player::Initialize(GLSLProgram* prog)
{
    m_shader = prog;

    if (!glGenBuffers || !glBindBuffer || !glBufferData)
    {
        std::cerr << "Your video card doesn't support VBOs. Is this 2001?" << std::endl;
        return false;
    }

    InitVertexBuffer();
    InitColorBuffer();

    m_shader->BindShader();

    glBindBuffer(GL_ARRAY_BUFFER, player_vertexBuffer);
    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, player_colorBuffer);
    glVertexAttribPointer((GLint)1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, player_indexBuffer);

    return true;
}

void Player::Render()
{
    glDrawElements(GL_TRIANGLES, sizeof(player_indices), GL_UNSIGNED_INT, 0);
}
