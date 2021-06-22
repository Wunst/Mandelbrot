#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mandelbrot.h"

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

int main(int argc, char const *argv[]) {
    if(!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot set", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    float vertices[] = {
        -1.0f, -1.0f,  0.0f,
        +1.0f, -1.0f,  0.0f,
        +1.0f, +1.0f,  0.0f,
        +1.0f, +1.0f,  0.0f,
        -1.0f, +1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,
    };
    Mesh *mesh = meshCreate(sizeof(vertices), vertices, 6);
    
    Shader *shader = shaderCreate(vsSource, fsSource);
    
    float zoom = 1.0f;
    float tlx = -0.73f;
    float tly = 0.25f;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        if(glfwGetKey(window, GLFW_KEY_ENTER)) {
            zoom *= 1.005;
        }
        if(glfwGetKey(window, GLFW_KEY_BACKSPACE)) {
            zoom /= 1.005;
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
            tlx += 0.05 / zoom;
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT)) {
            tlx -= 0.05 / zoom;
        }
        if(glfwGetKey(window, GLFW_KEY_UP)) {
            tly += 0.05 / zoom;
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN)) {
            tly -= 0.05 / zoom;
        }
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            break;
        }

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderUse(shader);
        shaderUniformFloat(shader, "zoom", 1/zoom);
        shaderUniformFloat(shader, "tlx", tlx);
        shaderUniformFloat(shader, "tly", tly);
        meshRender(mesh);

        glfwSwapBuffers(window);
        
        sleepMillis(17);
    }

    meshFree(mesh);
    textFree(vsSource);
    textFree(fsSource);
    shaderFree(shader);

    return 0;
}
