#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
	// Create an SFML window with OpenGL context
	sf::RenderWindow window(sf::VideoMode({1280, 720}), "Hello, World", sf::State::Windowed);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);

	// Initialize ImGui-SFML
	if (!ImGui::SFML::Init(window, {1280, 720})) {
		std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
		return 1;
	}

	// Clock for delta time calculation
	sf::Clock deltaClock;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		// Start a new ImGui frame
		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::ShowDemoWindow();

		window.clear(sf::Color(45, 60, 68, 255));

		// Render ImGui on top of the OpenGL content
		ImGui::SFML::Render(window);

		// Display the final frame
		window.display();
	}

	// Cleanup ImGui-SFML
	ImGui::SFML::Shutdown();

	return 0;
}