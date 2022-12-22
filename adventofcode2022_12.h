#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

namespace adv2022_12 {
	//---Part 1---
	void solve(std::vector <std::string>& map, std::vector<int>& activeTiles, std::unordered_set<int>& visited) {
		std::vector<int> newTiles;
		for (auto& tile : activeTiles) {
			int tile_y = tile / 1000;
			int tile_x = tile % 1000;
			//left
			if (tile_x != 0) {
				if (!visited.contains(tile - 1) &&
					map[tile_y][tile_x - 1] <= map[tile_y][tile_x] + 1) {
					newTiles.push_back(tile - 1);
					visited.insert(tile - 1);
				}
			}
			//right
			if (tile_x < map[0].length() - 1) {
				if (!visited.contains(tile + 1) &&
					map[tile_y][tile_x + 1] <= map[tile_y][tile_x] + 1) {
					newTiles.push_back(tile + 1);
					visited.insert(tile + 1);
				}
			}
			//up
			if (tile_y != 0) {
				if (!visited.contains(tile - 1000) &&
					map[tile_y - 1][tile_x] <= map[tile_y][tile_x] + 1) {
					newTiles.push_back(tile - 1000);
					visited.insert(tile - 1000);
				}
			}
			//down
			if (tile_y < map.size() - 1) {
				if (!visited.contains(tile + 1000) &&
					map[tile_y + 1][tile_x] <= map[tile_y][tile_x] + 1) {
					newTiles.push_back(tile + 1000);
					visited.insert(tile + 1000);
				}
			}
		}

		activeTiles = newTiles;
	}

	//---Part 2---
	// Start from E, till you find 'a'
	bool solve2(std::vector <std::string>& map, std::vector<int>& activeTiles, std::unordered_set<int>& visited) {
		std::vector<int> newTiles;
		for (auto& tile : activeTiles) {
			int tile_y = tile / 1000;
			int tile_x = tile % 1000;
			//left
			if (tile_x != 0) {
				if (!visited.contains(tile - 1) &&
					map[tile_y][tile_x - 1] >= map[tile_y][tile_x] - 1) {
					newTiles.push_back(tile - 1);
					visited.insert(tile - 1);
					if (map[tile_y][tile_x - 1] == 'a')return true;
				}
			}
			//right
			if (tile_x < map[0].length() - 1) {
				if (!visited.contains(tile + 1) &&
					map[tile_y][tile_x + 1] >= map[tile_y][tile_x] - 1) {
					newTiles.push_back(tile + 1);
					visited.insert(tile + 1);
					if (map[tile_y][tile_x + 1] == 'a')return true;
				}
			}
			//up
			if (tile_y != 0) {
				if (!visited.contains(tile - 1000) &&
					map[tile_y - 1][tile_x] >= map[tile_y][tile_x] - 1) {
					newTiles.push_back(tile - 1000);
					visited.insert(tile - 1000);
					if (map[tile_y - 1][tile_x] == 'a')return true;
				}
			}
			//down
			if (tile_y < map.size() - 1) {
				if (!visited.contains(tile + 1000) &&
					map[tile_y + 1][tile_x] >= map[tile_y][tile_x] - 1) {
					newTiles.push_back(tile + 1000);
					visited.insert(tile + 1000);
					if (map[tile_y + 1][tile_x] == 'a')return true;
				}
			}
		}

		activeTiles = newTiles;
		return false;
	}
}

void AdventOfCode2022_12() {

	std::fstream input("input/input_12.txt");
	std::string buffer;
	std::vector <std::string> map;
	std::unordered_set<int> visited;
	std::vector<int> activeTiles;

	while (input >> buffer) {
		map.push_back(buffer);
	}
	input.close();

	// Look for S and E, replace with a,z but remember position of S and E
	int S_x, S_y, E;
	for (int i = 0; i < map.size(); i++) {
		int index = map[i].find('S');
		if (index != -1) {
			S_y = i;
			S_x = index;
			map[S_y][S_x] = 'a';
		}
		index = map[i].find('E');
		if (index != -1) {
			E = i * 1000 + index;
			map[i][index] = 'z';
		}
	}

	visited.insert(S_y * 1000 + S_x);
	activeTiles.push_back(S_y * 1000 + S_x);

	int moves = 1;
	while (true) {
		adv2022_12::solve(map, activeTiles, visited);
		if (visited.contains(E)) break;
		moves++;
	}
	std::cout << "AdventOfCode2022_12_a: " << moves << std::endl;

	activeTiles.clear();
	activeTiles.push_back(E);
	visited.clear();
	visited.insert(E);
	moves = 1;
	while (!adv2022_12::solve2(map, activeTiles, visited)) {
		moves++;
	}
	std::cout << "AdventOfCode2022_12_b: " << moves << std::endl;

}