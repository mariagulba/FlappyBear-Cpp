#include "ScoreManager.h"
#include <fstream>
#include <filesystem>
#include <thread>
#include <ranges>
#include <algorithm>

namespace fs = std::filesystem;

ScoreManager::ScoreManager() {
    fs::path dataDir = fs::current_path() / "data";
    fs::create_directories(dataDir);
    filename = (dataDir / "scores.txt").string();

    loadFromFile();
}

void ScoreManager::submitScore(const std::string& name, int score) {
    if (scores[name] < score) {
        scores[name] = score;

        // Zapis do pliku w osobnym w¹tku
        std::thread saveThread([this]() {
            saveToFile();
            });
        saveThread.detach(); // Uruchom jako niezale¿ny w¹tek
    }
}

std::vector<std::pair<std::string, int>> ScoreManager::getTopScores(int count) const {

    std::vector<std::pair<std::string, int>> sorted;

    for (const auto& pair : scores) {
        sorted.push_back(pair);
    }

    
    std::ranges::sort(sorted, std::greater{}, &std::pair<std::string, int>::second);

    if (sorted.size() > static_cast<size_t>(count)) {
        sorted.resize(count);
    }

    return sorted;
}

void ScoreManager::loadFromFile() {
    std::ifstream in(filename);
    if (!in) return;

    scores.clear();
    std::string name;
    int score;

    while (in >> name >> score) {
        scores[name] = score;
    }

    in.close();
}

void ScoreManager::saveToFile() const {
    std::ofstream out(filename);
    if (!out) return;

    for (const auto& entry : scores) {
        out << entry.first << " " << entry.second << "\n";
    }

    out.close();
}