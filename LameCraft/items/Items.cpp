#include "Items.h"

//items' id begin from 250

WoodenPickaxe::WoodenPickaxe() : BaseItem() {
    textureRow = 9;

    plane = 0;
    durabilityPoints = 60;
    stackable = false;

    name = "Wooden Pickaxe";
}

item_id WoodenPickaxe::getID() { return 250; }

StonePickaxe::StonePickaxe() : BaseItem() {
    textureRow = 9;

    plane = 1;
    durabilityPoints = 132;
    stackable = false;

    name = "Stone Pickaxe";
}

item_id StonePickaxe::getID() { return 251; }

IronPickaxe::IronPickaxe() : BaseItem() {
    textureRow = 9;

    plane = 2;
    durabilityPoints = 251;
    stackable = false;

    name = "Iron Pickaxe";
}

item_id IronPickaxe::getID() { return 252; }

DiamondPickaxe::DiamondPickaxe() : BaseItem() {
    textureRow = 9;

    plane = 3;
    durabilityPoints = 1562;
    stackable = false;

    name = "Diamond Pickaxe";
}

item_id DiamondPickaxe::getID() { return 253; }

GoldenPickaxe::GoldenPickaxe() : BaseItem() {
    textureRow = 9;

    plane = 4;
    durabilityPoints = 33;
    stackable = false;

    name = "Golden Pickaxe";
}

item_id GoldenPickaxe::getID() { return 254; }

WoodenSword::WoodenSword() : BaseItem() {
    textureRow = 11;

    plane = 0;
    durabilityPoints = 60;
    stackable = false;

    name = "Wooden Sword";
}

item_id WoodenSword::getID() { return 255; }

StoneSword::StoneSword() : BaseItem() {
    textureRow = 11;

    plane = 1;
    durabilityPoints = 132;
    stackable = false;

    name = "Stone Sword";
}

item_id StoneSword::getID() { return 256; }

IronSword::IronSword() : BaseItem() {
    textureRow = 11;

    plane = 2;
    durabilityPoints = 251;
    stackable = false;

    name = "Iron Sword";
}

item_id IronSword::getID() { return 257; }

DiamondSword::DiamondSword() : BaseItem() {
    textureRow = 11;

    plane = 3;
    durabilityPoints = 1562;
    stackable = false;

    name = "Diamond Sword";
}

item_id DiamondSword::getID() { return 258; }

GoldenSword::GoldenSword() : BaseItem() {
    textureRow = 11;

    plane = 4;
    durabilityPoints = 33;
    stackable = false;

    name = "Golden Sword";
}

item_id GoldenSword::getID() { return 259; }
////////
WoodenShovel::WoodenShovel() : BaseItem() {
    textureRow = 10;

    plane = 0;
    durabilityPoints = 60;
    stackable = false;

    name = "Wooden Shovel";
}

item_id WoodenShovel::getID() { return 260; }

StoneShovel::StoneShovel() : BaseItem() {
    textureRow = 10;

    plane = 1;
    durabilityPoints = 132;
    stackable = false;

    name = "Stone Shovel";
}

item_id StoneShovel::getID() { return 261; }

IronShovel::IronShovel() : BaseItem() {
    textureRow = 10;

    plane = 2;
    durabilityPoints = 251;
    stackable = false;

    name = "Iron Shovel";
}

item_id IronShovel::getID() { return 262; }

DiamondShovel::DiamondShovel() : BaseItem() {
    textureRow = 10;

    plane = 3;
    durabilityPoints = 1562;
    stackable = false;

    name = "Diamond Shovel";
}

item_id DiamondShovel::getID() { return 263; }

GoldenShovel::GoldenShovel() : BaseItem() {
    textureRow = 10;

    plane = 4;
    durabilityPoints = 33;
    stackable = false;

    name = "Golden Shovel";
}

item_id GoldenShovel::getID() { return 264; }

