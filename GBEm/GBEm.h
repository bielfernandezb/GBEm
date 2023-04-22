#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#include "SDL_syswm.h"

#define WM_MESSAGE(x) (x.syswm.msg->msg.win)

#define IDM_FILE_OPEN 1
#define IDM_FILE_QUIT 2

class GBEm {

public:

	char CurrentRom[40];

	int WindowWidth = 160 * 5;
	int WindowHeight = 144 * 5;

	HMENU hMenuView;

	void OpenDialog(HWND hwnd);
	void CreateMenuBar(HWND hwnd);
	HWND getSDLWinHandle(SDL_Window* win);
	int initGBEm();

};