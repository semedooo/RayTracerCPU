#include "ShowPPM.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

static bool readNextPPMToken(std::istream& in, std::string& token) {
    while (in >> token) {
        if (!token.empty() && token[0] == '#') {
            std::string ignored;
            std::getline(in, ignored);
            continue;
        }
        return true;
    }
    return false;
}

static bool loadPPM(const std::string& filename, std::vector<sf::Uint8>& pixels, unsigned& width, unsigned& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    std::string magic;
    if (!readNextPPMToken(file, magic)) {
        std::cerr << "Failed to read PPM header." << std::endl;
        return false;
    }
    if (magic != "P6" && magic != "P3") {
        std::cerr << "Unsupported PPM format: " << magic << std::endl;
        return false;
    }

    std::string token;
    if (!readNextPPMToken(file, token)) {
        std::cerr << "Failed to read PPM width." << std::endl;
        return false;
    }
    width = static_cast<unsigned>(std::stoul(token));

    if (!readNextPPMToken(file, token)) {
        std::cerr << "Failed to read PPM height." << std::endl;
        return false;
    }
    height = static_cast<unsigned>(std::stoul(token));

    if (!readNextPPMToken(file, token)) {
        std::cerr << "Failed to read PPM max value." << std::endl;
        return false;
    }
    int maxval = std::stoi(token);
    if (maxval <= 0) {
        std::cerr << "Invalid PPM max value: " << maxval << std::endl;
        return false;
    }

    file.get(); // Skip newline
    pixels.resize(width * height * 3);

    if (magic == "P6") {
        file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
        if (!file) {
            std::cerr << "Failed to read P6 pixel data." << std::endl;
            return false;
        }
        if (maxval != 255) {
            for (auto& px : pixels) {
                px = static_cast<sf::Uint8>((static_cast<int>(px) * 255) / maxval);
            }
        }
    } else { // P3
        for (size_t i = 0; i < pixels.size(); ++i) {
            if (!readNextPPMToken(file, token)) {
                std::cerr << "Unexpected end of P3 pixel data." << std::endl;
                return false;
            }
            int val = std::stoi(token);
            val = std::max(0, std::min(val, maxval));
            pixels[i] = static_cast<sf::Uint8>((val * 255) / maxval);
        }
    }
    return true;
}

static std::vector<sf::Uint8> toRgba(const std::vector<sf::Uint8>& rgb) {
    std::vector<sf::Uint8> rgba;
    rgba.reserve((rgb.size() / 3) * 4);

    for (size_t i = 0; i + 2 < rgb.size(); i += 3) {
        rgba.push_back(rgb[i]);
        rgba.push_back(rgb[i + 1]);
        rgba.push_back(rgb[i + 2]);
        rgba.push_back(255);
    }

    return rgba;
}

class SfmlErrorSilencer {
public:
    SfmlErrorSilencer() : oldBuf(nullptr) {
        nullStream = std::make_unique<std::ofstream>("/dev/null");
        if (*nullStream) {
            oldBuf = sf::err().rdbuf(nullStream->rdbuf());
        }
    }

    ~SfmlErrorSilencer() {
        if (oldBuf != nullptr) {
            sf::err().rdbuf(oldBuf);
        }
    }

private:
    std::streambuf* oldBuf;
    std::unique_ptr<std::ofstream> nullStream;
};

bool showPPMImage(const std::string& filename) {
    SfmlErrorSilencer sfmlErrors;

    std::vector<sf::Uint8> pixels;
    unsigned width = 0;
    unsigned height = 0;
    if (!loadPPM(filename, pixels, width, height)) {
        return false;
    }
    if (width == 0 || height == 0) {
        std::cerr << "Invalid image dimensions: " << width << "x" << height << std::endl;
        return false;
    }
    if (pixels.size() != static_cast<size_t>(width) * static_cast<size_t>(height) * 3) {
        std::cerr << "Invalid pixel data size for PPM image." << std::endl;
        return false;
    }

    const std::vector<sf::Uint8> rgbaPixels = toRgba(pixels);

    sf::Image image;
    image.create(width, height, rgbaPixels.data());
    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "Failed to create SFML texture from image." << std::endl;
        return false;
    }
    sf::Sprite sprite(texture);
    sf::RenderWindow window(
        sf::VideoMode(width, height),
        "PPM Viewer - SFML",
        sf::Style::Titlebar | sf::Style::Close
    );
    const sf::Vector2u fixedSize(width, height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                window.setSize(fixedSize);
                sf::View fixedView(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height)));
                window.setView(fixedView);
            }
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
    return true;
}