WoodenAxe::WoodenAxe() : BaseItem() {
    textureRow = 8;

    plane = 0;
    durabilityPoints = 60;
    stackable = false;

    name = "Wooden Axe";
}

item_id WoodenAxe::getID() { return 265; }

StoneAxe::StoneAxe() : BaseItem() {
    textureRow = 8;

    plane = 1;
    durabilityPoints = 132;
    stackable = false;

    name = "Stone Axe";
}

item_id StoneAxe::getID() { return 266; }

IronAxe::IronAxe() : BaseItem() {
    textureRow = 8;

    plane = 2;
    durabilityPoints = 251;
    stackable = false;

    name = "Iron Axe";
}

item_id IronAxe::getID() { return 267; }

DiamondAxe::DiamondAxe() : BaseItem() {
    textureRow = 8;

    plane = 3;
    durabilityPoints = 1562;
    stackable = false;

    name = "Diamond Axe";
}

item_id DiamondAxe::getID() { return 268; }

GoldenAxe::GoldenAxe() : BaseItem() {
    textureRow = 8;

    plane = 4;
    durabilityPoints = 33;
    stackable = false;

    name = "Golden Axe";
}

item_id GoldenAxe::getID() { return 269; }
///////
WoodenHoe::WoodenHoe() : BaseItem() {
    textureRow = 7;

    plane = 0;
    durabilityPoints = 60;
    stackable = false;

    name = "Wooden Hoe";
}

item_id WoodenHoe::getID() { return 270; }

StoneHoe::StoneHoe() : BaseItem() {
    textureRow = 7;

    plane = 1;
    durabilityPoints = 132;
    stackable = false;

    name = "Stone Hoe";
}

item_id StoneHoe::getID() { return 271; }

IronHoe::IronHoe() : BaseItem() {
    textureRow = 7;

    plane = 2;
    durabilityPoints = 251;
    stackable = false;

    name = "Iron Hoe";
}

item_id IronHoe::getID() { return 272; }

DiamondHoe::DiamondHoe() : BaseItem() {
    textureRow = 7;

    plane = 3;
    durabilityPoints = 1562;
    stackable = false;

    name = "Diamond Hoe";
}

item_id DiamondHoe::getID() { return 273; }

GoldenHoe::GoldenHoe() : BaseItem() {
    textureRow = 7;

    plane = 4;
    durabilityPoints = 33;
    stackable = false;

    name = "Golden Hoe";
}

item_id GoldenHoe::getID() { return 274; }
///////
Scissors::Scissors() : BaseItem() {
    textureRow = 10;

    plane = 13;
    durabilityPoints = 239;
    stackable = false;

    name = "Shears";
}

item_id Scissors::getID() { return 275; }

Stick::Stick() : BaseItem() {
    textureRow = 12;

    plane = 5;

    name = "Stick";
}

item_id Stick::getID() { return 276; }

Coal::Coal() : BaseItem() {
    textureRow = 15;

    plane = 7;

    name = "Coal";
}

item_id Coal::getID() { return 277; }

IronBar::IronBar() : BaseItem() {
    textureRow = 14;

    plane = 7;

    name = "Iron Ingot";
}

item_id IronBar::getID() { return 278; }

DiamondItem::DiamondItem() : BaseItem() {
    textureRow = 12;

    plane = 7;

    name = "Diamond";
}

item_id DiamondItem::getID() { return 279; }

GoldenBar::GoldenBar() : BaseItem() {
    textureRow = 13;

    plane = 7;

    name = "Gold Ingot";
}

item_id GoldenBar::getID() { return 280; }

FireItem::FireItem() : BaseItem() {
    textureRow = 0;

    plane = 0;
}

item_id FireItem::getID() { return 281; }

LigniteCoal::LigniteCoal() : BaseItem() {
    textureRow = 14;

    plane = 9;
}

item_id LigniteCoal::getID() { return 282; }

