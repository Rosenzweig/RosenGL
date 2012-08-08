#include "rosengl.hpp"

RosenGL::RosenGL()
{

}

RosenGL::~RosenGL()
{

}

bool RosenGL::Initialize()
{
    m_shader = new GLSLProgram("data/vertshader.vert", "data/fragshader.frag");

    if (!m_shader->Initialize())
    {
        std::cerr << "Shader stuck! Shader stuck! Please, I beg you!" << std::endl;
        return false;
    }
    m_shader->BindAttrib(0, "a_position");
    m_shader->BindAttrib(1, "a_color");
    //m_shader->BindFragDataLocation(1, "outColor");
    m_shader->LinkProgram();
    m_shader->BindShader();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_player.Initialize(m_shader);

    return true;
}

void RosenGL::Render()
{
    //float modelviewMatrix[16];
    //float projectionMatrix[16];

    //glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    //glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

    //m_shader->SendUniform("modelview_matrix", modelviewMatrix);
    //m_shader->SendUniform("projection_matrix", projectionMatrix);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    m_player.Render();

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void RosenGL::Shutdown()
{
    delete m_shader;
}
