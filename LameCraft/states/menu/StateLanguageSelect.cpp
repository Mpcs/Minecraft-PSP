#include "StateLanguageSelect.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateMainMenu.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/System/SystemManager.h>
#include "SoundManager.h"
#include "MenuHelper.h"

using std::string;

StateLanguageSelect::StateLanguageSelect() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = Aurora::System::SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();

    selectedPosition = 0;

    FILE *file;
    file = fopen("Assets/Lang/languages.txt", "r");

    if (file == NULL)
        return;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        string linestr(line);
        int pos = linestr.find(":");
        string languageName = linestr.substr(0, pos);
        languageNames.push_back(languageName);

        string languageFileName = linestr.substr(pos+1, linestr.length()-pos-2 ); // -2 because we skip the last char - newline
        languageFileNames.push_back(languageFileName);
    }

    fclose(file);
}

StateLanguageSelect::~StateLanguageSelect() { }

void StateLanguageSelect::Init() { }

void StateLanguageSelect::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectedPosition = 0;
}

void StateLanguageSelect::CleanUp() {}

void StateLanguageSelect::Pause() {}

void StateLanguageSelect::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateLanguageSelect::HandleEvents(Aurora::Utils::StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        if (selectedPosition == 0) {
            selectedPosition = languageNames.size()-1;
        } else {
            selectedPosition--;
        }

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        selectedPosition++;
        if (selectedPosition > languageNames.size()-1)
            selectedPosition = 0;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        int fakeLangPos = selectedPosition; // Will be removed when translations work fully
        if(selectedPosition > 1) {
            fakeLangPos = 0;
        }
        RenderManager::InstancePtr()->defaultFontType = fakeLangPos + 1;
        RenderManager::InstancePtr()->SetDefaultFont();

        Translation* translation = Translation::GetInstance();
        translation->loadLanguage(languageNames[selectedPosition], languageFileNames[selectedPosition]);

        StateMainMenu *stateMainMenu = new StateMainMenu();
        stateMainMenu->Init();
        sManager->PushState(stateMainMenu);
    }
}

void StateLanguageSelect::Update(Aurora::Utils::StateManager*) {}

void StateLanguageSelect::Draw(Aurora::Utils::StateManager*) {
    mRender->StartFrame(1, 1, 1);

    menuHelper->drawDirtBackground();

    for (unsigned int i = 0; i < languageNames.size(); i++) {
        bool selected = (i == selectedPosition);
        menuHelper->drawButton(240, (40 * (i - selectedPosition)) + 120, selected);
    }

    for (unsigned int i = 0; i < languageNames.size(); i++) {
        float lightness = 0.25;
        if (selectedPosition == i) {
            lightness = 1;
        }

        menuHelper->drawText(240, 129 + 40 * (i - selectedPosition), GU_COLOR(1, 1, lightness, 1), default_size, INTRAFONT_ALIGN_CENTER, languageNames[i].c_str());
    }

    menuHelper->drawText(240, 24, GU_COLOR(1, 1, 1, 1), default_size, 0, Translation::GetInstance()->getValue("LANGUAGE", "TEXT").c_str());

    mRender->EndFrame();
}
