#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void usage() {
  cout << "Usage: intline <file>\n"
  "Reads the following newline-separated commands from stdin:\n"
  "<x>: prints line x \n"
  "<x> <y>: prints the lines starting from x up to and including y\n"
  "<x> <y> <c>: prints the lines using vim relativenumber, where"
    "c is the current line and x and y are relative line numbers,"
    "negative if behind cursor\n"
  "p <whatever>: prints everything after the first p token verbatim, as a line\n"
  "r: reloads the file\n";
  exit(0);
}

vector<string> readlines(string filepath) {
  ifstream file(filepath);
  if (file.fail()) {
    cerr << "Cannot open file " << filepath << ", terminating" << endl;
    exit(-1);
  }
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
  if (start > lines.size()) {
    return;
  }
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
    } else {
      int numtok = sscanf(command.c_str(), "%d %d %d", &x, &y, &c);
      if (numtok == 1 && x > 0) {
        printlines(lines, x - 1, x);
      } else if (numtok == 2 && x > 0 && y >= x) {
        printlines(lines, x - 1, y);
      } else if (numtok == 3 && c + x > 0 && y >= x) {
        printlines(lines, c + x - 1, c + y);
      } else if (command.find("p ") == 0) {
        cout << command.substr(strlen("p ")) << endl;
      } else {
        cerr << "error: invalid input (C-d to exit)" << endl;
      }
    }
  }
  cerr << "intline exiting" << endl;
}
