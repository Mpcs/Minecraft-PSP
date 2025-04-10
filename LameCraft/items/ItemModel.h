#ifndef ITEM_MODEL_H
#define ITEM_MODEL_H

#include <Aurora/Graphics/TextureManager.h>
#include <Aurora/Graphics/Vertex.h>
#include <Aurora/Math/Vector2.h>

using Aurora::Graphics::TexturesPSPVertex;
using Aurora::Math::Vector2;
class ItemModel {
public:
    ItemModel(int texture);
    
    void draw2D(int x, int y);
    void drawDropped(float x, float y, float z, float rotation);
    void drawInHand(float light);// TODO: come back to this
    void drawFull3D(float light);// TODO: come back to this

    int getTextureID();

    static TexturesPSPVertex itemVertices[6];
    static TexturesPSPVertex dropVertices[6];
    
private:
    void build3DVertices();

    int textureID;

    short addPoints;
    short add2Points;
    TexturesPSPVertex *addVertices;
    TexturesPSPVertex *add2Vertices;
};
#endif