Clay::Clay() : BaseItem() {
    textureRow = 12;

    plane = 9;

    furnItem = 289;

    name = "Clay";
}

item_id Clay::getID() { return 283; }


Apple::Apple() : BaseItem() {
    textureRow = 15;

    plane = 10;

    name = "Apple";
}

item_id Apple::getID() { return 284; }


GoldenApple::GoldenApple() : BaseItem() {
    textureRow = 15;

    plane = 11;

    name = "Golden Apple";
}

item_id GoldenApple::getID() { return 285; }

WheatSeeds::WheatSeeds() : BaseItem() {
    textureRow = 15;

    plane = 9;

    name = "Seeds";
}

item_id WheatSeeds::getID() { return 286; }

Wheat::Wheat() : BaseItem() {
    textureRow = 14;

    plane = 9;

    name = "Wheat";
}

item_id Wheat::getID() { return 287; }


WhiteBread::WhiteBread() : BaseItem() {
    textureRow = 13;

    plane = 9;

    name = "Bread";
}

item_id WhiteBread::getID() { return 288; }

Brick::Brick() : BaseItem() {
    textureRow = 14;

    plane = 6;

    name = "Brick";
}

item_id Brick::getID() { return 289; }

Busket::Busket() : BaseItem() {
    textureRow = 11;

    plane = 10;
    stackable = false;

    name = "Bucket";
}

item_id Busket::getID() { return 290; }

WaterBusket::WaterBusket() : BaseItem() {
    textureRow = 11;

    plane = 11;
    stackable = false;

    name = "Water Bucket";
}

item_id WaterBusket::getID() { return 291; }

LavaBusket::LavaBusket() : BaseItem() {
    textureRow = 11;

    plane = 12;
    stackable = false;

    name = "Lava Bucket";
}

item_id LavaBusket::getID() { return 292; }

CaneItem::CaneItem() : BaseItem() {
    textureRow = 14;

    plane = 11;

    name = "Sugar Canes";
}

item_id CaneItem::getID() { return 293; }

Flower1Item::Flower1Item() : BaseItem() {
    textureRow = 15;

    plane = 12;

    name = "Rose";
    terrainTexture = true;
}

item_id Flower1Item::getID() { return 294; }

Flower2Item::Flower2Item() : BaseItem() {
    textureRow = 15;

    plane = 13;

    name = "Dandelion";
    terrainTexture = true;
}

item_id Flower2Item::getID() { return 295; }

OakSaplingItem::OakSaplingItem() : BaseItem() {
    textureRow = 15;

    plane = 15;

    name = "Oak Sapling";
    terrainTexture = true;
}

item_id OakSaplingItem::getID() { return 296; }

Paper::Paper() : BaseItem() {
    textureRow = 12;

    plane = 10;

    name = "Paper";
}

item_id Paper::getID() { return 297; }
///////
Book::Book() : BaseItem() {
    textureRow = 12;

    plane = 11;

    name = "Book";
}

item_id Book::getID() { return 298; }

SnowBallItem::SnowBallItem() : BaseItem() {
    textureRow = 15;

    plane = 14;

    name = "Snowball";
}

item_id SnowBallItem::getID() { return 299; }

MooshroomItem1::MooshroomItem1() : BaseItem() {
    textureRow = 14;

    plane = 12;

    name = "Mushroom";
    terrainTexture = true;
}

item_id MooshroomItem1::getID() { return 300; }


MooshroomItem2::MooshroomItem2() : BaseItem() {
    textureRow = 14;

    plane = 13;

    name = "Mushroom";
    terrainTexture = true;
}

item_id MooshroomItem2::getID() { return 301; }

Bowl::Bowl() : BaseItem() {
    textureRow = 11;

    plane = 7;

    name = "Bowl";
}

item_id Bowl::getID() { return 302; }

MooshroomBowl::MooshroomBowl() : BaseItem() {
    textureRow = 11;

    plane = 8;

    name = "Mushroom Stew";
}

