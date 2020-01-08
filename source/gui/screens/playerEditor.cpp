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

#include "common/config.hpp"
#include "common/utils.hpp"

#include "core/management/playerManagement.hpp"

#include "gui/keyboard.hpp"

#include "gui/screens/itemEditor.hpp"
#include "gui/screens/playerEditor.hpp"
#include "gui/screens/screenCommon.hpp"

#include "core/save/offsets.h"
#include "core/save/player.h"
#include "core/save/save.h"
#include "core/save/villager.h"

#include <3ds.h>
#include <sys/stat.h>
#include <unistd.h>

extern Save* SaveFile;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

int selectedPassedPlayer;

void PlayerEditor::Draw(void) const {
	if (screen == 0) {
		DrawSubMenu();
	} else if (screen == 1) {
		DrawMainEditor();
	} else if (screen == 2) {
		DrawPlayerEditor();
	}
}

void PlayerEditor::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (screen == 0) {
		SubMenuLogic(hDown, hHeld);
	} else if (screen == 1) {
		MainEditorLogic(hDown, hHeld, touch);
	} else if (screen == 2) {
		PlayerEditorLogic(hDown, hHeld, touch);
	}
}

void PlayerEditor::DrawNameAndGender(void) const {
	u32 player = 0;
	for (u32 x = 0; x < 4; x++, player++) {
		if (SaveFile->players[player]->Exists()) {
			Gui::Draw_Rect(15 + x * 100, 93, 70, 70, BGBOTCOLOR);
		}
	}

	if (SaveFile->players[0]->Exists()) {
		Gui::DrawStringCentered(-150, 106, 0.45f, TXTCOLOR, StringUtils::UTF16toUTF8(SaveFile->players[0]->Name).c_str(), 55);
		if (SaveFile->players[0]->Gender == 0) {
			Gui::sprite(0, sprites_male_idx, 45, 140);
		} else {
			Gui::sprite(0, sprites_female_idx, 45, 140);
		}
	}

	if (SaveFile->players[1]->Exists()) {
		Gui::DrawStringCentered(-50, 106, 0.45f, TXTCOLOR, StringUtils::UTF16toUTF8(SaveFile->players[1]->Name).c_str(), 55);
		if (SaveFile->players[1]->Gender == 0) {
			Gui::sprite(0, sprites_male_idx, 145, 140);
		} else {
			Gui::sprite(0, sprites_female_idx, 145, 140);
		}
	}

	if (SaveFile->players[2]->Exists()) {
		Gui::DrawStringCentered(50, 106, 0.45f, TXTCOLOR, StringUtils::UTF16toUTF8(SaveFile->players[2]->Name).c_str(), 55);
		if (SaveFile->players[2]->Gender == 0) {
			Gui::sprite(0, sprites_male_idx, 245, 140);
		} else {
			Gui::sprite(0, sprites_female_idx, 245, 140);
		}
	}

	if (SaveFile->players[3]->Exists()) {
		Gui::DrawStringCentered(150, 106, 0.45f, TXTCOLOR, StringUtils::UTF16toUTF8(SaveFile->players[3]->Name).c_str(), 55);
		if (SaveFile->players[3]->Gender == 0) {
			Gui::sprite(0, sprites_male_idx, 345, 140);
		} else {
			Gui::sprite(0, sprites_female_idx, 345, 140);
		}
	}
}

void PlayerEditor::DrawSubMenu(void) const {
	std::string activePlayer;
	std::string Title;
	Title += "LeafEdit";
	Title += " - ";
	Title += Lang::get("PLAYER_SELECTION");

	Gui::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.8f, TXTCOLOR, Title, 400);
	DrawNameAndGender();
	if (selectedPlayer == 0)	Gui::drawAnimatedSelector(15 + 0 * 100, 93, 70, 70, .030f, C2D_Color32(0, 0, 0, 0));
	else if (selectedPlayer == 1)	Gui::drawAnimatedSelector(15 + 1 * 100, 93, 70, 70, .030f, C2D_Color32(0, 0, 0, 0));
	else if (selectedPlayer == 2)	Gui::drawAnimatedSelector(15 + 2 * 100, 93, 70, 70, .030f, C2D_Color32(0, 0, 0, 0));
	else if (selectedPlayer == 3)	Gui::drawAnimatedSelector(15 + 3 * 100, 93, 70, 70, .030f, C2D_Color32(0, 0, 0, 0));

	Gui::DrawBottom();
	activePlayer += Lang::get("CURRENT_PLAYER");
	activePlayer += ": ";
	for (int i = 0; i < 4; i++) {
		if (selectedPlayer == i) {
			activePlayer += std::to_string(i+1);
		}
	}

	Gui::DrawStringCentered(0, 212, 0.8f, TXTCOLOR, activePlayer, 320);
}

