#ifndef BASEITEM_H
#define BASEITEM_H

#include <Aurora/Graphics/Vertex.h>
#include <stdlib.h>
#include <string>
#include "ItemType.h"

using namespace Aurora::Graphics;

typedef const unsigned short item_id;

class BaseItem {
public:
    char textureRow;
    char plane;

    short furnItem;
    short durabilityPoints;

    short points;
    short addPoints;
    short add2Points;

    bool terrainTexture;
    bool stackable;

    item_t itemType; // "D" - default, "T" - tool, "F" - food, "H" - helmet, "C" - chestplate, "L" - leggings, "B" - boots "Y" - dye

    TexturesPSPVertex *vertices;
    TexturesPSPVertex *addVertices;
    TexturesPSPVertex *add2Vertices;

    TexturesPSPVertex *dropVertices;

    BaseItem();

    virtual ~BaseItem();

    static item_id getBaseID();

    std::string name;
};

#endif
