#ifndef SHEEP_MODEL_H_
#define SHEEP_MODEL_H_

#include <Aurora/Graphics/Vertex.h>

using Aurora::Graphics::TexturesPSPVertex;
class SheepModel {
public:
    static TexturesPSPVertex bodyVertices[36];
    static TexturesPSPVertex headVertices[36];
    static TexturesPSPVertex headFurVertices[36];
    static TexturesPSPVertex legVertices[36];
    static TexturesPSPVertex legFurVertices[30];
};

#endif

