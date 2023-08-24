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
#ifndef BASIC_URL_ENCODED_DATA_PARSER_HPP
#define BASIC_URL_ENCODED_DATA_PARSER_HPP

/** This class is used to perform data parsing on url encoded data. */
class BasicUrlEncodedDataParser {
    public:
        /* Constructors */
        /** Construct a default parser. */
        BasicUrlEncodedDataParser() = default;

        /* Deleted constructors */
        BasicUrlEncodedDataParser(const BasicUrlEncodedDataParser& o) = delete;
        BasicUrlEncodedDataParser(BasicUrlEncodedDataParser&& o) = delete;

        /* Deleted assignment operators */
        BasicUrlEncodedDataParser& operator=(const BasicUrlEncodedDataParser& o) = delete;
        BasicUrlEncodedDataParser& operator=(BasicUrlEncodedDataParser&& o) = delete;

        /* Destructor */
        virtual ~BasicUrlEncodedDataParser() = default;

        /* Functions */
        /**
         * Parse the url encoded data and return a map representing the data. This parser is very basic and doesn't handle nested/multiple values.
         * @param key The key.
         * @return The key.
         */
        std::shared_ptr<std::map<std::string,std::string>> parse(const std::string& data) {
            std::shared_ptr<std::map<std::string,std::string>> result = std::make_shared<std::map<std::string,std::string>>();

            std::istringstream stream(data);
            std::string substring;
            while (std::getline(stream, substring, '&')) {
                int pos = substring.find_first_of('=');
                std::string key = substring.substr(0, pos);
                std::string value = substring.substr(pos+1);
                (*result)[key] = value;
            }

            return result;
        }
};

#endif // BASIC_URL_ENCODED_DATA_PARSER_HPP
