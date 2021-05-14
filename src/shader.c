#include "mandelbrot.h"

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

Shader* shaderCreate(const char *vsSource, const char *fsSource)
{
    Shader *shader = (Shader*) malloc(sizeof(Shader));

    shader->vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vs, 1, &vsSource, NULL);
    glCompileShader(shader->vs);

    int success;
    glGetShaderiv(shader->vs, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infolog[512 + 1];
        glGetShaderInfoLog(shader->vs, 512, NULL, infolog);
        infolog[512] = '\00';

        fprintf(stderr, "VS Error: %s\n", infolog);

        free(shader);
        return NULL;
    }

    shader->fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fs, 1, &fsSource, NULL);
    glCompileShader(shader->fs);

    glGetShaderiv(shader->fs, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infolog[512 + 1];
        glGetShaderInfoLog(shader->fs, 512, NULL, infolog);
        infolog[512] = '\00';

        fprintf(stderr, "FS Error: %s\n", infolog);

        free(shader);
        return NULL;
    }

    shader->program = glCreateProgram();
    glAttachShader(shader->program, shader->vs);
    glAttachShader(shader->program, shader->fs);
    glLinkProgram(shader->program);

    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if(!success) {
        char infolog[512 + 1];
        glGetProgramInfoLog(shader->program, 512, NULL, infolog);
        infolog[512] = '\00';

        fprintf(stderr, "Program Error: %s\n", infolog);

        free(shader);
        return NULL;
    }

    return shader;
}



void shaderUse(const Shader *shader)
{
    glUseProgram(shader->program);
}



void shaderUniformFloat(const Shader *shader, const char *name, float f)
{
    glUniform1f(glGetUniformLocation(shader->program, name), f);
}



void shaderFree(Shader *shader)
{
    glDeleteShader(shader->vs);
    glDeleteShader(shader->fs);
    glDeleteProgram(shader->program);

    free(shader);
}
