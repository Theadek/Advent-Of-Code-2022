#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

// TODO(11)
// Make monkeys remember last number of investigations, so it doesn't need to do it again and again

namespace adv2022_11 {
	struct Operation {
		char operation;
		int value;
		Operation(char operation, int value) {
			this->operation = operation;
			this->value = value;
		}
	};
	struct Item {
		int startValue;
		std::vector<Operation> operations;
	};

	class Monkey {
	public:
		std::queue<long long> holds;
		std::queue<Item*> holds2;
		char operation;
		int operationNumber;
		int division;
		int trueThrow;
		int falseThrow;
		int business;
		int business2;

		void Throw(std::vector<adv2022_11::Monkey*>& Monkeys) {
			while (!holds.empty()) {
				int value = holds.front();
				holds.pop();
				if (operation == '+') {
					if (operationNumber == 0) value += value;
					else value += operationNumber;
				}
				else { // '*'
					if (operationNumber == 0) value *= value;
					else value *= operationNumber;
				}
				value /= 3;
				if (value % division == 0) Monkeys[trueThrow]->holds.push(value);
				else Monkeys[falseThrow]->holds.push(value);
				business++;
			}
		}
		void Throw2(std::vector<adv2022_11::Monkey*>& Monkeys) {
			while (!holds2.empty()) {
				Item* item = holds2.front();
				holds2.pop();
				if (operation == '+') {
					if (operationNumber == 0) {
						item->operations.emplace_back('+', 0);
					}
					else {
						item->operations.emplace_back('+', operationNumber);
					}
				}
				else { // '*'
					if (operationNumber == 0) {
						item->operations.emplace_back('*', 0);
					}
					else {
						item->operations.emplace_back('*', operationNumber);
					}
				}
				int value = item->startValue % division;
				for (auto& op : item->operations) {
					if (op.operation == '+') {
						if (op.value == 0) value += value;
						else value += op.value;
						value %= division;
					}
					else {
						if (op.value == 0) value *= value;
						else value *= op.value;
						value %= division;
					}
				}
				if (value % division == 0) Monkeys[trueThrow]->holds2.push(item);
				else Monkeys[falseThrow]->holds2.push(item);
				business2++;
			}
		}
	};
}


void AdventOfCode2022_11() {
	std::fstream input("input/input_11.txt");
	std::string buffer;
	int numberOfMonkeys = 0;
	std::vector<adv2022_11::Monkey*> Monkeys;
	while (input >> buffer >> buffer) {
		adv2022_11::Monkey* tmpMonkey = new adv2022_11::Monkey();
		numberOfMonkeys = std::stoi(buffer);
		input >> buffer >> buffer >> buffer;
		while (buffer != "Operation:") {
			tmpMonkey->holds.push(std::stoi(buffer));
			adv2022_11::Item* item = new adv2022_11::Item();
			item->startValue = std::stoi(buffer);
			tmpMonkey->holds2.push(item);
			input >> buffer;
		}
		input >> buffer >> buffer >> buffer >> buffer;
		tmpMonkey->operation = buffer[0];
		input >> buffer;
		if (buffer == "old") {
			tmpMonkey->operationNumber = 0; //Special operation
		}
		else {
			tmpMonkey->operationNumber = std::stoi(buffer);
		}
		input >> buffer >> buffer >> buffer >> buffer;
		tmpMonkey->division = std::stoi(buffer);
		input >> buffer >> buffer >> buffer >> buffer >> buffer >> buffer;
		tmpMonkey->trueThrow = std::stoi(buffer);
		input >> buffer >> buffer >> buffer >> buffer >> buffer >> buffer;
		tmpMonkey->falseThrow = std::stoi(buffer);
		tmpMonkey->business = 0;
		tmpMonkey->business2 = 0;
		Monkeys.push_back(tmpMonkey);
	}
	input.close();

	for (int i = 0; i < 20; i++) {
		for (auto& monkey : Monkeys) {
			monkey->Throw(Monkeys);
		}
	}
	std::vector<int> MonkeyBusiness;
	for (auto& monkey : Monkeys) {
		MonkeyBusiness.push_back(monkey->business);
	}
	std::sort(MonkeyBusiness.begin(), MonkeyBusiness.end());

	for (int i = 0; i < 10000; i++) {
		for (auto& monkey : Monkeys) {
			monkey->Throw2(Monkeys);
		}
	}
	std::vector<int> MonkeyBusiness2;
	for (auto& monkey : Monkeys) {
		MonkeyBusiness2.push_back(monkey->business2);
	}
	std::sort(MonkeyBusiness2.begin(), MonkeyBusiness2.end());



	std::cout << "AdventOfCode2022_11_a: " << MonkeyBusiness[numberOfMonkeys - 1] * MonkeyBusiness[numberOfMonkeys] << std::endl;
	std::cout << "AdventOfCode2022_11_b: " << (long long)((long long)MonkeyBusiness2[numberOfMonkeys - 1] * (long long)MonkeyBusiness2[numberOfMonkeys]) << std::endl;

	for (auto& monkey : Monkeys) {
		while (!monkey->holds2.empty()) {
			adv2022_11::Item* item = monkey->holds2.front();
			monkey->holds2.pop();
			delete item;
		}
		delete monkey;
	}
	Monkeys.clear();
}