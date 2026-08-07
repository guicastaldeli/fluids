#define DATA_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glad/glad.h>

std::string readShaderFile(const std::string& filepath);
unsigned int compileShader(const std::string& source, GLenum shaderType);
unsigned int createShaderProgram(const std::string& vertexPath, const string& fragmentPath);
void getShaders();