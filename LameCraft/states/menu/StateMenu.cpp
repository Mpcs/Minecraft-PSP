#include "StateMenu.h"
#include "states/menu/StateOptions.h"
#include "states/StatePlay.h"
#include "states/StatePlayCreative.h"
#include "screens/LoadingScreen.h"
#include "lang/Translation.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include <Aurora/System/NetworkManager.h>
#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

// font vars
#define default_size 0.5
#define default_big_size 0.687
#define PI 3.1415926535897f

#define ENGLISH 1
#define RUSSIAN 2

#define SURVIVAL 0
#define CREATIVE 1
#define HARDCORE 2

/*
q = �
w = �
e = �
y = �
u = y
i = �
o = o
p = �
g = �
j = �
z = �
x = �
c = �
v = �
~ = �

$ = �
& = �
^ = �
@ = �
# = �
*/

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;

StateMenu::StateMenu() {

}

StateMenu::~StateMenu() {

}

void StateMenu::Init() {
    newW_width = 0;
    newW_height = 0;
    newW_length = 0;

    newW_gameMode = SURVIVAL;
    newW_deleteCaves = true;
    conversionStage = 0;
    errorType = 0;

    converterPos = 0;
    schematicExists = false;

    lol = "";

    SplashNumber = rand() % 6;


    mainStatistics.blockPlaced = 0;
    mainStatistics.blockDestroyed = 0;
    mainStatistics.daysInGame = 0;
    mainStatistics.minutesPlayed = 0;
    mainStatistics.itemsCrafted = 0;
    mainStatistics.itemsSmelted = 0;
    mainStatistics.jumps = 0;
    mainStatistics.dies = 0;
    mainStatistics.foodEaten = 0;
    mainStatistics.badlyFalls = 0;
    mainStatistics.blocksWalked = 0;
    mainStatistics.treesGrowned = 0;
    mainStatistics.cropsGrowned = 0;
    mainStatistics.soilPlowed = 0;
    mainStatistics.timeInAir = 0;
    mainStatistics.timeInWater = 0;
    mainStatistics.damageRecieved = 0;
    // end

    // �������������� ���������� �����
    mainOptions.detailedSky = 1;
    mainOptions.smoothLighting = true;
    mainOptions.sounds = 1;
    mainOptions.music = 1;
    mainOptions.fogRendering = 1;
    mainOptions.fastRendering = true;
    mainOptions.mipMapTexturing = false;
    mainOptions.autoJump = 0;
    mainOptions.fov = 65;
    mainOptions.freezeDayTime = 0;
    mainOptions.worldBlockAnimation = 1;
    mainOptions.particles = 0;
    mainOptions.difficult = 2; // normal
    mainOptions.horizontalViewDistance = 4;
    mainOptions.verticalViewDistance = 1;
    mainOptions.guiDrawing = 1;



    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo), 0, 0, 256, 64);
    logoSprite->Scale(1.5f, 1.5f);
    logoSprite->SetPosition(240, 50);

    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
    backgroundSprite->Scale(2, 2);
    backgroundSprite->SetPosition(240, 136);

    bx = 240;
    by = 136;
    directionx = rand() % 2;
    directiony = rand() % 2;

    rectFilledSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles), 0, 0, 230, 37);
    rectFilledSprite->SetPosition(240, 150);
    rectFilledSprite->Scale(2, 2);

    rectEmptySprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Rectangles), 0, 37, 230, 37);
    rectEmptySprite->SetPosition(240, 150);
    rectEmptySprite->Scale(2, 2);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12); // stand
    buttonSprite->SetPosition(240, 150);
    buttonSprite->Scale(2, 2);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95,
                               12); // stand selected
    sbuttonSprite->SetPosition(240, 150);
    sbuttonSprite->Scale(2, 2);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 24, 95, 12); // dark
    nbuttonSprite->SetPosition(240, 150);
    nbuttonSprite->Scale(2, 2);

    // small buttons
    buttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95,
                                   12); // stand
    buttonSmallSprite->SetPosition(240, 150);
    buttonSmallSprite->Scale(0.45f, 1.0f);
    buttonSmallSprite->Scale(2, 2);

    sbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95,
                                    12); // stand selected
    sbuttonSmallSprite->SetPosition(240, 150);
    sbuttonSmallSprite->Scale(0.45f, 1.0f);
    sbuttonSmallSprite->Scale(2, 2);

    nbuttonSmallSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 24, 95,
                                    12); // dark
    nbuttonSmallSprite->SetPosition(240, 150);
    nbuttonSmallSprite->Scale(0.45f, 1.0f);
    nbuttonSmallSprite->Scale(2, 2);
    //

    mbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 36, 95, 12); // gray
    mbuttonSprite->SetPosition(240, 150);
    mbuttonSprite->Scale(2, 2);

    smbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 48, 95,
                                12); // gray selected
    smbuttonSprite->SetPosition(240, 150);
    smbuttonSprite->Scale(2, 2);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    backSprite->Scale(2, 2);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft), 0, 0, 320, 90);
    lamecraftSprite->SetPosition(240, 50);
    lamecraftSprite->Scale(1, 1);

    blackBackground = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 87, 60, 8, 8);
    blackBackground->SetPosition(240, 116);
    blackBackground->Scale(60, 22);

    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");
    ScanTexturePacks("Assets/Textures/");

    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    aboutPos = 0;

    newWorldName = "New World";
    newWorldNamestr = "";
    newWorldSeed = "";

    size_f = 0.347f;

    //for map generation
    makeTrees = true;
    makeWater = true;
    makeCaves = true;

    terrainBuilder = 0;
    worldType = 0; // default
    gameMode = SURVIVAL;
    seed_1 = 0;

    SplashNumber = rand() % 6;
    splashSize = 0.0f;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    generateSelectPose = 0;

    newWorldNamestr = newWorldName.c_str();
    currentVersion = 140;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

    animationscreen = 1;
    fontcoloroption = 0;
    fontcolor = 0;
    srand(time(0));

    tpCurrent = 0;
    tpMax = 0;
    tpEnd = 0;
    tpStart = 0;
    tpPos = 0;
    tpSelectPos = 0;

    for (int i = 0; i <= 31; i++) {
        worldName[i] = ' ';
    }
}

