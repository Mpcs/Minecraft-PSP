#include "StateAbout.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateMainMenu.h"
#include <vector>
#include <string>

using std::string;

#define ENGLISH 1
#define RUSSIAN 2

StateAbout::StateAbout() {

}

StateAbout::~StateAbout() {

}

void StateAbout::Init() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();
    Translation* translation = Translation::GetInstance();

    texts = translation->getTranslationsOfType("ABOUT");

    selectPos = 0;
}

void StateAbout::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateAbout::CleanUp() {}

void StateAbout::Pause() {}

void StateAbout::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateAbout::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        selectPos--;
        if (selectPos < 0)
            selectPos = 1;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        selectPos++;
        if (selectPos > 1)
            selectPos = 0;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        if (selectPos == 1) {
            sManager->PopState();
        }
        if (selectPos == 0) {
            //TODO: Converter
            //menuState = 6;
            //converterPos = 0;
//
            //schematicExists = fileExists("Converter/world.schematic");
            //ScanSaveFiles("Save/");
        }
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
        sManager->PopState();
    }
}

void StateAbout::Update(StateManager *sManager) {}

void StateAbout::Draw(StateManager *sManager) {
    mRender->StartFrame(1, 1, 1);

    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

    menuHelper->drawDirtBackground();

    menuHelper->drawButton(240, 225, selectPos == 0);
    menuHelper->drawButton(240, 255, selectPos == 1);

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    menuHelper->drawText(40, 60, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_LEFT, texts["author_label"].c_str());
    menuHelper->drawText(440, 60, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_RIGHT, "Marcin Ploska(Drakon)");

    menuHelper->drawText(40, 84, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_LEFT, texts["modder_label"].c_str());
    menuHelper->drawText(440, 84, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_RIGHT, "Kirill Skibin(Woolio)");

    menuHelper->drawText(40, 108, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_LEFT, texts["website_label"].c_str());
    menuHelper->drawText(440, 132, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_RIGHT, "github.com/Mpcs/Minecraft-PSP");

    menuHelper->drawText(40, 156, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_LEFT, texts["version_label"].c_str());
    menuHelper->drawText(440, 156, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_RIGHT, "1.0");

    menuHelper->drawText(40, 180, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_LEFT, texts["dev_stage_label"].c_str());
    menuHelper->drawText(440, 180, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_RIGHT, "DEV");

    menuHelper->drawText(240, 234, GU_COLOR(1, 1, selectPos == 0 ? 1 : 0.25, 1), 0.687, INTRAFONT_ALIGN_CENTER, texts["converter_button"].c_str());
    menuHelper->drawText(240, 264, GU_COLOR(1, 1, selectPos == 1 ? 1 : 0.25, 1), 0.687, INTRAFONT_ALIGN_CENTER, texts["cancel"].c_str());

    menuHelper->drawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, INTRAFONT_ALIGN_CENTER, texts["title"].c_str());

    mRender->EndFrame();
}
