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
#ifndef OWEBPP_CORE_COMMANDS_MODEL_ROUTE_MODEL_HPP
#define OWEBPP_CORE_COMMANDS_MODEL_ROUTE_MODEL_HPP

#include <memory>
#include <owebpp/HttpMethods.hpp>
#include <string>
#include <vector>

namespace owebpp::console {
    /** This class represents the data that can be assigned to a route. A route is  */
    class RouteModel {
        public:
            /* Constructors */
            /**
             * Construct a RouteModel based on the given parameters.
             * @param name Route name.
             * @param path The path (url with parameters) of the route.
             * @param allowed_methods Each bit represents a method that is allowed for the given route. See owebpp::HttpMethod.
             * @param generated_regex The c++ regex created from the path.
             * @param class_name The class that contains the function that must be called bythe framework for the given route.
             * @param class_include The file containing the class and function declaration that has to be called by the framework.
             * @param function_name The name of the function containing that must be called for the given route.
             * @param function_parameters Currently this field must contain as many values as the route has.
             *        The content of the values has no impact currently but it is advised to put "std::string" to avoid breaking your code later on.
             */
            RouteModel(const std::string& name,
                       const std::string& path,
                       const int allowed_methods,
                       const std::string& generated_regex,
                       const std::string& class_name,
                       const std::string& class_include,
                       const std::string function_name,
                       const std::shared_ptr<std::vector<std::string>>& function_parameters) :
                m_name(name),
                m_path(path),
                m_allowed_methods(allowed_methods),
                m_generated_regex(generated_regex),
                m_class_name(class_name),
                m_class_include(class_include),
                m_function_name(function_name),
                m_function_parameters(function_parameters){}

            /* Deleted constructors */
            RouteModel() = delete;
            RouteModel(const RouteModel& r) = delete;
            RouteModel(RouteModel&& r) = delete;

            /* Deleted assignment operators */
            RouteModel& operator=(const RouteModel& r) = delete;
            RouteModel& operator=(RouteModel&& r) = delete;

            /* Destructor */
            ~RouteModel() = default;

            /* Getters and Setters */
            /**
             * Getter for the route name.
             * @return the route name.
             */
            const std::string& getName() const { return m_name; }

            /**
             * Getter for the route path.
             * @return the route path.
             */
            const std::string& getPath() const { return m_path; }

            /**
             * Getter for allowed methods. See owebpp::HttpMethods.
             * @return the allowed methods.
             */
            int getAllowedMethods() const { return m_allowed_methods; }

            /**
             * Getter for the c++ regex generated from the path.
             * @return the route c++ regex.
             */
            const std::string& getGeneratedRegex() const { return m_generated_regex; }

            /**
             * Getter for the route class name.
             * @return the route class name.
             */
            const std::string& getClassName() const { return m_class_name; }

            /**
             * Getter for the route class include path.
             * @return the route class include path.
             */
            const std::string& getClassInclude() const { return m_class_include; }

            /**
             * Getter for the route function name.
             * @return the route function name.
             */
            const std::string& getFunctionName() const { return m_function_name; }

            /**
             * Getter for the route function parameters.
             * @return the route function parameters.
             */
            const std::shared_ptr<std::vector<std::string>>& getFunctionParameters() const { return m_function_parameters; }

        private:
            /* Members */
            /** Name of the route. */
            std::string m_name;

            /** URL associated to the route. */
            std::string m_path;

            /** Each bit represents a method that is allowed for the given route. See owebpp::HttpMethods. */
            int m_allowed_methods;

            /** The c++ regex created from the path. */
            std::string m_generated_regex;

            /** The class that contains the function that must be called bythe framework for the given route. */
            std::string m_class_name;

            /** The file containing the class and function declaration that has to be called by the framework. */
            std::string m_class_include;

            /** The name of the function containing that must be called for the given route. */
            std::string m_function_name;

            /**
             * Currently this field must contain as many values as the route has.
             * The content of the values has no impact currently but it is advised to put "std::string" to avoid breaking your code later on.
             */
            std::shared_ptr<std::vector<std::string>> m_function_parameters;
    };
}

#endif // OWEBPP_CORE_COMMANDS_MODEL_ROUTE_MODEL_HPP
