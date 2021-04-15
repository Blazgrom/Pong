#include <memory>

#include "Pong/GameLayer.hpp"

#include <Mojo/Mojo.hpp>

class Pong final : public mojo::Application
{
    public:
    Pong()
    {
        m_contentLayers.push_content_layer(std::make_unique<GameLayer>());
    }
};

std::unique_ptr<mojo::Application> mojo::create_application()
{
    return std::make_unique<Pong>();
}

mojo::InitializationInfo mojo::create_initialization_info()
{
    std::string logFileName = "pather.log";
    std::string configFileName = "./assets/configuration.json";
    return {logFileName, configFileName};
}
