	/*
*   This file is part of LeafEdit
*   Copyright (C) 2019-2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "core/management/itemManagement.hpp"

#include "gui/screens/editor.hpp"
#include "gui/screens/mainMenu.hpp"
#include "gui/screens/screenCommon.hpp"
#include "gui/screens/settings.hpp"
#include "gui/screens/townManager.hpp"

void MainMenu::Draw(void) const
{
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.8f, WHITE, "LeafEdit", 400);

	Gui::DrawBottom();

	for (int i = 0; i < 3; i++) {
		if (Selection == i) {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, selectedColor);
		} else {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, unselectedColor);
		}
	}

	Gui::DrawStringCentered(0, mainButtons[0].y+10, 0.6f, WHITE, Lang::get("TOWN_MANAGER"), 130);
	Gui::DrawStringCentered(0, mainButtons[1].y+10, 0.6f, WHITE, Lang::get("EDITOR"), 130);
	Gui::DrawStringCentered(0, mainButtons[2].y+10, 0.6f, WHITE, Lang::get("SETTINGS"), 130);
}

void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	SelectionLogic(hDown, hHeld);

	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_A) {
		switch(Selection) {
			case 0:
				Gui::setScreen(std::make_unique<TownManager>());
				break;
			case 1:
				Msg::DisplayMsg(Lang::get("PREPARING_EDITOR"));
				Gui::loadSheets();
				ItemManagement::LoadDatabase(Config::getLang("Lang"));
				Gui::setScreen(std::make_unique<Editor>());
				break;
			case 2:
				Gui::setScreen(std::make_unique<Settings>());
				break;
		}
	}
}

void MainMenu::SelectionLogic(u32 hDown, u32 hHeld)
{
	if (hDown & KEY_UP) {
		if(Selection > 0)	Selection--;
	} else if (hDown & KEY_DOWN) {
		if(Selection < 2)	Selection++;
	}
}