#include "data.h"

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

void initShaders() {
    std::string vertex = "vert.glsl";
    std::string frag = "frag.glsl";

    unsigned int shaderProgram = createShaderProgram(vertex, frag);
    if(shaderProgram == 0) {
        std::cerr << "Failed to create shader program!" << std::endl;
        return;
    }

    std::cout << "Shader prorgam created! ID: " << shaderProgram << std::endl;

    return shaderProgram;
}