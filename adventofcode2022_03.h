#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_03 {
	int getPriority(char& c) {
		if (c >= 'a' && c <= 'z') return (int)(c - 'a' + 1);
		else return (int)(c - 'A' + 27);
	}
}

void AdventOfCode2022_03() {
	std::fstream input("input/input_03.txt");
	std::string buffer;
	int sum = 0;
	while (input >> buffer) {
		std::string A = buffer.substr(0,					buffer.length() / 2);
		std::string B = buffer.substr(buffer.length() / 2,	buffer.length() / 2);
		bool found = false;
		for (char& a : A) {
			for (char& b : B) {
				if (a == b) {
					found = true;
					sum += adv2022_03::getPriority(a);
					break;
				}
			}
			if (found)break;
		}
		if (!found) {
			std::cout << "ERROR in line: " << buffer << std::endl;
		}
	}
	input.close();
	std::cout << "AdventOfCode2022_03_a: " << sum << std::endl;

	//---Part 2---
	sum = 0;
	input.open("input/input_03.txt");
	std::string elf1, elf2, elf3;
	while (input >> elf1 >> elf2 >> elf3) {
		bool found = false;
		for (char& a : elf1) {
			for (char& b : elf2) {
				if (a == b) {
					for (char& c : elf3) {
						if (a == c) {
							found = true;
							sum += adv2022_03::getPriority(a);
							break;
						}
					}
					if (found) break;
				}
			}
			if (found)break;
		}
	}

	std::cout << "AdventOfCode2022_03_b: " << sum << std::endl;
	input.close();

}