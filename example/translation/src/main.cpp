/*************************************************************************************
 *    MIT License
 *
 *    Copyright (c) 2023 Oliver Gibson
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
*************************************************************************************/
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <owebpp/Logger.hpp>
#include <MemoryTranslator.hpp>
#include <thread>

// Mandatory logger initialization
OWEBPP_STATIC_INIT_LOGGER

// Mandatory translator initialization
OWEBPP_STATIC_INIT_TRANSLATOR

/** Program entry. Basic usage of the translation capabilities. */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::map<std::string,std::map<std::string, std::string>> translations = {
        {"US", {
            {"hello.world", "Hello World."},
            {"translation.with.parameters", "I have %d apples, they weight %f kg."},
            {"translation.more.tests", "string: %s adress: %p %"}
        }},
        {"FR", {
            {"hello.world", "Bonjour le monde."}
        }},
        {"ES", {
            {"hello.world", "Hola el mundo."}
        }}
    };

    MemoryTranslator mt_us("US", translations);
    MemoryTranslator mt_fr("FR", translations);
    MemoryTranslator mt_es("ES", translations);

    // Basic translation tests without parameters.
    std::cout << mt_us.translate("hello.world") << std::endl;
    std::cout << mt_fr.translate("hello.world") << std::endl;
    std::cout << mt_es.translate("hello.world") << std::endl;
    std::cout << mt_us.translate("non.existant.key") << std::endl;
    std::cout << mt_us.translate("translation.with.parameters", 5, 2.5) << std::endl;
    // Not enough parameters, check logs.
    std::cout << mt_us.translate("translation.with.parameters", 5) << std::endl;
    // Too many parameters check logs.
    std::cout << mt_us.translate("translation.with.parameters", 5, 2.5,"test") << std::endl;
    // Additional example with text and pointers.
    std::cout << mt_us.translate("translation.more.tests", "my test string", &mt_us) << std::endl;
    return 0;
}
