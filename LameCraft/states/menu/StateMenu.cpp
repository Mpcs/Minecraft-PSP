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

}

void StateMenu::Update(StateManager *sManager) {


}

void StateMenu::Draw(StateManager *sManager) {
    //start rendering
    mRender->StartFrame(1, 1, 1);

    switch (menuState) {
            break;
        case 11://textures
        {

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
