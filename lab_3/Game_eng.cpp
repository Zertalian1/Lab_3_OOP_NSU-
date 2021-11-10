#include "Game_eng.h"
#include <map>

bool parseTrap(const string& trapfile, map<std::pair<int, int>, shared_ptr<Trap>>& traps) {
	ifstream fis(trapfile);
	string tmp0;
	unsigned int X, Y, num;
	while (!fis.eof() && fis.is_open()) {
		fis >> tmp0;
		X = stoi(tmp0);
		fis >> tmp0;
		Y = stoi(tmp0);
		fis >> tmp0;
		num = stoi(tmp0);
		traps[std::make_pair(X, Y)] = make_shared<Trap>(num);
	}
	return 1;
}

Game_engen::Game_engen(const string& map_name)
{
	Player player1(14.7f, 5.09f, 0.0f, 3.14159f / 3.0f, 16.0f, 5.0f);
	Start_X = 14.7f;
	Start_Y = 5.09f;
	player = player1;
	Map map1(120, 40, 16, 16, map_name);
	map_ = map1;
	parseTrap(map_name+"Trap.txt", traps);
}

bool Game_engen::Main_menu()
{
	int ScreenWidth = 120, ScreenHeight = 40;
	wchar_t* screen = new wchar_t[ScreenWidth * ScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	short choise=0;
	while (true) {
		Sleep(90);
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			if (choise == 0)
				choise = 2;
			choise--;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			if (choise == 1)
				choise = -1;
			choise++;
		}
		if (GetAsyncKeyState(13) & 0x8000) {
			if (choise == 0)
				return 0;
			return 1;
		}

		for (int nx = 0; nx < ScreenWidth; nx++)
			for (int ny = 0; ny < ScreenHeight; ny++)
			{
				screen[(ny) * ScreenWidth + nx] = ' ';
			}
		screen[(ScreenHeight / 2 - 1 + choise) * ScreenWidth + ScreenWidth / 2 - 1] = '#';
		swprintf_s(&screen[(ScreenHeight / 2-1) * ScreenWidth + ScreenWidth / 2], 6, L"Play ");
		swprintf_s(&screen[ScreenHeight / 2 * ScreenWidth + ScreenWidth / 2], 6, L"Maps ");
		WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
	}
}

