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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <regex>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "Exception/MissingRouteFieldException.hpp"
#include "Exception/NullOrEmptyRouteFieldException.hpp"
#include "Generation/RouteCodeGenerator.hpp"
#include <owebpp/Logger.hpp>
#include "Model/RouteModel.hpp"

namespace owebpp::console {

    std::shared_ptr<std::vector<std::shared_ptr<RouteModel>>> RouteCodeGenerator::buildRoutesModel(YAML::Node& routes_node) {
        std::shared_ptr<std::vector<std::shared_ptr<RouteModel>>> routes_models(std::make_shared<std::vector<std::shared_ptr<RouteModel>>>());

        if(routes_node) {
			/* Iterate all routes. */
			for(const auto& route : routes_node) {
				/* TODO: try to find a more straight forward way to do it, we need to go through a output stream to get the node data... */
				std::ostringstream oss;
				oss << route;
				std::istringstream iss(oss.str());
				std::string route_name;
				/* We get all the string corresponding to the node which includes sub nodes ect... So we get the string part up to the first : */
				getline(iss, route_name, ':');

                std::shared_ptr<std::vector<std::string>> parameters_list(std::make_shared<std::vector<std::string>>());

                // Iterate function parameters.
				for(const YAML::Node& parameter_node : route["function_parameters"]) {
                    parameters_list->push_back(parameter_node.as<std::string>());
				}

				const YAML::Node& methods_node(route["methods"]);
				int allowed_methods = 0;
				if(methods_node) {
                    if(methods_node.IsNull() || methods_node.as<std::string>() == "") {
                        throw NullOrEmptyRouteFieldException(route_name, "methods");
                    }
                    std::istringstream allowed_methods_stream(route["methods"].as<std::string>());
                    std::string http_method_allowed;
                    while (getline(allowed_methods_stream, http_method_allowed, '|')) {
                        size_t tmp = HttpMethodsUtils::convertMethodStringToValue(http_method_allowed);
                        if(tmp == 0) {
                            if(http_method_allowed == "") {
                                OWEBPP_LOG_WARNING("Method is an empty string.");
                            } else {
                                OWEBPP_LOG_WARNING("Unknown HTTP method: " + http_method_allowed);
                            }
                        }
                        allowed_methods |= tmp;
                    }
				} else {
                    throw MissingRouteFieldException(route_name, "methods");
				}
				// Retrieve path node data.
				std::string path;
                const YAML::Node& path_node(route["path"]);
                if(path_node) {
                    if(path_node.IsNull() || path_node.as<std::string>() == "") {
                        throw NullOrEmptyRouteFieldException(route_name, "path");
                    }
                    path = path_node.as<std::string>();
                } else {
                    throw MissingRouteFieldException(route_name, "path");
                }

                // Retrieve class name node data.
				std::string class_name;
                const YAML::Node& class_name_node(route["class_name"]);
                if(class_name_node) {
                    if(class_name_node.IsNull() || class_name_node.as<std::string>() == "") {
                        throw NullOrEmptyRouteFieldException(route_name, "class_name");
                    }
                    class_name = class_name_node.as<std::string>();
                } else {
                    throw MissingRouteFieldException(route_name, "class_name");
                }
                // Retrieve class include node data.
				std::string class_include;
                const YAML::Node& class_include_node(route["class_include"]);
                if(class_include_node) {
                    if(class_include_node.IsNull() || class_include_node.as<std::string>() == "") {
                        throw NullOrEmptyRouteFieldException(route_name, "class_include");
                    }
                    class_include = class_include_node.as<std::string>();
                } else {
                    throw MissingRouteFieldException(route_name, "class_include");
                }
                // Retrieve function name node data.
				std::string function_name;
                const YAML::Node& function_name_node(route["function_name"]);
                if(function_name_node) {
                    if(function_name_node.IsNull() || function_name_node.as<std::string>() == "") {
                        throw NullOrEmptyRouteFieldException(route_name, "function_name");
                    }
                    function_name = function_name_node.as<std::string>();
                } else {
                    throw MissingRouteFieldException(route_name, "function_name");
                }
                routes_models->push_back(std::make_shared<RouteModel>(route_name,
                    path,
                    allowed_methods,
                    convertYAMLRegexToCppRegex(path, parameters_list),
                    class_name,
                    class_include,
                    function_name,
                    parameters_list));
			}
		} else {
            OWEBPP_LOG_ERROR("Missing [routes] field in yaml file.");
		}
		return routes_models;
    }

