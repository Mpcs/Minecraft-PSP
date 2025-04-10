#include "ItemTypes.h"
ItemTypes* ItemTypes::instance = 0;

void ItemTypes::insertItem(Item item) {
    instance->nameToID.insert(std::map<std::string,item_id>::value_type (item.internalName, item.getBaseID()));
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
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_pickaxe", 251)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_pickaxe", 252)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("diamond_pickaxe", 253)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_pickaxe", 254)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::pickaxe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_sword", 255)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new WeaponFeature(-1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_sword", 256)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("iron_sword", 257)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("diamond_sword", 258)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("gold_sword", 259)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new WeaponFeature(-1))
    );

    insertItem(
        Item("wooden_shovel", 260)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_shovel", 261)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_shovel", 262)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_shovel", 263)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_shovel", 264)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::shovel, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_axe", 265)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_axe", 266)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_axe", 267)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_axe", 268)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::diamond, -1))
    );

    insertItem(
        Item("gold_axe", 269)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::axe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("wooden_hoe", 270)
        .setNotStackable()
        .addFeature(new DurabilityFeature(60))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::wood, -1))
        .addFeature(new FuelFeature(10))
    );

    insertItem(
        Item("stone_hoe", 271)
        .setNotStackable()
        .addFeature(new DurabilityFeature(132))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::stone, -1))
    );

    insertItem(
        Item("iron_hoe", 272)
        .setNotStackable()
        .addFeature(new DurabilityFeature(251))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::iron, -1))
    );

    insertItem(
        Item("diamond_hoe", 273)
        .setNotStackable()
        .addFeature(new DurabilityFeature(1562))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::diamond, -1))
    ); 

    insertItem(
        Item("gold_hoe", 274)
        .setNotStackable()
        .addFeature(new DurabilityFeature(33))
        .addFeature(new ToolFeature(ToolType::hoe, MiningLevel::gold, -1))
    );

    insertItem(
        Item("shears", 275)
        .setNotStackable()
        .addFeature(new DurabilityFeature(239))
    );

    insertItem(
        Item("stick", 276)
        .addFeature(new FuelFeature(5))
    );

    insertItem(
        Item("coal", 277)
        .addFeature(new FuelFeature(80))
    );

    insertItem(
        Item("iron_ingot", 278)
    );

    insertItem(
        Item("diamond", 279)
    );

    insertItem(
        Item("gold_ingot", 280)
    );

    insertItem(
        Item("fire_item", 281) // ??
    );
    
    insertItem(
        Item("charcoal", 282)
    );

    insertItem(
        Item("clay", 283)
        .addFeature(new SmeltableFeature("brick"))
    );

    insertItem(
        Item("apple", 284)
    );

    insertItem(
        Item("golden_apple", 285)
    );

    insertItem(
        Item("seeds", 286)
    );

    insertItem(
        Item("wheat", 287)
    );

    insertItem(
        Item("bread", 288)
    );

    insertItem(
        Item("brick", 289)
    );

    insertItem(
        Item("bucket", 290)
        .setNotStackable()
    );

    insertItem(
        Item("water_bucket", 291)
        .setNotStackable()
    );

    insertItem(
        Item("lava_bucket", 292)
        .setNotStackable()
        .addFeature(new FuelFeature(1000))
    );

    insertItem(
        Item("sugar_cane_item", 293)
        //.setTerrainTexture(14, 11)
    );
    
    insertItem(
        Item("flower_1_item", 294)
        //.setTerrainTexture(15, 12)
    );

    insertItem(
        Item("flower_2_item", 295)
        //.setTerrainTexture(15, 13)
    );

    insertItem(
        Item("oak_sapling", 296)
        //.setTerrainTexture(15, 15)
        .addFeature(new FuelFeature(5))
    );

    insertItem(
        Item("paper", 297)
    );

    insertItem(
        Item("book", 298)
    );

    insertItem(
        Item("snowball", 299)
    );

    insertItem(
        Item("mushroom_1_item", 300)
        //.setTerrainTexture(14, 12)
    );

    insertItem(
        Item("mushroom_2_item", 301)
        //.setTerrainTexture(14, 13)
    );

    insertItem(
        Item("bowl", 302)
    );

    insertItem(
        Item("mushroom_stew", 303)
    );

    insertItem(
        Item("door_item", 306)
        .setNotStackable()
        .addFeature(new FuelFeature(30))
    );

    insertItem(
        Item("ladder_item", 307)
        //.setTerrainTexture(10, 3)
    );

    insertItem(
        Item("torch_item", 308)
        //.setTerrainTexture(11, 8)
    );

    insertItem(
        Item("spruce_sapling_item", 309)
        //.setTerrainTexture(15, 14)
    );

    insertItem(
        Item("birch_sapling_item", 310)
        //.setTerrainTexture(14, 14)
    );

    insertItem(
        Item("melon_item", 311)
    );

    insertItem(
        Item("melon_seeds", 312)
    );

    insertItem(
        Item("sugar", 313)
    );

    insertItem(
        Item("cocoa_beans", 314)
    );

    insertItem(
        Item("cookie", 315)
    );

    insertItem(
        Item("raw_beef", 316)
        .addFeature(new SmeltableFeature("steak"))
    );

    insertItem(
        Item("steak", 317)
    );

    insertItem(
        Item("lapis_lazuli", 318)
    );

    insertItem(
        Item("milk_bucket", 319)
        .setNotStackable()
    );

    insertItem(
        Item("cake_item", 320)
        .setNotStackable()
    );

    insertItem(
        Item("bone", 321)
    );

    insertItem(
        Item("bone_meal", 322)
    );

    insertItem(
        Item("leather", 323)
    );

    insertItem( //TODO: REMOVE THIS! It's displayed int the inv if no armor worn
        Item("sample_helmet", 324)
        .setNotStackable()
    );

    insertItem(
        Item("sample_chestplate", 325)
        .setNotStackable()
    );

    insertItem(
        Item("sample_leggings", 326)
        .setNotStackable()
    );

    insertItem(
        Item("sample_boots", 327)
        .setNotStackable()
    );

    insertItem(
        Item("leather_helmet", 328)
        .setNotStackable()
        .addFeature(new DurabilityFeature(55))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("leather_chestplate", 329)
        .setNotStackable()
        .addFeature(new DurabilityFeature(80))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("leather_leggings", 330)
        .setNotStackable()
        .addFeature(new DurabilityFeature(75))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("leather_boots", 331)
        .setNotStackable()
        .addFeature(new DurabilityFeature(65))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("chainmail_helmet", 332)
        .setNotStackable()
        .addFeature(new DurabilityFeature(165))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("chainmail_chestplate", 333)
        .setNotStackable()
        .addFeature(new DurabilityFeature(240))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("chainmail_leggings", 334)
        .setNotStackable()
        .addFeature(new DurabilityFeature(225))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("chainmail_boots", 335)
        .setNotStackable()
        .addFeature(new DurabilityFeature(195))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("iron_helmet", 336)
        .setNotStackable()
        .addFeature(new DurabilityFeature(165))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("iron_chestplate", 337)
        .setNotStackable()
        .addFeature(new DurabilityFeature(240))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("iron_leggings", 338)
        .setNotStackable()
        .addFeature(new DurabilityFeature(225))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("iron_boots", 339)
        .setNotStackable()
        .addFeature(new DurabilityFeature(195))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("diamond_helmet", 340)
        .setNotStackable()
        .addFeature(new DurabilityFeature(363))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("diamond_chestplate", 341)
        .setNotStackable()
        .addFeature(new DurabilityFeature(528))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("diamond_leggings", 342)
        .setNotStackable()
        .addFeature(new DurabilityFeature(495))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("diamond_boots", 343)
        .setNotStackable()
        .addFeature(new DurabilityFeature(429))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );

    insertItem(
        Item("gold_helmet", 344)
        .setNotStackable()
        .addFeature(new DurabilityFeature(77))
        .addFeature(new ArmorFeature(ArmorSlot::helmet, -1))
    );

    insertItem(
        Item("gold_chestplate", 345)
        .setNotStackable()
        .addFeature(new DurabilityFeature(112))
        .addFeature(new ArmorFeature(ArmorSlot::chestplate, -1))
    );

    insertItem(
        Item("gold_leggings", 346)
        .setNotStackable()
        .addFeature(new DurabilityFeature(105))
        .addFeature(new ArmorFeature(ArmorSlot::leggings, -1))
    );

    insertItem(
        Item("gold_boots", 347)
        .setNotStackable()
        .addFeature(new DurabilityFeature(91))
        .addFeature(new ArmorFeature(ArmorSlot::boots, -1))
    );


    insertItem(
        Item("rotten_flesh", 348)
    );

    insertItem(
        Item("glass_panel_item", 349)
        //.setTerrainTexture(12, 1)
    );

    insertItem(
        Item("iron_bars_item", 350)
        //.setTerrainTexture(10, 5)
    );

    insertItem(
        Item("flint", 351)
    );

    insertItem(
        Item("gunpowder", 352)
    );

    insertItem(
        Item("redstone", 353)
    );

    insertItem(
        Item("clock", 354)
        .setNotStackable()
    );

    insertItem(
        Item("compass", 355)
        .setNotStackable()
    );

    insertItem(
        Item("saddle", 356)
        .setNotStackable()
    );

    insertItem(
        Item("sign", 357)
        .setNotStackable()
    );

    insertItem(
        Item("item_frame_item", 358)
    );

    insertItem(
        Item("flower_pot_item", 359)
    );

    insertItem(
        Item("painting_item", 360)
    );

    insertItem(
        Item("bed_item", 361)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_1", 362)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_2", 363)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_3", 364)
        .setNotStackable()
    );

    insertItem(
        Item("light_gray_dye", 365)
    );

    insertItem(
        Item("gray_dye", 366)
    );

    insertItem(
        Item("ink_sac", 367)
    );

    insertItem(
        Item("pink_dye", 368)
    );

    insertItem(
        Item("rose_red", 369)
    );

    insertItem(
        Item("orange_dye", 370)
    );

    insertItem(
        Item("dandelion_yellow", 371)
    );

    insertItem(
        Item("lime_dye", 372)
    );

    insertItem(
        Item("cactus_green", 373)
    );

    insertItem(
        Item("light_blue_dye", 374)
    );

    insertItem(
        Item("purple_dye", 375)
    );

    insertItem(
        Item("magenta_dye", 376)
    );

    insertItem(
        Item("pumpkin_seeds", 377)
    );

    insertItem(
        Item("flint_and_steel", 378)
        .setNotStackable()
        .addFeature(new DurabilityFeature(65))
    );

    insertItem(
        Item("potato", 379)
        .addFeature(new SmeltableFeature("baked_potato"))
    );

    insertItem(
        Item("baked_potato", 380)
    );

    insertItem(
        Item("poisoned_potato", 381)
    );

    insertItem(
        Item("carrot", 382)
    );

    insertItem(
        Item("music_disk_4", 383)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_5", 384)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_6", 385)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_7", 386)
        .setNotStackable()
    );


    insertItem(
        Item("music_disk_8", 387)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_9", 388)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_10", 389)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_11", 390)
        .setNotStackable()
    );

    insertItem(
        Item("music_disk_12", 391)
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