void PlayerEditor::SubMenuLogic(u32 hDown, u32 hHeld) {
	for (int player = 0; player < 4; player++) {
		if (SaveFile->players[player]->Exists())	maxPlayer = player;
	}

	if (hDown & KEY_RIGHT) {
		selectedPlayer++;
		if(selectedPlayer > maxPlayer)	selectedPlayer = 0;
	} else if (hDown & KEY_LEFT) {
		selectedPlayer--;
		if(selectedPlayer < 0)	selectedPlayer = maxPlayer;
	} else if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_A) {
		if (selectedPlayer == 0)	cp = 0;
		else if (selectedPlayer == 1)	cp = 1;
		else if (selectedPlayer == 2)	cp = 2;
		else if (selectedPlayer == 3)	cp = 3;
		Selection = 0;
		screen = 1;
	}
}

void PlayerEditor::DrawMainEditor(void) const {
	std::string Title;
	Title += "LeafEdit";
	Title += " - ";
	Title += Lang::get("PLAYER_EDITOR");

	Gui::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.8f, TXTCOLOR, Title, 400);

	Gui::DrawBottom();


	for (int i = 0; i < 3; i++) {
		if (Selection == i) {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, selectedColor);
		} else {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, unselectedColor);
		}
	}

	Gui::sprite(0, sprites_back_idx, mainButtons[3].x, mainButtons[3].y);

	Gui::DrawStringCentered(0, mainButtons[0].y+10, 0.6f, TXTCOLOR, Lang::get("PLAYER"), 130);
	Gui::DrawStringCentered(0, mainButtons[1].y+10, 0.6f, TXTCOLOR, Lang::get("ITEMS"), 130);
	Gui::DrawStringCentered(0, mainButtons[2].y+10, 0.6f, TXTCOLOR, "WIP", 130);
}


void PlayerEditor::MainEditorLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_UP) {
		if(Selection > 0)	Selection--;
	} else if (hDown & KEY_DOWN) {
		if(Selection < 2)	Selection++;
	} else if (hDown & KEY_TOUCH && touching(touch, mainButtons[3])) {
		screen = 0;
	}

	if (hDown & KEY_B) {
		screen = 0;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox("Select Player, to edit the Player Stuff.\nSelect Items, to edit the Items. (Not Implemented yet)\nSelect WIP to ?. (Not implemented yet)\nPress B to exit from this Screen.");
	}

	if (hDown & KEY_A) {
		switch(Selection) {
				case 0:
					Selection = 0;
					screen = 2;
					break;
				case 1:
					selectedPassedPlayer = cp;
					Gui::setScreen(std::make_unique<ItemEditor>());
					break;
				case 2:
					Msg::NotImplementedYet();
					//screen = 4;
					break;
		}
	}
}

