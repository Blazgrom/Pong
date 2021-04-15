#ifndef PONG_GAME_LAYER_HPP
#define PONG_GAME_LAYER_HPP
#include <cstdint>
#include <tuple>

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
    static constexpr float s_playerSpeed = 0.5f;
    static constexpr std::uint8_t s_fontSize = 32;
    std::shared_ptr<mojo::Font> m_font;

    mojo::Line m_middleLine;
    Score m_leftPlayerScore{0};
    Score m_rightPlayerScore{0};
    Player m_leftPlayer{s_playerSize, mojo::KeyCode::W, mojo::KeyCode::S, s_playerSpeed};
    Player m_rightPlayer{s_playerSize, mojo::KeyCode::I, mojo::KeyCode::K, s_playerSpeed};

    public:
    void update(const float dt) override final
    {
        m_leftPlayer.update(dt);
        m_rightPlayer.update(dt);
    }

    void render(const float dt) override final
    {
        m_leftPlayer.draw();
        m_rightPlayer.draw();
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
    }
};
#endif
