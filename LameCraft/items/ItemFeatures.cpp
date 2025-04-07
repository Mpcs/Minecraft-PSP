#include "ItemFeatures.h"

FuelFeature::FuelFeature(int burnTime) : ItemFeature() {
    this->burnTime = burnTime;
}
feature_type FuelFeature::getType() const {
    return FeatureType::fuel;
}
int FuelFeature::getBurnTime() {
    return burnTime;
}

DurabilityFeature::DurabilityFeature(int maxDurability) : ItemFeature() {
    this->maxDurability = maxDurability;
}
feature_type DurabilityFeature::getType() const {
    return FeatureType::durable;
}
int DurabilityFeature::getMaxDurability() {
    return maxDurability;
}

ToolFeature::ToolFeature(tool_type toolType, mining_level miningLevel, float speed) : ItemFeature() {
    this->toolType = toolType;
    this->miningLevel = miningLevel;
    this->speed = speed;
}
feature_type ToolFeature::getType() const {
    return FeatureType::tool;
}
mining_level ToolFeature::getMiningLevel() {
    return miningLevel;
}
float ToolFeature::getSpeed() {
    return speed;
}

WeaponFeature::WeaponFeature(float baseDamage) : ItemFeature() {
    this->baseDamage = baseDamage;
}
feature_type WeaponFeature::getType() const {
    return FeatureType::weapon;
}
int WeaponFeature::getBaseDamage() {
    return baseDamage;
}

ArmorFeature::ArmorFeature(armor_slot slot, int armorPoints) : ItemFeature() {
    this->slot = slot;
    this->armorPoints = slot;
}
feature_type ArmorFeature::getType() const {
    return FeatureType::armor;
}
armor_slot ArmorFeature::getArmorSlot() {
    return slot;
}
int ArmorFeature::getArmorPoints() {
    return armorPoints;
}

SmeltableFeature::SmeltableFeature(std::string resultItemName) : ItemFeature() {
    this->resultItemName = resultItemName;
}
feature_type SmeltableFeature::getType() const {
    return FeatureType::smeltable;
}
std::string SmeltableFeature::getResultItemName() {
    return resultItemName;
}



