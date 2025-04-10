#ifndef FEATURES_H
#define FEATURES_H

#include <string>

class FeatureType {
    public:
        enum type {
            durable,
            tool,
            fuel,
            weapon,
            armor,
            smeltable
        };
};

typedef FeatureType::type feature_type;

class ToolType {
    public:
        enum type {
            shovel,
            pickaxe,
            axe,
            hoe
        };
};
typedef ToolType::type tool_type;

class MiningLevel {
    public:
        enum type {
            wood,
            stone,
            iron,
            gold,
            diamond
        };
};
typedef MiningLevel::type mining_level;

class ArmorSlot {
    public:
        enum type {
            helmet,
            chestplate,
            leggings,
            boots
        };
};
typedef ArmorSlot::type armor_slot;



class ItemFeature {
    public:
        virtual feature_type getType() const = 0;
};

class FuelFeature : public ItemFeature {
    public:
        FuelFeature(int burnTime);
        feature_type getType() const;
        int getBurnTime();

    private:
        int burnTime;
};

class DurabilityFeature : public ItemFeature {
    public:
        DurabilityFeature(int maxDurability);
        feature_type getType() const;

        int getMaxDurability();

    private:
        int maxDurability;
};

class ToolFeature : public ItemFeature {
    public:
        ToolFeature(tool_type toolType, mining_level miningLevel, float speed);
        feature_type getType() const;
        
        tool_type getToolType();
        mining_level getMiningLevel();
        float getSpeed();

    private:
        tool_type toolType;
        mining_level miningLevel;
        float speed;
};

class WeaponFeature : public ItemFeature {
    public:
        WeaponFeature(float baseDamage);
        feature_type getType() const;
        int getBaseDamage();

    private:
        float baseDamage;
};

class ArmorFeature : public ItemFeature {
    public:
        ArmorFeature(armor_slot slot, int armorPoints);
        feature_type getType() const;
        armor_slot getArmorSlot();
        int getArmorPoints();

    private:
        armor_slot slot;
        int armorPoints;
};

class SmeltableFeature : public ItemFeature {
    public:
        SmeltableFeature(std::string resultItemName);
        feature_type getType() const;
        std::string getResultItemName();

    private:
        std::string resultItemName;
};

#endif
