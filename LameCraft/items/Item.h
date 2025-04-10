#ifndef ITEM_H
#define ITEM_H

#include <Aurora/Graphics/Vertex.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ItemFeatures.h"
#include "ItemModel.h"
#include "TextureHelper.h"
#include "lang/Translation.h"

using namespace Aurora::Graphics;

typedef const unsigned short item_id;

class Item {
public:
    Item(std::string internalName, item_id id);
    Item& setNotStackable();
    Item& addFeature(ItemFeature* feature);
    ItemFeature* getFeature(feature_type type);
    bool hasFeature(feature_type type);

    ItemModel* getModel();

    
    std::vector<ItemFeature*> itemFeatures;

    item_id getID();
    std::string getInternalName();
    std::string getDisplayName();
    bool isStackable();

    private:
        int id;
        std::string internalName;
        std::string displayName;
        bool stackable;
        ItemModel* itemModel;
};

#endif
