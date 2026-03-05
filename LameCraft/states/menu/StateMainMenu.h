#ifndef STATEMAINMENU_H_
#define STATEMAINMENU_H_

#include <string>
#include <vector>
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
class SoundManager;

class StateMainMenu : public Aurora::Utils::CGameState {
public:
    StateMainMenu();

    virtual ~StateMainMenu();

    void Init();

    void Enter();

    void CleanUp();

    void Pause();

    void Resume();

    void HandleEvents(Aurora::Utils::StateManager *sManager);

    void Update(Aurora::Utils::StateManager *sManager);

    void Draw(Aurora::Utils::StateManager *sManager);

    std::string getRandomSplashText();

private:
    Aurora::Graphics::RenderManager *mRender;
    Aurora::System::SystemManager *mSystemMgr;
    SoundManager *mSoundMgr;
    MenuHelper *menuHelper;

    Aurora::Graphics::Sprite *lamecraftSprite;
    Aurora::Graphics::Sprite *backgroundSprite;

    std::vector<std::string> menuOptionNames;

    std::string splashText;
    float splashSize;

    float backgroundPosX, backgroundPosY;
    bool backgroundDirectionX;
    bool backgroundDirectionY;

    int selectedPosition;
};

#endif
