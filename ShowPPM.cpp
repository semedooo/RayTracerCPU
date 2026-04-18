// ShowPPM.cpp
// PPM image viewer using SFML
// Compile with: g++ ShowPPM.cpp -o ShowPPM -lsfml-graphics -lsfml-window -lsfml-system
// Usage: ./ShowPPM path/to/image.ppm

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// Function to read PPM (P3 and P6)
bool loadPPM(const std::string& filename, std::vector<sf::Uint8>& pixels, unsigned& width, unsigned& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::string magic;
    file >> magic;
    if (magic != "P6" && magic != "P3") {
        std::cerr << "Unsupported PPM format: " << magic << std::endl;
        return false;
    }
    file >> width >> height;
    int maxval;
    file >> maxval;
    file.get(); // Skip newline
    pixels.resize(width * height * 3);
    if (magic == "P6") {
        file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    } else { // P3
        for (size_t i = 0; i < pixels.size(); ++i) {
            int val;
            file >> val;
            pixels[i] = static_cast<sf::Uint8>(val);
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " path/to/image.ppm" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::vector<sf::Uint8> pixels;
    unsigned width, height;
    if (!loadPPM(filename, pixels, width, height)) {
        return 1;
    }
    sf::Image image;
    if (!image.create(width, height, pixels.data())) {
        std::cerr << "Failed to create SFML image." << std::endl;
        return 1;
    }
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(width, height), "PPM Viewer - SFML");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
    return 0;
}
