#ifndef PONG_GAME_LAYER_HPP
#define PONG_GAME_LAYER_HPP
#include <cstdint>
#include <random>
#include <tuple>

#include "Pong/Ball.hpp"
#include "Pong/Player.hpp"
#include "Pong/Score.hpp"

#include <Mojo/Asserts.hpp>
#include <Mojo/Graphics/Renderer.hpp>
#include <Mojo/Layering/ContentLayer.hpp>
#include <Mojo/Services.hpp>
#include <Mojo/Window.hpp>

class GameLayer final : public mojo::ContentLayer
{
    static constexpr mojo::IVector2D s_playerSize{8, 100};
    static constexpr mojo::IVector2D s_ballSize{12, 12};
    static constexpr float s_playerSpeed = 0.5f;
    static constexpr float s_ballSpeed = 0.8f;
    static constexpr std::uint8_t s_fontSize = 32;
    std::shared_ptr<mojo::Font> m_font;

    mojo::Line m_middleLine;
    Score m_leftPlayerScore{0};
    Score m_rightPlayerScore{0};
    Player m_leftPlayer{s_playerSize, mojo::KeyCode::W, mojo::KeyCode::S, s_playerSpeed};
    Player m_rightPlayer{s_playerSize, mojo::KeyCode::I, mojo::KeyCode::K, s_playerSpeed};
    Ball m_ball{s_ballSize, s_ballSpeed};

    public:
    void update(const float dt) override final
    {
        m_leftPlayer.update(dt);
        m_rightPlayer.update(dt);
        m_ball.update(dt);
        check_collisions();
    }

    void render(const float dt) override final
    {
        m_leftPlayer.draw();
        m_rightPlayer.draw();
        m_ball.draw(dt);
        mojo::Renderer::draw(m_middleLine);
        m_leftPlayerScore.draw();
        m_rightPlayerScore.draw();
    }

    [[nodiscard]] bool handle_input(const mojo::InputEvent& event) override final
    {
        m_leftPlayer.handle_input(event);
        m_rightPlayer.handle_input(event);
        return true;
    }

    private:
    void custom_initialization() override final
    {
        const std::uint32_t windowHeight = m_window->height();
        m_leftPlayer.setWindowHeight(windowHeight);
        m_rightPlayer.setWindowHeight(windowHeight);
        const float yPos = (windowHeight / 2) - (s_playerSize.y / 2);
        MOJO_ASSERT((yPos >= 0 || yPos <= windowHeight), "Invalid Y coordinate for paddle calculated");
        m_leftPlayer.setPosition({0.0f, yPos});
        const float xPos = m_window->width() - s_playerSize.x;
        MOJO_ASSERT((xPos >= 0 || xPos <= m_window->width()), "Invalid X coordinate for paddle calculated");
        m_rightPlayer.setPosition({xPos, yPos});

        const int middle = m_window->width() / 2;
        m_middleLine.start = {middle, 0};
        m_middleLine.end = {middle, static_cast<int>(m_window->height())};

        m_font = mojo::Services::Resources::get()->load<mojo::Font>("./assets/roboto.ttf", s_fontSize);
        m_leftPlayerScore.setTextureGenerator(m_font);
        m_rightPlayerScore.setTextureGenerator(m_font);

        const int halfMiddle = middle / 2;
        const int scoreYPos = 25;
        m_leftPlayerScore.setPosition({halfMiddle, scoreYPos});
        m_rightPlayerScore.setPosition({middle + halfMiddle, scoreYPos});
        restart_game();
    }

    void check_collisions()
    {
        const std::uint32_t windowHeight = m_window->height();
        const std::uint32_t windowWidth = m_window->width();
        const mojo::FVector2D ballPosition = m_ball.position();
        const mojo::IVector2D ballSize = m_ball.size();
        mojo::FVector2D ballDirection = m_ball.direction();

        auto collidesWithPlayer = [&ballPosition, &ballSize](const Player& player) mutable -> bool {
            const mojo::FVector2D playerPosition = player.position();
            const mojo::IVector2D playerSize = player.size();
            bool collisionOnX = ((playerPosition.x + playerSize.x) >= ballPosition.x) && ((ballPosition.x + ballSize.x) >= playerPosition.x);
            bool collisionOnY = ((playerPosition.y + playerSize.y) >= ballPosition.y) && ((ballPosition.y + ballSize.y) >= playerPosition.y);
            return collisionOnX && collisionOnY;
        };

        if(collidesWithPlayer(m_rightPlayer))
        {
            ballDirection.x = -std::abs(ballDirection.x);
        }
        else if(collidesWithPlayer(m_leftPlayer))
        {
            ballDirection.x = std::abs(ballDirection.x);
        }
        else if((ballPosition.y + ballSize.y) > windowHeight)
        {
            ballDirection.y = -std::abs(ballDirection.y);
        }
        else if(ballPosition.y < 0)
        {
            ballDirection.y = std::abs(ballDirection.y);
        }
        else if(ballPosition.x > windowWidth)
        {
            m_leftPlayerScore.update_score(1);
            restart_game();
            return;
        }
        else if((ballPosition.x + ballSize.x) < 0)
        {
            m_rightPlayerScore.update_score(1);
            restart_game();
            return;
        }
        m_ball.setDirection(ballDirection);
    }

    float generate_random_float(const float min, const float max)
    {
        std::random_device rd;
        std::uniform_real_distribution<float> dist(min, max);
        const float value = dist(rd);
        ///NOTE: We need to clamp it because if not sometimes the URD will generate values that are so close to zero that our ball would seem to not be moving
        if(value > 0)
        {
            return std::clamp(value, 0.4f, max);
        }
        return std::clamp(value, min, -0.4f);
    }

    void restart_game()
    {
        m_ball.setDirection({generate_random_float(-1.f, 1.f), generate_random_float(-1.f, 1.f)});
        m_ball.setPosition({generate_random_float(0, m_window->width()), generate_random_float(0, m_window->height())});
    }
};
#endif
