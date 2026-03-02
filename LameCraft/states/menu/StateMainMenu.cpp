#include <stdlib.h>

#include "StateMainMenu.h"
#include "InputHelper.h"
#include "StateTexturepacks.h"
#include "StateWorldSelect.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateOptions.h"
#include "states/menu/StateAbout.h"
#include "states/menu/StateWorldSelect.h"
#include "states/menu/StateNewWorld.h"
#include "states/menu/StateTexturepacks.h"
#include "SoundManager.h"
#include "MenuHelper.h"


// font vars
#define default_size 0.5
#define PI 3.1415926535897f
#define MISSING_SPLASH_TEXT "MISSING SPLASH"
#define AMOUNT_OF_OPTIONS 4

StateMainMenu::StateMainMenu():
    mRender(0),
    mSystemMgr(0),
    mSoundMgr(0),
    menuHelper(0),
    lamecraftSprite(0),
    backgroundSprite(0),
    splashSize(0.0f),
    backgroundPosX(0.0f),
    backgroundPosY(0.0f),
    backgroundDirectionX(false),
    backgroundDirectionY(false),
    selectedPosition(0)
{
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();

    Translation* translation = Translation::GetInstance();
    menuOptionNames = translation->getValuesOfType("MAIN_MENU");

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft), 0, 0, 320, 90);
    lamecraftSprite->SetPosition(240, 50);
    lamecraftSprite->Scale(1, 1);

    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
    backgroundSprite->Scale(2, 2);
    backgroundSprite->SetPosition(240, 136);
}

StateMainMenu::~StateMainMenu() {
    delete lamecraftSprite;
    lamecraftSprite = 0;

    delete backgroundSprite;
    backgroundSprite = 0;
}

void StateMainMenu::Init() { }

void StateMainMenu::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    splashText = getRandomSplashText();
    selectedPosition = 0;

    backgroundPosX = 240;
    backgroundPosY = 136;
    backgroundDirectionX = rand() % 2;
    backgroundDirectionY = rand() % 2;
}

void StateMainMenu::CleanUp() { }

void StateMainMenu::Pause() { }

void StateMainMenu::Resume() { }

void StateMainMenu::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        selectedPosition--;
        if (selectedPosition < 0)
            selectedPosition = AMOUNT_OF_OPTIONS - 1;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        selectedPosition++;
        if (selectedPosition > AMOUNT_OF_OPTIONS - 1)
            selectedPosition = 0;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        switch (selectedPosition) {
            case 0:
                sManager->PushState(new StateWorldSelect());
                break;
            case 1:
                sManager->PushState(new StateOptions());
                break;
            case 2:
                sManager->PushState(new StateAbout());
                break;
            case 3:
                sManager->PushState(new StateTexturepacks());
                break;
        }
    }
}

void StateMainMenu::Update(StateManager*) {}

void StateMainMenu::Draw(StateManager*) {
    mRender->StartFrame(1, 1, 1);

    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

    if (backgroundPosX >= 360) {
        backgroundDirectionX = false;
    }
    if (backgroundPosX <= 120) {
        backgroundDirectionX = true;
    }

    if (backgroundPosY >= 272 - 68) {
        backgroundDirectionY = false;
    }
    if (backgroundPosY <= 68) {
        backgroundDirectionY = true;
    }

    if (backgroundDirectionX == true) {
        backgroundPosX += 1 / 6.0f;
    } else {
        backgroundPosX -= 1 / 6.0f;
    }

    if (backgroundDirectionY == true) {
        backgroundPosY += 272.0f / 960.0f / 6.0f;
    } else {
        backgroundPosY -= 272.0f / 960.0f / 6.0f;
    }

    backgroundSprite->SetPosition(backgroundPosX, backgroundPosY);
    backgroundSprite->DrawLinear();

    //logo
    lamecraftSprite->Draw();
    //singlePlayer
    menuHelper->drawButton(240, 120, selectedPosition == 0);
    //options
    menuHelper->drawButton(240, 160, selectedPosition == 1);
    //about
    menuHelper->drawButton(240, 200, selectedPosition == 2);
    //texture pack
    menuHelper->drawButton(240, 240, selectedPosition == 3);

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    for (int i = 0; i < 4; i++) {
        float lightness = 0.25;
        if (selectedPosition == i) {
            lightness = 1;
        }

        menuHelper->drawText(240, 129 + (i * 40), GU_COLOR(1, 1, lightness, 1),
            default_size, INTRAFONT_ALIGN_CENTER, menuOptionNames[i].c_str());
    }

    // splash text
    splashSize += 0.08f;
    if (splashSize > 2 * PI) {
        splashSize = 0.0f;
    }

    menuHelper->drawText(328, 86, GU_COLOR(1, 1, 0, 1), 0.6 + sinf(splashSize) * 0.04f, 0, splashText.c_str());
    mRender->EndFrame();
}

std::string StateMainMenu::getRandomSplashText()
{
    std::vector<std::string> splashTexts = Translation::GetInstance()->getValuesOfType("SPLASH");
    if (!splashTexts.empty()) {
        int splashNumber = rand() % splashTexts.size();
        return splashTexts[splashNumber];
    }

    return MISSING_SPLASH_TEXT;
}
