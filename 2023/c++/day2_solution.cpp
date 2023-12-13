/*
1. Read line (1 game)
2. Get game ID
3. Split line into sets by semicolon
4. Split sets into individual draws
5. Count up for each draw and check valid, this game is valid if all draws are
valid
*/

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define RED "red"
#define BLUE "blue"
#define GREEN "green"

int get_game_id_and_cut_str(std::string *s);
std::vector<std::string> split_into_sets(std::string line);

std::map<std::string, int> MAX_COUNTS = {{RED, 12}, {BLUE, 14}, {GREEN, 13}};

int main() {
  std::ifstream input("day2_input.txt");

  if (!input.is_open()) {
    perror("ERROR - failed to open file:");

    return -1;
  }

  int total = 0;
  std::string line;
  while (std::getline(input, line)) {
    int game_id = get_game_id_and_cut_str(&line);

    bool valid = true;
    std::string color;
    int count;
    std::vector<std::string> sets = split_into_sets(line);

    for (auto set : sets) {
      std::istringstream iss(set);
      std::map<std::string, int> counts = {{RED, 0}, {BLUE, 0}, {GREEN, 0}};

      while (iss >> count) {
        iss >> color;

        color.erase(std::remove(color.begin(), color.end(), ','), color.end());

        counts[color] += count;
      }

      for (auto [color, count] : counts) {
        if (count > MAX_COUNTS[color]) {
          valid = false;
        }
      }
    }

    if (valid) {
      total += game_id;
    }
  }

  std::cout << "P1 TOTAL: " << total << std::endl;
  return 0;
}

int get_game_id_and_cut_str(std::string *s) {
  size_t colon_pos = s->find(":");

  int id = strtol(s->substr(4, colon_pos).c_str(), NULL, 10);

  *s = s->substr(colon_pos + 2, s->length() - colon_pos - 1);

  return id;
}

std::vector<std::string> split_into_sets(std::string line) {
  std::vector<std::string> draws;

  size_t pos = 0;
  while (pos != std::string::npos) {
    pos = line.find(";");
    draws.push_back(line.substr(0, pos));
    line = line.substr(pos + 2, line.length() - pos - 1);
  }

  return draws;
}