void StateMenu::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateMenu::CleanUp() {
    delete logoSprite;
    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete mbuttonSprite;
    delete smbuttonSprite;
    delete backSprite;
    delete lamecraftSprite;

    delete buttonSmallSprite;
    delete sbuttonSmallSprite;
    delete nbuttonSmallSprite;

    delete backgroundSprite;
    delete blackBackground;
}

void StateMenu::Pause() {

}

void StateMenu::Resume() {
    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateMenu::HandleEvents(StateManager *sManager) {
    //update input
    mSystemMgr->InputUpdate();

    switch (menuState) {
        case 6://converter
        {
            if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
                converterPos--;
                if (converterPos < 0)
                    converterPos = 2;

                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
                converterPos++;
                if (converterPos > 2)
                    converterPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
                if (converterPos == 0) {
                    newW_gameMode == SURVIVAL ? newW_gameMode = CREATIVE : newW_gameMode = SURVIVAL;
                }
                if (converterPos == 1) {
                    errorType = 0;
                    if (schematicExists) {
                        char buffer[40];
                        char empty;
                        gzFile saveFile;

                        /// (1) FETCH SCHEMATIC WIDTH HEIGHT LENGTH AND TAKING ITS BLOCK IDS
                        saveFile = gzopen("Converter/world.schematic", "rb");
                        if (saveFile == 0)
                            return;
                        //compound
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        for (int i = 0; i < 9; i++) {
                            gzread(saveFile, &empty, sizeof(char));
                            lol += empty;
                        }

                        //height
                        gzread(saveFile, &empty, sizeof(char));

                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        for (int i = 0; i < 6; i++) {
                            gzread(saveFile, &empty, sizeof(char));
                            lol += empty;
                        }
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &newW_height, sizeof(char));


                        //length
                        gzread(saveFile, &empty, sizeof(char));

                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        for (int i = 0; i < 6; i++) {
                            gzread(saveFile, &empty, sizeof(char));
                            lol += empty;
                        }
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &newW_length, sizeof(char));


                        //width
                        gzread(saveFile, &empty, sizeof(char));

                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        for (int i = 0; i < 5; i++) {
                            gzread(saveFile, &empty, sizeof(char));
                            lol += empty;
                        }
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &newW_width, sizeof(char));

                        if (newW_height + newW_length + newW_width != 252 + 112 + 252) {
                            errorType = 1;
                            return;
                        }

                        //blocks
                        unsigned char *m_Array1;
                        m_Array1 = new block_t[252 * 112 * 252];
                        memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);

                        char need[6];
                        bool again = false;
                        for (int i = 0; i < 100000000; i++) {
                            for (int j = 1; j <= 5; j++) {
                                need[j - 1] = need[j];
                            }
                            gzread(saveFile, &empty, sizeof(char));
                            need[5] = empty;

                            if (need[0] == 'B' &&
                                need[1] == 'l' &&
                                need[2] == 'o' &&
                                need[3] == 'c' &&
                                need[4] == 'k' &&
                                need[5] == 's') {
                                i = 100000000;
                                break;
                            }

                            if (need[2] == 'D' &&
                                need[3] == 'a' &&
                                need[4] == 't' &&
                                need[5] == 'a') {
                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));

                                gzread(saveFile, m_Array1, sizeof(unsigned char) * (252 * 112 * 252));

                                again = true;;
                                i = 100000000;
                                break;
                            }
                        }

                        if (again) {
                            memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
                            for (int j = 0; j <= 6; j++) {
                                need[j] = '/0';
                            }

                            for (int i = 0; i < 100000000; i++) {
                                for (int j = 1; j <= 5; j++) {
                                    need[j - 1] = need[j];
                                }
                                gzread(saveFile, &empty, sizeof(char));
                                need[5] = empty;

                                if (need[0] == 'B' &&
                                    need[1] == 'l' &&
                                    need[2] == 'o' &&
                                    need[3] == 'c' &&
                                    need[4] == 'k' &&
                                    need[5] == 's') {
                                    i = 100000000;
                                    break;
                                }
                            }
                        }
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        gzread(saveFile, m_Array1, sizeof(unsigned char) * (252 * 112 * 252));

                        gzclose(saveFile);

                        // id converter
                        std::vector<unsigned char> id_map;
                        id_map.push_back(0); //0
                        id_map.push_back(RockBlock::getID());
                        id_map.push_back(GrassBlock::getID());
                        id_map.push_back(DirtBlock::getID());
                        id_map.push_back(CobbleStone::getID());
                        id_map.push_back(OakPlanks::getID());
                        id_map.push_back(OakSapling::getID());
                        id_map.push_back(IronBlock::getID());
                        id_map.push_back(WaterBlock::getID());
                        id_map.push_back(WaterBlock::getID());
                        id_map.push_back(Lava::getID());
                        id_map.push_back(Lava::getID());
                        id_map.push_back(SandBlock::getID());
                        id_map.push_back(Gravel::getID());
                        id_map.push_back(GoldBlock::getID());
                        id_map.push_back(IronOre::getID());
                        id_map.push_back(CoalOre::getID());
                        id_map.push_back(WoodBlock::getID());
                        id_map.push_back(LeavesBlock::getID());
                        id_map.push_back(Sponge::getID());
                        id_map.push_back(GlassBlock::getID());
                        id_map.push_back(LapisOre::getID());
                        id_map.push_back(LapisBlock::getID());
                        id_map.push_back(0);
                        id_map.push_back(SandStone::getID());
                        id_map.push_back(NoteBlock::getID());
                        id_map.push_back(0); // bed
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(WhiteWoolBlock::getID()); // 35
                        id_map.push_back(0);
                        id_map.push_back(Flower1::getID());
                        id_map.push_back(Flower2::getID());
                        id_map.push_back(Mooshroom1::getID());
                        id_map.push_back(Mooshroom2::getID());
                        id_map.push_back(GoldBlock::getID());
                        id_map.push_back(IronBlock::getID());
                        id_map.push_back(DoubleSlab::getID());
                        id_map.push_back(Slab::getID());
                        id_map.push_back(BrickBlock::getID());
                        id_map.push_back(TNTBlock::getID());
                        id_map.push_back(ShelfBlock::getID());
                        id_map.push_back(MossyCobblestone::getID());
                        id_map.push_back(Obsidian::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(BirchPlanks::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(DiamondOre::getID());
                        id_map.push_back(Diamond::getID());
                        id_map.push_back(CraftingTable::getID());
                        id_map.push_back(WheatBlock6::getID());
                        id_map.push_back(Soil::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(CobbleStone::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(RedstoneOre::getID());
                        id_map.push_back(RedstoneOre::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(Snow2::getID());
                        id_map.push_back(IceBlock::getID());
                        id_map.push_back(SnowBlock::getID());
                        id_map.push_back(CactusBlock::getID());
                        id_map.push_back(ClayBlock::getID());
                        id_map.push_back(CaneBlock::getID());
                        id_map.push_back(JukeBox::getID());
                        id_map.push_back(WoodenFence::getID());
                        id_map.push_back(Pumpkin1::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(JackOLantern1::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(StoneBrick::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(IronBars::getID());
                        id_map.push_back(GlassPanel::getID());
                        id_map.push_back(MelonBlock::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(BrickBlock::getID());
                        id_map.push_back(0);
                        id_map.push_back(GrassBlock::getID());
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(0);
                        id_map.push_back(OakHalfBlock::getID());


                        unsigned char *m_Array2;
                        m_Array2 = new block_t[252 * 112 * 252];
                        memset(m_Array2, 0, sizeof(unsigned char) * 252 * 252 * 112);

                        for (int x = 0; x < 252; x++) {
                            for (int z = 0; z < 252; z++) {
                                for (int y = 0; y < 112; y++) {
                                    int take_adress = x + z * 252 + y * 252 * 252;
                                    int take_id = m_Array1[take_adress];

                                    int put_adress = x + y * 252 + z * 252 * 112;
                                    int put_id = 0;

                                    if (take_id < id_map.size()) {
                                        put_id = id_map[take_id];
                                    }

                                    m_Array2[put_adress] = put_id;
                                }
                            }
                        }

                        // creating height map
                        unsigned char *m_Heightmap;
                        m_Heightmap = new block_t[252 * 252];
                        memset(m_Heightmap, 0, sizeof(unsigned char) * 252 * 252);

                        for (int x = 0; x < 252; x++) {
                            for (int z = 0; z < 252; z++) {
                                int adress = x + z * 252;
                                for (int y = 111; y >= 0; y--) {
                                    int block_adress = x + y * 252 + z * 252 * 112;
                                    unsigned char &block = m_Array2[block_adress];

                                    if (block == DirtBlock::getID() || block == GrassBlock::getID() ||
                                        block == SandBlock::getID() || block == RockBlock::getID() ||
                                        block == Gravel::getID() || block == SandStone::getID()) {
                                        m_Heightmap[adress] = y;
                                        y = -1;
                                    }
                                }
                            }
                        }

                        // delete caves
                        for (int x = 0; x < 252; x++) {
                            for (int z = 0; z < 252; z++) {
                                int adress = x + z * 252;
                                int height = m_Heightmap[adress];
                                for (int y = 0; y <= height - 1; y++) {
                                    int block_adress = x + y * 252 + z * 252 * 112;
                                    unsigned char &block = m_Array2[block_adress];


                                    if (block != 0) {
                                        if (block != IronBlock::getID() && block != RockBlock::getID() &&
                                            block != DirtBlock::getID() && block != GoldBlock::getID() &&
                                            block != IronOre::getID() && block != LapisOre::getID() &&
                                            block != RedstoneOre::getID()
                                            && block != Lava::getID() && block != WaterBlock::getID() &&
                                            block != RedstoneOre::getID() && block != CoalOre::getID() &&
                                            block != Gravel::getID() && block != DiamondOre::getID()
                                            && block != SandStone::getID() && block != SandBlock::getID() &&
                                            block != Mooshroom1::getID() && block != Mooshroom2::getID()) {
                                            y = 100;
                                            continue;
                                        }
                                    }
                                    if (block == 0 || block == Lava::getID() || block == WaterBlock::getID()) {
                                        block = RockBlock::getID();
                                    }

                                }
                            }
                        }
                        free(m_Heightmap);


                        /// (2) FETCH SCHEMATIC DATA
                        saveFile = gzopen("Converter/world.schematic", "rb");
                        if (saveFile == 0)
                            return;

                        for (int j = 0; j <= 6; j++) {
                            need[j] = '/0';
                        }

                        //data
                        again = false;
                        for (int i = 0; i < 100000000; i++) {
                            for (int j = 1; j <= 5; j++) {
                                need[j - 1] = need[j];
                            }
                            gzread(saveFile, &empty, sizeof(char));
                            need[5] = empty;

                            if (need[0] == 'B' &&
                                need[1] == 'l' &&
                                need[2] == 'o' &&
                                need[3] == 'c' &&
                                need[4] == 'k' &&
                                need[5] == 's') {
                                again = true;
                                i = 100000000;

                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));
                                gzread(saveFile, &empty, sizeof(char));

                                gzread(saveFile, m_Array1, sizeof(unsigned char) * (252 * 112 * 252));

                                break;
                            }

                            if (need[2] == 'D' &&
                                need[3] == 'a' &&
                                need[4] == 't' &&
                                need[5] == 'a') {
                                i = 100000000;
                                break;
                            }
                        }

                        if (again) {
                            memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
                            for (int j = 0; j <= 6; j++) {
                                need[j] = '/0';
                            }

                            for (int i = 0; i < 100000000; i++) {
                                for (int j = 1; j <= 5; j++) {
                                    need[j - 1] = need[j];
                                }
                                gzread(saveFile, &empty, sizeof(char));
                                need[5] = empty;

                                if (need[2] == 'D' &&
                                    need[3] == 'a' &&
                                    need[4] == 't' &&
                                    need[5] == 'a') {
                                    i = 100000000;
                                    break;
                                }
                            }
                        }

                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));
                        gzread(saveFile, &empty, sizeof(char));

                        memset(m_Array1, 0, sizeof(unsigned char) * 252 * 252 * 112);
                        gzread(saveFile, m_Array1, sizeof(unsigned char) * (252 * 112 * 252));

                        gzclose(saveFile);

                        // place correct blocks in our world using schematic blocks data
                        for (int x = 0; x < 252; x++) {
                            for (int z = 0; z < 252; z++) {
                                for (int y = 0; y < 112; y++) {
                                    int address = x + y * 252 + z * 252 * 112;
                                    int data_address = x + z * 252 + y * 252 * 252;
                                    unsigned char &block = m_Array2[address];
                                    unsigned char data = m_Array1[data_address];

                                    if (y < 111) {
                                        int up_address = x + (y + 1) * 252 + z * 252 * 112;
                                        unsigned char &up_block = m_Array2[up_address];

                                        if (up_block == Snow2::getID() &&
                                            (block == GrassBlock::getID() || block == DirtBlock::getID())) {
                                            block = SnowSoil::getID();
                                            continue;
                                        }
                                    }

                                    if (block == LeavesBlock::getID()) {
                                        if (data == 1 || data == 5 || data == 9 || data == 13) {
                                            block = SpruceLeaves::getID();
                                        }
                                        if (data == 2 || data == 6 || data == 10 || data == 14) {
                                            block = BirchLeaves::getID();
                                        }
                                        continue;
                                    }

                                    if (block == OakPlanks::getID()) {
                                        if (data == 1) {
                                            block = SprucePlanks::getID();
                                        }
                                        if (data == 2) {
                                            block = BirchPlanks::getID();
                                        }
                                        continue;
                                    }
                                    if (block == WoodBlock::getID()) {
                                        if (data == 1) {
                                            block = DarkWoodBlock::getID();
                                        }
                                        if (data == 2) {
                                            block = WhiteWoodBlock::getID();
                                        }
                                        continue;
                                    }
                                    if (block == WheatBlock6::getID()) {
                                        if (data == 0) {
                                            block = WheatBlock1::getID();
                                        }
                                        if (data == 1 || data == 2) {
                                            block = WheatBlock2::getID();
                                        }
                                        if (data == 3 || data == 4) {
                                            block = WheatBlock3::getID();
                                        }
                                        if (data >= 5) {
                                            block = WheatBlock4::getID() + (data - 5);
                                        }
                                        continue;
                                    }

                                    if (block == DoubleSlab::getID()) {
                                        if (data == 1) {
                                            block = SandStone::getID();
                                        }
                                        if (data == 2) {
                                            block = OakPlanks::getID();
                                        }
                                        if (data == 3) {
                                            block = CobbleStone::getID();
                                        }
                                        if (data == 4) {
                                            block = BrickBlock::getID();
                                        }
                                        if (data == 5) {
                                            block = StoneBrick::getID();
                                        }
                                        continue;
                                    }
                                    if (block == Slab::getID()) {
                                        if (data == 2) {
                                            block = OakHalfBlock::getID();
                                        }
                                        if (data == 3) {
                                            block = CobbleHalfBlock::getID();
                                        }
                                        if (data == 4) {
                                            block = BrickHalfBlock::getID();
                                        }
                                        if (data == 5) {
                                            block = HalfStoneBrick::getID();
                                        }
                                        continue;
                                    }
                                    if (block == OakHalfBlock::getID()) {
                                        if (data == 1) {
                                            block = SpruceHalfBlock::getID();
                                        }
                                        if (data == 2) {
                                            block = BirchHalfBlock::getID();
                                        }
                                        continue;
                                    }
                                    if (block == StoneBrick::getID()) {
                                        if (data == 2) {
                                            block = CrackedStoneBrick::getID();
                                        }
                                        if (data == 3) {
                                            block = CarvedStoneBrick::getID();
                                        }
                                        continue;
                                    }
                                    if (block == Pumpkin1::getID()) {
                                        block = Pumpkin1::getID() + data;
                                        continue;
                                    }
                                    if (block == WhiteWoolBlock::getID()) {
                                        if (data == 1) {
                                            block = OrangeWoolBlock::getID();
                                        }
                                        if (data == 2) {
                                            block = VioletWoolBlock::getID();
                                        }
                                        if (data == 3) {
                                            block = LightBlueWoolBlock::getID();
                                        }
                                        if (data == 4) {
                                            block = YellowWoolBlock::getID();
                                        }
                                        if (data == 5) {
                                            block = GreenWoolBlock::getID();
                                        }
                                        if (data == 6) {
                                            block = PinkWoolBlock::getID();
                                        }
                                        if (data == 7) {
                                            block = GrayWoolBlock::getID();
                                        }
                                        if (data == 8) {
                                            block = LightGrayWoolBlock::getID();
                                        }
                                        if (data == 9) {
                                            block = PastelWoolBlock::getID();
                                        }
                                        if (data == 10) {
                                            block == VioletWoolBlock::getID();
                                        }
                                        if (data == 11) {
                                            block = BlueWoolBlock::getID();
                                        }
                                        if (data == 12) {
                                            block = BrownWoolBlock::getID();
                                        }
                                        if (data == 13) {
                                            block = DarkGreenWoolBlock::getID();
                                        }
                                        if (data == 14) {
                                            block = RedWoolBlock::getID();
                                        }
                                        if (data == 15) {
                                            block = BlackWoolBlock::getID();
                                        }
                                        continue;
                                    }
                                }
                            }
                        }

                        free(m_Array1);
                        saveFile = 0;

                        /// (2.1) SET SUITABLE PLAYER POSITION

                        Vector3 playerPos = Vector3(128, 69, 128);
                        for (int y = 111; y >= 40; y--) {
                            int address = 128 + y * 252 + 128 * 252 * 112;
                            unsigned char block = m_Array2[address];

                            if (block != 0) {
                                playerPos = Vector3(128.5f, y + 1.7f, 128.5f);
                                break;
                            }
                        }


                        /// (3) SAVE WORLD
                        std::string filename = nextSaveFileName;

                        //first save version and name on normal file
                        FILE *pFile;
                        pFile = fopen(filename.c_str(), "wb");

                        if (pFile == NULL)
                            return;

                        //version
                        int _worldVersion = 150;
                        fwrite(&_worldVersion, sizeof(int), 1, pFile);

                        //game mode
                        fwrite(&newW_gameMode, sizeof(char), 1, pFile);

                        //game mode
                        bool locked = 0;
                        fwrite(&locked, sizeof(bool), 1, pFile);

                        //name
                        char _worldName[50];
                        _worldName[0] = 'C';
                        _worldName[1] = 'o';
                        _worldName[2] = 'n';
                        _worldName[3] = 'v';
                        _worldName[4] = 'e';
                        _worldName[5] = 'r';
                        _worldName[6] = 't';
                        _worldName[7] = 'e';
                        _worldName[8] = 'd';
                        _worldName[9] = 1 + rand() % 126;
                        _worldName[10] = '\0';
                        fwrite(_worldName, sizeof(char), 50, pFile);

                        //close file
                        fclose(pFile);


                        //now save compressed map info
                        filename = filename + "c";

                        saveFile = gzopen(filename.c_str(), "wb");
                        if (saveFile == 0)
                            return;

                        //player pos

                        gzwrite(saveFile, &playerPos.x, sizeof(float));
                        gzwrite(saveFile, &playerPos.y, sizeof(float));
                        gzwrite(saveFile, &playerPos.z, sizeof(float));

                        //player spawn pos
                        Vector3 playerSpawnPointPosition = playerPos;
                        gzwrite(saveFile, &playerSpawnPointPosition.x, sizeof(float));
                        gzwrite(saveFile, &playerSpawnPointPosition.y, sizeof(float));
                        gzwrite(saveFile, &playerSpawnPointPosition.z, sizeof(float));

                        //snow biome pos
                        Vector3 snowBiomePosition = Vector3(0, 0, 0);
                        float snowBiomeRadius = -1;
                        gzwrite(saveFile, &snowBiomePosition.x, sizeof(float));
                        gzwrite(saveFile, &snowBiomePosition.z, sizeof(float));
                        gzwrite(saveFile, &snowBiomeRadius, sizeof(float));

                        //desert biome pos
                        Vector3 desertBiomePosition = Vector3(0, 0, 0);
                        float desertBiomeRadius = -1;
                        gzwrite(saveFile, &desertBiomePosition.x, sizeof(float));
                        gzwrite(saveFile, &desertBiomePosition.z, sizeof(float));
                        gzwrite(saveFile, &desertBiomeRadius, sizeof(float));

                        //size
                        int WORLD_SIZE = 252;
                        gzwrite(saveFile, &WORLD_SIZE, sizeof(int));

                        //size
                        int WORLD_HEIGHT = 112;
                        gzwrite(saveFile, &WORLD_HEIGHT, sizeof(int));

                        //chunksize
                        int CHUNK_SIZE = 14;
                        gzwrite(saveFile, &CHUNK_SIZE, sizeof(int));

                        //cubes
                        gzwrite(saveFile, m_Array2, sizeof(unsigned char) * (WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

                        for (int x = 0; x < 252; x++) {
                            for (int z = 0; z < 252; z++) {
                                for (int y = 0; y < 112; y++) {
                                    m_Array2[z * 112 * 252 + y * 252 + x] = 0;
                                }
                            }
                        }

                        //settings
                        gzwrite(saveFile, m_Array2, sizeof(unsigned char) * (WORLD_SIZE * WORLD_HEIGHT * WORLD_SIZE));

                        float worldDayTime = 12.0f;
                        //world time
                        gzwrite(saveFile, &worldDayTime, sizeof(float));
                        //sun time
                        //gzwrite(saveFile, &sunTime,sizeof(float));

                        gzwrite(saveFile, &mainStatistics, sizeof(st));

                        gzwrite(saveFile, &mainOptions, sizeof(opt));


                        short invId[36];
                        short invAm[36];
                        bool invSt[36];
                        short armorId[4];
                        short armorAm[4];
                        bool armorSt[4];

                        for (int o = 0; o <= 35; o += 1) // ������������� ���������
                        {
                            invAm[o] = -1; // ���������� ����� � ������ = -1 (0)
                            invId[o] = -1; // Id ����� � ������ = -1 (������ �����)
                            invSt[o] = false; // ���� � ������ �� ��������� (�� ���������)
                        }

                        for (int o = 0; o <= 3; o += 1) {
                            armorId[o] = 324 + o;
                            armorAm[o] = -1;
                            armorSt[o] = false;
                        }
                        gzwrite(saveFile, &invId, sizeof(short) * (36));

                        gzwrite(saveFile, &invAm, sizeof(short) * (36));

                        gzwrite(saveFile, &invSt, sizeof(bool) * (36));

                        gzwrite(saveFile, &armorId, sizeof(short) * (4));

                        gzwrite(saveFile, &armorAm, sizeof(short) * (4));

                        gzwrite(saveFile, &armorSt, sizeof(bool) * (4));

                        float HP = 20;
                        gzwrite(saveFile, &HP, sizeof(unsigned int));

                        float HG = 20;
                        gzwrite(saveFile, &HG, sizeof(unsigned int));

                        float OS = 10;
                        gzwrite(saveFile, &OS, sizeof(unsigned int));

                        float brightFactor = 1.0f;
                        gzwrite(saveFile, &brightFactor, sizeof(float));

                        float starsFactor = 0.0f;
                        gzwrite(saveFile, &starsFactor, sizeof(float));

                        int worldSeed = 0;
                        gzwrite(saveFile, &worldSeed, sizeof(int));

                        float skyTime = 112.0f;
                        gzwrite(saveFile, &skyTime, sizeof(float));

                        int savedWeatherType = 0;
                        gzwrite(saveFile, &savedWeatherType, sizeof(int));

                        float savedWeatherDuration = 600 + rand() % 300;
                        gzwrite(saveFile, &savedWeatherDuration, sizeof(float));

                        int null_var = 0;
                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        gzwrite(saveFile, &null_var, sizeof(int));

                        //close file
                        gzclose(saveFile);
                        saveFile = 0;

                        free(m_Array2);
                    }
                }
                if (converterPos == 2) {
                    menuState = 3;
                }
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
                menuState = 3;
            }
        }
            break;
        case 10: {
            if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
                saveSubMenuSelect == 0 ? saveSubMenuSelect = 1 : saveSubMenuSelect = 0;

                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
                saveSubMenuSelect == 1 ? saveSubMenuSelect = 0 : saveSubMenuSelect = 1;

                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
                char worldNameTemp[50];
                for (char i = 0; i <= 49; i++) {
                    worldNameTemp[i] = saveFilesList[loadSavePos].worldName[i];
                }

                int saveVersionTemp = 3;
                char worldGameModeTemp = saveSubMenuSelect;
                bool locked = saveFilesList[loadSavePos].locked;

                FILE *pFile;
                pFile = fopen(saveFilesList[loadSavePos].fileName.c_str(), "wb");

                if (pFile != NULL) {
                    //version
                    fwrite(&saveVersionTemp, sizeof(int), 1, pFile);

                    fwrite(&worldGameModeTemp, sizeof(char), 1, pFile);

                    fwrite(&locked, sizeof(bool), 1, pFile);
                    //name
                    fwrite(worldNameTemp, sizeof(char), 50, pFile);

                    fclose(pFile);
                }

                ScanSaveFiles("Save/");

                if (saveFilesList[loadSavePos].locked == true) {
                    loadSelectPos = 1;
                }

                menuState = 1;
            }
        }
            break;
        case 11://tp
        {
            if (mSystemMgr->KeyPressed(PSP_CTRL_LEFT)) {
                tpSelectPos--;
                if (tpSelectPos < 0) {
                    tpSelectPos = 1;
                }
                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_RIGHT)) {
                tpSelectPos++;
                if (tpSelectPos > 1) {
                    tpSelectPos = 0;
                }
                mSoundMgr->PlayMenuSound();
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER)) {
                tpPos--;
                if (tpPos < tpStart) {
                    tpStart--;
                    tpMax--;

                    if (tpMax < 3) {
                        tpStart = 0;
                        tpMax = 3;
                    }
                }

                if (tpPos < 0) {
                    tpPos = texturePackList.size() - 1;
                    tpMax = tpEnd;
                    tpStart = tpEnd - 3;
                    if (tpStart < 0)
                        tpStart = 0;
                }
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER)) {
                tpPos++;
                if (tpPos == tpMax) {
                    tpStart++;
                    tpMax++;
                    if (tpMax > tpEnd) {
                        tpStart = tpEnd - 3;
                        if (tpStart < 0) {
                            tpStart = 0;
                        }
                        tpMax = tpEnd;
                    }
                }
                if (tpPos >= texturePackList.size()) {
                    tpPos = 0;
                    tpStart = 0;
                    tpMax = 3;
                    if (tpMax > tpEnd)
                        tpMax = tpEnd;
                }
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
                menuState = 0;
            }

            if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
                if (tpSelectPos == 0)//play state
                {
                    if (texturePackList.empty() == false) {
                        TextureHelper::Instance()->SetTexturePack(texturePackList[tpPos].name);
                        tpCurrent = tpPos;
                    }
                }
                if (tpSelectPos == 1)//delete save
                {
                    menuState = 0;
                }
            }
        }
            break;
    }
}

