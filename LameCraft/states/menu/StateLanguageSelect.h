#ifndef STATELANGUAGE_H_
#define STATELANGUAGE_H_

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

class StateLanguageSelect : public Aurora::Utils::CGameState {
public:
    StateLanguageSelect();

    virtual ~StateLanguageSelect();

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
    SoundManager *mSoundMgr;
    MenuHelper *menuHelper;

    std::vector<std::string> languageNames;
    std::vector<std::string> languageFileNames;

    unsigned int selectedPosition;
};

#endif
