#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>

typedef struct shader_t {
    unsigned int vs;
    unsigned int fs;
    unsigned int program;
} Shader;

typedef struct mesh_t {
    unsigned int vao;
    unsigned int vbo;
    unsigned int vertexCount;
} Mesh;

Shader*     shaderCreate(const char *vsSource, const char *fsSource);
void        shaderUse(const Shader *shader);
void        shaderUniformFloat(const Shader *shader, const char *name, float f);
void        shaderFree(Shader *shader);

Mesh*       meshCreate(size_t sizeofVertices, float* vertices, unsigned int vertexCount);
void        meshRender(const Mesh *mesh);
void        meshFree(Mesh *mesh);

char*       textLoad(const char *path);
void        textFree(char *text);

void        sleepMillis(unsigned millis);

#endif /* end of include guard: MANDELBROT_H_INCLUDED */
