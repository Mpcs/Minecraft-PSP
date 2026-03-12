#ifndef MENUHELPER_H_
#define MENUHELPER_H_

#include <Aurora/Graphics/Sprite.h>

// font vars
#define default_size 0.5
#define default_big_size 0.687

using namespace Aurora::Graphics;

class MenuHelper {
public:
    static MenuHelper *Instance();
    void drawButton(float x, float y, bool selected);
    void drawText(int x, int y, unsigned int color, float size, unsigned int flags, const char *message, ...);
    void drawDirtBackground();
    
private:
    Sprite *buttonSprite;
    Sprite *sbuttonSprite;
    Sprite *backgroundSprite;

    static MenuHelper *instance;
    MenuHelper();
    ~MenuHelper();
};

#endif
