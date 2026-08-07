#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp>

// Shaders
std::string readShaderFile(const std::string& filepath);
unsigned int compileShader(const std::string& source, GLenum shaderType);
unsigned int createShaderProgram(const std::string& vertexPath, const std::string& fragPath);
unsigned int initShaders();

// Mesh
namespace MeshData {
    enum class Type {
        TRIANGLE,
        SQUARE,
        QUAD
    };

    struct Data {
        std::vector<float> vertices;
        std::vector<GLuint> indices;
        glm::vec3 minBounds;
        glm::vec3 maxBounds;

        Data(
            const std::vector<float>& v,
            const std::vector<GLuint>& i,
            const glm::vec3& min,
            const glm::vec3& max
        ) :
            vertices(v),
            indices(i),
            minBounds(min),
            maxBounds(max)
        {}
    };

    namespace Internal {
        std::unordered_map<Type, Data> createDataMap() {
            std::unordered_map<Type, Data> map;

            // Triangle
            map.emplace(Type::TRIANGLE, Data{
                {
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    0.0f,  0.5f, 0.0f, 0.5f, 1.0f 
                },
                {
                    0, 1, 2
                },
                glm::vec2(-0.5, -0.5f),
                glm::vec2(0.5f, 0.5f)
            });
            // Cube
            map.emplace(Type::SQUARE, Data{
                {
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                    0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f 
                },
                {
                    0, 1, 2, 
                    0, 2, 3
                },
                glm::vec2(-0.5f, -0.5f),
                glm::vec2(0.5f, 0.5f)
            });
            // Quad
            map.emplace(Type::QUAD, Data{
                {
                    -0.8f, -0.4f, 0.0f, 0.0f, 0.0f,
                    0.8f, -0.4f, 0.0f, 1.0f, 0.0f,
                    0.8f,  0.4f, 0.0f, 1.0f, 1.0f,
                    -0.8f,  0.4f, 0.0f, 0.0f, 1.0f 
                },
                {
                    0, 1, 2, 
                    0, 2, 3,
                },
                glm::vec2(-0.8f, -0.4f),
                glm::vec2(0.8f, 0.4f)
            });

            return map;
        }
    }

    const Data& getMeshData(Type t) {
        static const std::unordered_map<Type, Data> map = Internal::createDataMap();
        
        MeshData& val = map.at(t);
        return val;
    }
}

namespace Mesh {
    unsigned int vao = 0;;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    unsigned int indexCount = 0;

    inline unsigned int create(const MeshData::Data& data) {
        destroy();

        indexCount = data.indices.size();

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(float), data.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLuint), data.indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        return indexCount;
    }

    inline void draw() {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    inline void destroy() [
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        vao = 0;
        vbo = 0;
        ebo = 0;
        indexCount = 0;
    ]
}