#include <algorithm>
#include <array>
#include <thread>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace sf;

class Visualizer
{
private:
    enum class Direction
    {
        down,
        left,
        right,
        up
    };

    struct Particle
    {
        Particle() = default;
        Particle(int coord_1, int coord_2, Direction dir):
        	x(coord_1), y(coord_2), direction(dir) {};

        int x;
        int y;
        Direction direction;
    };

public:
    Visualizer();

    ~Visualizer() noexcept = default;

private:

    void draw();

    void step(Particle& particle);
    void move();

public:
    void start_motion();

private:

    std::mt19937_64 m_mt;
    std::uniform_int_distribution<> m_uid;
    std::bernoulli_distribution m_bd;

    inline static const std::size_t m_width = 1000;
    inline static const std::size_t m_height = 1000;
    inline static const std::size_t m_particles_num = 5000;

    std::vector<Particle> m_particles;
    std::vector<std::vector<std::size_t>> m_field;

    const std::string m_window_name = "Broun movement";
    RenderWindow m_window;

    inline static const std::size_t m_colors_num = 5U;
    const std::array<Color, m_colors_num> m_colors =
    {Color(0, 50, 0), Color(0, 100, 0), Color(0, 150, 0), Color(0, 200, 0), Color(0, 250, 0)};
    inline static const std::size_t m_change_color_particles_num = 5U;
    const Color m_particle_color = { 255, 255, 255 };

    inline static const std::size_t m_squares_in_column = 50U;
    inline static const std::size_t m_squares_size = m_height / m_squares_in_column;
};
