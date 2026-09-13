#include"icosphere.h"

Icosahedron::Icosahedron(int numSubdivisons)
{
    generate(numSubdivisons);

    uploadToGL();
}

static uint64_t makeEdge(uint32_t vertexInd1, uint32_t vertexInd2)
{
    if (vertexInd1 > vertexInd2)
    {
        std::swap(vertexInd1, vertexInd2);
    }

    return (static_cast<uint64_t>(vertexInd1) << 32) | static_cast<uint64_t>(vertexInd2);
}

uint32_t Icosahedron::createMidpoint(uint32_t vertexInd1, uint32_t vertexInd2, std::unordered_map<uint64_t, uint32_t>& edgeMidCache)
{
    uint64_t edge = makeEdge(vertexInd1, vertexInd2);
    auto cachedResult = edgeMidCache.find(edge);
    if (cachedResult != edgeMidCache.end())
    {
        return cachedResult->second;
    }

    Vertex midpoint{};
    midpoint.pos = glm::normalize((vertices[vertexInd1].pos + vertices[vertexInd2].pos) * 0.5f);

    vertices.push_back(midpoint);
    uint32_t newMidpointInd = static_cast<uint32_t>(vertices.size() - 1);

    edgeMidCache[edge] = newMidpointInd;
    return newMidpointInd;
}

void Icosahedron::generate(int numSubdivisions)
{
    subdivisions = static_cast<unsigned int>(numSubdivisions);

    float phi = (1 + sqrt(5)) / 2;

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

    for (unsigned int pass = 0; pass < subdivisions; ++pass)
    {
        std::vector<unsigned int> newIndices;
        std::unordered_map<uint64_t, uint32_t> edgeMidCache;
        newIndices.reserve(indices.size() * 4);

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            uint32_t a = indices[i];
            uint32_t b = indices[i + 1];
            uint32_t c = indices[i + 2];

            uint32_t ab = createMidpoint(a, b, edgeMidCache);
            uint32_t bc = createMidpoint(b, c, edgeMidCache);
            uint32_t ca = createMidpoint(c, a, edgeMidCache);

            newIndices.insert(newIndices.end(), { a, ab, ca });
            newIndices.insert(newIndices.end(), { b, bc, ab });
            newIndices.insert(newIndices.end(), { c, ca, bc });
            newIndices.insert(newIndices.end(), { ab, bc, ca });
        }

        indices = std::move(newIndices);
    }

    for (Vertex& vertex : vertices)
    {
        vertex.normal = glm::normalize(vertex.pos);
    }
}

void Icosahedron::uploadToGL()
{
    delete vbo;
    delete ebo;

    vao.Bind();
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(Vertex));
    ebo = new EBO(indices.data(), indices.size() * sizeof(unsigned int));
    vao.LinkAttrib(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    vao.LinkAttrib(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    vao.Unbind();
}

void Icosahedron::draw()
{
    vao.Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    vao.Unbind();
}