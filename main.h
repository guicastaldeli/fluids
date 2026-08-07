#pragma once

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include "data.h"
#include "content.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void render(GLFWwindow* window);
void setWindow();
void init();