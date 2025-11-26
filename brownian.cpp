#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <optional>

struct Particle {
    float x, y;
};

int main() {
    const unsigned WIDTH = 700;
    const unsigned HEIGHT = 700;    
    const int N = 3000;             // number of balls
    const float STEP = 1.5f;        // adjust step

    sf::VideoMode mode(sf::Vector2u(WIDTH, HEIGHT));
    sf::RenderWindow window(mode, "Brownian Motion", sf::State::Windowed, sf::ContextSettings{});
    window.setFramerateLimit(60);

    std::vector<Particle> particles(N);

    // mersenne twister
    std::mt19937 rng(std::random_device{}());
    std::normal_distribution<float> dist(0.f, STEP);

    for (auto& p : particles) 
    {
        p.x = rng() % WIDTH;
        p.y = rng() % HEIGHT;
    }

    // blue dots
    sf::CircleShape dot(3.f);
    dot.setFillColor(sf::Color::Blue);

    // yellow dots
    sf::CircleShape highlight(4.f);
    highlight.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
    
        while (true) {
            std::optional<sf::Event> evt = window.pollEvent();
            if (!evt) break;

            if (evt->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(180, 180, 180)); // grey background

        for (int i = 0; i < N; i++) {
            particles[i].x += dist(rng);
            particles[i].y += dist(rng);

            if (particles[i].x < 0) particles[i].x += WIDTH;
            if (particles[i].x >= WIDTH) particles[i].x -= WIDTH;
            if (particles[i].y < 0) particles[i].y += HEIGHT;
            if (particles[i].y >= HEIGHT) particles[i].y -= HEIGHT;

            dot.setPosition(sf::Vector2f(particles[i].x, particles[i].y));
            window.draw(dot);
        }

        for (int i : {10, 500, 1200}) {
            highlight.setPosition(sf::Vector2f(particles[i].x, particles[i].y));
            window.draw(highlight);
        }
        window.display();
    }

    return 0;
}
