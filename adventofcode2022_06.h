#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_06 {
	int solve06(std::string& buffer, int howLong) {
		for (int i = 0; i < buffer.length() - howLong - 1;) {
			bool doublet = false;
			for (int j = howLong - 1; j > 0; j--) {
				for (int k = j - 1; k >= 0; k--) {
					if (buffer[i + j] == buffer[i + k]) {
						doublet = true;
						i += k + 1;
						break;
					}
				}
				if (doublet)break;
			}
			if (!doublet) {
				return  i + howLong;
				break;
			}
		}
	}
}

void AdventOfCode2022_06() {
	std::fstream input("input/input_06.txt");
	std::string buffer;
	input >> buffer;
	input.close();

	//---Part 1---
	/*int answer1 = 0;
	for (int i = 3; i < buffer.length();) {
		if (buffer[i] == buffer[i - 1]) {
			i += 3;
			continue;
		}
		else if (buffer[i] == buffer[i - 2]) {
			i += 2;
			continue;
		}
		else if (buffer[i] == buffer[i - 3]) {
			i += 1;
			continue;
		}
		else if (buffer[i - 1] == buffer[i - 2]) {
			i += 2;
			continue;
		}
		else if (buffer[i - 1] == buffer[i - 3]) {
			i += 1;
			continue;
		}
		else if (buffer[i - 2] == buffer[i - 3]) {
			i += 1;
			continue;
		}
		else {
			answer1 = i+1;
			break;
		}
	}*/
	int answer1 = adv2022_06::solve06(buffer, 4);
	std::cout << "AdventOfCode2022_06_a: " << answer1 << std::endl;

	//---Part 2---
	/*int answer2 = 0;
	for (int i = 0; i < buffer.length() - 13;) {
		bool doublet = false;
		for (int j = 13; j > 0 ; j--) {
			for (int k = j - 1; k >= 0; k--) {
				if (buffer[i + j] == buffer[i + k]) {
					doublet = true;
					i += k + 1;
					break;
				}
			}
			if (doublet)break;
		}
		if (!doublet) {
			answer2 = i + 14;
			break;
		}
	}*/
	int answer2 = adv2022_06::solve06(buffer, 14);
	std::cout << "AdventOfCode2022_06_b: " << answer2 << std::endl;

}