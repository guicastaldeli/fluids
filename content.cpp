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
    Mesh::setColor(0.15f, 0.15f, 0.15f);
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

void Grid::setGridEvent(double xpos, double ypos) {
    float cellSize = (float)WINDOW_WIDTH / width;

    int x = (int)(xpos / cellSize);
    int y = (int)((WINDOW_HEIGHT - ypos) / cellSize);

    if(x >= 0 && x < width && y >= 0 && y < height) {
        onCellClicked(x, y);
        //std::cout << "mouse over " << cell.name << std::endl;
    }
}

void Grid::resetGrid(GLFWwindow* window) {
    static bool wasPressed = false;
    
    bool isPressed = glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
    if(isPressed && !wasPressed) initGrid();
    wasPressed = isPressed;
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
            Mesh::setScale(0.9f, 0.9f);
            Mesh::renderMesh();
        }
    }
}

void Grid::onCellClicked(int x, int y) {
    Cell& cell = Grid::getCell(x, y);
    cell.active = true;
    cell.color = glm::vec3(
        (float)(rand() % 100) / 100.0f,
        (float)(rand() % 100) / 100.0f,
        (float)(rand() % 100) / 100.0f
    );
}

/**
 * 
 * Render
 * 
 */
void renderContent() {
    if(!initialized) {
        //testTriangle();

        srand((unsigned int)time(nullptr));

        camera.setCamera();

        Grid::setGrid();
        
        initialized = true;
    }

    setBackground();
    Grid::setCells();
}