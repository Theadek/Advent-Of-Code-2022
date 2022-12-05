#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_05 {

}

void AdventOfCode2022_05() {
	std::fstream input("input/input_05.txt");
	std::string buffer;
	std::vector<std::string> bufferLines;
	while (std::getline(input, buffer)) {
		if (buffer[1] == '1')break;
		bufferLines.push_back(buffer);
	}
	int NoLines = 0;
	for (auto& line : bufferLines) {
		if (NoLines < line.length())NoLines = line.length();
	}
	NoLines = (NoLines + 1) / 4;

	std::vector<std::vector<char>> stacks;
	stacks.resize(NoLines);

	for (int i = bufferLines.size()-1; i >= 0; i--) {
		bufferLines[i];
		for (int j = 0; 1 + 4 * j < bufferLines[i].size(); j++) {
			if (bufferLines[i][1 + 4 * j] != ' ') {
				stacks[j].push_back(bufferLines[i][1 + 4 * j]);
			}
		}
	}
	std::vector<std::vector<char>> stacks2 = stacks;

	int a, b, c;
	while (input >> buffer >> a >> buffer >> b >> buffer >> c) {
		//---Part1---
		for (int i = 0; i < a; i++) {
			stacks[c - 1].push_back(stacks[b - 1].back());
			stacks[b - 1].pop_back();
		}
		//---Part2---
		for (int i = a; i > 0; i--) {
			stacks2[c - 1].push_back(stacks2[b - 1][stacks2[b-1].size()-i]);
		}
		for (int i = 0; i < a; i++) {
			stacks2[b - 1].pop_back();
		}
	}
	input.close();

	//---Part1---
	std::string answer = "";
	for (auto& stack : stacks) {
		answer += stack.back();
	}
	std::cout << "AdventOfCode2022_05_a: " << answer << std::endl;

	//---Part2---
	std::string answer2 = "";
	for (auto& stack : stacks2) {
		answer2 += stack.back();
	}
	std::cout << "AdventOfCode2022_05_b: " << answer2 << std::endl;

}