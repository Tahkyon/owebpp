/*************************************************************************************
 *	MIT License
 *
 *	Copyright (c) 2023 Oliver Gibson
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
*************************************************************************************/
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <owebpp/Logger.hpp>
#include <thread>

#include "Generation/RouteCodeGenerator.hpp"

// Mandatory logger initialization
OWEBPP_STATIC_INIT_LOGGER

/**
 * Prints to the console how to use the program.
 * @param argc The number of command line arguments.
 * @param argv Pointer to the list of arguments given through the command line.
 */
static void usage([[maybe_unused]] int argc, char** argv) {
    std::cout << argv[0] << std::endl;
    std::cout << "generate:code:watch <input_yaml_file> <output_cpp_code_file> Watch the input yaml file provided for changes to generate the code for the routes from the given yaml file." << std::endl;
    std::cout << "generate:code       <input_yaml_file> <output_cpp_code_file> Generates c++ code for the routes from the given yaml file." << std::endl;
    std::cout << "--help                                                              Print this help text." << std::endl;
}

/**
 * Provides a list of all functions that are recognized by the program as well as the associated code.
 * @return The list of all functions that are recognized by the program as well as the associated code.
 */
static std::shared_ptr<std::map<std::string, std::function<int(int, char**)>>> getExecutors() {
     return std::make_shared<std::map<std::string, std::function<int(int, char**)>>>( std::map<std::string, std::function<int(int, char**)>>({
        {
            "generate:code",
            [](int ac, char** av) {
                if(ac == 4) {
                    owebpp::console::RouteCodeGenerator rcg(av[2], av[3]);

                    std::string out("Generating routes code from configuration file ");
                    out += av[2];
                    out += " and writing to ";
                    out += av[3];

                    OWEBPP_LOG_INFO(out);

                    rcg.generateCode(false);
                } else {
                    usage(ac, av);
                }
                return 0;
            }
        }, {
            "generate:code:watch",
            [](int ac, char** av) {
                if(ac == 4) {
                    owebpp::console::RouteCodeGenerator rcg(av[2], av[3]);

                    std::filesystem::path p(av[2]);

                    std::filesystem::file_time_type lwt;

                    /* This variable is used to avoid printing continuously to the console in case of exceptions */
                    bool is_generator_ok(true);
                    bool has_io_error(false);

                    try {
                        lwt = std::filesystem::last_write_time(p);
                        std::string out("Generating routes code from configuration file ");
                        out += p.string();
                        out += " and writing to ";
                        out += av[3];

                        OWEBPP_LOG_INFO(out);
                        is_generator_ok = rcg.generateCode(true);
                    } catch(const std::filesystem::filesystem_error& e) {
                        OWEBPP_LOG_ERROR("Error acquiring " + p.string() + " data.");
                        is_generator_ok = false;
                        has_io_error = true;
                    }

                    while(true) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(200));

                        try {
                            std::filesystem::file_time_type tmp_lwt(std::filesystem::last_write_time(p));

                            /* If the generator is bugged check if we can reestablish it. */
                            if(has_io_error) {
                                lwt = tmp_lwt;
                                OWEBPP_LOG_INFO("Recovered from I/O error on input file:" + p.string());
                                is_generator_ok = rcg.generateCode(is_generator_ok);
                            }

                            if(tmp_lwt > lwt) {
                                OWEBPP_LOG_INFO("Changes detected, regenerating routes code.");
                                lwt = tmp_lwt;
                                is_generator_ok = rcg.generateCode(is_generator_ok);
                            }

                            has_io_error = false;
                        } catch(const std::filesystem::filesystem_error& e) {
                            has_io_error = true;
                            if(is_generator_ok) {
                                OWEBPP_LOG_ERROR("Error acquiring " + p.string() + " data.");
                            }
                            is_generator_ok = false;
                        }
                    }
                } else {
                    usage(ac, av);
                }
                return 0;
            }
        }, {
            "--help",
            [](int ac, char** av) {
                usage(ac, av);
                return 0;
            }
        }
    }));
}

/** Program entry. Generates code based on input file and write it to output file. */
int main(int argc, char* argv[]) {
    if(argc > 1) {
        try {
            return getExecutors()->at(argv[1])(argc, argv);
        } catch(const std::out_of_range& e) {
            OWEBPP_LOG_ERROR(std::string("Exception: operation ") + argv[1] + " does not exist.");
            return 1;
        }
    } else {
        usage(argc, argv);
        return 0;
    }
}
