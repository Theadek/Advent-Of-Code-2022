#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void AdventOfCode2022_01() {
	std::fstream input("input/input_01.txt");

	int currentSum = 0;
	std::string buffer = "";
	std::vector<int> elves;
	while (std::getline(input, buffer)) {
		if (buffer == "") {
			elves.push_back(currentSum);
			currentSum = 0;
		}
		else {
			currentSum += stoi(buffer);
		}
	}

	std::sort(elves.begin(), elves.end(), std::greater<int>());

	std::cout << "AdventOfCode2022_01_a: " << elves[0] << std::endl;
	std::cout << "AdventOfCode2022_01_b: " << elves[0] + elves[1] + elves[2] << std::endl;


	input.close();

}