void PlayerEditor::DrawPlayerEditor(void) const {
	std::string Title;
	Title += "LeafEdit";
	Title += " - ";
	Title += Lang::get("PLAYER_EDITOR");

	// Display First Player Name.
	std::string PlayerName = Lang::get("PLAYER_NAME");
	PlayerName += ": ";
	PlayerName += StringUtils::UTF16toUTF8(SaveFile->players[cp]->Name).c_str();

	// Display the Amount of Bells inside the Wallet.
	std::string Wallet = std::to_string((SaveFile->players[cp]->Wallet.value));
	std::string WalletAmount = Lang::get("WALLET_AMOUNT");
	WalletAmount += ": ";
	WalletAmount += Wallet.c_str();

	// Display the current Tan of the Player.
	std::string Tan = std::to_string((SaveFile->players[cp]->PlayerTan));
	std::string TanPlayer = Lang::get("TAN_VALUE");
	TanPlayer += ": ";
	TanPlayer += Tan.c_str();

	// Display the Amount of Bells from the Bank.
	std::string Bank = std::to_string((SaveFile->players[cp]->BankAmount.value));
	std::string BankAmount = Lang::get("BANK_AMOUNT");
	BankAmount += ": ";
	BankAmount += Bank.c_str();

	// Display the amount of medals.
	std::string Medals = std::to_string((SaveFile->players[cp]->IslandMedals.value));
	std::string MedalsAmount = Lang::get("MEDAL_AMOUNT");
	MedalsAmount += ": ";
	MedalsAmount += Medals.c_str();

	// Display the amount of Coupons.
	std::string Coupons = std::to_string((SaveFile->players[cp]->MeowCoupons.value));
	std::string CouponsAmount = Lang::get("COUPON_AMOUNT");
	CouponsAmount += ": ";
	CouponsAmount += Coupons.c_str();

	Gui::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.8f, TXTCOLOR, Title, 400);

	// Draw Rectangles first, then Player Info.
	Gui::Draw_Rect(40, 37, 320, 22, BGBOTCOLOR);
	Gui::Draw_Rect(40, 65, 320, 22, BGBOTCOLOR);
	Gui::Draw_Rect(40, 93, 320, 22, BGBOTCOLOR);
	Gui::Draw_Rect(40, 121, 320, 22, BGBOTCOLOR);
	Gui::Draw_Rect(40, 149, 320, 22, BGBOTCOLOR);
	Gui::Draw_Rect(40, 177, 320, 22, BGBOTCOLOR);
	Gui::DrawStringCentered(0, 35, 0.8f, TXTCOLOR, PlayerName, 380);
	Gui::DrawStringCentered(0, 63, 0.8f, TXTCOLOR, WalletAmount, 380);
	Gui::DrawStringCentered(0, 91, 0.8f, TXTCOLOR, TanPlayer, 380);
	Gui::DrawStringCentered(0, 119, 0.8f, TXTCOLOR, BankAmount, 380);
	Gui::DrawStringCentered(0, 147, 0.8f, TXTCOLOR, MedalsAmount, 380);
	Gui::DrawStringCentered(0, 175, 0.8f, TXTCOLOR, CouponsAmount, 380);

	// Player Bottom.
	Gui::DrawBottom();

	for (int i = 0; i < 6; i++) {
		if (Selection == i) {
			Gui::Draw_Rect(playerButtons[i].x, playerButtons[i].y, playerButtons[i].w, playerButtons[i].h, selectedColor);
		} else {
			Gui::Draw_Rect(playerButtons[i].x, playerButtons[i].y, playerButtons[i].w, playerButtons[i].h, unselectedColor);
		}
	}

	if (currentPage == 1) {
		// Display Player Name.
		Gui::DrawStringCentered(-80, playerButtons[0].y+10, 0.6f, TXTCOLOR, Lang::get("PLAYER_NAME"), 130);
		// Display Wallet Amount.
		Gui::DrawStringCentered(-80, playerButtons[1].y+10, 0.6f, TXTCOLOR, Lang::get("WALLET_AMOUNT"), 130);
		// Display current Tan Value.
		Gui::DrawStringCentered(-80, playerButtons[2].y+10, 0.6f, TXTCOLOR, Lang::get("TAN_VALUE"), 130);
		// Display Bank Amount.
		Gui::DrawStringCentered(80, playerButtons[3].y+10, 0.6f, TXTCOLOR, Lang::get("BANK_AMOUNT"), 130);
		// Display Medal Amount.
		Gui::DrawStringCentered(80, playerButtons[4].y+10, 0.6f, TXTCOLOR, Lang::get("MEDAL_AMOUNT"), 130);
		// Display Coupon Amount.
		Gui::DrawStringCentered(80, playerButtons[5].y+10, 0.6f, TXTCOLOR, Lang::get("COUPON_AMOUNT"), 130);

	} else if (currentPage == 2) {

		// Max Bank.
		Gui::DrawStringCentered(-80, playerButtons[0].y+10, 0.6f, TXTCOLOR, Lang::get("MAX_BANK"), 130);
		// Max Medals.
		Gui::DrawStringCentered(-80, playerButtons[1].y+10, 0.6f, TXTCOLOR, Lang::get("MAX_MEDALS"), 130);
		// Max Coupons.
		Gui::DrawStringCentered(-80, playerButtons[2].y+10, 0.6f, TXTCOLOR, Lang::get("MAX_COUPONS"), 130);
		// Clear Bank.
		Gui::DrawStringCentered(80, playerButtons[3].y+10, 0.6f, TXTCOLOR, Lang::get("CLEAR_BANK"), 130);
		// Clear Medals.
		Gui::DrawStringCentered(80, playerButtons[4].y+10, 0.6f, TXTCOLOR, Lang::get("CLEAR_MEDALS"), 130);
		// Clear Coupons.
		Gui::DrawStringCentered(80, playerButtons[5].y+10, 0.6f, TXTCOLOR, Lang::get("CLEAR_COUPONS"), 130);
	}
}

