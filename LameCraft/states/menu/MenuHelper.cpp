#include "MenuHelper.h"
#include "TextureHelper.h"
#include <Aurora/Graphics/RenderManager.h>


MenuHelper::MenuHelper() {
    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 0, 95, 12);
    buttonSprite->Scale(2, 2);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Buttons), 0, 12, 95, 12);
    sbuttonSprite->Scale(2, 2);

    backgroundSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt), 0, 0, 32, 32);
    backgroundSprite->Scale(2, 2);
}

MenuHelper::~MenuHelper() {
    delete buttonSprite;
    delete sbuttonSprite;
    delete backgroundSprite;
}

void MenuHelper::drawDirtBackground() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 5; y++) {
            backgroundSprite->SetPosition(x * 64, y * 64);
            backgroundSprite->Draw();
        }
    }
}

void MenuHelper::drawButton(float x, float y, bool selected) {
    sceGuDisable(GU_DEPTH_TEST);
    sceGuEnable(GU_BLEND);
    sceGuColor(GU_COLOR(1, 1, 1, 1.0f));
    if (selected) {
        sbuttonSprite->SetPosition(x, y);
        sbuttonSprite->Draw();
    } else {
        buttonSprite->SetPosition(x, y);
        buttonSprite->Draw();
    }
    sceGuDisable(GU_BLEND);
    sceGuEnable(GU_DEPTH_TEST);
}

void MenuHelper::drawText(int x, int y, unsigned int color, float size, const char *message, ...) {
    RenderManager::InstancePtr()->SetFontStyle(size, color, 0, 0x00000200 | 0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x, y, message);
}

MenuHelper *MenuHelper::instance = NULL;
MenuHelper *MenuHelper::Instance() {
    if (instance == NULL) {
        instance = new MenuHelper();
    }
    return instance;
}