#include "StateWorldSelect.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateMainMenu.h"
#include "states/menu/StateNewWorld.h"
#include "states/StatePlay.h"
#include "states/StatePlayCreative.h"
#include <vector>
#include <string>

using std::string;

#define default_size 0.5
#define default_big_size 0.687
#define PI 3.1415926535897f

#define ENGLISH 1
#define RUSSIAN 2

#define SURVIVAL 0
#define CREATIVE 1
#define HARDCORE 2

StateWorldSelect::StateWorldSelect() {

}

StateWorldSelect::~StateWorldSelect() {

}

void StateWorldSelect::Init() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();
    // Translation* translation = Translation::GetInstance();

    //texts = translation->getTranslationsOfType("ABOUT");

    selectPos = 0;

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

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo), 0, 0, 256, 64);
    logoSprite->Scale(1.5f, 1.5f);
    logoSprite->SetPosition(240, 50);

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

    ScanSaveFiles("Save/");

    loadSavePos = 0;
    loadSaveStart = 0;
    loadSaveEnd = saveFilesList.size();
    loadSaveMax = 4;
    if (loadSaveMax > loadSaveEnd)
       loadSaveMax = loadSaveEnd;

    menuState = 1;
    if (saveFilesList.empty() == false) {
       loadSelectPos = 0;
    } else {
       loadSelectPos = 3;
    }
}

void StateWorldSelect::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateWorldSelect::CleanUp() {}

void StateWorldSelect::Pause() {}

