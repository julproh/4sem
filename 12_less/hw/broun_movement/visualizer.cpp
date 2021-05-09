#include "visualizer.hpp"

using namespace sf;

    Visualizer::Visualizer() :
    
        m_window(VideoMode(m_width, m_height), m_window_name),
        m_uid(0,3), m_bd(0.1),
        m_field(m_squares_in_column, std::vector<std::size_t>(m_squares_in_column, 0U))
    
        {
            std::uniform_int_distribution uid(0, static_cast<int>(m_width) - 1);
            m_particles.reserve(m_particles_num);
            for (auto i = 0U; i < m_particles_num; ++i)
            {
                auto x = uid(m_mt);
                auto y = uid(m_mt);
                auto dir = static_cast<Direction>(m_uid(m_mt));
                ++m_field[x/m_squares_size][y/m_squares_size];
                m_particles.emplace(std::end(m_particles), Particle(x, y, dir));
            }
        };


    void Visualizer::draw()
    {
        for(auto& column : m_field)
        {
            for (auto& cell : column)
            {
                cell = 0U;
            }
        }
        std::for_each(std::begin(m_particles), std::end(m_particles), [this](const Particle& particle)
                      {
                          ++m_field[particle.x / m_squares_size][particle.y / m_squares_size];
                      });
        RectangleShape big_rect(Vector2f(m_squares_size, m_squares_size));
        for (auto i = 0U; i < m_squares_in_column; ++i)
        {
            for (auto j = 0U; j < m_squares_in_column; ++j)
            {
                Color color;
                const std::size_t particles_num = m_field[i][j];
                if (!particles_num)
                {
                    color = Color::Black;
                }
                else
                {
                    auto saturation = particles_num / m_change_color_particles_num;
                    saturation = (saturation > m_colors_num - 1 ? m_colors_num - 1 : saturation);
                    color = m_colors[saturation];
                }
                big_rect.setPosition(static_cast <float> (i * m_squares_size), static_cast <float> (j * m_squares_size));
                big_rect.setFillColor(color);
                m_window.draw(big_rect);
            }
        }
        RectangleShape small_rect(Vector2f(2.5f, 2.5f));
        std::for_each(std::begin(m_particles), std::end(m_particles), [this, &small_rect](const Particle& particle)
                      {
                          small_rect.setPosition(static_cast<float> (particle.x), static_cast<float>(particle.y));
                          small_rect.setFillColor(m_particle_color);
                          m_window.draw(small_rect);
                      });
        m_window.display();
    }

    void Visualizer::step(Particle& particle)
    {
        switch (particle.direction)
        {
            case Direction::left:
                if (particle.x == 0U)
                {
                    particle.direction = Direction::right;
                }
                else
                {
                    --particle.x;
                }
                break;
            case Direction::right:
                if (particle.x == m_width - 1)
                {
                    particle.direction = Direction::left;
                }
                else
                {
                    ++particle.x;
                }
                break;
            case Direction::up:
                if (particle.y == 0U)
                {
                    particle.direction = Direction::down;
                }
                else
                {
                    --particle.y;
                }
                break;
            case Direction::down:
                if (particle.y == m_height - 1)
                {
                    particle.direction = Direction::up;
                }
                else
                {
                    ++particle.y;
                }
                break;
            default:
                break;
        }
        if (m_bd(m_mt))
        {
            particle.direction = static_cast<Direction>(m_uid(m_mt));
        }
    }

    void Visualizer::move()
    {
        std::for_each(std::begin(Visualizer::m_particles), std::end(Visualizer::m_particles), [this](auto& particle) {step(particle); });
    }

    void Visualizer::start_motion()
    {
        while (m_window.isOpen())
        {
            Event event;

            while (m_window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    m_window.close();
                }
            }
            Visualizer::move();
            m_window.clear();
            Visualizer::draw();
        }
    }
