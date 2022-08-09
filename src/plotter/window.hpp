#ifndef CPT_WINDOW_H_INCLUDED
#define CPT_WINDOW_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <future>
#include <mutex>
#include "internal/x11_threads.hpp"
#include "../utils/error.hpp"

namespace cpt
{
   class WindowConcurrencyError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    class Window {
    
    public:

        Window(std::string_view name, std::size_t width, std::size_t height);

        Window(Window const &) = delete;

        Window(Window &&) = default;

        ~Window();

        bool is_blocking() const noexcept;

        void set_blocking(bool blocking) noexcept;

        void show();

        sf::Vector2f get_size() const noexcept;

        sf::Vector2u get_usize() const noexcept;

    protected:

        void launch();

        static void create_window(
            sf::RenderWindow          &window,
            sf::VideoMode       const &mode,
            std::string         const &name,
            uint32_t                   style,
            sf::ContextSettings const &settings = sf::ContextSettings());

    protected:
        std::string       _name;
        std::size_t       _width;
        std::size_t       _height;
        sf::RenderWindow  _window;
        bool              _blocking = false;
        std::future<void> _execution_result;
        std::mutex        _mutex;
    }; 
} // namespace cpt


#endif