item_id MooshroomBowl::getID() { return 303; }

DoorItem::DoorItem() : BaseItem() {
    textureRow = 13;

    plane = 11;
    stackable = false;

    name = "Door";
}

item_id DoorItem::getID() { return 306; }

LadderItem::LadderItem() : BaseItem() {
    textureRow = 10;

    plane = 3;

    name = "Ladder";
    terrainTexture = true;
}

item_id LadderItem::getID() { return 307; }

TorchItem::TorchItem() : BaseItem() {
    textureRow = 10;

    plane = 0;

    name = "Torch";
    terrainTexture = true;
}

item_id TorchItem::getID() { return 308; }
/// @brief ////
SpruceSaplingItem::SpruceSaplingItem() : BaseItem() {
    textureRow = 15;

    plane = 14;

    name = "Spruce Sapling";
    terrainTexture = true;
}

item_id SpruceSaplingItem::getID() { return 309; }

BirchSaplingItem::BirchSaplingItem() : BaseItem() {
    textureRow = 14;

    plane = 14;

    name = "Birch Sapling";
    terrainTexture = true;
}

item_id BirchSaplingItem::getID() { return 310; }

MelonItem::MelonItem() : BaseItem() {
    textureRow = 9;

    plane = 13;

    name = "Melon";
}

item_id MelonItem::getID() { return 311; }

MelonSeeds::MelonSeeds() : BaseItem() {
    textureRow = 12;

    plane = 14;

    name = "Melon Seeds";
}

item_id MelonSeeds::getID() { return 312; }

Sugar::Sugar() : BaseItem() {
    textureRow = 15;

    plane = 13;

    name = "Sugar";
}

item_id Sugar::getID() { return 313; }

CocoaBeans::CocoaBeans() : BaseItem() {
    textureRow = 8;
    plane = 14;
    itemType = ItemType::dye;

    name = "Cocoa Beans";
}

item_id CocoaBeans::getID() { return 314; }

Cookie::Cookie() : BaseItem() {
    textureRow = 10;

    plane = 12;

    name = "Cookie";
}

item_id Cookie::getID() { return 315; }

RawBeef::RawBeef() : BaseItem() {
    textureRow = 9;

    plane = 9;
    furnItem = 317;

    name = "Raw Beef";
}

item_id RawBeef::getID() { return 316; }

Steak::Steak() : BaseItem() {
    textureRow = 9;

    plane = 10;

    name = "Steak";
}

item_id Steak::getID() { return 317; }

LapisLazuli::LapisLazuli() : BaseItem() {
    textureRow = 7;
    plane = 14;
    itemType = ItemType::dye;

    name = "Lapis Lazuli";
}

item_id LapisLazuli::getID() { return 318; }

MilkBusket::MilkBusket() : BaseItem() {
    textureRow = 11;

    plane = 13;

    name = "Milk";
    stackable = false;
}

item_id MilkBusket::getID() { return 319; }

CakeItem::CakeItem() : BaseItem() {
    textureRow = 14;

    plane = 13;

    name = "Cake";
    stackable = false;
}

item_id CakeItem::getID() { return 320; }

Bone::Bone() : BaseItem() {
    textureRow = 14;

    plane = 12;

    name = "Bone";
}

item_id Bone::getID() { return 321; }

BoneMeal::BoneMeal() : BaseItem() {
    textureRow = 4;
    plane = 15;
    itemType = ItemType::dye;

    name = "Bone Meal";
}

item_id BoneMeal::getID() { return 322; }

Leather::Leather() : BaseItem() {
    textureRow = 9;

    plane = 7;

    name = "Leather";
}

item_id Leather::getID() { return 323; }

SampleHelmet::SampleHelmet() : BaseItem() {
    textureRow = 15;

    plane = 15;
    stackable = false;
}

item_id SampleHelmet::getID() { return 324; }

