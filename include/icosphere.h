#pragma once

#include<glm/glm.hpp>
#include<vector>
#include"buffers.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 texCoord;
};

class Icosahedron
{
    public:
        Icosahedron(int numSubdivisions = 1);

        void generate();
        void uploadToGL();
        void draw();

    private:
        unsigned int subdivisions = 1;
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

        VAO vao;
        VBO* vbo;
        EBO* ebo;
};