#include "Item.h"

#include <Aurora/Utils/Logger.h>

using namespace Aurora;

Item::Item(const std::string internalName, item_id id) {
    this->internalName = internalName;
    this->displayName = Translation::GetInstance()->getValue("ITEM", internalName);
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

item_id Item::getID() { return id; }
std::string Item::getInternalName() { return internalName; }
std::string Item::getDisplayName() { return displayName; }

bool Item::isStackable() { return stackable; }


