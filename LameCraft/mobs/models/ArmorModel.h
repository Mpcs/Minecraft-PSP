#ifndef ARMOR_MODEL_H_
#define ARMOR_MODEL_H_

#include <Aurora/Graphics/TextureManager.h>
#include <Aurora/Graphics/Vertex.h>

using Aurora::Graphics::TexturesPSPVertex;

class ArmorModel {
public:
    static TexturesPSPVertex helmetVertices[30];
    static TexturesPSPVertex shoulderVertices[30];
    static TexturesPSPVertex chestplateVertices[24];
    static TexturesPSPVertex bellyVertices[24];
    static TexturesPSPVertex leggingVertices[24];
    static TexturesPSPVertex bootVertices[30];
};

#endif
