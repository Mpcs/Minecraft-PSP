#include "StateTexturepacks.h"
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

StateTexturepacks::StateTexturepacks() {
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

    tpCurrent = 0;
    tpMax = 0;
    tpEnd = 0;
    tpStart = 0;
    tpPos = 0;
    tpSelectPos = 0;

    ScanTexturePacks("Assets/Textures/");

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

    tpCurrent = 0;
    tpMax = 0;
    tpEnd = 0;
    tpStart = 0;
    tpPos = 0;
    tpSelectPos = 0;

    menuState = 11;
    tpSelectPos = 0;
    tpEnd = texturePackList.size();
    tpMax = 3;
}

StateTexturepacks::~StateTexturepacks() {

}

void StateTexturepacks::Init() {

}

void StateTexturepacks::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateTexturepacks::CleanUp() {}

void StateTexturepacks::Pause() {}

void StateTexturepacks::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateTexturepacks::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

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
        sManager->PopState();
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
            sManager->PopState();
        }
    }
}

void StateTexturepacks::Update(StateManager *sManager) {}

void StateTexturepacks::Draw(StateManager *sManager) {
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

    mRender->EndFrame();
}

int StateTexturepacks::fileSize(const std::string &name) {
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? (int) stat_buf.st_size : -1;
}

void StateTexturepacks::ScanSaveFiles(const char *dirName) {
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

void StateTexturepacks::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}

void StateTexturepacks::ScanTexturePacks(const char *dirName) {
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

inline bool StateTexturepacks::fileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
