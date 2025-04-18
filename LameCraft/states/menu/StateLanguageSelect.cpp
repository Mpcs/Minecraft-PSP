#include "StateLanguageSelect.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateMainMenu.h"
#include <vector>
#include <string>

using std::string;

StateLanguageSelect::StateLanguageSelect() {

}

StateLanguageSelect::~StateLanguageSelect() {

}

void StateLanguageSelect::Init() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();

    selectPos = 0;

    FILE *file;
    file = fopen("Assets/Lang/languages.txt", "r");

    if (file == NULL)
        return;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        string linestr(line);
        int pos = linestr.find(":");
        string languageName = linestr.substr(0, pos);
        string languageFileName = linestr.substr(pos+1, linestr.length()-pos-2 ); // -2 because we skip the last char - newline
        printf(languageFileName.c_str());
        languageNames.push_back(languageName);
        languageFileNames.push_back(languageFileName);
    }
    
    fclose(file);
}

void StateLanguageSelect::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateLanguageSelect::CleanUp() {}

void StateLanguageSelect::Pause() {}

void StateLanguageSelect::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateLanguageSelect::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        selectPos--;
        if (selectPos < 0)
            selectPos = languageNames.size()-1;
        
        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        selectPos++;
        if (selectPos > languageNames.size()-1)
            selectPos = 0;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        int fakeLangPos = selectPos; // Will be removed when translations work fully
        if(selectPos > 1) {
            fakeLangPos = 0;
        }
        RenderManager::InstancePtr()->defaultFontType = fakeLangPos + 1;
        RenderManager::InstancePtr()->SetDefaultFont();

        Translation* translation = Translation::GetInstance();
        translation->loadLanguage(languageNames[selectPos], languageFileNames[selectPos]); 
        
        StateMainMenu *stateMainMenu = new StateMainMenu();
        stateMainMenu->Init();
        sManager->PushState(stateMainMenu);
    }
}

void StateLanguageSelect::Update(StateManager *sManager) {}

void StateLanguageSelect::Draw(StateManager *sManager) {
    mRender->StartFrame(1, 1, 1);

    menuHelper->drawDirtBackground();

    for (int i = 0; i < languageNames.size(); i++) {
        bool selected = (i == selectPos);
        menuHelper->drawButton(240, (40 * (i - selectPos)) + 120, selected);
    }

    for (int i = 0; i < languageNames.size(); i++) {
        float lightness = 0.25;
        if (selectPos == i) {
            lightness = 1;
        }

        menuHelper->drawText(240, 129 + 40 * (i - selectPos), GU_COLOR(1, 1, lightness, 1), default_size, languageNames[i].c_str());
    }

    menuHelper->drawText(240, 24, GU_COLOR(1, 1, 1, 1), default_size, "Choose your language");

    mRender->EndFrame();
}
