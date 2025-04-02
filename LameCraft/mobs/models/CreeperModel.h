#ifndef CREEPER_MODEL_H_
#define CREEPER_MODEL_H_

#include <Aurora/Graphics/Vertex.h>

using Aurora::Graphics::TexturesPSPVertex;

class CreeperModel {
public:
    static TexturesPSPVertex headVertices[36];
    static TexturesPSPVertex bodyVertices[36];
    static TexturesPSPVertex legVertices[36];
};

#endif

