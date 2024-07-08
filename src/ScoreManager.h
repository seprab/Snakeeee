//
// Created by Sergio Prada on 6/07/24.
//

#ifndef SNAKEEEEE_SCOREMANAGER_H
#define SNAKEEEEE_SCOREMANAGER_H

#include <string>
#include <vector>

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();
    void AddScore(const std::string& user, int score);
    std::vector<std::string> GetTopFiveScores();

private:
    void LoadScores();
    void SaveScores();
    const std::string m_FileName = "scores.txt";
    std::vector<std::pair<std::string, int>> m_Scores;
};


#endif //SNAKEEEEE_SCOREMANAGER_H
