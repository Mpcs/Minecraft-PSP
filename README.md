# Minecraft-PSP
This project aims to bring most modern Minecraft features to the PSP. Originally forked Woolio's Minecraft-PSP.

## Goals for release 1.0
- [x] Refactor Item type definitions
- [ ] Refactor Block type definitions
- [ ] Loading textures from separate files for blocks and items
- [ ] Finish translation files for all in-game text
- [ ] TBD...

# Future Features

### Code refactoring
- Better crafting recipe system
- Merge StatePlay with StatePlayCreative
- Split menus into separate classes
- loading textures from separate files instead of a spritesheet.
### Feature Parity
 - Furnace item burn times
 - Dye items
 - Armor/tools durability, speed, mining levels
## QoL
- fix item staying in cursor when closing a GUI
- quick move in inventories
- Swap cursor item with item from the hovered slot in inventories
- bigger pick up range for dropped items
- Better block targeting
- Save language after first boot selection
- Add language change option to options
# Building
To build the game you will need a psp SDK, I suggest the minimalist PSP SDK. With pspsdk installed and in your PATH environment variable or otherwise available run
```
make clean
make
```
# Running
To run, move the generated EBOOT file, into the ` _Game` folder. This folder contains all the resources needed for the game to run. Now you can run this on an emulator of your choice, or a PSP by moving the folder in the PSP/GAME folder on your console.