SampleChestplate::SampleChestplate() : BaseItem() {
    textureRow = 14;

    plane = 15;
    stackable = false;
}

item_id SampleChestplate::getID() { return 325; }

SampleLeggings::SampleLeggings() : BaseItem() {
    textureRow = 13;

    plane = 15;
    stackable = false;
}

item_id SampleLeggings::getID() { return 326; }

SampleBoots::SampleBoots() : BaseItem() {
    textureRow = 12;

    plane = 15;
    stackable = false;
}

item_id SampleBoots::getID() { return 327; }

LeatherHelmet::LeatherHelmet() : BaseItem() {
    textureRow = 15;

    plane = 0;
    itemType = ItemType::helmet;
    durabilityPoints = 55;
    stackable = false;

    name = "Leather Helmet";
}

item_id LeatherHelmet::getID() { return 328; }

LeatherChestplate::LeatherChestplate() : BaseItem() {
    textureRow = 14;

    plane = 0;
    itemType = ItemType::chestplate;
    durabilityPoints = 80;
    stackable = false;

    name = "Leather Chestplate";
}

item_id LeatherChestplate::getID() { return 329; }

LeatherLeggings::LeatherLeggings() : BaseItem() {
    textureRow = 13;

    plane = 0;
    itemType = ItemType::leggings;
    durabilityPoints = 75;
    stackable = false;

    name = "Leather Leggings";
}

item_id LeatherLeggings::getID() { return 330; }

LeatherBoots::LeatherBoots() : BaseItem() {
    textureRow = 12;

    plane = 0;
    itemType = ItemType::boots;
    durabilityPoints = 65;
    stackable = false;

    name = "Leather Boots";
}

item_id LeatherBoots::getID() { return 331; }

ChainmailHelmet::ChainmailHelmet() : BaseItem() {
    textureRow = 15;

    plane = 1;
    itemType = ItemType::helmet;
    durabilityPoints = 165;
    stackable = false;

    name = "Chainmail Helmet";
}

item_id ChainmailHelmet::getID() { return 332; }

ChainmailChestplate::ChainmailChestplate() : BaseItem() {
    textureRow = 14;

    plane = 1;
    itemType = ItemType::chestplate;
    durabilityPoints = 240;
    stackable = false;

    name = "Chainmail Chestplate";
}

item_id ChainmailChestplate::getID() { return 333; }

ChainmailLeggings::ChainmailLeggings() : BaseItem() {
    textureRow = 13;

    plane = 1;
    itemType = ItemType::leggings;
    durabilityPoints = 225;
    stackable = false;

    name = "Chainmail Leggings";
}

item_id ChainmailLeggings::getID() { return 334; }

ChainmailBoots::ChainmailBoots() : BaseItem() {
    textureRow = 12;

    plane = 1;
    itemType = ItemType::boots;
    durabilityPoints = 195;
    stackable = false;

    name = "Chainmail Boots";
}

item_id ChainmailBoots::getID() { return 335; }
///////
IronHelmet::IronHelmet() : BaseItem() {
    textureRow = 15;

    plane = 2;
    itemType = ItemType::helmet;
    durabilityPoints = 165;
    stackable = false;

    name = "Iron Helmet";
}

item_id IronHelmet::getID() { return 336; }

IronChestplate::IronChestplate() : BaseItem() {
    textureRow = 14;

    plane = 2;
    itemType = ItemType::chestplate;
    durabilityPoints = 240;
    stackable = false;

    name = "Iron Chestplate";
}

item_id IronChestplate::getID() { return 337; }

IronLeggings::IronLeggings() : BaseItem() {
    textureRow = 13;

    plane = 2;
    itemType = ItemType::leggings;
    durabilityPoints = 225;
    stackable = false;

    name = "Iron Leggings";
}

item_id IronLeggings::getID() { return 338; }

