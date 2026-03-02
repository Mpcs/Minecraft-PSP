#include "StateMainMenu.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/menu/StateOptions.h"
#include "states/menu/StateAbout.h"
#include "states/menu/StateWorldSelect.h"
#include "states/menu/StateNewWorld.h"
#include "MenuHelper.h"
#include <vector>
#include <string>

// font vars
#define default_size 0.5
#define default_big_size 0.687
#define PI 3.1415926535897f
using std::string;

StateMainMenu::StateMainMenu() {

}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::Init() {
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    menuHelper = MenuHelper::Instance();

    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

    Translation* translation = Translation::GetInstance();

    splashTexts = translation->getValuesOfType("SPLASH");
    menuOptionNames = translation->getValuesOfType("MAIN_MENU");

    SplashNumber = rand() % splashTexts.size();

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft), 0, 0, 320, 90);
    lamecraftSprite->SetPosition(240, 50);
    lamecraftSprite->Scale(1, 1);

    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
    backgroundSprite->Scale(2, 2);
    backgroundSprite->SetPosition(240, 136);

    selectPos = 0;

    bx = 240;
    by = 136;
    directionx = rand() % 2;
    directiony = rand() % 2;
}

void StateMainMenu::Enter() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
    selectPos = 0;
}

void StateMainMenu::CleanUp() {
}

void StateMainMenu::Pause() {

}

void StateMainMenu::Resume() {
    mRender->SetOrtho(0, 0, 0, 0, 0, 0);
}

void StateMainMenu::HandleEvents(StateManager *sManager) {
    mSystemMgr->InputUpdate();

    //if triangle button pressed the exit
    if (mSystemMgr->KeyPressed(PSP_CTRL_START)) {
        //running = false;
        sManager->Quit();
    }

    //up, down
    if (mSystemMgr->KeyPressed(PSP_CTRL_UP)) {
        selectPos--;
        if (selectPos < 0)
            selectPos = 3;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_DOWN)) {
        selectPos++;
        if (selectPos > 3)
            selectPos = 0;

        mSoundMgr->PlayMenuSound();
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE)) {
        if (selectPos == 0) {

        }
    }

    if (mSystemMgr->KeyPressed(PSP_CTRL_CROSS)) {
        if (selectPos == 0)//play state
        {
            // TODO: move this into the world select state
            //ScanSaveFiles("Save/");
//
            //loadSavePos = 0;
            //loadSaveStart = 0;
            //loadSaveEnd = saveFilesList.size();
            //loadSaveMax = 4;
            //if (loadSaveMax > loadSaveEnd)
            //    loadSaveMax = loadSaveEnd;
//
            //menuState = 1;
            //if (saveFilesList.empty() == false) {
            //    loadSelectPos = 0;
            //} else {
            //    loadSelectPos = 3;
            //}

            StateWorldSelect *stateWorldSelect = new StateWorldSelect();
            stateWorldSelect->Init();
            sManager->PushState(stateWorldSelect);
        } else
        if (selectPos == 1) {
            //options
            StateOptions *stateOptions = new StateOptions();
            stateOptions->Init();
            sManager->PushState(stateOptions);
        } else
        if (selectPos == 2) {

            StateAbout *stateAbout = new StateAbout();
            stateAbout->Init();
            sManager->PushState(stateAbout);
        } else
        if (selectPos == 3) {
            //textures
            //TODO: Open Texture Packs state
            //tpCurrent = 0;
            //tpMax = 0;
            //tpEnd = 0;
            //tpStart = 0;
            //tpPos = 0;
            //tpSelectPos = 0;
//
            //menuState = 11;
            //tpSelectPos = 0;
            //tpEnd = texturePackList.size();
            //tpMax = 3;
            //ScanTexturePacks("Assets/Textures/");
        }
    }
}

void StateMainMenu::Update(StateManager *sManager) {}

void StateMainMenu::Draw(StateManager *sManager) {
    mRender->StartFrame(1, 1, 1);

    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));

    if (bx >= 360) {
        directionx = false;
    }
    if (bx <= 120) {
        directionx = true;
    }

    if (by >= 272 - 68) {
        directiony = false;
    }
    if (by <= 68) {
        directiony = true;
    }

    if (directionx == true) {
        bx += 1 / 6.0f;
    } else {
        bx -= 1 / 6.0f;
    }

    if (directiony == true) {
        by += 272.0f / 960.0f / 6.0f;
    } else {
        by -= 272.0f / 960.0f / 6.0f;
    }


    backgroundSprite->SetPosition(bx, by);
    backgroundSprite->DrawLinear();
    //logo
    lamecraftSprite->Draw();

    //singlePlayer
    menuHelper->drawButton(240, 120, selectPos == 0);

    //options
    menuHelper->drawButton(240, 160, selectPos == 1);

    //about
    menuHelper->drawButton(240, 200, selectPos == 2);

    //texture pack
    menuHelper->drawButton(240, 240, selectPos == 3);

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    splashSize += 0.08f;
    if (splashSize > 2 * PI) {
        splashSize = 0.0f;
    }

    for (int i = 0; i < 4; i++) {
        float lightness = 0.25;
        if (selectPos == i) {
            lightness = 1;
        }

        menuHelper->drawText(240, 129 + (i * 40), GU_COLOR(1, 1, lightness, 1), default_size, INTRAFONT_ALIGN_CENTER, menuOptionNames[i].c_str());
    }

    menuHelper->drawText(328, 86, GU_COLOR(1, 1, 0, 1), 0.6 + sinf(splashSize) * 0.04f, 0, splashTexts[SplashNumber].c_str());
    mRender->EndFrame();
}
