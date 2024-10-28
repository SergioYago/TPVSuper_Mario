#include "TileMap.h"


TileMap::TileMap(const string& filename, Game g)
{
	
	vector<vector<int>> indices [Game::WINDOW_HEIGHT][40];
	ifstream file(filename);
	string line;
	for (int i = 0; i < Game::WINDOW_HEIGHT; ++i) {
		for (int j = 0; j < Game::WINDOW_WIDTH; ++j) {
			getline(file, line, ',');
			//indices[i][j] = stoi(line);
			cout << line<<" ";
		}
		cout << '\n';
	}
}
