#include "data.h"

/**
 * 
 * Shader
 * 
 */
// Render Shader File
std::string readShaderFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if(!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    std::cout << "=== " << filepath << " ===" << std::endl;
    std::cout << content << std::endl;
    std::cout << "=== End of " << filepath << " ===" << std::endl;

    return content;
}

// Compile Shader
unsigned int compileShader(const std::string& source, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    const char* src = source.c_str();
    
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;

        return 0;
    }

    return shader;
}

unsigned createShaderProgram(const std::string& vertexPath, const std::string& fragPath) {
    std::string vertexSource = readShaderFile(vertexPath);
    std::string fragSource = readShaderFile(fragPath);
    if(vertexSource.empty() || fragSource.empty()) return 0;

    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragShader = compileShader(fragSource, GL_FRAGMENT_SHADER);
    if(vertexShader == 0 || fragShader == 0) return 0;

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program link fail: " << infoLog << std::endl;

        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    return shaderProgram;
}

// Init Shaders
unsigned int initShaders() {
    std::string vertex = "vert.glsl";
    std::string frag = "frag.glsl";

    unsigned int shaderProgram = createShaderProgram(vertex, frag);
    if(shaderProgram == 0) {
        std::cerr << "Failed to create shader program!" << std::endl;
        return 0;
    }

    std::cout << "Shader prorgam created! ID: " << shaderProgram << std::endl;

    return shaderProgram;
}

/**
 * 
 * Mesh
 * 
 */
// Create Mesh
unsigned int Mesh::createMesh(const MeshData::Data& data) {
    initMesh();
    //destroyMesh();

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

    glUseProgram(shaderProgram);

    modelLoc = glGetUniformLocation(shaderProgram, "model");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");

    glBindVertexArray(0);

    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        std::cout << "OPENGL ERROR: " << err << std::endl;
    } else {
        std::cout << "No OpenGL errors" << std::endl;
    }

    std::cout << "Mesh created! VAO: " << vao << ", Indices: " << indexCount << ", Shader: " << shaderProgram << std::endl;

    return indexCount;
}

// Render Mesh
void Mesh::renderMesh() {
    if(vao == 0 || indexCount == 0) {
        std::cerr << "Cannot render: VAO or indexCount is 0!" << std::endl;
        return;
    }

    glUseProgram(shaderProgram);

    if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
    if(viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
    if(projLoc != -1) glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projMatrix[0][0]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Init Mesh
void Mesh::initMesh() {
    if(!shaderInitialized) {
        shaderProgram = initShaders();
        shaderInitialized = true;
    }
}

// Destroy Mesh
void Mesh::destroyMesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    vao = 0;
    vbo = 0;
    ebo = 0;
    indexCount = 0;
}