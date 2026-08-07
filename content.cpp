#include "content.h"

static bool initialized = false;
static Camera camera;

int screenWidth = WINDOW_WIDTH;
int screenHeight = WINDOW_HEIGHT;

/*void testTriangle() {
    const auto& triangle = MeshData::getData(MeshData::Type::TRIANGLE);
    Mesh::create(triangle);
    std::cout << "Triangle created! Index count: " << triangle.indices.size() << std::endl;  // ← Add this
}*/

void Camera::setCamera() {
    Mesh::setProjectionMatrix(getProjectionMatrix());
    Mesh::setViewMatrix(getViewMatrix());
}

/**
 * 
 * Background
 * 
 */
void setBackground() {
    const auto& data = MeshData::getData(MeshData::Type::SQUARE);
    
    Mesh::createMesh(data);
    Mesh::setTransform(0.0f, 0.0f, (float)screenWidth, (float)screenHeight);
    Mesh::setColor(0.3f, 0.3f, 0.3f);
    Mesh::renderMesh();
}

/**
 * 
 * Cells
 * 
 */
void Grid::setGrid() {
    initGrid();
}

void Grid::setCells() {
    const auto& data = MeshData::getData(MeshData::Type::QUAD);
    Mesh::createMesh(data);

    float cellSize = (float)screenWidth / width;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            Cell& cell = getCell(x, y);
            if(!cell.active) continue;
            
            float uWidth = screenWidth / 2.0f;
            float uHeight = screenHeight / 2.0f;
            float uCellSize = cellSize / 2.0f;

            float posX = x * cellSize - uWidth + uCellSize;
            float posY = y * cellSize - uHeight + uCellSize;
            
            Mesh::setTransform(posX, posY, cellSize, cellSize);
            Mesh::setColor(cell.color);
            Mesh::setScale(0.5f, 0.5f);
            Mesh::renderMesh();
        }
    }
}

/**
 * 
 * Render
 * 
 */
void renderContent() {
    if(!initialized) {
        //testTriangle();

        camera.setCamera();

        Grid::setGrid();
        
        initialized = true;
    }

    setBackground();
    Grid::setCells();
}