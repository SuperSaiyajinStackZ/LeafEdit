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

#include "gui/msg.hpp"

#include "gui/screens/screenCommon.hpp"

// Display a Message, which needs to be confirmed with A/B.
bool Msg::promptMsg2(std::string promptMsg)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 100, 0.6f, TXTCOLOR, promptMsg, 390);
	Gui::DrawStringCentered(0, 214, 0.72f, TXTCOLOR, Lang::get("CONFIRM_OR_CANCEL"), 390);
	Gui::DrawBottom();
	C3D_FrameEnd(0);

	while(1)
	{
		gspWaitForVBlank();
		hidScanInput();
		if(hidKeysDown() & KEY_A) {
			return true;
		} else if(hidKeysDown() & KEY_B) {
			return false;
		}
	}
}

bool Msg::promptMsg(std::string msg) {
	return Msg::promptMsg2(msg);
}

// Displays a Warn Message.
void Msg::DisplayWarnMsg(std::string Text)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.72f, TXTCOLOR, Text, 395);
	Gui::DrawBottom();
	C3D_FrameEnd(0);
	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

// Displays a Warn Message. This is mostly be used for things with more text.
void Msg::DisplayWarnMsg2(std::string Text)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 40, 0.72f, TXTCOLOR, Text, 395);
	Gui::DrawBottom();
	C3D_FrameEnd(0);
	for (int i = 0; i < 60*2; i++) {
		gspWaitForVBlank();
	}
}

// Display a Message, which can be skipped with A.
void Msg::DisplayWaitMsg(std::string waitMsg, ...)
{
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 100, 0.72f, TXTCOLOR, waitMsg, 390);
	Gui::DrawStringCentered(0, 214, 0.6f, TXTCOLOR, Lang::get("A_CONTINUE"), 390);
	Gui::DrawBottom();
	C3D_FrameEnd(0);

	while(1)
	{
		hidScanInput();
		if(hidKeysDown() & KEY_A)
			break;
	}
}

void Msg::HelperBox(std::string Msg) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	Gui::ScreenDraw(top);
	Gui::Draw_Rect(0, 0, 400, 240, DIM);
	Gui::sprite(0, sprites_helperBox_idx, 0, 27);
	Gui::DrawString(10, 42, 0.45f, TXTCOLOR, Msg, 380);
	Gui::ScreenDraw(bottom);
	Gui::Draw_Rect(0, 0, 320, 240, DIM);
	C3D_FrameEnd(0);
}

void Msg::DisplayMsg(std::string Message) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.60f, TXTCOLOR, Message, 390);
	Gui::DrawBottom();
	C3D_FrameEnd(0);
}


void Msg::NotImplementedYet(void) {
	Msg::DisplayWarnMsg(Lang::get("NOT_IMPLEMENTED"));
}

// I think that's not used anymore? I just keep it for now.
void Msg::SheetMsg(std::string Message) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, BLACK);
	C2D_TargetClear(bottom, BLACK);
	Gui::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.60f, WHITE, Message, 390);
	Gui::DrawBottom();
	C3D_FrameEnd(0);
}