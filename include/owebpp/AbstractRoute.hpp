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
#ifndef OWEBPP_ABSTRACTROUTE_HPP
#define OWEBPP_ABSTRACTROUTE_HPP

#include <memory>
#include <owebpp/Request.hpp>
#include <owebpp/Response.hpp>
#include <regex>

namespace owebpp {
    /** This is the base class used to create all routes class which are generated. This class doesn't have any use for client code.  */
    class AbstractRoute {
        public:
            /* Constructors */
            /**
             * Construct an AbstractRoute for the given methods, rurl regex and number of parameters.
             * @param allowed_methods .
             * @param reg The c++ URL regex associated with the route.
             * @param parameters_number The number of parameters the URL route has.
             */
            AbstractRoute(int allowed_methods, const std::string& reg, int parameters_number ):
                m_allowed_methods(allowed_methods),
                m_url_regex_string(reg),
                m_url_regex(m_url_regex_string),
                m_parameters_number(parameters_number){}

            /* Deleted constructors */
            AbstractRoute() = delete;
            AbstractRoute(const AbstractRoute& o) = delete;
            AbstractRoute(AbstractRoute&& o) = delete;

            /* Deleted assignment operators */
            AbstractRoute& operator=(const AbstractRoute& o) = delete;
            AbstractRoute& operator=(AbstractRoute&& o) = delete;

            /* Destructor */
            virtual ~AbstractRoute() = default;

            /* Functions */
            /**
             * This method is extended by the classes in the generated code and calls the client code for a given owebpp::Request.
             * @param r The request that was sent to the server.
             * @param sm The object holding the information about the parameters in the URL.
             * @return The owebpp::Response to The given request.
             */
            [[nodiscard]] virtual std::shared_ptr<Response> execute(const std::shared_ptr<owebpp::Request>& r, std::smatch& sm) = 0;

            /* Getters and Setters*/
            /**
             * Getter for the methods allowed on this route.
             * @return the methods allowed on this route.
             */
            int getAllowedMethods() { return m_allowed_methods; }

            /**
             * Getter for the c++ regex string of this route.
             * @return the c++ regex string of this route.
             */
            const std::string& getRegexString() const { return m_url_regex_string; }

            /**
             * Getter for the c++ regex of this route.
             * @return the c++ regex of this route.
             */
            const std::regex& getRegex() { return m_url_regex; }

            /**
             * Getter for the number of parameters this route has.
             * @return the number of parameters this route has.
             */
            size_t getParametersNumber() { return m_parameters_number; }

        private:
            /* Members */
            /** Methods allowed for the route. */
            int m_allowed_methods;

            /** The regex string for this route. */
            std::string m_url_regex_string;

            /** The regex for this route. */
            std::regex m_url_regex;

            /** The number of parameters for this route. */
            size_t m_parameters_number;
    };
}
#endif // OWEBPP_ABSTRACTROUTE_HPP