void StateMenu::Update(StateManager *sManager) {


}

void StateMenu::Draw(StateManager *sManager) {
    //start rendering
    mRender->StartFrame(1, 1, 1);

    switch (menuState) {
        case 5://paramateric view
        {

        }
            break;
        case 10://New or load map
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 5; y++) {
                    backSprite->SetPosition(x * 64, y * 64);
                    backSprite->Draw();
                }
            }

            buttonSprite->SetPosition(240, 100);
            buttonSprite->Draw();

            buttonSprite->SetPosition(240, 140);
            buttonSprite->Draw();

            sbuttonSprite->SetPosition(240, 100 + saveSubMenuSelect * 40);
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            if (mRender->GetFontLanguage() == ENGLISH) {
                DrawText(240, 64, GU_COLOR(1, 1, 1, 1), default_size, "Choose Game Mode");

                saveSubMenuSelect == 0 ? DrawText(240, 109, GU_COLOR(1, 1, 0.25, 1), default_size, "Survival")
                                       : DrawText(240, 109, GU_COLOR(1, 1, 1, 1), default_size, "Survival");
                saveSubMenuSelect == 1 ? DrawText(240, 149, GU_COLOR(1, 1, 0.25, 1), default_size, "Creative")
                                       : DrawText(240, 149, GU_COLOR(1, 1, 1, 1), default_size, "Creative");
            }
            if (mRender->GetFontLanguage() == RUSSIAN) {
                DrawText(240, 64, GU_COLOR(1, 1, 1, 1), default_size, "V@berite Igrovo~ Rejim");

                saveSubMenuSelect == 0 ? DrawText(240, 109, GU_COLOR(1, 1, 0.25, 1), default_size, "V@jivanie")
                                       : DrawText(240, 109, GU_COLOR(1, 1, 1, 1), default_size, "V@jivanie");
                saveSubMenuSelect == 1 ? DrawText(240, 149, GU_COLOR(1, 1, 0.25, 1), default_size, "Tvoryeski~")
                                       : DrawText(240, 149, GU_COLOR(1, 1, 1, 1), default_size, "Tvoryeski~");
            }
        }
            break;
        case 11://textures
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 5; y++) {
                    backSprite->SetPosition(x * 64, y * 64);
                    backSprite->Draw();
                }
            }

            //select sprite
            if (texturePackList.size() > 0) {

            }

            for (int i = tpStart; i < tpMax; i++) {
                if (i < texturePackList.size()) {
                    sceGuEnable(GU_BLEND);

                    rectFilledSprite->SetPosition(240, 56 - 8 + (tpCurrent * 72) - (tpStart * 72));

                    if (i == tpCurrent) {
                        rectFilledSprite->Draw();
                    }

                    rectEmptySprite->SetPosition(240, 56 - 8 + (tpPos * 72) - (tpStart * 72));
                    if (i == tpPos) {
                        sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
                        rectEmptySprite->Draw();
                        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
                    }

                    Sprite *DrawSprite = texturePackList[i].packSprite;
                    DrawSprite->SetPosition(46, 56 - 8 + (i * 72) - (tpStart * 72));
                    DrawSprite->ConstDraw();

                    sceGuDisable(GU_BLEND);

                    mRender->SetFont(ENGLISH);
                    if (i == tpPos) {
                        mRender->SetFontStyle(default_big_size, GU_COLOR(0.25, 0.25, 0, 1), 0, 0x00000000);
                        mRender->DebugPrint(94, 52 - 8 + (i * 72) - (tpStart * 72), "%s",
                                            texturePackList[i].name.c_str());

                        mRender->SetFontStyle(default_big_size, GU_COLOR(1, 1, 0, 1), 0, 0x00000000);
                        mRender->DebugPrint(92, 50 - 8 + (i * 72) - (tpStart * 72), "%s",
                                            texturePackList[i].name.c_str());

                        mRender->SetFontStyle(default_size, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                        mRender->DebugPrint(92, 50 - 8 + (i * 72) - (tpStart * 72) + 18, "%s",
                                            texturePackList[i].description.c_str());
                    } else {
                        mRender->SetFontStyle(default_big_size, GU_COLOR(0.25, 0.25, 0.25, 1), 0, 0x00000000);
                        mRender->DebugPrint(94, 52 - 8 + (i * 72) - (tpStart * 72), "%s",
                                            texturePackList[i].name.c_str());

                        mRender->SetFontStyle(default_big_size, GU_COLOR(1, 1, 1, 1), 0, 0x00000000);
                        mRender->DebugPrint(92, 50 - 8 + (i * 72) - (tpStart * 72), "%s",
                                            texturePackList[i].name.c_str());

                        mRender->SetFontStyle(default_size, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                        mRender->DebugPrint(92, 50 - 8 + (i * 72) - (tpStart * 72) + 18, "%s",
                                            texturePackList[i].description.c_str());
                    }
                    mRender->SetDefaultFont();
                }
            }


            buttonSprite->SetPosition(120, 254);
            buttonSprite->Draw();

            buttonSprite->SetPosition(360, 254);
            buttonSprite->Draw();


            sbuttonSprite->SetPosition(120 + (tpSelectPos * 240), 254);
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            if (mRender->GetFontLanguage() == ENGLISH) {
                tpSelectPos == 0 ? DrawText(120, 263, GU_COLOR(1, 1, 0.25, 1), default_size, "Select") : DrawText(120,
                                                                                                                  263,
                                                                                                                  GU_COLOR(
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1),
                                                                                                                  default_size,
                                                                                                                  "Select");
                tpSelectPos == 1 ? DrawText(360, 263, GU_COLOR(1, 1, 0.25, 1), default_size, "Cancel") : DrawText(360,
                                                                                                                  263,
                                                                                                                  GU_COLOR(
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1),
                                                                                                                  default_size,
                                                                                                                  "Cancel");
            }
            if (mRender->GetFontLanguage() == RUSSIAN) {
                tpSelectPos == 0 ? DrawText(120, 263, GU_COLOR(1, 1, 0.25, 1), default_size, "V@brat$") : DrawText(120,
                                                                                                                   263,
                                                                                                                   GU_COLOR(
                                                                                                                           1,
                                                                                                                           1,
                                                                                                                           1,
                                                                                                                           1),
                                                                                                                   default_size,
                                                                                                                   "V@brat$");
                tpSelectPos == 1 ? DrawText(360, 263, GU_COLOR(1, 1, 0.25, 1), default_size, "Otmena") : DrawText(360,
                                                                                                                  263,
                                                                                                                  GU_COLOR(
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1,
                                                                                                                          1),
                                                                                                                  default_size,
                                                                                                                  "Otmena");
            }
        }
            break;
    }

    //mRender->SetFontStyle(0.5f,GU_COLOR(1,1,1,1),0,0x00000000);
    //mRender->DebugPrint(30,50,"%f",size_f);

    //draw debug text at the end
    /*mRender->DebugPrint(40,30,"cpu: %d%%",mRender->GetCpuUsage());
    mRender->DebugPrint(40,40,"gpu: %d%%",mRender->GetGpuUsage());
    mRender->DebugPrint(40,50,"saves: %d",saveFilesList.size());*/

    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000400);
    //mRender->DebugPrint(475,15,"CraftSite.pl Edition");
    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);

    //end frame
    mRender->EndFrame();
}

