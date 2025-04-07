#include "Item.h"

#include <Aurora/Utils/Logger.h>

using namespace Aurora;

Item::Item(const std::string internalName, item_id id) {
    this->internalName = internalName;
    this->id = id;

    textureRow = 0;
    plane = 0;

    points = 0;
    addPoints = 0;
    vertices = NULL;
    addVertices = NULL;

    stackable = true;
}

Item::~Item() {
    if (vertices != NULL) {
        free(vertices);
        free(addVertices);
        free(add2Vertices);
        free(dropVertices);
    }
}

Item& Item::setTexture(short textureRow, short plane) {
    terrainTexture = false;
    this->textureRow = textureRow;
    this->plane = plane;
    return *this;
}

Item& Item::setTerrainTexture(short textureRow, short plane) {
    terrainTexture = true;
    this->textureRow = textureRow;
    this->plane = plane;
    return *this;
}

Item& Item::setNotStackable() {
    stackable = false;
    return *this;
}

Item& Item::addFeature(Feature* feature) {
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

Feature* Item::getFeature(feature_type type) {
    for (int i = 0; i < itemFeatures.size(); i++) {
        if (itemFeatures[i]->getType() == type) {
            return itemFeatures[i];
        }
    }
    return NULL;
}

item_id Item::getBaseID() { return id; }