void StateWorldSelect::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateWorldSelect::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (saveSubmenu) {
        if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
            saveSubMenuSelect--;
            if (saveSubMenuSelect < 1)
                saveSubMenuSelect = 2;

            mSoundMgr->PlayMenuSound();
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
            saveSubMenuSelect++;
            if (saveSubMenuSelect > 2)
                saveSubMenuSelect = 1;

            mSoundMgr->PlayMenuSound();
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
            if (saveSubMenuSelect == 1)//remove file
            {
                //remove file
                if (saveFilesList.size() > 0) {
                    if (saveFilesList[loadSavePos].compression) {
                        //remove normal file
                        remove(saveFilesList[loadSavePos].fileName.c_str());

                        //remove compressed one
                        saveFilesList[loadSavePos].fileName += "c";
                        remove(saveFilesList[loadSavePos].fileName.c_str());

                    } else {
                        remove(saveFilesList[loadSavePos].fileName.c_str());
                    }

                    ScanSaveFiles("Save/");

                    loadSavePos = 0;
                    loadSaveStart = 0;
                    loadSaveEnd = saveFilesList.size();
                    loadSaveMax = 4;
                    if (loadSaveMax > loadSaveEnd)
                        loadSaveMax = loadSaveEnd;

                    saveSubmenu = false;
                    saveSubMenuSelect = 2;

                    if (saveFilesList.empty() == false) {
                        loadSelectPos = 0;
                    } else {
                        loadSelectPos = 2;
                    }
                }
            }
            if (saveSubMenuSelect == 2)//return
            {
                saveSubMenuSelect = 2;
                saveSubmenu = false;
            }
        }
    } else {
        if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
            if (loadSelectPos == 1 || loadSelectPos == 2) {
                loadSelectPos = 0;
                mSoundMgr->PlayMenuSound();
            }
            if (loadSelectPos == 4) {
                loadSelectPos = 3;
                mSoundMgr->PlayMenuSound();
            }
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
            if (loadSelectPos == 0 || loadSelectPos == 3) {
                loadSelectPos++;
                mSoundMgr->PlayMenuSound();
            }
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_LEFT)) {
            if (saveFilesList.empty() == false) {
                switch (loadSelectPos) {
                    case 2:
                        loadSelectPos = 1;
                        mSoundMgr->PlayMenuSound();
                        break;
                    case 3:
                        loadSelectPos = 0;
                        mSoundMgr->PlayMenuSound();
                        break;
                    case 4:
                        loadSelectPos = 2;
                        mSoundMgr->PlayMenuSound();
                        break;
                }
            }
        }


        if (mSystemMgr->KeyPressed(PSP_CTRL_RIGHT)) {
            switch (loadSelectPos) {
                case 0:
                    loadSelectPos = 3;
                    mSoundMgr->PlayMenuSound();
                    break;
                case 1:
                    loadSelectPos = 2;
                    mSoundMgr->PlayMenuSound();
                    break;
                case 2:
                    loadSelectPos = 4;
                    mSoundMgr->PlayMenuSound();
                    break;
            }
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER)) {
            if (saveFilesList.empty() == false) {
                loadSavePos--;

                if (loadSavePos < loadSaveStart) {
                    loadSaveStart--;
                    loadSaveMax--;

                    if (loadSaveMax < 4) {
                        loadSaveStart = 0;
                        loadSaveMax = 4;
                    }
                }

                if (loadSavePos < 0) {
                    loadSavePos = saveFilesList.size() - 1;
                    loadSaveMax = loadSaveEnd;
                    loadSaveStart = loadSaveEnd - 4;
                    if (loadSaveStart < 0)
                        loadSaveStart = 0;
                }
            }
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER)) {
            if (saveFilesList.empty() == false) {
                loadSavePos++;
                if (loadSavePos == loadSaveMax) {
                    loadSaveStart++;
                    loadSaveMax++;
                    if (loadSaveMax > loadSaveEnd) {
                        loadSaveStart = loadSaveEnd - 4;
                        if (loadSaveStart < 0)
                            loadSaveStart = 0;
                        loadSaveMax = loadSaveEnd;
                    }
                }
                if (loadSavePos >= saveFilesList.size()) {
                    loadSavePos = 0;
                    loadSaveStart = 0;
                    loadSaveMax = 4;
                    if (loadSaveMax > loadSaveEnd)
                        loadSaveMax = loadSaveEnd;
                }
            }
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
            menuState = 0;
        }

        if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
            if (loadSelectPos == 0)//play selected world
            {
                if (saveFilesList.size() > 0) {
                    if (saveFilesList[loadSavePos].locked == false) {
                        if (saveFilesList[loadSavePos].worldGameMode == SURVIVAL ||
                            saveFilesList[loadSavePos].worldGameMode == HARDCORE) {
                            StatePlay *statePlay = new StatePlay();
                            statePlay->LoadMap(saveFilesList[loadSavePos].fileName,
                                               saveFilesList[loadSavePos].compression);
                            statePlay->InitCamera();
                            sManager->PushState(statePlay);
                        } else {
                            StatePlayCreative *statePlay = new StatePlayCreative();
                            statePlay->LoadMap(saveFilesList[loadSavePos].fileName,
                                               saveFilesList[loadSavePos].compression);
                            statePlay->InitCamera();
                            sManager->PushState(statePlay);
                        }
                    }
                }
            }
            if (loadSelectPos == 1)//rename world
            {
                if (saveFilesList.size() > 0) {
                    char worldNameTemp[50];

                    unsigned short test[128];
                    unsigned short opis[10] = {'W', 'o', 'r', 'l', 'd', ' ', 'n', 'a', 'm', 'e'};
                    if (mSystemMgr->ShowOSK(opis, test, 128) != -1) {
                        std::string newWorldName = "";
                        for (int j = 0; test[j]; j++) {
                            unsigned c = test[j];

                            if (32 <= c && c <= 127) // print ascii only
                                newWorldName += c;
                        }

                        sprintf(worldNameTemp, "%s", newWorldName.c_str());
                    }

                    int saveVersionTemp = 3;
                    char worldGameModeTemp = saveFilesList[loadSavePos].worldGameMode;
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
                }
            }
            if (loadSelectPos == 2)//delete world
            {
                if (saveFilesList.size() > 0) {
                    saveSubmenu = true;
                    saveSubMenuSelect = 2;
                }
            }
            if (loadSelectPos == 3)//create new world
            {
                StateNewWorld *stateNewWorld = new StateNewWorld();
                stateNewWorld->Init();
                sManager->PushState(stateNewWorld);
            }
            if (loadSelectPos == 4)//cancel
            {
                sManager->PopState();
            }
        }
    }
}

void StateWorldSelect::Update(StateManager *sManager) {}

