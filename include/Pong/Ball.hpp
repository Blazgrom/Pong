#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <Mojo/Graphics/Renderer.hpp>
#include <Mojo/Math/Vector.hpp>

class Ball final
{
    mojo::FVector2D m_position;
    mojo::FVector2D m_direction;
    mojo::IVector2D m_size;
    float m_speed;

    public:
    Ball(const mojo::IVector2D& size, const float speed) : m_position{}, m_direction{0.f, 0.f}, m_size{size}, m_speed(speed)
    {
    }

    void setDirection(const mojo::FVector2D direction)
    {
        m_direction = direction;
    }

    void setPosition(const mojo::FVector2D position)
    {
        m_position = position;
    }

    void update(const float dt)
    {
        m_position.x += m_direction.x * dt * m_speed;
        m_position.y += m_direction.y * dt * m_speed;
    }

    void draw(const float dt)
    {
        mojo::Rect rect{mojo::IVector2D{static_cast<int>(m_position.x), static_cast<int>(m_position.y)}, m_size.x, m_size.y};
        mojo::Renderer::draw(rect, true);
    }

    [[nodiscard]] mojo::FVector2D position() const noexcept
    {
        return m_position;
    }

    [[nodiscard]] mojo::IVector2D size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] mojo::FVector2D direction() const noexcept
    {
        return m_direction;
    }
};
#endif
