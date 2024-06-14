#include <fstream>

#include <sstream>

#include <iostream>

void PrintOptions() {
    system("cls");
    std::cout << "What would you like to do?" << std::endl <<
        "1. View all data entries" << std::endl <<
        "2. Add a data entry" << std::endl <<
        "3. Remove a data entry" << std::endl;
}
bool Finished() {
    char decision;
    std::cout << "Are you finished? Y/N" << std::endl;
    std::cin >> decision;
    if (decision == 'Y' || decision == 'y') {
        return false;
    }
    else {
        return true;
    }
}
void ViewEntry() {
    std::ifstream fin("ItemList.txt");
    std::string line;
    int linecount = 0;

    system("cls");
    while (std::getline(fin, line)) {
        linecount++;
        std::cout << linecount << ": " << line << std::endl;
    }
    std::cout << "Viewed all data entries" << std::endl;
}
void AddEntry() {
    std::ifstream fin("ItemList.txt");
    std::string line;
    std::string entry;
    std::ofstream temp("temp.txt");
    system("cls");
    ViewEntry();
    std::cin >> entry;
    while (getline(fin, line)) {
        temp << line << std::endl;
    }
    temp << entry << std::endl;
    temp.close();
    fin.close();
    remove("ItemList.txt");
    if (rename("temp.txt", "ItemList.txt")) {
        std::cout << "Error renaming";
        return;
    }
    std::cout << "Added a data entry" << std::endl;
}
void SubEntry() {

    int SubEntry;
    int linecount = 0;
    std::ifstream fin("ItemList.txt");
    std::string line;
    std::ofstream temp("temp.txt");
    system("cls");
    ViewEntry();
    std::cout << "Which entry would you like to remove?" << std::endl;
    std::cin >> SubEntry;
    if (!std::cin.fail()) {
        while (getline(fin, line)) {
            linecount++;
            if (linecount != SubEntry) {
                temp << line << std::endl;
            }
        }
        temp.close();
        fin.close();
        remove("ItemList.txt");
        if (rename("temp.txt", "ItemList.txt")) {
            std::cout << "Error renaming";
            return;
        }
        std::cout << "Removed entry: " << SubEntry << std::endl;
    }
    else {
        do {
            std::cout << "Failed to delete entry due to incorrect input" << std::endl;
            std::cin.clear();
        } while (std::cin.fail());
    }
}
int main() {
    int ans1;
    bool FCheck = true;
    do {
        PrintOptions();
        std::cin >> ans1;
        switch (ans1) {
        case 1:
            ViewEntry();
            FCheck = Finished();
            break;
        case 2:
            AddEntry();
            FCheck = Finished();
            break;
        case 3:
            SubEntry();
            FCheck = Finished();
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
            FCheck = true;
            break;
        }
    } while (FCheck == true);

    return 0;
}