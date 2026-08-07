#include "content.h"

static bool initialized = false;

void testTriangle() {
    const auto& triangle = MeshData::getData(MeshData::Type::TRIANGLE);
    Mesh::create(triangle);
    std::cout << "Triangle created! Index count: " << triangle.indices.size() << std::endl;  // ← Add this
}


void renderContent() {
    if(!initialized) {
        testTriangle();

        initialized = true;
    }

    Mesh::render();
}