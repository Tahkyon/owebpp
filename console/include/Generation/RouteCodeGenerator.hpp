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
#ifndef OWEBPP_COMMANDS_GENERATION_ROUTE_CODE_GENERATOR_HPP
#define OWEBPP_COMMANDS_GENERATION_ROUTE_CODE_GENERATOR_HPP

#include <memory>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "Model/RouteModel.hpp"

namespace owebpp::console {
    /** This class takes a YAML file converts the content to code and outputs it to a given file.  */
	class RouteCodeGenerator {
		public:
			/* Constructors */
            /**
             * Construct an object that can generate code to link owebpp library and user code based on input YAML file.
             * @param yaml_file_name The file to use to generate code.
             * @param output_code_file The file to write the code to.
             */
            RouteCodeGenerator(const std::string_view& yaml_file_name, const std::string& output_code_file):
                m_yaml_file_name(yaml_file_name),
                m_output_code_file(output_code_file) {}

            /* Deleted constructors */
            RouteCodeGenerator() = delete;
            RouteCodeGenerator(const RouteCodeGenerator& r) = delete;
            RouteCodeGenerator(RouteCodeGenerator&& r) = delete;

            /* Deleted assignment operators */
            RouteCodeGenerator& operator=(const RouteCodeGenerator& r) = delete;
            RouteCodeGenerator& operator=(RouteCodeGenerator&& r) = delete;

            /* Destructor */
            ~RouteCodeGenerator() = default;

			/* Functions */
            /**
             * Generates code based on a given YAML configuration file.
             * @param is_generator_ok Avoid logging multiple times an error message, if false then no error message will be logged.
             * @return true if the code generation worked, false otherwise.
             */
			bool generateCode(bool is_generator_ok);

		private:
            /* Functions */
            /**
             * Converts a YAML route regex e.g "/three_param_route/:param1/:var2/:id" to c++ regex e.g "/three_param_route/([a-zA-Z0-9_]+)/([a-zA-Z0-9_]+)/([a-zA-Z0-9_]+)"
             * @param yaml_regex The regex to convert.
             * @param function_parameters This parameter is unused for the moment, it will allow to customize the regex based on the regex parameters type.
             * @return The generated c++ regex.
             */
            static std::string convertYAMLRegexToCppRegex(std::string yaml_regex, const std::shared_ptr<std::vector<std::string>>& function_parameters);

            /**
             * Convert yaml data to a model that can be used to generate code.
             * @param routes_node The yaml data.
             * @param function_parameters This parameter is unused for the moment, it will allow to customize the regex based on the regex parameters type.
             * @return The model generated from the YAML data.
             */
			static std::shared_ptr<std::vector<std::shared_ptr<RouteModel>>> buildRoutesModel(YAML::Node& routes_node);

            /**
             * Generates code and writes it to the given file based on the provided model.
             * @param output_file The file to write the code to.
             * @param routes The model to use to write the generated code.
             */
			static void writeGeneratedRoutesFile(const std::string& output_file, std::shared_ptr<std::vector<std::shared_ptr<RouteModel>>> routes);

			/* Members */
			/** the YAML file that will be used to generate code.*/
			std::string m_yaml_file_name;

			/** the file to write the generated code to.*/
			std::string m_output_code_file;
	};
}
#endif //OWEBPP_COMMANDS_GENERATION_ROUTE_CODE_GENERATOR_HPP
