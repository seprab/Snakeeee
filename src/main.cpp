#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"
#include "ScoreManager.h"

void Play(size_t gridWidth, size_t gridHeight, const std::shared_ptr<Renderer>& renderer, size_t frameTime, const std::string& username, std::shared_ptr<ScoreManager>& scoreManager);

int main()
{
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    std::unique_ptr<Menu> menu = std::make_unique<Menu>(renderer->GetRenderer());
    std::shared_ptr<ScoreManager> scoreManager = std::make_shared<ScoreManager>();

    std::string username;
    menu->RenderUsernameScreen(username);
    bool running = true;
    while(running)
    {
        Menu::OPTIONS option = menu->Show();
        switch (option)
        {
            case Menu::OPTIONS::PLAY:
                std::cout << "Play option selected" << std::endl;
                Play(kGridWidth, kGridHeight, renderer, kMsPerFrame, username, scoreManager);
            case Menu::OPTIONS::SCOREBOARD:
                std::cout << "Scoreboard option selected" << std::endl;
                menu->RenderScoreboard(scoreManager);
                break;
            case Menu::OPTIONS::QUIT:
                std::cout << "Quit option selected" << std::endl;
                running = false;
                break;
        }
    }
    return 0;
}

void Play(const size_t gridWidth, const size_t gridHeight, const std::shared_ptr<Renderer>& renderer, const size_t frameTime, const std::string& username, std::shared_ptr<ScoreManager>& scoreManager)
{
    Controller controller;
    Game game(gridWidth, gridHeight);
    game.Run(controller, renderer, frameTime);
    scoreManager->AddScore(username, game.GetScore());
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";
    std::cout << "Size: " << game.GetSize() << "\n";
}