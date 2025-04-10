#include "Item.h"

#include <Aurora/Utils/Logger.h>

using namespace Aurora;

Item::Item(const std::string internalName, item_id id) {
    this->internalName = internalName;
    this->id = id;

    stackable = true;
    std::string textureName = "Assets/Textures/Default/items/" + this->internalName + ".png";
    int textureID = TextureManager::Instance()->GetTextureNumber(textureName);

    itemModel = new ItemModel(textureID);
}

Item& Item::setNotStackable() {
    stackable = false;
    return *this;
}

Item& Item::addFeature(ItemFeature* feature) {
    itemFeatures.push_back(feature);
    return *this;
}

bool Item::hasFeature(feature_type type) {
    for (int i = 0; i < itemFeatures.size(); i++) {
        if (itemFeatures[i]->getType() == type) {
            return true;
        }
    }
    return false;
}

ItemFeature* Item::getFeature(feature_type type) {
    for (int i = 0; i < itemFeatures.size(); i++) {
        if (itemFeatures[i]->getType() == type) {
            return itemFeatures[i];
        }
    }
    return NULL;
}

ItemModel* Item::getModel() {
    return itemModel;
}

item_id Item::getBaseID() { return id; }