void PlayerEditor::PlayerEditorLogic(u32 hDown, u32 hHeld, touchPosition touch) {

	// Selection / Page.
	if (hDown & KEY_UP) {
		if(Selection > 0)	Selection--;
	}
	if (hDown & KEY_DOWN) {
			if(Selection < 5)	Selection++;
	}
	if (hDown & KEY_RIGHT) {
		if (Selection == 0)	Selection = 3;
		else if (Selection == 1)	Selection = 4;
		else if (Selection == 2)	Selection = 5;
	}
	if (hDown & KEY_LEFT) {
		if (Selection == 3)	Selection = 0;
		else if (Selection == 4)	Selection = 1;
		else if (Selection == 5)	Selection = 2;
	}

	// Pages.
	if (hDown & KEY_R) {
		if(currentPage <2) currentPage++;
			Selection = 0;
	} else if (hDown & KEY_L) {
		if(currentPage > 1)	currentPage--;
			Selection = 0;
	}

	// Selection A / Touch.
	if (hDown & KEY_A) {
		if (currentPage == 1) {
			switch(Selection) {
				case 0:
					SaveFile->players[cp]->Name = Input::handleu16String(8, Lang::get("NEW_PLAYER_NAME"), SaveFile->players[cp]->Name);
					break;
				case 1:
					SaveFile->players[cp]->Wallet.value = Input::handleu32(5, Lang::get("ENTER_WALLET_AMOUNT"), 99999, SaveFile->players[cp]->Wallet.value);
					break;
				case 2:
					SaveFile->players[cp]->PlayerTan = Input::handleu32(2, Lang::get("ENTER_TAN_VALUE"), 15, SaveFile->players[cp]->PlayerTan);
					break;
				case 3:
					SaveFile->players[cp]->BankAmount.value = Input::handleu32(9, Lang::get("ENTER_BANK_AMOUNT"), 999999999, SaveFile->players[cp]->BankAmount.value);
						break;
				case 4:
					SaveFile->players[cp]->IslandMedals.value = Input::handleu32(4, Lang::get("ENTER_MEDAL_AMOUNT"), 9999, SaveFile->players[cp]->IslandMedals.value);
					break;
				case 5:
					SaveFile->players[cp]->MeowCoupons.value = Input::handleu32(4, Lang::get("ENTER_COUPON_AMOUNT"), 9999, SaveFile->players[cp]->MeowCoupons.value);
					break;
			}

		} else if (currentPage == 2) {
			switch(Selection) {
				case 0:
					SaveFile->players[cp]->BankAmount.value = 999999999;
					break;
				case 1:
					SaveFile->players[cp]->IslandMedals.value = 9999;
					break;
				case 2:
					SaveFile->players[cp]->MeowCoupons.value = 9999;
					break;
				case 3:
					SaveFile->players[cp]->BankAmount.value = 0;
					break;
				case 4:
					SaveFile->players[cp]->IslandMedals.value = 0;
					break;
				case 5:
					SaveFile->players[cp]->MeowCoupons.value = 0;
					break;
			}
		}
	}

	if (hDown & KEY_TOUCH) {
		if (currentPage == 1) {
			if (touching(touch, playerButtons[0])) {
				SaveFile->players[cp]->Name = Input::handleu16String(8, Lang::get("NEW_PLAYER_NAME"), SaveFile->players[cp]->Name);
			} else if (touching(touch, playerButtons[1])) {
				SaveFile->players[cp]->Wallet.value = Input::handleu32(5, Lang::get("ENTER_WALLET_AMOUNT"), 99999, SaveFile->players[cp]->Wallet.value);
			} else if (touching(touch, playerButtons[2])) {
				SaveFile->players[cp]->PlayerTan = Input::handleu32(2, Lang::get("ENTER_TAN_VALUE"), 15, SaveFile->players[cp]->PlayerTan);
			} else if (touching(touch, playerButtons[3])) {
				SaveFile->players[cp]->BankAmount.value = Input::handleu32(9, Lang::get("ENTER_BANK_AMOUNT"), 999999999, SaveFile->players[cp]->BankAmount.value);
			} else if (touching(touch, playerButtons[4])) {
				SaveFile->players[cp]->IslandMedals.value = Input::handleu32(4, Lang::get("ENTER_MEDAL_AMOUNT"), 9999, SaveFile->players[cp]->IslandMedals.value);
			} else if (touching(touch, playerButtons[5])) {
				SaveFile->players[cp]->MeowCoupons.value = Input::handleu32(4, Lang::get("ENTER_COUPON_AMOUNT"), 9999, SaveFile->players[cp]->MeowCoupons.value);
			}

		} else if (currentPage == 2) {
			if (touching(touch, playerButtons[0])) {
				SaveFile->players[cp]->BankAmount.value = 999999999;
			} else if (touching(touch, playerButtons[1])) {
				SaveFile->players[cp]->IslandMedals.value = 9999;
			} else if (touching(touch, playerButtons[2])) {
				SaveFile->players[cp]->MeowCoupons.value = 9999;
			} else if (touching(touch, playerButtons[3])) {
				SaveFile->players[cp]->BankAmount.value = 0;
			} else if (touching(touch, playerButtons[4])) {
				SaveFile->players[cp]->IslandMedals.value = 0;
			} else if (touching(touch, playerButtons[5])) {
				SaveFile->players[cp]->MeowCoupons.value = 0;
			}
		}
	}

	if (hDown & KEY_B) {
		Selection = 0;
		screen = 1;
	}
}