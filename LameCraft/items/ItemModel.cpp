#include "ItemModel.h"

#include <math.h>
#include <psptypes.h>
#include "LameFunctions.h"
#include <Aurora/Graphics/TextureManager.h>

using Aurora::Graphics::TextureManager;

TexturesPSPVertex ItemModel::itemVertices[6] = {
    {0, 0, -0.5, -0.5, 0},
    {1, 0,  0.5, -0.5, 0},
    {1, 1,  0.5,  0.5, 0},
    {1, 1,  0.5,  0.5, 0},
    {0, 1, -0.5,  0.5, 0},
    {0, 0, -0.5, -0.5, 0}
};
TexturesPSPVertex ItemModel::dropVertices[6] = {
    {1, 1, 0, -0.25,  0.25},
    {1, 0, 0,  0.25,  0.25},
    {0, 0, 0,  0.25, -0.25},
    {0, 0, 0,  0.25, -0.25},
    {0, 1, 0, -0.25, -0.25},
    {1, 1, 0, -0.25,  0.25}
};

ItemModel::ItemModel(int texture) {
    textureID = texture;
    build3DVertices();
}

void ItemModel::build3DVertices() {
    addPoints = 0;
    addVertices = NULL;

    std::vector<Vector3 *> mPosition;
    std::vector<Vector2 *> mtextures;
    std::vector<Vector3 *> mTriangle;
    std::vector<Vector3 *> mPosition2;
    std::vector<Vector2 *> mtextures2;
    std::vector<Vector3 *> mTriangle2;

    int iVertex = 0;
    int points = 0;

    int iVertex2 = 0;
    int points2 = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -1.0f;

    float pixel = 1.0f / 16.0f;
    float texturepixel = 1 / 16.0f;

    float down = 0;
    float left = 0;

    float size2 = 0.25f;

        for (int xx = 15; xx >= 0; xx--) {
            for (int yy = 15; yy >= 0; yy--) {
                int i = xx;
                int j = yy;
                if (TextureManager::Instance()->getAlpha(xx, yy, textureID) == 255) {
                    if ((j == 255) || (j != 255 && TextureManager::Instance()->getAlpha(xx, yy + 1, textureID) == 0)) {
                        mPosition.push_back(new Vector3(x + i * pixel, y + (j + 1) * pixel, z + pixel * 17));
                        mtextures.push_back(new Vector2(left + texturepixel * i, down + texturepixel * j));

                        mPosition.push_back(new Vector3(x + (i + 1) * pixel, y + (j + 1) * pixel, z + pixel * 17));
                        mtextures.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * j));

                        mPosition.push_back(new Vector3(x + (i + 1) * pixel, y + (j + 1) * pixel, z + pixel * 16));
                        mtextures.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * (j + 1)));

                        mPosition.push_back(new Vector3(x + i * pixel, y + (j + 1) * pixel, z + pixel * 16));
                        mtextures.push_back(new Vector2(left + texturepixel * i, down + texturepixel * (j + 1)));

                        mTriangle.push_back(new Vector3(iVertex, iVertex + 1, iVertex + 2));
                        mTriangle.push_back(new Vector3(iVertex + 2, iVertex + 3, iVertex));

                        iVertex += 4;
                        points += 6;
                    }

                    if ((i == 15) || (i != 255 && TextureManager::Instance()->getAlpha(xx + 1, yy, textureID) == 0)) {
                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + j * pixel, z + pixel * 17));
                        mtextures2.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * (j + 1)));

                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + (j + 1) * pixel, z + pixel * 17));
                        mtextures2.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * j));

                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + (j + 1) * pixel, z + pixel * 16));
                        mtextures2.push_back(new Vector2(left + texturepixel * i, down + texturepixel * j));

                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + j * pixel, z + pixel * 16));
                        mtextures2.push_back(new Vector2(left + texturepixel * i, down + texturepixel * (j + 1)));

                        mTriangle2.push_back(new Vector3(iVertex2, iVertex2 + 1, iVertex2 + 2));
                        mTriangle2.push_back(new Vector3(iVertex2 + 2, iVertex2 + 3, iVertex2));

                        iVertex2 += 4;
                        points2 += 6;
                    }

                    if ((j == 0) || (j != 0 && TextureManager::Instance()->getAlpha(xx, yy - 1, textureID) == 0)) {
                        mPosition2.push_back(new Vector3(x + i * pixel, y + j * pixel, z + pixel * 17));
                        mtextures2.push_back(new Vector2(left + texturepixel * i, down + texturepixel * j));

                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + j * pixel, z + pixel * 17));
                        mtextures2.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * j));

                        mPosition2.push_back(new Vector3(x + (i + 1) * pixel, y + j * pixel, z + pixel * 16));
                        mtextures2.push_back(new Vector2(left + texturepixel * (i + 1), down + texturepixel * (j + 1)));

                        mPosition2.push_back(new Vector3(x + i * pixel, y + j * pixel, z + pixel * 16));
                        mtextures2.push_back(new Vector2(left + texturepixel * i, down + texturepixel * (j + 1)));

                        mTriangle2.push_back(new Vector3(iVertex2, iVertex2 + 1, iVertex2 + 2));
                        mTriangle2.push_back(new Vector3(iVertex2 + 2, iVertex2 + 3, iVertex2));

                        iVertex2 += 4;
                        points2 += 6;
                    }
                }
            }
        }


    addVertices = (TexturesPSPVertex *) memalign(16, (mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    addPoints = points;

    int vert = 0;
 
    unsigned int size = mTriangle.size();
    for (unsigned int j = 0; j < size; j++) {
        addVertices[vert].u = mtextures[mTriangle[j]->x]->x;
        addVertices[vert].v = mtextures[mTriangle[j]->x]->y;
        addVertices[vert].x = mPosition[mTriangle[j]->x]->x;
        addVertices[vert].y = mPosition[mTriangle[j]->x]->y;
        addVertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        addVertices[vert].u = mtextures[mTriangle[j]->y]->x;
        addVertices[vert].v = mtextures[mTriangle[j]->y]->y;
        addVertices[vert].x = mPosition[mTriangle[j]->y]->x;
        addVertices[vert].y = mPosition[mTriangle[j]->y]->y;
        addVertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        addVertices[vert].u = mtextures[mTriangle[j]->z]->x;
        addVertices[vert].v = mtextures[mTriangle[j]->z]->y;
        addVertices[vert].x = mPosition[mTriangle[j]->z]->x;
        addVertices[vert].y = mPosition[mTriangle[j]->z]->y;
        addVertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(addVertices,
                                            (mTriangle.size() * 3) * sizeof(TexturesPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for (unsigned int aa = 0; aa < mPosition.size(); aa++) {
        delete mPosition[aa];
        delete mtextures[aa];
    }
    mPosition.clear();
    mtextures.clear();

    for (unsigned int aa = 0; aa < mTriangle.size(); aa++) {
        delete mTriangle[aa];
    }
    mTriangle.clear();

    add2Vertices = (TexturesPSPVertex *) memalign(16, (mTriangle2.size() * 3) * sizeof(TexturesPSPVertex));
    add2Points = points2;

    //build verts for add2Vertices
    //vertices
    vert = 0;
    size = mTriangle2.size();
    for (unsigned int j = 0; j < size; j++) {
        add2Vertices[vert].u = mtextures2[mTriangle2[j]->x]->x;
        add2Vertices[vert].v = mtextures2[mTriangle2[j]->x]->y;
        add2Vertices[vert].x = mPosition2[mTriangle2[j]->x]->x;
        add2Vertices[vert].y = mPosition2[mTriangle2[j]->x]->y;
        add2Vertices[vert].z = mPosition2[mTriangle2[j]->x]->z;
        vert++;

        add2Vertices[vert].u = mtextures2[mTriangle2[j]->y]->x;
        add2Vertices[vert].v = mtextures2[mTriangle2[j]->y]->y;
        add2Vertices[vert].x = mPosition2[mTriangle2[j]->y]->x;
        add2Vertices[vert].y = mPosition2[mTriangle2[j]->y]->y;
        add2Vertices[vert].z = mPosition2[mTriangle2[j]->y]->z;
        vert++;

        add2Vertices[vert].u = mtextures2[mTriangle2[j]->z]->x;
        add2Vertices[vert].v = mtextures2[mTriangle2[j]->z]->y;
        add2Vertices[vert].x = mPosition2[mTriangle2[j]->z]->x;
        add2Vertices[vert].y = mPosition2[mTriangle2[j]->z]->y;
        add2Vertices[vert].z = mPosition2[mTriangle2[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(add2Vertices,
                                            (mTriangle2.size() * 3) * sizeof(TexturesPSPVertex));

    for (unsigned int aa = 0; aa < mPosition2.size(); aa++) {
        delete mPosition2[aa];
        delete mtextures2[aa];
    }
    mPosition2.clear();
    mtextures2.clear();

    for (unsigned int aa = 0; aa < mTriangle2.size(); aa++) {
        delete mTriangle2[aa];
    }
    mTriangle2.clear();
}

void ItemModel::draw2D(int x, int y) {
    MatrixPush();
    MatrixTranslation(Vector3(x, y, 0));
    MatrixAngle(Vector3(0, 0, 0));
    MatrixScale(Vector3(32, 32, 32));
    TextureManager::Instance()->SetTextureModeulate(textureID);

    DrawSetCulling(true);
    DrawPlaceTexture(true);
    sceGuDisable(GU_DEPTH_TEST);
    DrawSetDepthMask(true);
    DrawSetBlend(true);

    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0,
        itemVertices);

    DrawSetBlend(false);
    DrawSetDepthMask(false);
    sceGuEnable(GU_DEPTH_TEST);
    DrawPlaceTexture(false);
    DrawSetCulling(false);

    MatrixPop();
}

void ItemModel::drawDropped(float x, float y, float z, float rotation) {
    MatrixPush();
    MatrixTranslation(Vector3(x, y, z));
    MatrixRadianAngle(Vector3(0, rotation, 0));
    MatrixScale(Vector3(1, 1, 1));
    TextureManager::Instance()->SetTextureModeulate(textureID);

    DrawPlaceTexture(true);
    DrawSetBlend(true);
    
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0,
                    ItemModel::dropVertices);

    DrawSetBlend(false);
    DrawPlaceTexture(false);

    sceGuDisable(GU_ALPHA_TEST);
    sceGuDisable(GU_DEPTH_TEST);
    MatrixPop();
}

void ItemModel::drawInHand(float light) {
    TextureManager::Instance()->SetTextureModeulate(textureID);

    DrawPlaceTexture(true);
    DrawSetBlend(true);

    sceGuColor(GU_COLOR(light * 0.75, light * 0.75, light * 0.75, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, addPoints,
                    0, addVertices);

    DrawSetCulling(true);
    sceGuColor(GU_COLOR(light * 0.75, light * 0.75, light * 0.75, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, add2Points,
                    0, add2Vertices);
    sceGuColor(GU_COLOR(light, light, light, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0,
                    itemVertices);
    DrawSetCulling(false);

    DrawSetBlend(false);
    DrawPlaceTexture(false);

}

void ItemModel::drawFull3D(float light) {
    TextureManager::Instance()->SetTextureModeulate(textureID);

    DrawPlaceTexture(true);
    DrawSetBlend(true);

    DrawSetCulling(false);

    sceGuColor(GU_COLOR(light * 0.75, light * 0.75, light * 0.75, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, add2Points,
                    0, add2Vertices);

    DrawSetCulling(true);
    sceGuColor(GU_COLOR(light * 0.75, light * 0.75, light * 0.75, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, addPoints,
                    0, addVertices);

    sceGuColor(GU_COLOR(light, light, light, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0,
                    itemVertices);
    DrawSetCulling(false);
    sceGuColor(GU_COLOR(light, light, light, 1));
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0,
                    itemVertices);

    DrawSetCulling(true);

    DrawSetBlend(false);
    DrawPlaceTexture(false);
}

int ItemModel::getTextureID() {
    return textureID;
}