#include "content.h"

static bool initialized = false;
static Camera camera;

/*void testTriangle() {
    const auto& triangle = MeshData::getData(MeshData::Type::TRIANGLE);
    Mesh::create(triangle);
    std::cout << "Triangle created! Index count: " << triangle.indices.size() << std::endl;  // ← Add this
}*/

void Camera::setCamera() {
    Mesh::setProjectionMatrix(getProjectionMatrix());
    Mesh::setViewMatrix(getViewMatrix());
}

void setBackground() {
    const auto& data = MeshData::getData(MeshData::Type::SQUARE);
    Mesh::createMesh(data);
    Mesh::setScale((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
}

void renderContent() {
    if(!initialized) {
        //testTriangle();

        camera.setCamera();
        setBackground();
        
        initialized = true;
    }

    Mesh::renderMesh();
}