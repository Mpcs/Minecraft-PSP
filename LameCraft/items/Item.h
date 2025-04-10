#ifndef ITEM_H
#define ITEM_H

#include <Aurora/Graphics/Vertex.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ItemFeatures.h"
#include "ItemModel.h"
#include "TextureHelper.h"

using namespace Aurora::Graphics;

typedef const unsigned short item_id;

class Item {
public:
    bool stackable;

    Item(std::string internalName, item_id id);
    Item& setNotStackable();
    
    Item& addFeature(ItemFeature* feature);
    ItemFeature* getFeature(feature_type type);
    ItemModel* getModel();

    bool hasFeature(feature_type type);

    std::vector<ItemFeature*> itemFeatures;

    item_id getBaseID();

    std::string internalName;
    std::string displayName;

    private:
        ItemModel* itemModel;
        int id;
};

#endif