//additional functions
void StateMenu::ScanSaveFiles(const char *dirName) {
    //clear list with save files
    saveFilesList.clear();

    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(dirName);

    while ((DirEntry = readdir(Dir)) != NULL) {
        if (DirEntry->d_stat.st_attr & FIO_SO_IFREG) // we found file
        {
            SaveFile newSaveFile;
            std::string plik = dirName;
            plik += DirEntry->d_name;
            //dont load lmsc files
            size_t found = plik.find(".lmsc");
            size_t found2 = plik.find(".LMSc");
            if (found == std::string::npos && found2 == std::string::npos) {
                newSaveFile.fileName = plik;
                saveFilesList.push_back(newSaveFile);
            }
        }
    }

    closedir(Dir);


    //now update all info in save files
    for (unsigned int i = 0; i < saveFilesList.size(); i++) {
        FILE *pFile;
        pFile = fopen(saveFilesList[i].fileName.c_str(), "rb");

        if (pFile != NULL) {
            //version
            fread(&saveFilesList[i].saveVersion, sizeof(int), 1, pFile);

            fread(&saveFilesList[i].worldGameMode, sizeof(char), 1, pFile);

            fread(&saveFilesList[i].locked, sizeof(bool), 1, pFile);
            //name
            fread(saveFilesList[i].worldName, sizeof(char), 50, pFile);

            if (saveFilesList[i].saveVersion >= 2)
                saveFilesList[i].compression = true;
            else
                saveFilesList[i].compression = false;

            fclose(pFile);
        }

        saveFilesList[i].saveSize = fileSize(saveFilesList[i].fileName + "c");
    }

    //set next save name and numer
    nextSaveFileNumber = saveFilesList.size() + 1;
    {
        //ride thru all saves and check if i can use new name
        char liczba[3];
        sprintf(liczba, "%d", nextSaveFileNumber);
        nextSaveFileName = "Save/world";
        nextSaveFileName += liczba;
        nextSaveFileName += ".lms";

        for (unsigned int i = 0; i < saveFilesList.size(); i++) {
            if (nextSaveFileName.compare(saveFilesList[i].fileName) == 0) {
                nextSaveFileNumber += 1;
                char liczba[3];
                sprintf(liczba, "%d", nextSaveFileNumber);
                nextSaveFileName = "Save/world";
                nextSaveFileName += liczba;
                nextSaveFileName += ".lms";

                /* if (newWorldName == "World")
                {
                    newWorldName += liczba;
                } */
            }
        }
    }
}

