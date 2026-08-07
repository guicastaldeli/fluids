#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "content.h"

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void initInput(GLFWwindow* window);
void processInput(GLFWwindow* window);