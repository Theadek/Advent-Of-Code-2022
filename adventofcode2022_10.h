#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_10 {
	void checkStrength(int& cycle, int& stop, int& signalStrength, int& reg, std::string& output) {
		//---Part 1---
		if (cycle == stop) {
			signalStrength += reg * cycle;
 			stop += 40;
		}

		//---Part 2---
		if ((cycle%40) >= reg && (cycle%40) <= reg + 2) {
			output += "#";
		}
		else {
			output += ".";
		}
	}
}


void AdventOfCode2022_10() {
	std::fstream input("input/input_10.txt");
	std::string buffer;
	int reg = 1;
	int cycle = 1;
	int nextStop = 20;
	int signalStrength = 0;
	std::string output = "";
	while (input >> buffer) {
		if (buffer == "noop") {
			adv2022_10::checkStrength(cycle, nextStop, signalStrength, reg, output);
			cycle++;
		}
		else {
			adv2022_10::checkStrength(cycle, nextStop, signalStrength, reg, output);
			cycle++;
			adv2022_10::checkStrength(cycle, nextStop, signalStrength, reg, output);
			cycle++;
			input >> buffer;
			reg += std::stoi(buffer);
		}
	}
	input.close();

	std::cout << "AdventOfCode2022_10_a: " << signalStrength << std::endl;
	std::cout << "AdventOfCode2022_10_b: " << std::endl;

	for (int i = 0; i < 6; i++) {
		std::cout << output.substr(i * 40, 40) << std::endl;
	}

}