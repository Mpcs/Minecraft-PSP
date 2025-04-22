#ifndef STATEABOUT_H_
#define STATEABOUT_H_

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

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;
using std::vector;
using std::string;
using std::map;

class StateAbout : public CGameState {
public:
    StateAbout();

    virtual ~StateAbout();

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
    RenderManager *mRender;
    SystemManager *mSystemMgr;
    SoundManager *mSoundMgr;
    MenuHelper *menuHelper;

    map<string, string> texts;
    int selectPos;

};

#endif
