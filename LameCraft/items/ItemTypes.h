#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H

#include "items/Item.h"
#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <Aurora/Utils/Logger.h>

class ItemTypes {
    public:
        static void initialize();

        static Item* getItem(item_id id);
        static Item* getItem(std::string internalName);
        static item_id getItemID(std::string internalName);
        static std::vector<Item*> getAllItems();
        static int getAmountOfItemTypes();

        static void clear();

    private:   
        static void insertItem(Item item);
        static ItemTypes* instance;

        std::map<std::string, item_id> nameToID;
        std::map<item_id, Item*> itemTypes;
};

#endif