IronBoots::IronBoots() : BaseItem() {
    textureRow = 12;

    plane = 2;
    itemType = ItemType::boots;
    durabilityPoints = 195;
    stackable = false;

    name = "Iron Boots";
}

item_id IronBoots::getID() { return 339; }

DiamondHelmet::DiamondHelmet() : BaseItem() {
    textureRow = 15;

    plane = 3;
    itemType = ItemType::helmet;
    durabilityPoints = 363;
    stackable = false;

    name = "Diamond Helmet";
}

item_id DiamondHelmet::getID() { return 340; }

DiamondChestplate::DiamondChestplate() : BaseItem() {
    textureRow = 14;

    plane = 3;
    itemType = ItemType::chestplate;
    durabilityPoints = 528;
    stackable = false;

    name = "Diamond Chestplate";
}

item_id DiamondChestplate::getID() { return 341; }

DiamondLeggings::DiamondLeggings() : BaseItem() {
    textureRow = 13;

    plane = 3;
    itemType = ItemType::leggings;
    durabilityPoints = 495;
    stackable = false;

    name = "Diamond Leggings";
}

item_id DiamondLeggings::getID() { return 342; }

DiamondBoots::DiamondBoots() : BaseItem() {
    textureRow = 12;

    plane = 3;
    itemType = ItemType::boots;
    durabilityPoints = 429;
    stackable = false;

    name = "Diamond Boots";
}

item_id DiamondBoots::getID() { return 343; }

GoldenHelmet::GoldenHelmet() : BaseItem() {
    textureRow = 15;

    plane = 4;
    itemType = ItemType::helmet;
    durabilityPoints = 77;
    stackable = false;

    name = "Golden Helmet";
}

item_id GoldenHelmet::getID() { return 344; }

GoldenChestplate::GoldenChestplate() : BaseItem() {
    textureRow = 14;

    plane = 4;
    itemType = ItemType::chestplate;
    durabilityPoints = 112;
    stackable = false;

    name = "Golden Chestplate";
}

item_id GoldenChestplate::getID() { return 345; }

GoldenLeggings::GoldenLeggings() : BaseItem() {
    textureRow = 13;

    plane = 4;
    itemType = ItemType::leggings;
    durabilityPoints = 105;
    stackable = false;

    name = "Golden Leggings";
}

item_id GoldenLeggings::getID() { return 346; }

GoldenBoots::GoldenBoots() : BaseItem() {
    textureRow = 12;

    plane = 4;
    itemType = ItemType::boots;
    durabilityPoints = 91;
    stackable = false;

    name = "Golden Boots";
}

item_id GoldenBoots::getID() { return 347; }

RottenFlesh::RottenFlesh() : BaseItem() {
    textureRow = 10;

    plane = 11;

    name = "Rotten Flesh";
}

item_id RottenFlesh::getID() { return 348; }

GlassPanelItem::GlassPanelItem() : BaseItem() {
    textureRow = 12;
    plane = 1;

    terrainTexture = true;

    name = "Glass Panel";
}

item_id GlassPanelItem::getID() { return 349; }

IronBarsItem::IronBarsItem() : BaseItem() {
    textureRow = 10;
    plane = 5;

    terrainTexture = true;

    name = "Iron Bars";
}

item_id IronBarsItem::getID() { return 350; }

Flint::Flint() : BaseItem() {
    textureRow = 15;
    plane = 6;

    name = "Flint";
}

item_id Flint::getID() { return 351; }

Gunpowder::Gunpowder() : BaseItem() {
    textureRow = 13;
    plane = 8;

    name = "Gunpowder";
}

item_id Gunpowder::getID() { return 352; }

Redstone::Redstone() : BaseItem() {
    textureRow = 12;
    plane = 8;

    name = "Redstone";
}

item_id Redstone::getID() { return 353; }

Clock::Clock() : BaseItem() {
    textureRow = 11;
    plane = 6;
    stackable = false;

    name = "Clock";
}

