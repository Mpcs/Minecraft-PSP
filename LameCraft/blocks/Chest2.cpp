#include "Chest2.h"


Chest::Chest(int x, int y, int z) {
    for (int i = 0; i < 27; i++) {
        chestSlotId[i] = -1;
        chestSlotAm[i] = -1;
        chestSlotSt[i] = false;
    }

    chestAddress = x + y * 252 + z * 252 * 112;

    id = 0;
}

Chest::~Chest() {

}

