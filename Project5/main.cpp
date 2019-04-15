#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<string> mazeStrings;
    ifstream file("maze.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            //cout << line << endl;
            mazeStrings.push_back(line);
        }
    }
    file.close();
    int mazeR = atoi(mazeStrings[0].substr(0, mazeStrings[0].find(' ')).c_str());
    int mazeC = atoi(mazeStrings[0].substr(3, mazeStrings[0].find(' ')).c_str());
    int start = atoi(mazeStrings[1].substr(0, mazeStrings[0].find(' ')).c_str());
    int finish = atoi(mazeStrings[1].substr(2, mazeStrings[0].find(' ')).c_str());
    char maze[mazeR][mazeC];
    cout << endl;
    for (int i = 2; i < mazeStrings.size(); i++) {
        for (int j = 0; j < mazeStrings[i].length(); j++) {
            maze[i - 2][j] = mazeStrings[i][j];
        }
    };

    //Loop through the maze and print
    for(int i = 0; i < mazeR; i++){
        for (int j = 0; j < mazeC; j++){
            cout << maze[i][j];
        }
        cout << endl;
    }

}