item_id Clock::getID() { return 354; }

Compass::Compass() : BaseItem() {
    textureRow = 12;
    plane = 6;
    stackable = false;

    name = "Compass";
}

item_id Compass::getID() { return 355; }
/// @brief /
Saddle::Saddle() : BaseItem() {
    textureRow = 9;
    plane = 8;
    stackable = false;

    name = "Saddle";
}

item_id Saddle::getID() { return 356; }

Sign::Sign() : BaseItem() {
    textureRow = 13;
    plane = 10;
    stackable = false;

    name = "Sign";
}

item_id Sign::getID() { return 357; }

ItemFrameItem::ItemFrameItem() : BaseItem() {
    textureRow = 3;
    plane = 14;

    name = "Item Frame";
}

item_id ItemFrameItem::getID() { return 358; }

FlowerPotItem::FlowerPotItem() : BaseItem() {
    textureRow = 3;
    plane = 15;

    name = "Flower Pot";
}

item_id FlowerPotItem::getID() { return 359; }

PaintningItem::PaintningItem() : BaseItem() {
    textureRow = 14;
    plane = 10;

    name = "Paintning";
}

item_id PaintningItem::getID() { return 360; }

BedItem::BedItem() : BaseItem() {
    textureRow = 13;
    plane = 13;
    stackable = false;

    name = "Bed";
}

item_id BedItem::getID() { return 361; }


Disk1::Disk1() : BaseItem() {
    textureRow = 0;
    plane = 0;
    stackable = false;

    name = "Music Disk";
}

item_id Disk1::getID() { return 362; }

Disk2::Disk2() : BaseItem() {
    textureRow = 0;
    plane = 1;
    stackable = false;

    name = "Music Disk";
}

item_id Disk2::getID() { return 363; }

Disk3::Disk3() : BaseItem() {
    textureRow = 0;
    plane = 2;
    stackable = false;

    name = "Music Disk";
}

item_id Disk3::getID() { return 364; }


LightGrayDye::LightGrayDye() : BaseItem() {
    textureRow = 4;
    plane = 14;
    itemType = ItemType::dye;

    name = "Light Gray Dye";
}

item_id LightGrayDye::getID() { return 365; }

GrayDye::GrayDye() : BaseItem() {
    textureRow = 11;
    plane = 15;
    itemType = ItemType::dye;

    name = "Gray Dye";
}

item_id GrayDye::getID() { return 366; }

InkSac::InkSac() : BaseItem() {
    textureRow = 11;
    plane = 14;
    itemType = ItemType::dye;

    name = "Ink Sac";
}

item_id InkSac::getID() { return 367; }

PinkDye::PinkDye() : BaseItem() {
    textureRow = 10;
    plane = 15;
    itemType = ItemType::dye;

    name = "Pink Dye";
}

item_id PinkDye::getID() { return 368; }

RoseRed::RoseRed() : BaseItem() {
    textureRow = 10;
    plane = 14;
    itemType = ItemType::dye;

    name = "Rose Red";
}

item_id RoseRed::getID() { return 369; }

OrangeDye::OrangeDye() : BaseItem() {
    textureRow = 5;
    plane = 15;
    itemType = ItemType::dye;

    name = "Orange Dye";
}

item_id OrangeDye::getID() { return 370; }

DandelionYellow::DandelionYellow() : BaseItem() {
    textureRow = 8;
    plane = 15;
    itemType = ItemType::dye;

    name = "Dandelion Yellow";
}

item_id DandelionYellow::getID() { return 371; }

LimeDye::LimeDye() : BaseItem() {
    textureRow = 9;
    plane = 15;
    itemType = ItemType::dye;

    name = "Lime Dye";
}

item_id LimeDye::getID() { return 372; }

CactusGreen::CactusGreen() : BaseItem() {
    textureRow = 9;
    plane = 14;
    itemType = ItemType::dye;

    name = "Cactus Green";
}

