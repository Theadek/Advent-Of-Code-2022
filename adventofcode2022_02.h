#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_02{
	int Points(char enemy, char me) {
		if (enemy == 'A') { // Enemy picks Rock
			if (me == 'X') return 3 + 1;
			if (me == 'Y') return 6 + 2;
			if (me == 'Z') return 0 + 3;
		}
		if (enemy == 'B') { // Enemy picks Paper
			if (me == 'X') return 0 + 1;
			if (me == 'Y') return 3 + 2;
			if (me == 'Z') return 6 + 3;
		}
		if (enemy == 'C') { // Enemy picks Scissors
			if (me == 'X') return 6 + 1;
			if (me == 'Y') return 0 + 2;
			if (me == 'Z') return 3 + 3;
		}
	}
	int Points2(char enemy, char me) {
		if (me == 'X') { // I have to lose
			if (enemy == 'A') return 0 + 3;
			if (enemy == 'B') return 0 + 1;
			if (enemy == 'C') return 0 + 2;
		}
		if (me == 'Y') { // I have to draw
			if (enemy == 'A') return 3 + 1;
			if (enemy == 'B') return 3 + 2;
			if (enemy == 'C') return 3 + 3;
		}
		if (me == 'Z') { // I have to win
			if (enemy == 'A') return 6 + 2;
			if (enemy == 'B') return 6 + 3;
			if (enemy == 'C') return 6 + 1;
		}
	}
}

void AdventOfCode2022_02() {
	std::fstream input("input/input_02.txt");
	//ABC - ROCK,PAPER,SCISSORS
	//XYZ - ROCK,PAPER,SCISSORS
	char enemy, me;
	int sum = 0;
	int sum2 = 0;
	while (input >> enemy >> me) {
		sum += adv2022_02::Points(enemy, me);
		sum2 += adv2022_02::Points2(enemy, me);
	}

	std::cout << "AdventOfCode2022_02_a: " << sum << std::endl;
	std::cout << "AdventOfCode2022_02_b: " << sum2 << std::endl;


	input.close();

}