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
#ifndef MEMORY_TRANSLATOR_HPP
#define MEMORY_TRANSLATOR_HPP

#include <map>
#include <owebpp/Logger.hpp>
#include <owebpp/Translator.hpp>

/** This class is uses in memory data to perform translations. */
class MemoryTranslator : public owebpp::Translator {
    public:
        /* Constructors */
        /**
         * Construct a translator.
         * @param local The language to use for translation.
         * @param translations The translation data to use for translations.
         */
        MemoryTranslator(const std::string& local, std::map<std::string,std::map<std::string, std::string>> translations):
            m_local(local),
            m_translations(translations) {}

        /* Deleted constructors */
        MemoryTranslator(const MemoryTranslator& r) = delete;
        MemoryTranslator(MemoryTranslator&& r) = delete;

        /* Deleted assignment operators */
        MemoryTranslator& operator=(const MemoryTranslator& r) = delete;
        MemoryTranslator& operator=(MemoryTranslator&& r) = delete;

        /* Destructor */
        virtual ~MemoryTranslator() = default;

        /* Functions */
        /**
         * Returns the translation associated to the given key.
         * @param key The key to use to translate.
         * @return The translation associated to the key or the key if no translation was found.
         */
        std::string getTranslatedText(const std::string& key) override {
            std::string tr(key);
            // Check if language is supported.
            if(m_translations.find(m_local) == m_translations.end()) {
                OWEBPP_LOG_WARNING("Locale " + m_local + " is not supported.");
            } else {
                std::map<std::string, std::string>& tr_map(m_translations[m_local]);
                // Check if translation  exists.
                if(tr_map.find(key) == tr_map.end()) {
                    OWEBPP_LOG_WARNING("Key " + key + " has no translation for locale " + m_local + ".");
                } else {
                    tr = m_translations[m_local][key];
                }
            }
            return tr;
        }

    private:
        /* Members */
        /** Allows to select for which language the translations should me made. */
        std::string m_local;

        /** The translation data. */
        std::map<std::string,std::map<std::string, std::string>> m_translations;
};

#endif // MEMORY_TRANSLATOR_HPP
