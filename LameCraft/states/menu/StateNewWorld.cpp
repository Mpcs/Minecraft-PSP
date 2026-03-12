#include "StateNewWorld.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateMainMenu.h"
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

StateNewWorld::StateNewWorld() {
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

    generateSelectPose = 0;
    menuState = 5;

    makeTrees = true;
    makeWater = true;
    makeCaves = true;
    terrainBuilder = 0;
    worldType = 0;

    newWorldName = "New World";
    newWorldSeed = "";
}

StateNewWorld::~StateNewWorld() {

}

void StateNewWorld::Init() {

}

void StateNewWorld::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateNewWorld::CleanUp() {}

void StateNewWorld::Pause() {}

void StateNewWorld::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateNewWorld::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();



    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        mSoundMgr->PlayMenuSound();

        if (generateSelectPose == 0) {
            generateSelectPose = 4;
            return;
        }

        generateSelectPose--;
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        mSoundMgr->PlayMenuSound();
        if (generateSelectPose == 4) {
            generateSelectPose = 0;
            return;
        }
        generateSelectPose++;

    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
        ScanSaveFiles("Save/");

        menuState = 1;
        loadSavePos = 0;
        loadSaveStart = 0;
        loadSaveEnd = saveFilesList.size();
        loadSaveMax = 4;
        if (loadSaveMax > loadSaveEnd)
            loadSaveMax = loadSaveEnd;

        menuState = 1;

        loadSelectPos = 3;
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        if (generateSelectPose == 0) {
            newWorldName = "";

            unsigned short test[128];
            unsigned short opis[10] = {'W', 'o', 'r', 'l', 'd', ' ', 'n', 'a', 'm', 'e'};
            if (mSystemMgr->ShowOSK(opis, test, 128) != -1) {
                for (int j = 0; j < 14; j++) {
                    unsigned c = test[j];

                    if (32 <= c && c <= 127) // print ascii only
                        newWorldName += c;
                }
            }
            newWorldNamestr = newWorldName.c_str();
        }

        if (generateSelectPose == 1) {
            seed_1 = 0;
            newWorldSeed = "";

            unsigned short test[128];
            unsigned short opis[10] = {'W', 'o', 'r', 'l', 'd', ' ', 's', 'e', 'e', 'd'};
            if (mSystemMgr->ShowOSK(opis, test, 128) != -1) {

                for (int j = 0; j < 14; j++) {
                    unsigned c = test[j];

                    if (c >= 32 && c <= 127) {
                        newWorldSeed += c;
                    }
                }
                seed_1 = hash(newWorldSeed.c_str(), 0);
                //seed_1 = std::atoi(newWorldSeed.c_str());
            }
        }


        if (generateSelectPose == 2) {
            gameMode += 1;
            if (gameMode == 3) {
                gameMode = 0;
            }
        }

        if (generateSelectPose == 3) {
            worldType += 1;
            if (worldType > 1) {
                worldType = 0;
            }
        }

        if (generateSelectPose == 4) {
            //terrainBuilder = 2;
            sManager->PopState();
            if (gameMode == 0 || gameMode == 2) {
                StatePlay *statePlay = new StatePlay();
                statePlay->InitParametric(makeTrees, makeWater, makeCaves, seed_1, worldType, gameMode);
                statePlay->InitCamera();
                statePlay->SetWorldAndSaveName(newWorldName, nextSaveFileName);
                sManager->PushState(statePlay);
            } else {
                StatePlayCreative *statePlay = new StatePlayCreative();
                statePlay->InitParametric(makeTrees, makeWater, makeCaves, seed_1, worldType, gameMode);
                statePlay->InitCamera();
                statePlay->SetWorldAndSaveName(newWorldName, nextSaveFileName);
                sManager->PushState(statePlay);
            }
            seed_1 = 0;
        }
    }
}

void StateNewWorld::Update(StateManager *sManager) {}

