#include "StateAbout.h"

#include "lang/Translation.h"

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>

#include "MenuHelper.h"

StateAbout::StateAbout():
    mRender(0),
    mSystemMgr(0),
    menuHelper(0)
{
    mRender = RenderManager::InstancePtr();
    mSystemMgr = Aurora::System::SystemManager::Instance();
    menuHelper = MenuHelper::Instance();
    Translation* translation = Translation::GetInstance();

    texts = translation->getTranslationsOfType("ABOUT");
}

StateAbout::~StateAbout() {}

void StateAbout::Init() {}

void StateAbout::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateAbout::CleanUp() {}

void StateAbout::Pause() {}

void StateAbout::Resume() {}

void StateAbout::HandleEvents(Aurora::Utils::StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        sManager->PopState();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE)) {
        sManager->PopState();
    }
}

void StateAbout::Update(Aurora::Utils::StateManager*) {}

void StateAbout::Draw(Aurora::Utils::StateManager*) {
    mRender->StartFrame(1, 1, 1);

    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

    menuHelper->drawDirtBackground();

    menuHelper->drawButton(240, 255, true);

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

    menuHelper->drawText(240, 264, GU_COLOR(1, 1, 1, 1), 0.687, INTRAFONT_ALIGN_CENTER, texts["cancel"].c_str());

    menuHelper->drawText(240, 29, GU_COLOR(1, 1, 1, 1), default_size, INTRAFONT_ALIGN_CENTER, texts["title"].c_str());

    mRender->EndFrame();
}