    void RouteCodeGenerator::writeGeneratedRoutesFile(const std::string& output_file, const std::shared_ptr<std::vector<std::shared_ptr<RouteModel>>> routes) {
        std::ofstream fs(output_file, fs.trunc);
        if(!fs.is_open()) {
            throw std::invalid_argument("Unable to open output file: " + output_file + " Aborting code generation.");
        }
        /* Write file start. */
        fs << "/* Do not edit this file, the content is automatically generated. */" << std::endl;
        fs << "#ifndef _oweb_generated_code_hpp" << std::endl;
        fs << "#define _oweb_generated_code_hpp" << std::endl;
        fs << std::endl;
        fs << "#include <memory>" << std::endl;
        fs << "#include <owebpp/AbstractRoute.hpp>" << std::endl;
        fs << "#include <owebpp/Response.hpp>" << std::endl;
        fs << "#include <owebpp/Request.hpp>" << std::endl;
        fs << "#include <regex>" << std::endl;
        fs << std::endl;
        fs << "namespace owebpp::generated {" << std::endl;

        /* Iterate routes and write corresponding code. */
        for(size_t i = 0; i < routes->size(); i++) {
            fs << std::endl;
            fs << "\t#include \"" << (*routes)[i]->getClassInclude() << '"' << std::endl;
            fs << std::endl;

            fs << "\tclass _owebpp_genroute_" << (*routes)[i]->getName() << (*routes)[i]->getFunctionName() << " final : public owebpp::AbstractRoute " << '{' << std::endl;
            fs << "\t\tpublic:" << std::endl;
            fs << "\t\t\t_owebpp_genroute_" << (*routes)[i]->getName() << (*routes)[i]->getFunctionName() << "(const std::string& reg): owebpp::AbstractRoute(" << (*routes)[i]->getAllowedMethods() << ",reg," << (*routes)[i]->getFunctionParameters()->size() << ") {}" << std::endl;
            fs << "\t\t\t~_owebpp_genroute_" << (*routes)[i]->getName() << (*routes)[i]->getFunctionName() << "() = default;" << std::endl;
            fs << std::endl;
            fs << "\t\t\t[[nodiscard]] std::shared_ptr<owebpp::Response> execute(const std::shared_ptr<owebpp::Request>& req, [[maybe_unused]] std::smatch& sm) override {" << std::endl;
            //fs << "\t\t\t\tstd::unique_ptr<" << (*routes)[i]->getClassName() << "> p = std::make_unique<" << (*routes)[i]->getClassName() << ">();" << std::endl;
            fs << "\t\t\t\treturn " << (*routes)[i]->getClassName() << "()." << (*routes)[i]->getFunctionName() << "(req";

            /* iterate parameters provided to client code function call */
            for(size_t cpt = 0; cpt < (*routes)[i]->getFunctionParameters()->size(); cpt++) {
                fs << ',' << "sm[" << cpt+1 << ']';
            }
            fs << ");" << std::endl;
            fs << "\t\t\t}" << std::endl;
            fs << "\t};" << std::endl;
        }
        fs << '}' << std::endl;
        fs << std::endl;
        /* Write code for routes list population. */
        fs << "void owebpp::Router::loadRoutes() {" << std::endl;
        for(size_t i = 0; i < routes->size(); i++) {
            fs << "\tm_routes.push_back(createRoute<owebpp::generated::_owebpp_genroute_" << (*routes)[i]->getName() << (*routes)[i]->getFunctionName() << ">(\"" << (*routes)[i]->getGeneratedRegex() << "\"));" << std::endl;
        }
        fs << "}" << std::endl;
        fs << std::endl;
        /* Write code for static initialization of router. */
        fs << "std::shared_ptr<owebpp::Router> owebpp::Router::s_router = nullptr;" << std::endl;
        fs << std::endl;
        fs << "#endif" << std::endl;
    }

	std::string RouteCodeGenerator::convertYAMLRegexToCppRegex(std::string yaml_regex, [[maybe_unused]] const std::shared_ptr<std::vector<std::string>>& function_parameters) {

        std::istringstream route_stream(yaml_regex);
        std::string route_part;
        std::string reconstructed_regex;
        while (getline(route_stream, route_part, '/')) {
            if(route_part[0] == ':') {
                reconstructed_regex += "/([a-zA-Z0-9_]+)";
            } else if (route_part.size() > 0){
                reconstructed_regex += '/';
                reconstructed_regex += route_part;
            }
        }
        return reconstructed_regex;
	}

	bool RouteCodeGenerator::generateCode(bool is_generator_ok) {
        try {
            YAML::Node config = YAML::LoadFile(m_yaml_file_name);
            YAML::Node routes_node = config["routes"];
            writeGeneratedRoutesFile(m_output_code_file, buildRoutesModel(routes_node));
            is_generator_ok = true;
        } catch(const NullOrEmptyRouteFieldException& e) {
            if(is_generator_ok) {
                OWEBPP_LOG_ERROR(e.what());
            }
            is_generator_ok = false;
        } catch(const std::invalid_argument& e) {
            if(is_generator_ok) {
                OWEBPP_LOG_ERROR(e.what());
            }
            is_generator_ok = false;
        } catch (const MissingRouteFieldException& e) {
            if(is_generator_ok) {
                OWEBPP_LOG_ERROR(e.what());
            }
            is_generator_ok = false;
        } catch( const YAML::BadFile& e ) {
            if(!is_generator_ok) {
                OWEBPP_LOG_FATAL("Couldn't read file: " + m_yaml_file_name + " Code generation aborted.");
            }
            is_generator_ok = false;
        } catch(const YAML::ParserException& e) {
            OWEBPP_LOG_FATAL(m_yaml_file_name + " has invalid synthax: " + e.what());
            is_generator_ok = false;
        }
        return is_generator_ok;
	}
}