void Game_engen::Game_eng()
{
	wchar_t* screen = new wchar_t[map_.get_ScreenWidth() * map_.get_ScreenHeight()];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (1)
	{
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float ElapsedTime = elapsedTime.count();

		if (!player.Move(ElapsedTime, map_)) {
				break;
		}
		auto itr = traps.find(std::make_pair((int)player.get_X(), (int)player.get_Y()));
		if (itr  != traps.end()) {
			wchar_t* wc = new wchar_t[30];
			int voice = (itr->second)->get_voice();
			wsprintf(wc, TEXT("play Trap%d.mp3"), voice);
			mciSendString(wc, NULL, 0, NULL);
			player.set_X(Start_X);
			player.set_Y(Start_Y);
		}

		for (int x = 0; x < map_.get_ScreenWidth(); x++)
		{
			// For each column, calculate the projected ray angle into world space
			float fRayAngle = (player.get_A() - player.get_FOV() / 2.0f) + ((float)x / (float)map_.get_ScreenWidth()) * player.get_FOV();

			// Find distance to wall
			float fStepSize = 0.1f;		  // Increment size for ray casting, decrease to increase
			float fDistanceToWall = 0.0f; //                                      resolution

			bool bHitWall = false;		// Set when ray hits wall block
			bool bBoundary = false;		// Set when ray hits boundary between two wall blocks

			float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < player.get_Depth())
			{
				fDistanceToWall += fStepSize;
				int nTestX = (int)(player.get_X() + fEyeX * fDistanceToWall);
				int nTestY = (int)(player.get_Y() + fEyeY * fDistanceToWall);

				// Test if ray is out of bounds
				if (nTestX < 0 || nTestX >= map_.get_MapWidth() || nTestY < 0 || nTestY >= map_.get_MapHeight())
				{
					bHitWall = true;			// Just set distance to maximum depth
					fDistanceToWall = player.get_Depth();
				}
				else
				{
					// Ray is inbounds so test to see if the ray cell is a wall block
					if (map_.get_map().c_str()[nTestX * map_.get_MapWidth() + nTestY] == '#')
					{

						bHitWall = true;

						vector<pair<float, float>> p;

						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{

								float vy = (float)nTestY + ty - player.get_Y();
								float vx = (float)nTestX + tx - player.get_X();
								float d = sqrt(vx * vx + vy * vy);
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
								p.push_back(make_pair(d, dot));
							}


						sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

						float fBound = 0.005;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}

			// Calculate distance to ceiling and floor
			int nCeiling = (float)(map_.get_ScreenHeight() / 2.0) - map_.get_ScreenHeight() / ((float)fDistanceToWall);
			int nFloor = map_.get_ScreenHeight() - nCeiling;

			// Shader walls based on distance
			short nShade = ' ';
			if (fDistanceToWall <= player.get_Depth() / 4.0f)			nShade = 0x2588;	// Very close
			else if (fDistanceToWall < player.get_Depth() / 3.0f)		nShade = 0x2593;
			else if (fDistanceToWall < player.get_Depth() / 2.0f)		nShade = 0x2592;
			else if (fDistanceToWall < player.get_Depth())				nShade = 0x2591;
			else											nShade = ' ';		// Too far away

			if (bBoundary)		nShade = ' '; // Black it out

			for (int y = 0; y < map_.get_ScreenHeight(); y++)
			{
				// Each Row
				if (y <= nCeiling)
					screen[y * map_.get_ScreenWidth() + x] = ' ';
				else if (y > nCeiling && y <= nFloor)
					screen[y * map_.get_ScreenWidth() + x] = nShade;
				else // Floor
				{
					// Shade floor based on distance
					float b = 1.0f - (((float)y - map_.get_ScreenHeight() / 2.0f) / ((float)map_.get_ScreenHeight() / 2.0f));
					if (b < 0.25)		nShade = '#';
					else if (b < 0.5)	nShade = 'x';
					else if (b < 0.75)	nShade = '.';
					else if (b < 0.9)	nShade = '-';
					else				nShade = ' ';
					screen[y * map_.get_ScreenWidth() + x] = nShade;
				}
			}
		}

		// Display Stats
		swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", player.get_X(), player.get_Y(), player.get_A(), 1.0f / ElapsedTime);

		// Display Map
		for (int nx = 0; nx < map_.get_MapWidth(); nx++)
			for (int ny = 0; ny < map_.get_MapWidth(); ny++)
			{
				screen[(ny + 1) * map_.get_ScreenWidth() + nx] = map_[ny * map_.get_MapWidth() + nx];
			}
		screen[((int)player.get_X() + 1) * map_.get_ScreenWidth() + (int)player.get_Y()] = 'P';

		// Display Frame
		screen[map_.get_ScreenWidth() * map_.get_ScreenHeight() - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, map_.get_ScreenWidth() * map_.get_ScreenHeight(), { 0,0 }, &dwBytesWritten);
	}
	//delete[] screen;
}

bool Game_engen::Esc_menu()
{
	int ScreenWidth = 120, ScreenHeight = 40;
	wchar_t* screen1 = new wchar_t[ScreenWidth * ScreenHeight];
	HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole1);
	DWORD dwBytesWritten1 = 0;
	short choise = 0;
	while (true) {
		Sleep(90);
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			if (choise == 0)
				choise = 2;
			choise--;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			if (choise == 1)
				choise = -1;
			choise++;
		}
		if (GetAsyncKeyState(13) & 0x8000) {
			if (choise == 0)
				return 0;
			return 1;
		}


		for (int nx = 0; nx < ScreenWidth; nx++)
			for (int ny = 0; ny < ScreenHeight; ny++)
			{
				screen1[(ny)*ScreenWidth + nx] = ' ';
			}
		screen1[(ScreenHeight / 2 - 1 + choise) * ScreenWidth + ScreenWidth / 2 - 1] = '#';
		swprintf_s(&screen1[(ScreenHeight / 2 - 1) * ScreenWidth + ScreenWidth / 2], 10, L"Continue ");
		swprintf_s(&screen1[ScreenHeight / 2 * ScreenWidth + ScreenWidth / 2], 6, L"Exit ");
		WriteConsoleOutputCharacter(hConsole1, screen1, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten1);
	}
}

string Game_engen::Map_menu()
{
	int ScreenWidth = 120, ScreenHeight = 40;
	wchar_t* screen1 = new wchar_t[ScreenWidth * ScreenHeight];
	HANDLE hConsole1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole1);
	DWORD dwBytesWritten1 = 0;
	short choise = 0;
	vector <string> maps;
	//maps.push_back("Map1.txt");
	//maps.push_back("Map2.txt");
	//maps.push_back("Map3.txt");

	std::ifstream fis("map_names.txt");
	std::string line;
	if (!fis)
	{
		std::cerr << ("File map_names cannot opened!");
		return "error";
	}
	while (getline(fis, line))
		maps.push_back(line);
	fis.close();

	while (true) {
		Sleep(90);
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			if (choise == 0)
				choise = maps.size();
			choise--;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			if (choise == maps.size()-1)
				choise = -1;
			choise++;
		}
		if (GetAsyncKeyState(27) & 0x8000) {
			return "error";
		}
		if (GetAsyncKeyState(13) & 0x8000) {
			return  maps.at(choise);
		}


		for (int nx = 0; nx < ScreenWidth; nx++)
			for (int ny = 0; ny < ScreenHeight; ny++)
			{
				screen1[(ny)*ScreenWidth + nx] = ' ';
			}

		screen1[(ScreenHeight / 2 - maps.size() / 2 + choise) * ScreenWidth + ScreenWidth / 2 - 1] = '#';
		for(int i=0; i< maps.size();i++)
			swprintf_s(&screen1[(ScreenHeight / 2 - maps.size()/2 + i) * ScreenWidth + ScreenWidth / 2], 5, L"Map%d", i+1);
		WriteConsoleOutputCharacter(hConsole1, screen1, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten1);
	}
}
