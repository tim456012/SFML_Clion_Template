#include <glad/glad.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

// clang-format off
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
// clang-format on

int
main()
{
    // Create an SFML window with OpenGL context
    sf::RenderWindow window(
        sf::VideoMode(1280, 720), "Hello, World", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);
    window.setActive();

    // Initialize OpenGL using glad AFTER creating the window
    if (! gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Initialize ImGui-SFML
    if (! ImGui::SFML::Init(window))
    {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
        return 1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (! success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragementShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragementShader);

    glGetShaderiv(fragementShader, GL_COMPILE_STATUS, &success);
    if (! success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragementShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragementShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(shaderProgram);
    glDeleteShader(fragementShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (! success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // // Clock for delta time calculation
    // sf::Clock deltaClock;

    bool isRunning = true;
    while (isRunning)
    {
        // Handle events
        sf::Event event {};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
                isRunning = false;
            }
        }

        // // Start a new ImGui frame
        // ImGui::SFML::Update(window, deltaClock.restart());
        // ImGui::ShowDemoWindow();

        // Clear the window and OpenGL buffers
        glClearColor(0.404f, 0.576f, 0.643f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // // Render ImGui on top of the OpenGL content
        // ImGui::SFML::Render(window);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Display the final frame
        window.display();
    }

    // // Cleanup ImGui-SFML
    // ImGui::SFML::Shutdown();

    return 0;
}