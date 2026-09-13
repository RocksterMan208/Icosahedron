#pragma once

#include<glm/glm.hpp>
#include<vector>
#include<unordered_map>
#include<cstdint>
#include"buffers.h"

enum WireFrame : int {WIREFRAME_OFF, WIREFRAME_ON};

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

        void generate(int numSubdivisions);
        void uploadToGL();
        void draw(int toggleWireFrame);

    private:
        uint32_t createMidpoint(uint32_t vertexInd1, uint32_t vertexInd2, std::unordered_map<uint64_t, uint32_t>& edgeMidCache);

        unsigned int subdivisions = 1;
        std::vector<unsigned int> indices;
        std::vector<Vertex> vertices;

        VAO vao;
        VBO* vbo = nullptr;
        EBO* ebo = nullptr;
};