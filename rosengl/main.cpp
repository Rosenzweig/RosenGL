#include "rosengl.hpp"
#include <GL/glfw.h>


int main()
{
    int running = GL_TRUE;
    RosenGL Game;

    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    if(!glfwOpenWindow(720, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        return 0;
    }

    glfwSetWindowTitle("RosenGL");
    glewInit();

    while(running)
    {
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
        Game.Initialize();
        Game.Render();
        glfwSwapBuffers();
    }

    Game.Shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}



