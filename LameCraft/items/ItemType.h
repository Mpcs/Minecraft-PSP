//
// Created by Mpcs on 08.05.2020.
//

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

class ItemType {
public:
    enum type{
        normal,
        tool,
        food,
        helmet,
        chestplate,
        leggings,
        boots,
        dye
    };
};

typedef ItemType::type item_t;

#endif //ITEMTYPE_H g
