#ifndef STATELANGUAGE_H_
#define STATELANGUAGE_H_

#include <stdlib.h>
#include <string>

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

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;
using std::vector;
using std::string;

class StateLanguageSelect : public CGameState {
public:
    StateLanguageSelect();

    virtual ~StateLanguageSelect();

    void Init();

    void Enter();

    void CleanUp();

    void Pause();

    void Resume();

    void HandleEvents(StateManager *sManager);

    void Update(StateManager *sManager);

    void Draw(StateManager *sManager);

    void DrawText(int x, int y, unsigned int color, float size, const char *message, ...);

private:
    Sprite *buttonSprite;
    Sprite *sbuttonSprite;
    Sprite *backSprite;

    RenderManager *mRender;
    SystemManager *mSystemMgr;
    SoundManager *mSoundMgr;

    vector<string> languageNames;
    vector<string> languageFileNames;

    int selectPos;

};

#endif
