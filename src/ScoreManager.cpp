//
// Created by Sergio Prada on 6/07/24.
//
#include <iostream>
#include <fstream>
#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
    m_Scores = std::vector<std::pair<std::string, int>>();
    LoadScores();
}

ScoreManager::~ScoreManager()= default;

void ScoreManager::AddScore(const std::string& user, int score)
{
    m_Scores.emplace_back(user, score);
    SaveScores();
}

std::vector<std::string> ScoreManager::GetTopFiveScores()
{
    std::sort(m_Scores.begin(), m_Scores.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
    {
        return a.second > b.second;
    });

    int count = m_Scores.size() < 5 ? m_Scores.size() : 5;
    std::vector<std::string> topFive;
    topFive.reserve(count);
for (int i=0; i<count; i++)
    {
        topFive.push_back(m_Scores[i].first + " " + std::to_string(m_Scores[i].second));
    }
    return topFive;
}

void ScoreManager::LoadScores()
{
    m_Scores.clear();

    // Check if the file exists
    std::ifstream file(m_FileName.c_str());
    if (!file.good())
    {
        // Create the file
        std::ofstream fileCreation(m_FileName.c_str());
        if (!fileCreation.is_open())
        {
            std::cerr << "Error creating the file" << std::endl;
            return;
        }
        fileCreation.close();
        return;
    }

    // Open the file
    if (!file.is_open())
    {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }
    // Read the scores
    std::string line;
    while (std::getline(file, line))
    {
        // Split the line into user and score
        size_t pos = line.find(',');
        std::string user = line.substr(0, pos);
        int score = std::stoi(line.substr(pos + 1));
        m_Scores.emplace_back(user, score);
    }
    // Close the file
    file.close();
}

void ScoreManager::SaveScores()
{
    // Open the file
    std::ofstream file(m_FileName.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }
    // Write the scores
    for (const auto& score : m_Scores)
    {
        file << score.first << "," << score.second << std::endl;
    }
    // Close the file
    file.close();
}
