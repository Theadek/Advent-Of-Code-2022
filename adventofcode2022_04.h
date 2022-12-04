#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_04 {
	void getRange(std::string& input, int& a, int& b, int& c, int& d) {
		int index = input.find(",");
		std::string first = input.substr(0, index);
		std::string second = input.substr(index + 1, input.length() - index - 1);

		index = first.find("-");
		a = std::stoi(first.substr(0, index));
		b = std::stoi(first.substr(index + 1, first.length() - index - 1));

		index = second.find("-");
		c = std::stoi(second.substr(0, index));
		d = std::stoi(second.substr(index + 1, second.length() - index - 1));
	}

	bool checkCoverage1(int& a, int& b, int& c, int& d) {
		return ((a <= c && b >= d) || (c <= a && d >= b));
	}

	bool checkCoverage2(int& a, int& b, int& c, int& d) {
		return std::max(a,c) <= std::min(b,d);
	}
}

void AdventOfCode2022_04() {
	std::fstream input("input/input_04.txt");
	int sum1 = 0;
	int sum2 = 0;
	std::string buffer;
	while (input >> buffer) {
		int a, b, c, d;
		adv2022_04::getRange(buffer, a, b, c, d);
		if (adv2022_04::checkCoverage1(a, b, c, d)) {
			sum1++;
		}
		if (adv2022_04::checkCoverage2(a, b, c, d)) {
			sum2++;
		}

	}

	std::cout << "AdventOfCode2022_04_a: " << sum1 << std::endl;
	std::cout << "AdventOfCode2022_04_b: " << sum2 << std::endl;
	input.close();

}