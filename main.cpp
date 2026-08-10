#include <iostream>
#include <memory>
#include <array>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class ArchManager {
private:
    bool loop = true;
    string main_menu = R"(       <--- ARCHGER MENU --->
    
    1. find & del Orphans
    0. exit
    )";

    string execCommand(string cmd) {
        array<char, 128> buffer;
        string result = "";

        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) return "";

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        pclose(pipe);
        return result;
    }

    void delOrphans(string get_orps) {
        if (get_orps.empty()) return;
        string cmd = "sudo pacman -Rns " + pkg;
        system(cmd.c_str());
        return;
    }

    int Orphans() {
        string orps = execCommand("pacman -Qtdq");
        string orps_backup = orps;
        if (orps.empty()) {
            cout << "You haven't got orphans!";
            return 0;
        } else {
            cout << orps << endl << "Write name of orphan which you do not want to delete: " << endl;
            string safeOrps;

            cin.ignore();
            getline(cin, safeOrps);
            cout << "This is your last chance to back out. (Y/n): ";
            string yorn;
            getline(cin, yorn);
            if (yorn.empty()) cout << "That's fine." << endl;
            else {
                if (yorn == "Y" || yorn == "y") {
                    cout << "That's fine" << endl;
                } else if (yorn == "N" || yorn == "n") {
                    cout << "It's ok.";
                    return 0;
                } else {
                    cout << "I’ll take that as a no." << endl;
                    return 0;
                }
            }

            stringstream ss(safeOrps);
            string word;
            while (ss >> word) {
                size_t pos = orps.find(word);

                if (pos != string::npos) orps.erase(pos, word.length());
                cout << "dbg: " << orps << " will delete." << endl; // DEGUB
                
            }

            delOrphans(orps);

            string new_orps = execCommand("pacman -Qtdq");
            if (new_orps.empty()) return 1;
            else {
                if (orps_backup == new_orps) return -1;
                else {
                    cout << "The ones left behind: " << new_orps;
                    return 1;
                }
            }
        }
    }

public:
    void run() {
        cout << "Archger started!" << endl;

        int input;

        while (loop) {
            cout << main_menu;
            cin >> input;
            switch(input) {
                case 0:
                    return;
                    break;
                case 1: {
                    int debug_code = Orphans();
                    if (debug_code == 1) cout << "The operation was successfully performed.";
                    else if (debug_code == -1) cout << "The operation failed.";
                    else if (debug_code == 0) cout << "The operation was halted.";
                    else cout << "The operation code was lost.";
                    break;
                }
                default:
                    cout << "Oups! What's mean?";
                    break;
            }
        }
    }
};

int main() {
    ArchManager app;
    app.run();
    return 0;
}