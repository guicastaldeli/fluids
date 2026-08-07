#pragma once

#include "main.h"
#include "data.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
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

/**
 * 
 * Cells
 * 
 */
struct Cell {
    int id;
    std::string name;
    glm::vec2 position;
    glm::vec3 color;
    bool active = true;
};

namespace Grid {
    inline int width = 20;
    inline int height = 20;

    inline std::vector<Cell> cells;
    inline std::unordered_map<std::string, int> nameToIndex;

    void setGrid();
    void setCells();

    inline std::string getCellName(int x, int y) {
        return "cell_" + std::to_string(x) + "_" + std::to_string(y);
    }

    inline Cell& getCell(int x, int y) {
        return cells[y * width + x];
    }

    inline Cell& getCell(int id) {
        return cells[id];
    }

    inline void setCellColor(int id, const glm::vec3& color) {
        getCell(id).color = color;
    }

    inline void toggleCell(int x, int y) {
        getCell(x, y).active = !getCell(x, y).active;
    }

    inline Cell& getNeighbor(int x, int y, int dx, int dy) {
        int nx = x + dx;
        int ny = y + dy;
        if(nx >= 0 && nx < width && ny >= 0 && ny < height) return getCell(nx, ny);

        throw std::out_of_range("out of bounds!");
    }

    inline int getCellCount() {
        return cells.size();
    }

    template<typename T>
    inline void forEach(auto cb) {
        for(auto& cell : cells) {
            cb(cell);
        }
    }

    inline void initGrid() {
        cells.resize(width * height);
        nameToIndex.clear();

        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                int i = y * width + x;
                
                cells[i].id = i;
                cells[i].name = getCellName(x, y);
                cells[i].position = glm::vec2(x, y);
                cells[i].color = glm::vec3(0.3f, 0.3f, 0.3f);
                cells[i].active = true;

                nameToIndex[cells[i].name] = i;
            }
        }
    }
};
