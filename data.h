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
#include <glm/gtc/matrix_transform.hpp>

/**
 * 
 * Shader
 *  
 * */  
std::string readShaderFile(const std::string& filepath);
unsigned int compileShader(const std::string& source, GLenum shaderType);
unsigned int createShaderProgram(const std::string& vertexPath, const std::string& fragPath);
unsigned int initShaders();

/**
 * 
 * Mesh
 *  
 * */  
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
                    -0.9f, -0.9f, 0.0f, 0.0f, 0.0f,
                    0.9f, -0.9f, 0.0f, 1.0f, 0.0f,
                    0.0f,  0.9f, 0.0f, 0.5f, 1.0f
                },
                {
                    0, 1, 2
                },
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
    static unsigned int shaderProgram = 0;
    static bool shaderInitialized = false;
    
    static unsigned int vao = 0;
    static unsigned int vbo = 0;
    static unsigned int ebo = 0;
    static unsigned int indexCount = 0;

    static int modelLoc = -1;
    static int viewLoc = -1;
    static int projLoc = -1;

    static glm::mat4 modelMatrix = glm::mat4(1.0f);
    static glm::mat4 viewMatrix = glm::mat4(1.0f);
    static glm::mat4 projMatrix = glm::mat4(1.0f);

    unsigned int createMesh(const MeshData::Data& data);
    void renderMesh();
    void initMesh();
    void destroyMesh();

    inline void setModelMatrix(const glm::mat4& m) { modelMatrix = m; }
    inline void setViewMatrix(const glm::mat4& m) { viewMatrix = m; }
    inline void setProjectionMatrix(const glm::mat4& m) { projMatrix = m; }

    inline void setScale(float width, float height) {
        modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0f));
    }

    inline void setPosition(float x, float y) {
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    }

    inline void setTransform(float x, float y, float width, float height) {
        modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(width, height, 1.0f));
    }
}