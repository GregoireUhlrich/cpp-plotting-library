#ifndef CPT_WINDOW_H_INCLUDED
#define CPT_WINDOW_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <future>
#include <mutex>
#include <functional>
#include "internal/x11_threads.hpp"
#include "../utils/error.hpp"

namespace cpt
{
   class FigureConcurrencyError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    class FigureWindow {
    
    public:

        FigureWindow(
            std::string_view name, 
            std::size_t width, 
            std::size_t height
            );

        FigureWindow(FigureWindow const &) = delete;

        ~FigureWindow();

        bool is_blocking() const noexcept;

        void set_blocking(bool blocking) noexcept;

        void show(
            std::function<void(sf::RenderTarget&)> draw_callback
            );

        sf::Vector2f get_size() const noexcept;

        sf::Vector2u get_usize() const noexcept;

        void wait_for_close() const;

    protected:

        void launch(
            std::function<void(sf::RenderTarget&)> draw_callback
        );

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