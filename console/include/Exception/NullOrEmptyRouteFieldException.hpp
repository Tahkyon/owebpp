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
#ifndef OWEBPP_COMMANDS_EXCEPTION_NULL_OR_EMPTY_ROUTE_FIELD_EXCEPTION_HPP
#define OWEBPP_COMMANDS_EXCEPTION_NULL_OR_EMPTY_ROUTE_FIELD_EXCEPTION_HPP

#include <exception>

namespace owebpp::console {
    /** This exception is thrown when reading the YAML data if a field is null or is empty where it shouldn't be.  */
    class NullOrEmptyRouteFieldException: public std::exception {
            public:
                /* Constructors */
                /**
                 * Construct an exception for the given route name and null or empty field name
                 * @param route_name The route name with the bad field.
                 * @param field_name The field that is null or empty.
                 */
                NullOrEmptyRouteFieldException(const std::string& route_name, const std::string& field_name):
                    m_route_name(route_name),
                    m_field_name(field_name) {}

                /* Deleted constructors */
                NullOrEmptyRouteFieldException() = delete;
                NullOrEmptyRouteFieldException(const NullOrEmptyRouteFieldException& r) = delete;
                NullOrEmptyRouteFieldException(NullOrEmptyRouteFieldException&& r) = delete;

                /* Deleted assignment operators */
                NullOrEmptyRouteFieldException& operator=(const NullOrEmptyRouteFieldException& r) = delete;
                NullOrEmptyRouteFieldException& operator=(NullOrEmptyRouteFieldException&& r) = delete;

                /* Destructor */
                virtual ~NullOrEmptyRouteFieldException() = default;

                /* Functions */
                /**
                 * Returns to error message of the given exception.
                 * @return The error message
                 */
                const char* what() const noexcept {
                    return ("Field [" + m_field_name + "] for route: " + m_route_name + " is null or empty.").c_str();
                }

            private:
                /* Members */
                /** The route with the bad field */
                std::string m_route_name;

                /** The null or empty field. */
                std::string m_field_name;
    };
}

#endif // OWEBPP_COMMANDS_EXCEPTION_NULL_OR_EMPTY_ROUTE_FIELD_EXCEPTION_HPP
