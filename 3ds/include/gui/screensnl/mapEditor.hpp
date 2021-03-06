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

#ifndef MAPEDITOR_HPP
#define MAPEDITOR_HPP

#include "common/structs.hpp"

#include "gui/screens/screen.hpp"
#include "gui/screens/screenCommon.hpp"

#include <vector>

class MapEditor : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;

private:
	/* Mostly selection stuff. */
	int Mode = 0;
	int selection = 0; // Selection for "Items" / "Buildings".
	int selectionMode = 0;
	int currentPosX = 0;
	int currentPosY = 0;
	int currentAcre = 0;
	u8 acreImage = 0x10;
	int BuildingSelection = 0; // For the Building list indicator.

	/* Main Screen. */
	void DrawMapScreen(void) const;
	void MapScreenLogic(u32 hDown, u32 hHeld, touchPosition touch);

	/* Building List. */
	void DrawBuildingList(void) const;
	void BuildingListLogic(u32 hDown, u32 hHeld, touchPosition touch);

	/* Utilities. */
	void DrawGrid(void) const;
	void DrawTownMap() const;
	void DrawCurrentPos(void) const;
	void updateAcre(void);

	std::vector<Structs::ButtonPos> mapButtons = {
		{230, 75, 75, 30, -1}, // Items.
		{230, 140, 75, 30, -1}, // Buildings.
	};

};

#endif