void StateNewWorld::Draw(StateManager *sManager) {
    mRender->StartFrame(1, 1, 1);



                sceGuDisable(GU_DEPTH_TEST);
                sceGuEnable(GU_BLEND);
                sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 5; y++) {
                        backSprite->SetPosition(x * 64, y * 64);
                        backSprite->Draw();
                    }
                }


                //name
                mbuttonSprite->SetPosition(240, 70);
                mbuttonSprite->Draw();
                //seed
                mbuttonSprite->SetPosition(240, 110);
                mbuttonSprite->Draw();

                buttonSprite->SetPosition(240, 150);
                buttonSprite->Draw();

                buttonSprite->SetPosition(240, 190);
                buttonSprite->Draw();

                buttonSprite->SetPosition(240, 230);
                buttonSprite->Draw();

                if (generateSelectPose > 1) {
                    sbuttonSprite->SetPosition(240, 150 + (generateSelectPose - 2) * 40);
                    sbuttonSprite->Draw();
                }
                if (generateSelectPose <= 1) {
                    smbuttonSprite->SetPosition(240, 70 + generateSelectPose * 40);
                    smbuttonSprite->Draw();
                }

                sceGuDisable(GU_BLEND);
                sceGuEnable(GU_DEPTH_TEST);

                if (mRender->GetFontLanguage() == ENGLISH) {
                    DrawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, "Create New World");
                    DrawText(240, 58, GU_COLOR(0.25, 0.25, 0.25, 1), default_size, "Name");
                    DrawText(240, 98, GU_COLOR(0.25, 0.25, 0.25, 1), default_size, "Seed");

                    //draw subtitles on buttons
                    if (gameMode == SURVIVAL) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Game Mode: Survival") : DrawText(240, 159, GU_COLOR(1, 1, 1, 1),
                                                                                             default_size,
                                                                                             "Game Mode: Survival");
                    }
                    if (gameMode == CREATIVE) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Game Mode: Creative") : DrawText(240, 159, GU_COLOR(1, 1, 1, 1),
                                                                                             default_size,
                                                                                             "Game Mode: Creative");
                    }
                    if (gameMode == HARDCORE) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Game Mode: Hardcore") : DrawText(240, 159, GU_COLOR(1, 1, 1, 1),
                                                                                             default_size,
                                                                                             "Game Mode: Hardcore");
                    }

                    if (worldType == 0) {
                        generateSelectPose == 3 ? DrawText(240, 199, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "World Type : Default") : DrawText(240, 199,
                                                                                              GU_COLOR(1, 1, 1, 1),
                                                                                              default_size,
                                                                                              "World Type : Default");
                    }
                    if (worldType == 1) {
                        generateSelectPose == 3 ? DrawText(240, 199, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "World Type : Flat") : DrawText(240, 199, GU_COLOR(1, 1, 1, 1),
                                                                                           default_size,
                                                                                           "World Type : Flat");
                    }

                    generateSelectPose == 4 ? DrawText(240, 239, GU_COLOR(1, 1, 0.25, 1), default_size, "Create New World")
                                            : DrawText(240, 239, GU_COLOR(1, 1, 1, 1), default_size, "Create New World");
                }
                if (mRender->GetFontLanguage() == RUSSIAN) {
                    DrawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, "Sozdat$ nov@~ mir");
                    DrawText(240, 58, GU_COLOR(0.25, 0.25, 0.25, 1), default_size, "Nazvanie Mira");
                    DrawText(240, 98, GU_COLOR(0.25, 0.25, 0.25, 1), default_size, "Sid Mira");

                    //draw subtitles on buttons
                    if (gameMode == SURVIVAL) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Igrovo~ rejim : V@jivanie") : DrawText(240, 159,
                                                                                                   GU_COLOR(1, 1, 1, 1),
                                                                                                   default_size,
                                                                                                   "Igrovo~ rejim : V@jivanie");
                    }
                    if (gameMode == CREATIVE) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Igrovo~ rejim : Tvoryeski~") : DrawText(240, 159,
                                                                                                    GU_COLOR(1, 1, 1, 1),
                                                                                                    default_size,
                                                                                                    "Igrovo~ rejim : Tvoryeski~");
                    }
                    if (gameMode == HARDCORE) {
                        generateSelectPose == 2 ? DrawText(240, 159, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Igrovo~ rejim : Hardkor") : DrawText(240, 159,
                                                                                                 GU_COLOR(1, 1, 1, 1),
                                                                                                 default_size,
                                                                                                 "Igrovo~ rejim : Hardkor");
                    }

                    if (worldType == 0) {
                        generateSelectPose == 3 ? DrawText(240, 199, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Tip mira : Standartn@~") : DrawText(240, 199,
                                                                                                GU_COLOR(1, 1, 1, 1),
                                                                                                default_size,
                                                                                                "Tip mira : Standartn@~");
                    }
                    if (worldType == 1) {
                        generateSelectPose == 3 ? DrawText(240, 199, GU_COLOR(1, 1, 0.25, 1), default_size,
                                                           "Tip mira : Super-ploski~") : DrawText(240, 199,
                                                                                                  GU_COLOR(1, 1, 1, 1),
                                                                                                  default_size,
                                                                                                  "Tip mira : Super-ploski~");
                    }

                    generateSelectPose == 4 ? DrawText(240, 239, GU_COLOR(1, 1, 0.25, 1), default_size, "Sozdat$ nov@~ mir")
                                            : DrawText(240, 239, GU_COLOR(1, 1, 1, 1), default_size, "Sozdat$ nov@~ mir");
                }

                mRender->SetFont(ENGLISH);
                mRender->SetFontStyle(default_size, GU_COLOR(1, 1, 1, 1), 0, 0x00000000 | 0x00004000);
                mRender->DebugPrint(159, 79, "%s", newWorldName.c_str());
                if (seed_1 == 0) {
                    mRender->SetFontStyle(default_size, GU_COLOR(0.65, 0.65, 0.65, 1), 999, 0x00000200 | 0x00004000);
                    if (mRender->GetFontLanguage() == ENGLISH) {
                        mRender->DebugPrint(240, 119, "random");
                    }
                    if (mRender->GetFontLanguage() == RUSSIAN) {
                        mRender->DebugPrint(240, 119, "sluya~n@~");
                    }
                } else {
                    mRender->DebugPrint(159, 119, "%s", newWorldSeed.c_str());
                }
                mRender->SetDefaultFont();
    mRender->EndFrame();
}

int StateNewWorld::fileSize(const std::string &name) {
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int) stat_buf.st_size : -1;
}

void StateNewWorld::ScanSaveFiles(const char *dirName) {
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

void StateNewWorld::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}

unsigned int StateNewWorld::hash(const char *s, unsigned int seed) {
    unsigned int hash = seed;
    while (*s) {
        hash = hash * 101 + *s++;
    }
    return hash;
}
