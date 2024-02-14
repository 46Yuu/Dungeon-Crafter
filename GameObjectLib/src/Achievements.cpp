#include "Achievements.h"

Achievements::Achievements() {
    std::ifstream achievementFile("Assets/Saves/Achievements.txt");
    std::string data;
    if (achievementFile.is_open()) {
        for (float i = 0; i < allAchievementsAmount; i++) {
            std::getline(achievementFile, data);
            float score = std::stof(data);
            PlayerActualStats.push_back(score);
        }
    }
    achievementFile.close();
}

float Achievements::GetFileSize() {
    std::ifstream file("Assets/Saves/Rankings.txt");
    float lineCount = 0;
    std::string line;

    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();
    return lineCount;
}

std::string Achievements::AllAchievementsToString(){
    std::string achievementsInfos;
    for (int i = 0; i < allAchievementsAmount; i++) {
        if (i == 0) {//Games played
            achievementsInfos = "Play 5 games : " + std::to_string(PlayerActualStats.at(i)) + " / " + std::to_string(AchievementTargetList.at(i)) + "\n";
        }
    }
    return achievementsInfos;
}

void Achievements::Update(AchievementType _type) {
    switch (_type)
    {
    case AchievementType::GamePlayed:
        PlayerActualStats.at(0)++;
        RewriteAchievementsFile();
        break;
    case AchievementType::Default:
        break;
    default:
        break;
    }

}

void Achievements::RewriteAchievementsFile() {
    std::string newContent;
    for (float statsAchievement : PlayerActualStats) {
        newContent = newContent + std::to_string(statsAchievement) + "\n";
    }
    std::ofstream file("Assets/Saves/Achievements.txt");
    file << newContent;
    file.close();
}