item_id CactusGreen::getID() { return 373; }

LightBlueDye::LightBlueDye() : BaseItem() {
    textureRow = 7;
    plane = 15;
    itemType = ItemType::dye;

    name = "Light Blue Dye";
}

item_id LightBlueDye::getID() { return 374; }

PurpleDye::PurpleDye() : BaseItem() {
    textureRow = 6;
    plane = 14;
    itemType = ItemType::dye;

    name = "Purple Dye";
}

item_id PurpleDye::getID() { return 375; }

MagnetaDye::MagnetaDye() : BaseItem() {
    textureRow = 6;
    plane = 15;
    itemType = ItemType::dye;

    name = "Magneta Dye";
}

item_id MagnetaDye::getID() { return 376; }


PumpkinSeeds::PumpkinSeeds() : BaseItem() {
    textureRow = 12;
    plane = 13;

    name = "Pumpkin Seeds";
}

item_id PumpkinSeeds::getID() { return 377; }

FlintAndSteel::FlintAndSteel() : BaseItem() {
    textureRow = 15;
    plane = 5;
    stackable = false;

    durabilityPoints = 65;

    name = "Flint and Steel";
}

item_id FlintAndSteel::getID() { return 378; }

Potato::Potato() : BaseItem() {
    textureRow = 8;
    plane = 7;
    furnItem = 380;

    name = "Potato";
}

item_id Potato::getID() { return 379; }

BakedPotato::BakedPotato() : BaseItem() {
    textureRow = 8;
    plane = 6;

    name = "Baked Potato";
}

item_id BakedPotato::getID() { return 380; }

PoisonedPotato::PoisonedPotato() : BaseItem() {
    textureRow = 7;
    plane = 6;

    name = "Poisioned Potato";
}

item_id PoisonedPotato::getID() { return 381; }

Carrot::Carrot() : BaseItem() {
    textureRow = 8;
    plane = 8;

    name = "Carrot";
}

item_id Carrot::getID() { return 382; }

Disk4::Disk4() : BaseItem() {
    textureRow = 0;
    plane = 3;
    stackable = false;

    name = "Music Disk";
}

item_id Disk4::getID() { return 383; }

Disk5::Disk5() : BaseItem() {
    textureRow = 0;
    plane = 4;
    stackable = false;

    name = "Music Disk";
}

item_id Disk5::getID() { return 384; }

Disk6::Disk6() : BaseItem() {
    textureRow = 0;
    plane = 5;
    stackable = false;

    name = "Music Disk";
}

item_id Disk6::getID() { return 385; }

Disk7::Disk7() : BaseItem() {
    textureRow = 0;
    plane = 6;
    stackable = false;

    name = "Music Disk";
}

item_id Disk7::getID() { return 386; }

Disk8::Disk8() : BaseItem() {
    textureRow = 0;
    plane = 7;
    stackable = false;

    name = "Music Disk";
}

item_id Disk8::getID() { return 387; }

Disk9::Disk9() : BaseItem() {
    textureRow = 0;
    plane = 8;
    stackable = false;

    name = "Music Disk";
}

item_id Disk9::getID() { return 388; }

Disk10::Disk10() : BaseItem() {
    textureRow = 0;
    plane = 9;
    stackable = false;

    name = "Music Disk";
}

item_id Disk10::getID() { return 389; }

Disk11::Disk11() : BaseItem() {
    textureRow = 0;
    plane = 10;
    stackable = false;

    name = "Music Disk";
}

item_id Disk11::getID() { return 390; }

Disk12::Disk12() : BaseItem() {
    textureRow = 0;
    plane = 11;
    stackable = false;

    name = "Music Disk";
}

item_id Disk12::getID() { return 391; }

Charcoal::Charcoal() : BaseItem() {
    textureRow = 13;

    plane = 6;

    name = "Charcoal";
}

item_id Charcoal::getID() { return 392; }