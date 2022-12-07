#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


namespace adv2022_07 {
	class Node {
	public:
		std::string name;
		virtual int size() const = 0;
	};
	class File : virtual public Node{
	public:
		int m_size;
		int size() const {
			return m_size;
		}
		File(int m_size, std::string name) : m_size(m_size){
			this->name = name;
		}
		~File(){}
	};
	class Directory : virtual public Node{
	public:
		std::vector<Directory*> containsDirs;
		std::vector<File*> containsFiles;
		Directory* parent;
		int size() const {
			int sum = 0;
			for (Directory* a : containsDirs) {
				sum += a->size();
			}
			for (File* a : containsFiles) {
				sum += a->size();
			}
			return sum;
		}
		Directory(std::string name, Directory* parent){
			this->name = name;
			this->parent = parent;
		}
		~Directory(){}
	};
}

void AdventOfCode2022_07() {
	std::fstream input("input/input_07.txt");
	std::string buffer;

	adv2022_07::Directory* root = new adv2022_07::Directory("\/", nullptr);
	std::vector<adv2022_07::File*> Files;
	std::vector<adv2022_07::Directory*> Directories;
	Directories.push_back(root);
	adv2022_07::Directory* currentDir = root;

	input >> buffer; // Eat first $, later used as stop sign for ls
	bool end = false;
	while (input >> buffer) {
		if (buffer == "cd") {
			input >> buffer;
			if (buffer == "..") {
				currentDir = currentDir->parent;
			}
			else if (buffer == "\/") {
				currentDir = root;
			}
			else {
				for (adv2022_07::Directory* dir : currentDir->containsDirs) {
					if (dir->name == buffer) {
						currentDir = dir;
						break;
					}
				}
			}
			input >> buffer; // Eat $
		}
		else if (buffer == "ls") {
			while (true) {
				if (!(input >> buffer)) {
					end = true;
					break;
				}
				if (buffer == "$") break;
				if (buffer == "dir") {
					input >> buffer;
					adv2022_07::Directory* temp = new adv2022_07::Directory(buffer, currentDir);
					currentDir->containsDirs.push_back(temp);
					Directories.push_back(temp);
				}
				else {
					std::string name;
					input >> name;
					adv2022_07::File* temp = new adv2022_07::File(std::stoi(buffer), name);
					currentDir->containsFiles.push_back(temp);
					Files.push_back(temp);
				}
			}
		}
		if (end)break;
	}
	input.close();

	int answer1 = 0;
	for (adv2022_07::Directory* x : Directories) {
		int size = x->size();
		if (size <= 100000) answer1 += size;
	}
	std::cout << "AdventOfCode2022_07_a: " << answer1 << std::endl;

	int answer2 = 70000000;
	int threshold = root->size() - 40000000;
	for (adv2022_07::Directory* x : Directories) {
		int size = x->size();
		if ((size >= threshold) && (size < answer2)) answer2 = size;
	}
	std::cout << "AdventOfCode2022_07_b: " << answer2 << std::endl;

	for (adv2022_07::File* x : Files) {
		delete x;
	}
	Files.clear();
	for (adv2022_07::Directory* x : Directories) {
		delete x;
	}
	Directories.clear();
}