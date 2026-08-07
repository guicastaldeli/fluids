#include "main.h"

void render(GLFWwindow* window) {
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void setWindow() {
    GLFWwindow* win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "window", NULL, NULL);
    if(win == NULL) {
        std::cout << "Window failed" << std::endl;
        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, [](GLFWwindow* w, int width, int height) { glViewport(0, 0, width, height); });
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        glfwTerminate();
        
        return;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    initShaders();
    
    render(win);
}

void init() {
    if(!glfwInit()) {
        std::cout << "Failed to init GL" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    setWindow();

    glfwTerminate(); 
}

int main() {
    init();

    return 0;
}