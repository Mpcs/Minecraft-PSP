#ifndef StateNewWorld_H_
#define StateNewWorld_H_

#include <stdlib.h>
#include <string>
#include <map>

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include "SoundManager.h"
#include "MenuHelper.h"

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/Utils/pgeZip.h>
#include <Aurora/Utils/pgeDir.h>
#include <Aurora/Utils/pge.h>

#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include<fstream>
#include<iostream>

#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __PSP__
#include <sys/stat.h>
#endif


#include "SoundManager.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;
using std::vector;
using std::string;
using std::map;

#ifndef SAVEFILE_H
#define SAVEFILE_H

class SaveFile {
public:

    int saveVersion;
    bool compression;
    char worldGameMode;
    char worldName[50];
    bool locked;
    std::string fileName;

    int saveSize;
};

#endif

class StateNewWorld : public CGameState {
public:
    StateNewWorld();

    virtual ~StateNewWorld();

    void Init();

    void Enter();

    void CleanUp();

    void Pause();

    void Resume();

    void HandleEvents(StateManager *sManager);

    void Update(StateManager *sManager);

    void Draw(StateManager *sManager);

    void DrawText(int x, int y, unsigned int color, float size, const char *message, ...);

    void ScanSaveFiles(const char *dirName);

    int fileSize(const std::string &name);

    unsigned int hash(const char *s, unsigned int seed);

private:
    RenderManager *mRender;
    SystemManager *mSystemMgr;
    SoundManager *mSoundMgr;
    MenuHelper *menuHelper;

    map<string, string> texts;
    int selectPos;

    // converter vars
    bool schematicExists;

    short newW_width;
    short newW_height;
    short newW_length;

    char newW_gameMode;
    bool newW_deleteCaves;
    int conversionStage;
    int errorType;

    std::string lol;

    int converterPos;
    //

    int SplashNumber;
    float splashSize;

    unsigned int seed_1;
    int loadSelectPos;
    int loadSavePos;
    int aboutPos;
    char worldName[32];

    float size_f;

    float fontcolor;
    bool fontcoloroption;

    bool saveSubmenu;
    int saveSubMenuSelect;

    pgeZip *theZip;

    int loadSaveStart;
    int loadSaveEnd;
    int loadSaveMax;

    short animationscreen;
    short menuState;//0 main,1 load,2 options

    int nextSaveFileNumber;
    std::string nextSaveFileName;

    std::vector<SaveFile> saveFilesList;
    std::string newWorldName;
    std::string newWorldSeed;
    std::string newWorldNamestr;
    //options for parametric map generation
    bool makeTrees;
    bool makeWater;
    bool makeCaves;
    int terrainBuilder;
    short gameMode;
    int worldType;

    short generateSelectPose;

    //game version
    short currentVersion;

    Sprite *buttonSmallSprite;
    Sprite *sbuttonSmallSprite;
    Sprite *nbuttonSmallSprite;

    Sprite *buttonSprite;
    Sprite *sbuttonSprite;

    Sprite *nbuttonSprite;

    Sprite *mbuttonSprite;
    Sprite *smbuttonSprite;

    Sprite *backSprite;
    Sprite *logoSprite;
    Sprite *lamecraftSprite;

    Sprite *rectFilledSprite;
    Sprite *rectEmptySprite;

    Sprite *blackBackground;

};

#endif
