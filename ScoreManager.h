#pragma once

#include <map>
#include <string>
#include <vector>
#include <filesystem>

class ScoreManager {
private:
    std::map<std::string, int> scores;
    std::filesystem::path filename;

public:
    ScoreManager();

    void submitScore(const std::string& name, int score);
    std::vector<std::pair<std::string, int>> getTopScores(int count = 3) const;

private:
    void loadFromFile();
    void saveToFile() const;
};