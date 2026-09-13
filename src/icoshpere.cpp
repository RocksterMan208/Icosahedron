#include"icosphere.h"

Icosahedron::Icosahedron(int numSubdivisons) : subdivisions(numSubdivisons)
{
    generate();

    uploadToGL();
}

void Icosahedron::generate()
{
    float phi = (1+sqrt(5) / 2);

    vertices = 
    {
        {{-1, phi, 0}},
        {{1, phi, 0}},
        {{-1, -phi, 0}},
        {{1, -phi, 0}},

        {{0, -1, phi}},
        {{0, 1, phi}},
        {{0, -1, -phi}},
        {{0, 1, -phi}},

        {{phi, 0, -1}},
        {{phi, 0, 1}},
        {{-phi, 0, -1}},
        {{-phi, 0, 1}},
    };

    indices =
    {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7,
        0, 7, 10,
        0, 10, 11,

        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,

        3, 9, 4,
        3, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,

        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1
    };

    for (Vertex& vertex : vertices)
    {
        vertex.pos = glm::normalize(vertex.pos);
    }
}

void Icosahedron::uploadToGL()
{
    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(Vertex));
    ebo = new EBO(indices.data(), indices.size()*sizeof(unsigned int));
    vao.LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    vao.Unbind();
}

void Icosahedron::draw()
{
    vao.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao.Unbind();
}