#include "input.h"

static bool mousePressed = false;

static void activateMouseEvent(GLFWwindow* window, double xpos, double ypos) {
    Grid::setGridEvent(xpos, ypos);
}

static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if(mousePressed) activateMouseEvent(window, xpos, ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        mousePressed = (action == GLFW_PRESS);

        if(mousePressed) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            activateMouseEvent(window, xpos, ypos);
        }
    }
}

void initInput(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    Grid::resetGrid(window); // Reset
}