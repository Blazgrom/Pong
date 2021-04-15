#include "Pong/Player.hpp"

#include <iostream>

#include <Mojo/Graphics/Renderer.hpp>
Player::Player(const mojo::IVector2D& size, const const mojo::KeyCode upButton, const const mojo::KeyCode downButton, const float speed)
: m_position{0, 0}, m_size(size), m_upButton(upButton), m_downButton(downButton), m_speed(speed), m_appliedSpeed(0), m_windowHeight{0}
{
}

void Player::setWindowHeight(const std::uint32_t newHeight)
{
    m_windowHeight = newHeight;
}

void Player::setPosition(const mojo::FVector2D& newPosition)
{
    m_position = newPosition;
}

void Player::handle_input(const mojo::InputEvent& event)
{
    if(event.type() == mojo::InputEventType::Keyboard &&
       (event.keyboard()->state == mojo::KeyState::Pressed || event.keyboard()->state == mojo::KeyState::Held))
    {
        if(event.keyboard()->code == m_upButton)
        {
            m_appliedSpeed = -m_speed;
        }
        else if(event.keyboard()->code == m_downButton)
        {
            m_appliedSpeed = m_speed;
        }
    }
    else if(event.type() == mojo::InputEventType::Keyboard && event.keyboard()->state == mojo::KeyState::Released)
    {
        m_appliedSpeed = 0;
    }
}

void Player::update(const float dt)
{
    m_position.y += (m_appliedSpeed * dt);

    if(!valid_position())
    {
        fix_position();
    }
}

bool Player::valid_position() const noexcept
{
    return m_position.y > 0 && ((m_position.y + m_size.y) < m_windowHeight);
}

void Player::fix_position()
{
    if(m_position.y < 0)
    {
        m_position.y = 0;
    }
    else if((m_position.y + m_size.y) > m_windowHeight)
    {
        m_position.y = m_windowHeight - m_size.y;
    }
}

void Player::draw() const
{
    mojo::Rect rect{{static_cast<int>(m_position.x), static_cast<int>(m_position.y)}, m_size.x, m_size.y};
    mojo::Renderer::draw(rect, true);
}
