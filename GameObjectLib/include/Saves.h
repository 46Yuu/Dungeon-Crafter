#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


class Saves
{
public: 
	Saves();
	~Saves() = default;
	std::vector<float> GetLeaderboard() { return leaderboard; }
	void AddNewScore(sf::Time& newTime);
	std::string sfTimeToString(sf::Time time);
	std::vector<std::string> GetFormatedLeaderboard();
	void RewriteSaveFile();
	float GetFileSize();
private:
	std::vector<float> leaderboard;
};