#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void usage() {
  cout << "Usage: intline <file>\n"
  "Reads the following newline-separated commands from stdin:\n"
  "<x> <y>: prints the lines starting from x up to and including y\n"
  "<x> <c> <y>: prints the lines using vim relativenumber, where"
    "c is the current line and x and y are relative line numbers,"
    "negative if behind cursor\n"
  "r: reloads the file\n";
  exit(0);
}

vector<string> readlines(string filepath) {
  ifstream file(filepath);
  string line;
  vector<string> lines;
  while (getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<string> split(string line) {
  // commence autismo
  auto linestream = stringstream(line);
  vector<string> tokens;
  string token;
  while (linestream >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

void printlines(vector<string> lines, int start, int end) {
  for (auto it = lines.begin() + start; it != lines.end()
      && it != lines.begin() + end; it++) {
    cout << *it << endl;
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    usage();
  }
  string filepath(argv[1]);
  vector<string> lines = readlines(filepath);
  string command;
  while (1) {
    getline(cin, command);
    if (cin.eof()) {
      // ctrl-d reached
      break;
    }
    int x, y, c;
    if (command == "r") {
      lines = readlines(filepath);
    } else if (sscanf(command.c_str(), "%d %d", &x, &y) == 2 
        && y >= x && x >= 1) {
      printlines(lines, x - 1, y);
    } else if (sscanf(command.c_str(), "%d %d %d", &x, &c, &y) == 3
      && y >= x && c + x >= 1) {
      printlines(lines, c + x - 1, c + y);
    } else {
      cerr << "error: invalid command" << endl;
    }
  }
  cerr << "intline exiting" << endl;
}
