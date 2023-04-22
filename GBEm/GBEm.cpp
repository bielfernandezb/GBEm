#include "GBEm.h"


HWND GBEm::getSDLWinHandle(SDL_Window* win)
{
	SDL_SysWMinfo infoWindow;
	SDL_VERSION(&infoWindow.version);
	if (!SDL_GetWindowWMInfo(win, &infoWindow))
	{
		printf("No Window Handler!");
		return NULL;
	}
	return (infoWindow.info.win.window);
}

void GBEm::CreateMenuBar(HWND hwnd)
{

	HMENU hMenubar;
	HMENU hMenuFile;


	hMenubar = CreateMenu();
	hMenuFile = CreateMenu();


	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hMenuFile, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_QUIT, L"&Quit");

	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenuFile, L"&File");

	SetMenu(hwnd, hMenubar);

}

void GBEm::OpenDialog(HWND hwnd) {

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0");
	ofn.nFilterIndex = 1;

	if (GetOpenFileName(&ofn))
		ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	{

	}

}

int GBEm::initGBEm() {

	double fps = 59.73;
	double DesiredDelta = 1000 / fps;


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
		return 1;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("SDL failed to initialize : %s\n", SDL_GetError());

	}

	SDL_Window* window = SDL_CreateWindow("GBEm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE);


	if (!window) {
		printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
		return 1;
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
		SDL_TEXTUREACCESS_STREAMING, 160, 144);


	HWND WindowHandler = getSDLWinHandle(window);

	CreateMenuBar(WindowHandler);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	bool running = true;

	while (running) {

		int startLoop = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_SYSWMEVENT:

				switch (WM_MESSAGE(event).msg) {

				case WM_COMMAND:

					switch (LOWORD(WM_MESSAGE(event).wParam))
					{

					case IDM_FILE_OPEN:

						MessageBeep(MB_ICONINFORMATION);
						OpenDialog(WindowHandler);
						break;

					case IDM_FILE_QUIT:
						SendMessage(WindowHandler, WM_CLOSE, 0, 0);
						break;

					}

					break;

				case WM_KEYDOWN:

					switch (LOWORD(WM_MESSAGE(event).wParam))
					{
					case VK_LEFT:

						break;

					case VK_RIGHT:

						break;

					case VK_UP:

						break;

					case VK_DOWN:

						break;

					case VK_RETURN:

						break;

					case VK_SHIFT:

						break;

					case VK_BACK:

						break;

					case 0x5A:

						break;

					case 0x58:

						break;
					}

					break;

				case WM_KEYUP:

					switch (LOWORD(WM_MESSAGE(event).wParam))
					{
					case VK_LEFT:

						break;

					case VK_RIGHT:

						break;

					case VK_UP:

						break;

					case VK_DOWN:

						break;

					case VK_RETURN:

						break;

					case VK_SHIFT:

						break;

					case VK_BACK:

						break;

					case 0x5A:

						break;

					case 0x58:

						break;

					case VK_OEM_PLUS:

						break;

					case VK_OEM_MINUS:

						break;

					}

					break;
				}

				break;

			case SDL_WINDOWEVENT:

				if (!(event.window.event == SDL_WINDOWEVENT_CLOSE)) break;

			case SDL_QUIT:

				SDL_DestroyRenderer(renderer);

				SDL_DestroyTexture(texture);
				SDL_DestroyWindow(window);

				running = false;
				break;

			default:
				break;
			}

		}

		int delta = SDL_GetTicks() - startLoop;
		DesiredDelta = 1000 / fps;

	}

	return 0;

}

int main(int argc, char* argv[]) {

	GBEm gbEm;

	return gbEm.initGBEm();

}
