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
#ifndef OWEBPP_TRANSLATOR_HPP
#define OWEBPP_TRANSLATOR_HPP

#include <memory>
#include <type_traits>

/** This macro needs to be called at the beginning of the program using the framework. */
#define OWEBPP_STATIC_INIT_TRANSLATOR std::shared_ptr<owebpp::Translator> owebpp::Translator::s_translator = nullptr;

namespace owebpp {
    /** This class is used to perform text translation. */
    class Translator {
        public:
            /* Constructors */
            /** Construct a default translator. */
            Translator() = default;

            /* Deleted constructors */
            Translator(const Translator& o) = delete;
            Translator(Translator&& o) = delete;

            /* Deleted assignment operators */
            Translator& operator=(const Translator& o) = delete;
            Translator& operator=(Translator&& o) = delete;

            /* Destructor */
            virtual ~Translator() = default;

            /* Functions */
            /**
             * Set the translator to use.
             * @param translator The translator to use.
             */
            static void setTranslator(std::shared_ptr<Translator> translator) {
                s_translator = translator;
            }

            /**
             * Return the key without translating it, behavior should be overriden in child classes to properly translate.
             * @param key The key.
             * @return The key.
             */
            virtual std::string getTranslatedText(const std::string& key) { return key; };

            /**
             * Call getTranslatedText function to translate key.
             * @param key The key to translate.
             * @return getTranslatedText() result.
             */
            std::string translate(const std::string& key) {
                return getTranslatedText(key);
            }

            /**
             * Call getTranslatedText function to translate key and do parameter replacement.
             * Thanks to concepts we can make some compile time checking to make sure we can perform replacements in the translated string.
             * @param key The key to translate.
             * @param args The parameters that must be replaced in the key translation.
             * @return getTranslatedText() result with parameter replacement.
             * @todo If possible add more checks between the format parameters and args checking the type.
             */
            template<class... Tparams> requires((std::is_integral_v<Tparams> || std::is_floating_point_v<Tparams> || std::is_pointer_v<Tparams>) && ...)
            std::string translate(const std::string& key, Tparams... args) {
                std::string result(key);
                const std::string& format = getTranslatedText(key);
                size_t param_format_count = parameterCount(format);
                size_t arg_count = sizeof...(Tparams);

                if( param_format_count == sizeof...(args)) {
                    int size_s = std::snprintf( nullptr, 0, format.c_str(), args... ) + 1; // Extra space for '\0'
                    if( size_s <= 0 ) {
                        OWEBPP_LOG_WARNING("Error translating text. Simply returning key.");
                    } else {
                        size_t size = static_cast<size_t>( size_s );
                        std::unique_ptr<char[]> buf( new char[ size ] );
                        std::snprintf( buf.get(), size, format.c_str(), args ... );
                        result.assign( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
                    }
                } else {
                    OWEBPP_LOG_WARNING("Mismatch number of arguments " + std::to_string(arg_count) +
                                       " provided but " + std::to_string(param_format_count) + " expected. Simply returning key.");
                }
                return result;
            }

            /* Singleton call method */
            /**
             * Get the translator instance.
             * @return The translator instance.
             */
            static Translator& getInstance() {
                if(s_translator==nullptr) {
                    s_translator = std::make_shared<Translator>();
                }
                return *s_translator;
            }

        private:
            /* Functions */
            /**
             * Determine the number of arguments expected by the format following printf synthax.
             * @param format The format for which to count the number of expected arguments.
             * @return The number of expected arguments by format.
             */
            static size_t parameterCount(const std::string& format) {
                size_t param_count(0);
                size_t format_length = format.size();
                for(size_t i = 0; i < format_length; i++) {
                    if(format[i] == '%') {
                        size_t index_check(i+1);
                        // We are at the end so donc do any checks if index_check == format_length.
                        if(index_check < format_length) {
                            if(format[i+1] == '%') {
                                i++;
                            } else {
                                param_count+= 1;
                                i++;
                            }
                        }
                    }
                }
                return param_count;
            }

            /** Singleton object */
            static std::shared_ptr<Translator> s_translator;
    };
}

#endif // OWEBPP_TRANSLATOR_HPP
