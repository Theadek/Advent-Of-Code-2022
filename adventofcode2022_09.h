#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>


namespace adv2022_09 {

	int normalize(int& x) {
		return x / std::abs(x);
	}

	bool moveTail(
		std::pair<int, int>& headPosition,
		std::pair<int, int>& tailPosition) {

		bool moved = true;

		std::pair<int, int> distance = { headPosition.first - tailPosition.first,
										headPosition.second - tailPosition.second };
		if (std::abs(distance.first) == 2) {
			tailPosition.first += normalize(distance.first);
			if (std::abs(distance.second) >= 1)
				tailPosition.second += normalize(distance.second);
		}
		else if(std::abs(distance.second) == 2){
			tailPosition.second += normalize(distance.second);
			if (std::abs(distance.first) >= 1)
				tailPosition.first += normalize(distance.first);
		}
		else {
			moved = false;
		}
		return moved;
	}
}

std::pair<int, int> operator+(std::pair<int, int> lhs, std::pair<int, int> rhs) {
	return { lhs.first + rhs.first, lhs.second + rhs.second };
}

void AdventOfCode2022_09() {
	std::fstream input("input/input_09.txt");
	std::string direction;
	int number;

	//std::unordered_set<std::pair<int, int>> visited;
	std::unordered_set<int> visited;
	visited.insert({ 0,0 });
	std::unordered_set<int> visited2;
	visited2.insert({ 0,0 });
	std::pair<int, int> headPosition = { 0,0 };
	std::pair<int, int> tailPosition = { 0,0 };
	std::pair<int, int> tailsPositions[8] = { {0, 0}, {0, 0},
											  {0, 0}, {0, 0},
											  {0, 0}, {0, 0},
											  {0, 0}, {0, 0} };
	std::pair<int, int> move = { 0,0 };

	while (input >> direction >> number) {
		if (direction == "U")		move = {  0, 1 };
		else if (direction == "D")	move = {  0,-1 };
		else if (direction == "L")	move = { -1, 0 };
		else if (direction == "R")	move = {  1, 0 };

		for (int i = 0; i < number; i++) {
			headPosition = headPosition + move;
			if(adv2022_09::moveTail(headPosition, tailPosition))
				visited.insert(tailPosition.first * 100000 + tailPosition.second);
			adv2022_09::moveTail(tailPosition, tailsPositions[0]);
			bool moved = false;
			for (int j = 0; j < 7; j++) {
				moved = adv2022_09::moveTail(tailsPositions[j], tailsPositions[j+1]);
			}
			if (moved) {
				visited2.insert(tailsPositions[7].first * 100000 + tailsPositions[7].second);
			}
		}
	}
	input.close();


	std::cout << "AdventOfCode2022_09_a: " << visited.size() << std::endl;
	std::cout << "AdventOfCode2022_09_b: " << visited2.size() << std::endl;

}