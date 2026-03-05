#ifndef STATEABOUT_H_
#define STATEABOUT_H_

#include <string>
#include <map>
#include <Aurora/Utils/GameState.h>

namespace Aurora {
    namespace Graphics {
        class RenderManager;
        class Sprite;
    }
    namespace System {
        class SystemManager;
    }
    namespace Utils {
        class StateManager;
    }
}

class MenuHelper;

class StateAbout : public Aurora::Utils::CGameState {
public:
    StateAbout();

    virtual ~StateAbout();

    void Init();

    void Enter();

    void CleanUp();

    void Pause();

    void Resume();

    void HandleEvents(Aurora::Utils::StateManager *sManager);

    void Update(Aurora::Utils::StateManager *sManager);

    void Draw(Aurora::Utils::StateManager *sManager);

private:
    Aurora::Graphics::RenderManager *mRender;
    Aurora::System::SystemManager *mSystemMgr;
    MenuHelper *menuHelper;

    std::map<std::string, std::string> texts;
};

#endif
