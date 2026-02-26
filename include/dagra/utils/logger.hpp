/**
 * @file logger.hpp
 * @brief A thread-safe, colorful logging utility for the Dagra application.
 * @version 1.0.0
 *
 * Provides static methods for logging messages at different levels (INFO, SUCCESS,
 * WARN, ERROR, DRY-RUN), each with a distinct color for better readability in
 * the console.
 */

#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <string_view>

namespace dagra::utils {

    /**
     * @namespace colors
     * @brief Defines ANSI escape codes for terminal text coloring.
     */
    namespace colors {
        constexpr std::string_view RESET   = "\033[0m";
        constexpr std::string_view RED     = "\033[31m";
        constexpr std::string_view GREEN   = "\033[32m";
        constexpr std::string_view YELLOW  = "\033[33m";
        constexpr std::string_view CYAN    = "\033[36m";
    } // namespace colors

    /**
     * @class Logger
     * @brief A static class providing thread-safe logging functionalities.
     */
    class Logger {
    public:
        /**
         * @brief Logs an informational message.
         * @param message The message to log.
         */
        static void info(const std::string& message) {
            log(std::cout, "[INFO]    ", message);
        }

        /**
         * @brief Logs a success message in green.
         * @param message The message to log.
         */
        static void success(const std::string& message) {
            log(std::cout, colors::GREEN, "[SUCCESS] ", message);
        }
        
        /**
         * @brief Logs a warning message in yellow.
         * @param message The message to log.
         */
        static void warn(const std::string& message) {
            log(std::cout, colors::YELLOW, "[WARN]    ", message);
        }

        /**
         * @brief Logs an error message in red to the standard error stream.
         * @param message The message to log.
         */
        static void error(const std::string& message) {
            log(std::cerr, colors::RED, "[ERROR]   ", message);
        }
        
        /**
         * @brief Logs a dry-run message in cyan.
         * @param message The message to log.
         */
        static void dry_run(const std::string& message) {
            log(std::cout, colors::CYAN, "[DRY-RUN] ", message);
        }

    private:
        /**
         * @brief Retrieves a singleton instance of a mutex for thread safety.
         * @return A reference to the static mutex.
         */
        static std::mutex& get_mutex() {
            static std::mutex mtx;
            return mtx;
        }

        /**
         * @brief A generic, thread-safe logging function.
         *
         * Acquires a lock and prints a series of arguments to the specified
         * output stream, resetting the color at the end.
         *
         * @tparam Args Variadic template for message parts.
         * @param stream The output stream (e.g., std::cout, std::cerr).
         * @param args The parts of the message to log.
         */
        template<typename... Args>
        static void log(std::ostream& stream, Args&&... args) {
            std::lock_guard<std::mutex> lock(get_mutex());
            (stream << ... << std::forward<Args>(args));
            stream << colors::RESET << std::endl;
        }
    };

} // namespace dagra::utils
