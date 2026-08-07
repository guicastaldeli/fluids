#pragma once

#include "main.h"
#include "data.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

/**
 * 
 * Camera
 * 
 */
struct Camera {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float fov = 1.0f;
    float aspectRatio = 1.0f;

    int screenWidth = WINDOW_WIDTH;
    int screenHeight = WINDOW_HEIGHT;

    void setCamera();

    glm::mat4 getProjectionMatrix() {
        float halfWidth = screenWidth / 2.0f / fov;
        float halfHeight = screenHeight / 2.0f / fov;

        return glm::ortho(
            -halfWidth + position.x, halfWidth + position.x,
            -halfHeight + position.y, halfHeight + position.y,
            -1.0f, 1.0f
        );
    }

    glm::mat4 getViewMatrix() {
        auto val = glm::mat4(1.0f);
        return val;
    }
};

void testTriangle();
void renderContent();