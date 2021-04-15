#ifndef PONG_PLAYER_HPP
#define PONG_PLAYER_HPP
#include <cstdint>

#include <Mojo/Input/InputData.hpp>
#include <Mojo/Input/InputEvent.hpp>
#include <Mojo/Math/Vector.hpp>

class Player final
{
    mojo::FVector2D m_position;
    mojo::IVector2D m_size;
    mojo::KeyCode m_upButton;
    mojo::KeyCode m_downButton;
    float m_speed;
    float m_appliedSpeed;
    std::uint32_t m_windowHeight;

    public:
    Player(const mojo::IVector2D& size, const mojo::KeyCode upButton, const mojo::KeyCode downButton, const float speed);

    void setWindowHeight(const std::uint32_t newHeight);

    void setPosition(const mojo::FVector2D& newPosition);

    void handle_input(const mojo::InputEvent& event);

    void update(const float dt);

    [[nodiscard]] mojo::FVector2D position() const noexcept
    {
        return m_position;
    }

    [[nodiscard]] mojo::IVector2D size() const noexcept
    {
        return m_size;
    }

    void draw() const;

    private:
    [[nodiscard]] bool valid_position() const noexcept;

    void fix_position();
};
#endif