void StateMenu::ScanTexturePacks(const char *dirName) {
    if (texturePackList.empty() != false) {
        TextureHelper::Instance()->RemoveConstTextures();
        for (int j = 0; j < texturePackList.size(); j++) {
            if (texturePackList[j].packSprite != NULL) {
                delete texturePackList[j].packSprite;
            }
        }
        texturePackList.clear();
    }
    texturePackList.clear();

    TextureManager::Instance()->LoadConstTexture("Assets/unknown_pack.png");

    int TPcheck = 0;

    DIR *dir = opendir(dirName);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (FIO_SO_ISDIR(entry->d_stat.st_attr)) {
            std::string plik = "";
            plik += entry->d_name;

            size_t found = plik.find(".");
            size_t found2 = plik.find("..");
            size_t found3 = plik.find(".svn");

            if (found == std::string::npos && found2 == std::string::npos && found3 == std::string::npos)//�� �������
            {
                TP newTP;

                std::string plik2 = plik + "/";
                if (plik2 == TextureHelper::Instance()->defaultFolder) {
                    tpCurrent = TPcheck;
                }

                newTP.name = plik;

                texturePackList.push_back(newTP);
                TPcheck++;
            }
        }
    }

    closedir(dir);

    for (int j = 0; j < texturePackList.size(); j++) {
        std::string packPath = "Assets/Textures/" + texturePackList[j].name + "/pack.png";

        if (fileExists(packPath) == true) // if we have pack sprite
        {
            TextureManager::Instance()->LoadConstTexture(packPath);
            texturePackList[j].packSprite = new Sprite(TextureManager::Instance()->GetConstTextureNumber(packPath),
                                                       true);
        } else {
            texturePackList[j].packSprite = new Sprite(
                    TextureManager::Instance()->GetConstTextureNumber("Assets/unknown_pack.png"), true);
        }

        std::string packDescriptionPath = "Assets/Textures/" + texturePackList[j].name + "/pack.txt";

        if (fileExists(packDescriptionPath) == true) // if we have pack description file
        {
            std::string str;
            std::string file_contents;

            std::ifstream file(packDescriptionPath.c_str());

            if (file.is_open()) {
                while (std::getline(file, str)) {
                    file_contents += str;
                    file_contents.push_back('\n');
                }
            }

            file.close();
            texturePackList[j].description = file_contents;
        }
    }
}

/*
    texturePackList.clear();

	FILE *infile;
	char textLine[80];
	char textPack[80];

	infile = fopen("Assets/texturePacks.txt","rt");

	 while(fgets(textLine, 80, infile) != NULL)
	 {
		 sscanf(textLine,"%s",textPack);
		 std::string texturePack = textPack;

		 size_t found = texturePack.find(".tp");
		 size_t found2 = texturePack.find(".TP");
		 if(found != std::string::npos || found2 != std::string::npos)// found
		 {
		 	texturePackList.push_back(texturePack);
		 }
	 }
	 fclose(infile);

*/

inline bool StateMenu::fileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

unsigned int StateMenu::hash(const char *s, unsigned int seed) {
    unsigned int hash = seed;
    while (*s) {
        hash = hash * 101 + *s++;
    }
    return hash;
}

int StateMenu::fileSize(const std::string &name) {
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int) stat_buf.st_size : -1;
}

void StateMenu::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}
