#ifndef COW_MODEL_H_
#define COW_MODEL_H_

#include <Aurora/Graphics/Vertex.h>

using Aurora::Graphics::TexturesPSPVertex;

class CowModel {
public:
    static TexturesPSPVertex bodyVertices[36];
    static TexturesPSPVertex headVertices[36];
    static TexturesPSPVertex legVertices[36];
    static TexturesPSPVertex hornsVertices[36];
};

#endif

