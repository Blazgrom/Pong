#ifndef PONG_SCORE_HPP
#define PONG_SCORE_HPP
#include <cstdint>

#include <Mojo/Font.hpp>
#include <Mojo/Graphics/Renderer.hpp>
#include <Mojo/Graphics/Texture.hpp>
#include <Mojo/Logging.hpp>
#include <Mojo/Math/Vector.hpp>

class Score final
{
    std::shared_ptr<mojo::Font> m_textureGenerator;
    std::shared_ptr<mojo::Texture> m_texture;
    mojo::IVector2D m_position;
    std::uint8_t m_score;

    public:
    Score(const std::uint8_t score) : m_textureGenerator(nullptr), m_texture{nullptr}, m_position{}, m_score{score}
    {
    }
    void update_score(const std::uint32_t increaseAmount) noexcept
    {
        m_score += increaseAmount;
        update_texture();
    }

    void setTextureGenerator(std::shared_ptr<mojo::Font> generator)
    {
        m_textureGenerator = generator;
        if(m_textureGenerator)
        {
            update_texture();
        }
        else
        {
            MOJO_LOG_WARNING("Invalid texture generator used for score");
        }
    }

    void setPosition(const mojo::IVector2D& position)
    {
        m_position = position;
        if(m_texture)
        {
            m_position.x -= (m_texture->size().y / 2);
        }
        else
        {
            MOJO_LOG_WARNING("Cannot calculate score texture");
        }
    }

    void draw() noexcept
    {
        mojo::Renderer::draw(m_texture.get(), m_position);
    }

    private:
    void update_texture()
    {
        m_texture = m_textureGenerator->create_texture(std::to_string(m_score));
        if(m_texture)
        {
            m_texture->finalize();
        }
        else
        {
            MOJO_LOG_WARNING("Cannot update score texture");
        }
    }
};
#endif
