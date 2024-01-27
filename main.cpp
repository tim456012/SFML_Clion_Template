#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Hello, World!");
    ImGui::SFML::Init(window);

    bool circleExists = true;
    float circleRadius = 200.f;
    int circleSegments = 100;
    float circleColors[3] = {(float)204/255, (float)77/255, (float)5/255 };

    sf::CircleShape shape(circleRadius, 100);


    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Title");
        ImGui::Text("Hello World");
        ImGui::Checkbox("Circle", &circleExists);
        ImGui::SliderFloat("Radius", &circleRadius, 100.f, 300.f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 150);
        ImGui::ColorEdit3("Circle Color", circleColors);
        ImGui::End();

        shape.setRadius(circleRadius);
        shape.setFillColor(sf::Color(
            (int)(circleColors[0] * 255),
            (int)(circleColors[1] * 255),
            (int)(circleColors[2] * 255)
            ));

        float windowWidth = static_cast<float>(window.getSize().x);
        float windowHeight = static_cast<float>(window.getSize().y);

        float centerX = (windowWidth - 2 * shape.getRadius()) / 2;
        float centerY = (windowHeight - 2 * shape.getRadius()) / 2;

        shape.setPosition(centerX, centerY);
        shape.setPointCount(circleSegments);

        window.clear(sf::Color(18,33,43));
        if (circleExists) {
            window.draw(shape);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
