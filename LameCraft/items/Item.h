#ifndef ITEM_H
#define ITEM_H

#include <Aurora/Graphics/Vertex.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ItemFeatures.h"

using namespace Aurora::Graphics;

typedef const unsigned short item_id;

class Item {
public:
    char textureRow;
    char plane;
    bool terrainTexture;

    bool stackable;

    short points;
    short addPoints;
    short add2Points;
    TexturesPSPVertex *vertices;
    TexturesPSPVertex *addVertices;
    TexturesPSPVertex *add2Vertices;
    TexturesPSPVertex *dropVertices;

    Item(std::string internalName, item_id id);
    Item& setTexture(short textureRow, short plane);
    Item& setTerrainTexture(short textureRow, short plane);
    Item& setNotStackable();
    
    Item& addFeature(ItemFeature* feature);
    ItemFeature* getFeature(feature_type type);

    bool hasFeature(feature_type type);

    std::vector<ItemFeature*> itemFeatures;

    virtual ~Item();

    item_id getBaseID();

    std::string internalName;
    std::string displayName;

    private:
        int id;
};

#endif
