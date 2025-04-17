#include "StateMainMenu.h"
#include "InputHelper.h"
#include "TextureHelper.h"
#include "lang/Translation.h"
#include "states/StateOptions.h"
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

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);
    buttonSprite->SetPosition(240, 150);
    buttonSprite->Scale(2, 2);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95,
                               12);
    sbuttonSprite->SetPosition(240, 150);
    sbuttonSprite->Scale(2, 2);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft), 0, 0, 320, 90);
    lamecraftSprite->SetPosition(240, 50);
    lamecraftSprite->Scale(1, 1);

    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::background));
    backgroundSprite->Scale(2, 2);
    backgroundSprite->SetPosition(240, 136);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    backSprite->Scale(2, 2);

    SplashNumber = rand() % 6;

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
    delete buttonSprite;
    delete sbuttonSprite;
    delete backSprite;
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
        }
        if (selectPos == 1) {
            //options
            StateOptions *stateOptions = new StateOptions();
            stateOptions->Init();
            sManager->PushState(stateOptions);
        }
        if (selectPos == 2) {
            //about
            //TODO: Open About state
            //menuState = 3;
            //aboutPos = 1;
        }
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

            /*for(int x = 0; x < 8; x++)
        {
            for(int y = 0; y < 5; y++)
            {
                backSprite->SetPosition(x*64,y*64);
                backSprite->Draw();
            }
        }*/

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
    buttonSprite->SetPosition(240, 120);
    buttonSprite->Draw();

    //options
    buttonSprite->SetPosition(240, 160);
    buttonSprite->Draw();

    //about
    buttonSprite->SetPosition(240, 200);
    buttonSprite->Draw();

    //texture pack
    buttonSprite->SetPosition(240, 240);
    buttonSprite->Draw();

    //selected button
    sbuttonSprite->SetPosition(240, (selectPos * 40) + 120);
    sbuttonSprite->Draw();

    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);

    splashSize += 0.08f;
    if (splashSize > 2 * PI) {
        splashSize = 0.0f;
    }

    Translation* translation = Translation::GetInstance();
    vector<string> splashTexts = translation->getValuesOfType("SPLASH");
    vector<string> menuOptionNames = translation->getValuesOfType("MAIN_MENU");

    int optionVerticalPosition = 129;
    for (int i = 0; i < 4; i++) {
        float lightness = 0.25;
        if (selectPos == i) {
            lightness = 1;
        }

        DrawText(240, optionVerticalPosition, GU_COLOR(1, 1, lightness, 1), default_size, menuOptionNames[i].c_str());

        optionVerticalPosition += 40;
    }

    DrawText(328, 86, GU_COLOR(1, 1, 0, 1), 0.6 + sinf(splashSize) * 0.04f, splashTexts[SplashNumber].c_str());
    mRender->EndFrame();
}

void StateMainMenu::DrawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    mRender->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    mRender->DebugPrint(x, y, message);
}
