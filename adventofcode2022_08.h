#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_08 {

}

void AdventOfCode2022_08() {
	std::fstream input("input/input_08.txt");
	std::string buffer;
	std::vector<std::string> trees;
	while (input >> buffer) {
		trees.push_back(buffer);
	}
	input.close();
	int width = trees[0].length();
	std::vector<std::vector<int>> visibility;
	std::vector<std::vector<int>> distance;
	for (int i = 1; i < trees.size() - 1; i++) {
		std::vector<int> tmp(width - 2, 0);
		visibility.push_back(tmp);
		std::vector<int> tmp2(width - 2, 1);
		distance.push_back(tmp2);
	}

	//---Part 1---
	int visible = 2 * trees.size() + 2 * width - 4;
	for (int i = 1; i < trees.size() - 1; i++) {
		int currentMax = trees[i][0];
		for (int j = 1; j < width - 1; j++) { // from left
			if (trees[i][j] <= currentMax) {
				visibility[i - 1][j - 1]++;
			}
			else {
				currentMax = trees[i][j];
			}
		}
		currentMax = trees[i][width-1];
		for (int j = width - 2; j > 0; j--) { // from right
			if (trees[i][j] <= currentMax) {
				visibility[i - 1][j - 1]++;
			}
			else {
				currentMax = trees[i][j];
			}
		}
	}
	for (int j = 1; j < width - 1; j++) {
		int currentMax = trees[0][j];
		for (int i = 1; i < trees.size() - 1; i++) { // from up
			if (trees[i][j] <= currentMax) {
				visibility[i - 1][j - 1]++;
			}
			else {
				currentMax = trees[i][j];
			}
		}
		currentMax = trees[trees.size()-1][j];
		for (int i = trees.size()-2; i > 0; i--) { // from down
			if (trees[i][j] <= currentMax) {
				visibility[i - 1][j - 1]++;
			}
			else {
				currentMax = trees[i][j];
			}
		}
	}

	for (auto& row : visibility) {
		for (auto& column : row) {
			if (column != 4) visible++;
		}
	}

	//---Part 2---
	int maxScore = 0;
	for (int i = 1; i < trees.size() - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			int score = 1;
			int currentDistance = 0;
			for (int k = j - 1; k >= 0; k--) { // go left
				if (trees[i][j] > trees[i][k]) currentDistance++;
				else {
					currentDistance++;
					break;
				}
			}
			score *= currentDistance;
			currentDistance = 0;
			for (int k = j + 1; k <= width - 1; k++) { //go rigth
				if (trees[i][j] > trees[i][k]) currentDistance++;
				else {
					currentDistance++;
					break;
				}
			}
			score *= currentDistance;
			currentDistance = 0;
			for (int k = i - 1; k >= 0; k--) { // go up
				if (trees[i][j] > trees[k][j]) currentDistance++;
				else {
					currentDistance++;
					break;
				}
			}
			score *= currentDistance;
			currentDistance = 0;
			for (int k = i + 1; k <= trees.size()-1; k++) { // go up
				if (trees[i][j] > trees[k][j]) currentDistance++;
				else {
					currentDistance++;
					break;
				}
			}
			score *= currentDistance;
			maxScore = std::max(score, maxScore);
		}
	}

	std::cout << "AdventOfCode2022_08_a: " << visible << std::endl;
	std::cout << "AdventOfCode2022_08_b: " << maxScore << std::endl;

}