void StateWorldSelect::Draw(StateManager *sManager) {
    mRender->StartFrame(1, 1, 1);

    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

    menuHelper->drawDirtBackground();

    if (saveSubmenu) // delete world
    {
        buttonSprite->SetPosition(240, 235);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240, 260);
        buttonSprite->Draw();
    } else {
        /// left part
        if (saveFilesList.empty() == false) {
            buttonSprite->SetPosition(120, 222); // play selected world
            buttonSprite->Draw();

            buttonSmallSprite->SetPosition(67.75, 255); // rename
            buttonSmallSprite->Draw();

            buttonSmallSprite->SetPosition(172.25, 255); // delete
            buttonSmallSprite->Draw();
        } else {
            nbuttonSprite->SetPosition(120, 222); // play selected world
            nbuttonSprite->Draw();

            nbuttonSmallSprite->SetPosition(67.75, 255); // rename
            nbuttonSmallSprite->Draw();

            nbuttonSmallSprite->SetPosition(172.25, 255); // delete
            nbuttonSmallSprite->Draw();
        }

        ///right part
        buttonSprite->SetPosition(360, 222); // create new world
        buttonSprite->Draw();

        buttonSprite->SetPosition(360, 255); // cancel
        buttonSprite->Draw();
    }


    bool smallButton = false;
    if (saveSubmenu) {
        sbuttonSprite->SetPosition(240, (saveSubMenuSelect * 25) + 210);
    } else {
        switch (loadSelectPos) {
            case 0:
                sbuttonSprite->SetPosition(120, 222);
                break;
            case 1:
                sbuttonSmallSprite->SetPosition(67.75, 255);
                smallButton = true;
                break;
            case 2:
                sbuttonSmallSprite->SetPosition(172.25, 255);
                smallButton = true;
                break;
            case 3:
                sbuttonSprite->SetPosition(360, 222);
                break;
            case 4:
                sbuttonSprite->SetPosition(360, 255);
                break;
        }
    }
    smallButton == true ? sbuttonSmallSprite->Draw() : sbuttonSprite->Draw();

    blackBackground->Draw();

    //select sprite
    if (saveFilesList.size() > 0) {
        //save files
        for (int i = loadSaveStart; i < loadSaveMax; i++) {
            if (loadSavePos == i) {
                mRender->SetFont(ENGLISH);
                if (saveFilesList[i].worldName[0] != '\0') {
                    mRender->SetFontStyle(0.8f, GU_COLOR(1, 1, 0, 1), 0, 0x00000000);
                    mRender->DebugPrint(30, 54 + (i * 41) - (loadSaveStart * 41), "%s",
                                        saveFilesList[i].worldName);
                } else {
                    mRender->SetFontStyle(0.8f, GU_COLOR(0.6, 0.6, 0, 1), 0, 0x00000000);
                    mRender->DebugPrint(30, 54 + (i * 41) - (loadSaveStart * 41), "<no name>");
                }

                mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                mRender->DebugPrint(30, 66 + (i * 41) - (loadSaveStart * 41), "%s",
                                    saveFilesList[i].fileName.c_str());

                mRender->SetDefaultFont();

                if (mRender->GetFontLanguage() == ENGLISH) {
                    switch (saveFilesList[i].worldGameMode) {
                        case 0:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Survival mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                        case 1:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Creative mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                        case 2:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Hardcore mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                    }
                }
                if (mRender->GetFontLanguage() == RUSSIAN) {
                    switch (saveFilesList[i].worldGameMode) {
                        case 0:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "V@jivanie (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                        case 1:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "Tvoryeski~ (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                        case 2:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "Hardkor (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                    }
                }
            } else {
                mRender->SetFont(ENGLISH);

                if (saveFilesList[i].worldName[0] != '\0') {
                    mRender->SetFontStyle(0.8f, GU_COLOR(1, 1, 1, 1), 0, 0x00000000);
                    mRender->DebugPrint(30, 54 + (i * 41) - (loadSaveStart * 41), "%s",
                                        saveFilesList[i].worldName);
                } else {
                    mRender->SetFontStyle(0.8f, GU_COLOR(0.6, 0.6, 0.6, 1), 0, 0x00000000);
                    mRender->DebugPrint(30, 54 + (i * 41) - (loadSaveStart * 41), "<no name>");
                }

                mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                mRender->DebugPrint(30, 66 + (i * 41) - (loadSaveStart * 41), "%s",
                                    saveFilesList[i].fileName.c_str());

                mRender->SetDefaultFont();

                if (mRender->GetFontLanguage() == ENGLISH) {
                    switch (saveFilesList[i].worldGameMode) {
                        case 0:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Survival mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                        case 1:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Creative mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                        case 2:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41),
                                                "Hardcore mode (%i KB)", saveFilesList[i].saveSize / 1024);
                            break;
                    }
                }

                if (mRender->GetFontLanguage() == RUSSIAN) {
                    switch (saveFilesList[i].worldGameMode) {
                        case 0:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "V@jivanie (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                        case 1:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "Tvoryeski~ (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                        case 2:
                            mRender->SetFontStyle(0.5f, GU_COLOR(0.5, 0.5, 0.5, 1), 0, 0x00000000);
                            mRender->DebugPrint(30, 78 + (i * 41) - (loadSaveStart * 41), "Hardkor (%i KB)",
                                                saveFilesList[i].saveSize / 1024);
                            break;
                    }
                }
            }
        }
    }

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    if (mRender->GetFontLanguage() == ENGLISH) {
        if (saveSubmenu) {
            saveSubMenuSelect == 0 ? DrawText(240, 219, GU_COLOR(1, 1, 0.25, 1), default_size, "Are you sure?")
                                   : DrawText(240, 219, GU_COLOR(1, 1, 1, 1), default_size, "Are you sure?");
            saveSubMenuSelect == 1 ? DrawText(240, 244, GU_COLOR(1, 1, 0.25, 1), default_size, "Yes")
                                   : DrawText(240, 244, GU_COLOR(1, 1, 1, 1), default_size, "Yes");
            saveSubMenuSelect == 2 ? DrawText(240, 269, GU_COLOR(1, 1, 0.25, 1), default_size, "No") : DrawText(
                    240, 269, GU_COLOR(1, 1, 1, 1), default_size, "No");
        } else {
            float buttonTextColor = 1.0f; // for left part
            if (saveFilesList.empty() == true) {
                buttonTextColor = 0.5f;
            }

            loadSelectPos == 0 ? DrawText(120, 231, GU_COLOR(1, 1, 0.25, 1), default_size,
                                          "Play Selected World") : DrawText(120, 231, GU_COLOR(buttonTextColor,
                                                                                               buttonTextColor,
                                                                                               buttonTextColor,
                                                                                               1), default_size,
                                                                            "Play Selected World");
            loadSelectPos == 1 ? DrawText(67.75f, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Rename")
                               : DrawText(67.75f, 264,
                                          GU_COLOR(buttonTextColor, buttonTextColor, buttonTextColor, 1),
                                          default_size, "Rename");
            loadSelectPos == 2 ? DrawText(172.25f, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Delete")
                               : DrawText(172.25f, 264,
                                          GU_COLOR(buttonTextColor, buttonTextColor, buttonTextColor, 1),
                                          default_size, "Delete");
            loadSelectPos == 3 ? DrawText(360, 231, GU_COLOR(1, 1, 0.25, 1), default_size, "Create New World")
                               : DrawText(360, 231, GU_COLOR(1.0f, 1.0f, 1.0f, 1), default_size,
                                          "Create New World");
            loadSelectPos == 4 ? DrawText(360, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Cancel") : DrawText(
                    360, 264, GU_COLOR(1.0f, 1.0f, 1.0f, 1), default_size, "Cancel");
        }
        DrawText(240, 24, GU_COLOR(1, 1, 1, 1), default_size, "Select World");
    }

    if (mRender->GetFontLanguage() == RUSSIAN) {
        if (saveSubmenu) {
            saveSubMenuSelect == 0 ? DrawText(240, 219, GU_COLOR(1, 1, 0.25, 1), default_size, "V@ uveren@?")
                                   : DrawText(240, 219, GU_COLOR(1, 1, 1, 1), default_size, "V@ uveren@?");
            saveSubMenuSelect == 1 ? DrawText(240, 244, GU_COLOR(1, 1, 0.25, 1), default_size, "Da") : DrawText(
                    240, 244, GU_COLOR(1, 1, 1, 1), default_size, "Da");
            saveSubMenuSelect == 2 ? DrawText(240, 269, GU_COLOR(1, 1, 0.25, 1), default_size, "Net")
                                   : DrawText(240, 269, GU_COLOR(1, 1, 1, 1), default_size, "Net");
        } else {
            float buttonTextColor = 1.0f; // for left part
            if (saveFilesList.empty() == true) {
                buttonTextColor = 0.5f;
            }

            loadSelectPos == 0 ? DrawText(120, 231, GU_COLOR(1, 1, 0.25, 1), default_size,
                                          "Igrat$ v v@brannom mire") : DrawText(120, 231,
                                                                                GU_COLOR(buttonTextColor,
                                                                                         buttonTextColor,
                                                                                         buttonTextColor, 1),
                                                                                default_size,
                                                                                "Igrat$ v v@brannom mire");
            loadSelectPos == 1 ? DrawText(67.75f, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Pereimenovat$")
                               : DrawText(67.75f, 264,
                                          GU_COLOR(buttonTextColor, buttonTextColor, buttonTextColor, 1),
                                          default_size, "Pereimenovat$");
            loadSelectPos == 2 ? DrawText(172.25f, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Udalit$")
                               : DrawText(172.25f, 264,
                                          GU_COLOR(buttonTextColor, buttonTextColor, buttonTextColor, 1),
                                          default_size, "Udalit$");
            loadSelectPos == 3 ? DrawText(360, 231, GU_COLOR(1, 1, 0.25, 1), default_size, "Sozdat$ nov@~ mir")
                               : DrawText(360, 231, GU_COLOR(1.0f, 1.0f, 1.0f, 1), default_size,
                                          "Sozdat$ nov@~ mir");
            loadSelectPos == 4 ? DrawText(360, 264, GU_COLOR(1, 1, 0.25, 1), default_size, "Otmena") : DrawText(
                    360, 264, GU_COLOR(1.0f, 1.0f, 1.0f, 1), default_size, "Otmena");
        }
        DrawText(240, 24, GU_COLOR(1, 1, 1, 1), default_size, "V@bor mira");
    }

    mRender->EndFrame();
}

int StateWorldSelect::fileSize(const std::string &name) {
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int) stat_buf.st_size : -1;
}

void StateWorldSelect::ScanSaveFiles(const char *dirName) {
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

void StateWorldSelect::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}
