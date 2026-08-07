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
        inline std::unordered_map<Type, Data> createDataMap() {
            std::unordered_map<Type, Data> map;

            // Triangle
            map.emplace(Type::TRIANGLE, Data{
                {
        -0.9f, -0.9f, 0.0f, 0.0f, 0.0f,  // Bottom-left
         0.9f, -0.9f, 0.0f, 1.0f, 0.0f,  // Bottom-right
         0.0f,  0.9f, 0.0f, 0.5f, 1.0f   // Top-center
    },
    {0, 1, 2},
    glm::vec3(-0.9f, -0.9f, 0.0f),
    glm::vec3(0.9f, 0.9f, 0.0f) 
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
                glm::vec3(-0.5f, -0.5f, 0.0f),
                glm::vec3(0.5f, 0.5f, 0.0f) 
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
                glm::vec3(-0.8f, -0.4f, 0.0f),
                glm::vec3(0.8f, 0.4f, 0.0f)
            });

            return map;
        }
    }

    inline const Data& getData(Type t) {
        static const std::unordered_map<Type, Data> map = Internal::createDataMap();
        return map.at(t);
    }
}

namespace Mesh {
    static unsigned int vao = 0;
    static unsigned int vbo = 0;
    static unsigned int ebo = 0;
    static unsigned int indexCount = 0;

    static unsigned int shaderProgram = 0;
    static bool shaderInitialized = false;

    inline void init() {
        if(!shaderInitialized) {
            shaderProgram = initShaders();
            shaderInitialized = true;
        }
    }
    
    inline void destroy() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        vao = 0;
        vbo = 0;
        ebo = 0;
        indexCount = 0;
    }

    inline unsigned int create(const MeshData::Data& data) {
        init();
        destroy();

        indexCount = data.indices.size();

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(float), data.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLuint), data.indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "OPENGL ERROR: " << err << std::endl;
        } else {
            std::cout << "No OpenGL errors" << std::endl;
        }

        std::cout << "Mesh created! VAO: " << vao << ", Indices: " << indexCount << ", Shader: " << shaderProgram << std::endl;

        return indexCount;
    }

    inline void render() {
        if(vao == 0 || indexCount == 0) {
            std::cerr << "Cannot render: VAO or indexCount is 0!" << std::endl;
            return;
        }

        glUseProgram(shaderProgram);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}