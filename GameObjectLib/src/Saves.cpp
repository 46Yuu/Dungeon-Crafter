#include "Saves.h"

Saves::Saves() {
    std::ifstream statsFile("Assets/Saves/Rankings.txt");
    if (!statsFile.is_open()) {
        std::cout << "Failed to open the file Assets/Saves/Rankings.txt." << std::endl;
    }
    float size = GetFileSize();
    std::string data;
    if (statsFile.is_open()) {
        for (float i = 0; i < size; i++) {
            std::getline(statsFile, data);
            float score = std::stof(data);
            leaderboard.push_back(score);
        }
    }
    statsFile.close();
}

float Saves::GetFileSize() {
    std::ifstream file("Assets/Saves/Rankings.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open the file Assets/Saves/Rankings.txt." << std::endl;
    }
    float lineCount = 0;
    std::string line;

    // Read the file line by line
    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();
    return lineCount;
}

void Saves::AddNewScore(sf::Time& newTime) {
    if (!leaderboard.empty()) {
        auto it = leaderboard.begin();
        while (it != leaderboard.end() && newTime.asSeconds() > *it) {
            ++it;
        }
        leaderboard.insert(it, newTime.asSeconds());
    }
    else {
        leaderboard.push_back(newTime.asSeconds());
    }
    RewriteSaveFile();
}

std::vector<std::string> Saves::GetFormatedLeaderboard() {
    std::vector<std::string> formatedLeaderboard;
    for (float ScoreAsSeconds : leaderboard) {
        sf::Time asSfTime = sf::seconds(ScoreAsSeconds);
        formatedLeaderboard.push_back(sfTimeToString(asSfTime));
    }
    return formatedLeaderboard;
}

std::string Saves::sfTimeToString(sf::Time time) {
    int totalMilliseconds = time.asMilliseconds();
    int milliseconds = totalMilliseconds % 1000;
    int totalSeconds = totalMilliseconds / 1000;
    int seconds = totalSeconds % 60;
    int minutes = totalSeconds / 60;

    char formattedTime[9];
    std::snprintf(formattedTime, sizeof(formattedTime), "%02d:%02d:%03d", minutes, seconds, milliseconds);

    return formattedTime;
}


void Saves::RewriteSaveFile() {
    std::string newContent;
    for (float scoreSeconds : leaderboard) {
        newContent = newContent + std::to_string(scoreSeconds) + "\n";
    }
    std::ofstream file("Assets/Saves/Rankings.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open the file Assets/Saves/Rankings.txt." << std::endl;
    }
    file << newContent;
    file.close();
}