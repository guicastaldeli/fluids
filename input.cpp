#include "input.h"

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    float cellSize = (float)WINDOW_WIDTH / Grid::width;

    int x = (int)(xpos / cellSize);
    int y = (int)((WINDOW_HEIGHT - ypos) / cellSize);

    if(x >= 0 && x < Grid::width && y >= 0 && y < Grid::height) {
        Cell& cell = Grid::getCell(x, y);
        std::cout << "mouse over " << cell.name << std::endl;
    }
}

void initInput(GLFWwindow* window) {
    glfwSetCursorPosCallback(window, mouseCallback);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}