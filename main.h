#pragma once

#include "data.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void render(GLFWwindow* window);
void setWindow();
void init();