#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

enum class AchievementType
{
	GamePlayed,
	Default,
};
class Achievements
{
public :
	Achievements();
	~Achievements() = default;
	
	float GetFileSize();
	void Update(AchievementType _type);
	std::string AllAchievementsToString();
	void RewriteAchievementsFile();

private:
	std::vector<float> AchievementTargetList;
	float allAchievementsAmount = 1;
	std::vector<float> PlayerActualStats;
};