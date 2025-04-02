#ifndef HUMANOID_MODEL_H_
#define HUMANOID_MODEL_H_

#include <Aurora/Graphics/Vertex.h>

using Aurora::Graphics::TexturesPSPVertex;

class HumanoidModel {
public:
    static TexturesPSPVertex headVertices[36];
    static TexturesPSPVertex bodyVertices[36];
    static TexturesPSPVertex armVertices[36];
    static TexturesPSPVertex legVertices[36];
};

#endif

