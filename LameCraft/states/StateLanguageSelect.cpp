#include "StateLanguageSelect.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/StateMenu.h"
#include <vector>
#include <string>

// font vars
#define default_size 0.5
#define default_big_size 0.687

using std::string;

StateLanguageSelect::StateLanguageSelect() {

}

StateLanguageSelect::~StateLanguageSelect() {

}

void StateLanguageSelect::Init() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);
    buttonSprite->SetPosition(240, 150);
    buttonSprite->Scale(2, 2);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95,
                               12);
    sbuttonSprite->SetPosition(240, 150);
    sbuttonSprite->Scale(2, 2);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    backSprite->Scale(2, 2);

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

void StateLanguageSelect::CleanUp() {
    delete buttonSprite;
    delete sbuttonSprite;
    delete backSprite;
}

void StateLanguageSelect::Pause() {

}

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
        
        StateMenu *stateMenu = new StateMenu();
        stateMenu->Init();
        sManager->PushState(stateMenu);
    }
}

void StateLanguageSelect::Update(StateManager *sManager) {}

void StateLanguageSelect::Draw(StateManager *sManager) {
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

    for (int i = 0; i < languageNames.size(); i++) {
        if (i == selectPos) {
            sbuttonSprite->SetPosition(240, (40 * (i - selectPos)) + 120);
            sbuttonSprite->Draw();
        } else {
            buttonSprite->SetPosition(240, (40 * (i - selectPos)) + 120);
            buttonSprite->Draw();
        }
    }

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    for (int i = 0; i < languageNames.size(); i++) {
        float lightness = 0.25;
        if (selectPos == i) {
            lightness = 1;
        }

        DrawText(240, 129 + 40 * (i - selectPos), GU_COLOR(1, 1, lightness, 1), default_size, languageNames[i].c_str());
    }

    DrawText(240, 24, GU_COLOR(1, 1, 1, 1), default_size, "Choose your language");

    mRender->EndFrame();
}

void StateLanguageSelect::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}
