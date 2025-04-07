#include "ItemTypes.h"
ItemTypes* ItemTypes::instance = 0;


void ItemTypes::insertItem(Item& item) {
    instance->nameToID.insert(std::map<std::string,item_id>::value_type (item.internalName, item.getBaseID()));
    //ItemTypes::nameToID[item.internalName] = item.getBaseID();
    instance->itemTypes[item.getBaseID()] = new Item(item);
}

Item* ItemTypes::getItem(item_id id) {
    return instance->itemTypes[id];
}

Item* ItemTypes::getItem(std::string internalName) {
    item_id id = instance->nameToID[internalName];
    return instance->itemTypes[id];
}

item_id ItemTypes::getItemID(std::string internalName) {
    if (instance->nameToID.count(internalName)) {
        return instance->nameToID[internalName];
    }
    return -1;
}

std::vector<Item*> ItemTypes::getAllItems() {
    std::vector<Item*> allItems;
    std::map<item_id, Item*>::iterator it;
    for (it = (instance->itemTypes).begin(); it != (instance->itemTypes).end(); it++) {
        allItems.push_back(it->second);
    }
    return allItems;
}

int ItemTypes::getAmountOfItemTypes() {
    return instance->itemTypes.size();
}

void ItemTypes::initialize() {
    instance = new ItemTypes();

    time_t startTime;
    startTime=time(NULL);
    
    //TODO: Replace all -1s
    insertItem(
        Item("wooden_pickaxe", 250)
        .setTexture(9, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_pickaxe", 251)
        .setTexture(9, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_pickaxe", 252)
        .setTexture(9, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("diamond_pickaxe", 253)
        .setTexture(9, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_pickaxe", 254)
        .setTexture(9, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_sword", 255)
        .setTexture(11, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new WeaponFeature(-1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_sword", 256)
        .setTexture(11, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("iron_sword", 257)
        .setTexture(11, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("diamond_sword", 258)
        .setTexture(11, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("gold_sword", 259)
        .setTexture(11, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("wooden_shovel", 260)
        .setTexture(10, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_shovel", 261)
        .setTexture(10, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_shovel", 262)
        .setTexture(10, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_shovel", 263)
        .setTexture(10, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_shovel", 264)
        .setTexture(10, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_axe", 265)
        .setTexture(8, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_axe", 266)
        .setTexture(8, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_axe", 267)
        .setTexture(8, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_axe", 268)
        .setTexture(8, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_axe", 269)
        .setTexture(8, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_hoe", 270)
        .setTexture(7, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_hoe", 271)
        .setTexture(7, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_hoe", 272)
        .setTexture(7, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_hoe", 273)
        .setTexture(7, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::diamond, -1))
    ); 

    insertItem(
        Item("gold_hoe", 274)
        .setTexture(7, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("shears", 275)
        .setTexture(10, 13)
        .setNotStackable()
        .addFeature(new DurabilityFeature(239))
    );

    insertItem(
        Item("stick", 276)
        .setTexture(12, 5)
        .addFeature(new FuelFeature(5))
    );

    insertItem(
        Item("coal", 277)
        .setTexture(15, 7)
        .addFeature(new FuelFeature(80))
    );

    insertItem(
        Item("iron_ingot", 278)
        .setTexture(14, 7)
    );

    insertItem(
        Item("diamond", 279)
        .setTexture(12, 7)
    );

    insertItem(
        Item("gold_ingot", 280)
        .setTexture(13, 7)
    );

    insertItem(
        Item("fire_item", 281) // ??
        .setTexture(0,0)
    );
    
    insertItem(
        Item("charcoal", 282)
        .setTexture(14, 9)
    );

    insertItem(
        Item("clay", 283)
        .setTexture(12, 9)
        .addFeature(new SmeltableFeature("brick"))
    );

    insertItem(
        Item("apple", 284)
        .setTexture(15, 10)
    );

    insertItem(
        Item("golden_apple", 285)
        .setTexture(15, 11)
    );

    insertItem(
        Item("seeds", 286)
        .setTexture(15, 9)
    );

    insertItem(
        Item("wheat", 287)
        .setTexture(14, 9)
    );

    insertItem(
        Item("bread", 288)
        .setTexture(13, 9)
    );

    insertItem(
        Item("brick", 289)
        .setTexture(14, 6)
    );

    insertItem(
        Item("bucket", 290)
        .setTexture(11, 10)
        .setNotStackable()
    );

    insertItem(
        Item("water_bucket", 291)
        .setTexture(11, 11)
        .setNotStackable()
    );

    insertItem(
        Item("lava_bucket", 292)
        .setTexture(11, 12)
        .setNotStackable()
        .addFeature(new FuelFeature(1000))
    );

    insertItem(
        Item("sugar_cane_item", 293)
        .setTerrainTexture(14, 11)
    );
    
    insertItem(
        Item("flower_1_item", 294)
        .setTerrainTexture(15, 12)
    );

    insertItem(
        Item("flower_2_item", 295)
        .setTerrainTexture(15, 13)
    );

    insertItem(
        Item("oak_sapling", 296)
        .setTerrainTexture(15, 15)
        .addFeature(new FuelFeature(5))
    );

    insertItem(
        Item("paper", 297)
        .setTexture(12, 10)
    );

    insertItem(
        Item("book", 298)
        .setTexture(12, 11)
    );

    insertItem(
        Item("snowball", 299)
        .setTexture(15, 14)
    );

    insertItem(
        Item("mushroom_1_item", 300)
        .setTerrainTexture(14, 12)
    );

    insertItem(
        Item("mushroom_2_item", 301)
        .setTerrainTexture(14, 13)
    );

    insertItem(
        Item("bowl", 302)
        .setTexture(11, 8)
    );

    insertItem(
        Item("mushroom_stew", 303)
        .setTexture(11, 8)
    );

    insertItem(
        Item("door_item", 306)
        .setTexture(11, 11)
        .setNotStackable()
        .addFeature(new FuelFeature(30))
    );

    insertItem(
        Item("ladder_item", 307)
        .setTerrainTexture(10, 3)
    );

    insertItem(
        Item("torch_item", 308)
        .setTerrainTexture(11, 8)
    );

    insertItem(
        Item("spruce_sapling_item", 309)
        .setTerrainTexture(15, 14)
    );

    insertItem(
        Item("birch_sapling_item", 310)
        .setTerrainTexture(14, 14)
    );

    insertItem(
        Item("melon_item", 311)
        .setTexture(9, 13)
    );

    insertItem(
        Item("melon_seeds", 312)
        .setTexture(2, 14)
    );

    insertItem(
        Item("sugar", 313)
        .setTexture(15, 3)
    );

    insertItem(
        Item("cocoa_beans", 314)
        .setTexture(8, 14)
    );

    insertItem(
        Item("cookie", 315)
        .setTexture(10, 12)
    );

    insertItem(
        Item("raw_beef", 316)
        .setTexture(9, 9)
        .addFeature(new SmeltableFeature("steak"))
    );

    insertItem(
        Item("steak", 317)
        .setTexture(9, 10)
    );

    insertItem(
        Item("lapis_lazuli", 318)
        .setTexture(7, 14)
    );

    insertItem(
        Item("milk_bucket", 319)
        .setTexture(11, 13)
        .setNotStackable()
    );

    insertItem(
        Item("cake_item", 320)
        .setTexture(14, 13)
        .setNotStackable()
    );

    insertItem(
        Item("bone", 321)
        .setTexture(14, 12)
    );

    insertItem(
        Item("bone_meal", 322)
        .setTexture(4, 15)
    );

    insertItem(
        Item("leather", 323)
        .setTexture(9, 7)
    );

    insertItem( //TODO: REMOVE THIS! It's displayed int the inv if no armor worn
        Item("sample_helmet", 324)
        .setTexture(15, 15)
        .setNotStackable()
    );

    insertItem(
        Item("sample_chestplate", 325)
        .setTexture(14, 15)
        .setNotStackable()
    );

    insertItem(
        Item("sample_leggings", 326)
        .setTexture(13, 15)
        .setNotStackable()
    );

    insertItem(
        Item("sample_boots", 327)
        .setTexture(12, 15)
        .setNotStackable()
    );

    insertItem(
        Item("leather_helmet", 328)
        .setTexture(15, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(55))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("leather_chestplate", 329)
        .setTexture(14, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(80))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("leather_leggings", 330)
        .setTexture(13, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(75))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("leather_boots", 331)
        .setTexture(12, 0)
        .setNotStackable()
        .addFeature(new DurabilityFeature(65))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("chainmail_helmet", 332)
        .setTexture(15, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(165))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("chainmail_chestplate", 333)
        .setTexture(14, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(240))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("chainmail_leggings", 334)
        .setTexture(13, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(225))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("chainmail_boots", 335)
        .setTexture(12, 1)
        .setNotStackable()
        .addFeature(new DurabilityFeature(195))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("iron_helmet", 336)
        .setTexture(15, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(165))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("iron_chestplate", 337)
        .setTexture(14, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(240))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("iron_leggings", 338)
        .setTexture(13, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(225))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("iron_boots", 339)
        .setTexture(12, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(195))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("diamond_helmet", 340)
        .setTexture(15, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(363))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("diamond_chestplate", 341)
        .setTexture(14, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(528))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("diamond_leggings", 342)
        .setTexture(13, 3)
        .setNotStackable()
        .addFeature(new DurabilityFeature(495))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("diamond_boots", 343)
        .setTexture(12, 2)
        .setNotStackable()
        .addFeature(new DurabilityFeature(429))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("gold_helmet", 344)
        .setTexture(15, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(77))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("gold_chestplate", 345)
        .setTexture(14, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(112))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("gold_leggings", 346)
        .setTexture(13, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(105))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("gold_boots", 347)
        .setTexture(12, 4)
        .setNotStackable()
        .addFeature(new DurabilityFeature(91))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );


    insertItem(
        Item("rotten_flesh", 348)
        .setTexture(10, 11)
    );

    insertItem(
        Item("glass_panel_item", 349)
        .setTerrainTexture(12, 1)
    );

    insertItem(
        Item("iron_bars_item", 350)
        .setTerrainTexture(10, 5)
    );

    insertItem(
        Item("flint", 351)
        .setTexture(15, 6)
    );

    insertItem(
        Item("gunpowder", 352)
        .setTexture(13, 8)
    );

    insertItem(
        Item("redstone", 353)
        .setTexture(12, 8)
    );

    insertItem(
        Item("clock", 354)
        .setTexture(11, 6)
        .setNotStackable()
    );

    insertItem(
        Item("compass", 355)
        .setTexture(12, 6)
        .setNotStackable()
    );

    insertItem(
        Item("saddle", 356)
        .setTexture(9, 8)
        .setNotStackable()
    );

    insertItem(
        Item("sign", 357)
        .setTexture(13, 10)
        .setNotStackable()
    );

    insertItem(
        Item("item_frame_item", 358)
        .setTexture(3, 14)
    );

    insertItem(
        Item("flower_pot_item", 359)
        .setTexture(3, 15)
    );

    insertItem(
        Item("painting_item", 360)
        .setTexture(14, 10)
    );

    insertItem(
        Item("bed_item", 361)
        .setTexture(13, 13)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_1", 362)
        .setTexture(0, 0)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_2", 363)
        .setTexture(0, 1)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_3", 364)
        .setTexture(0, 2)
        .setNotStackable()
    );

    insertItem(
        Item("light_gray_dye", 365)
        .setTexture(4, 14)
    );

    insertItem(
        Item("gray_dye", 366)
        .setTexture(11, 15)
    );

    insertItem(
        Item("ink_sac", 367)
        .setTexture(11, 14)
    );

    insertItem(
        Item("pink_dye", 368)
        .setTexture(10, 15)
    );

    insertItem(
        Item("rose_red", 369)
        .setTexture(10, 14)
    );

    insertItem(
        Item("orange_dye", 370)
        .setTexture(5, 15)
    );

    insertItem(
        Item("dandelion_yellow", 371)
        .setTexture(8, 15)
    );

    insertItem(
        Item("lime_dye", 372)
        .setTexture(9, 15)
    );

    insertItem(
        Item("cactus_green", 373)
        .setTexture(9, 14)
    );

    insertItem(
        Item("light_blue_dye", 374)
        .setTexture(7, 15)
    );

    insertItem(
        Item("purple_dye", 375)
        .setTexture(6, 14)
    );

    insertItem(
        Item("magenta_dye", 376)
        .setTexture(6, 15)
    );

    insertItem(
        Item("pumpkin_seeds", 377)
        .setTexture(12, 13)
    );

    insertItem(
        Item("flint_and_steel", 378)
        .setTexture(15, 7)
        .setNotStackable()
        .addFeature(new DurabilityFeature(65))
    );

    insertItem(
        Item("potato", 379)
        .setTexture(8, 7)
        .addFeature(new SmeltableFeature("baked_potato"))
    );

    insertItem(
        Item("baked_potato", 380)
        .setTexture(8, 6)
    );

    insertItem(
        Item("poisoned_potato", 381)
        .setTexture(7, 6)
    );

    insertItem(
        Item("carrot", 382)
        .setTexture(8, 8)
    );

    insertItem(
        Item("music_disk_4", 383)
        .setTexture(0, 3)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_5", 384)
        .setTexture(0, 4)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_6", 385)
        .setTexture(0, 5)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_7", 386)
        .setTexture(0, 6)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_8", 387)
        .setTexture(0, 7)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_9", 388)
        .setTexture(0, 8)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_10", 389)
        .setTexture(0, 9)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_11", 390)
        .setTexture(0, 10)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_12", 391)
        .setTexture(0, 11)
        .setNotStackable()
    );

    time_t endTime;
    endTime=time(NULL);
    Aurora::Utils::Logger::Instance()->LogMessage("Initialized %i item types in %i ms.\n", instance->itemTypes.size(), endTime-startTime);
}

void ItemTypes::clear() {
    instance->nameToID.clear();
    instance->itemTypes.clear();
}