#include "mandelbrot.h"

#include <stdlib.h>

#include <glad/glad.h>

Mesh* meshCreate(size_t sizeofVertices, float* vertices, unsigned int vertexCount)
{
    Mesh *mesh = (Mesh*) malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);

    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    mesh->vertexCount = vertexCount;

    return mesh;
}



void meshRender(const Mesh *mesh)
{
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
}


void meshFree(Mesh *mesh)
{
    glDeleteVertexArrays(1, &mesh->vao);
    glDeleteBuffers(1, &mesh->vbo);

    free(mesh);
}
