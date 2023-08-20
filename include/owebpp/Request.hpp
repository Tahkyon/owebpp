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
#ifndef OWEBPP_REQUEST_HPP
#define OWEBPP_REQUEST_HPP

#include <string>
#include <map>
#include <owebpp/HttpMethods.hpp>

namespace owebpp {
    /** Represents an HTTP request. */
    class Request {
        public:
            /* Constructors */
            /**
             * Construct a Request representing an HTTP request data.
             * @param method The method used for the request see owebpp::HttpMethods.
             * @param url The URL used for this request.
             * @param headers The headers sent for this request.
             * @param get_parameters The get parameters sent for this request.
             * @param body The request body.
             */
            Request(HttpMethods method,
                    const std::string& url,
                    const std::map<std::string,std::string>& headers,
                    const std::map<std::string,std::string>& get_parameters,
                    const std::string& body):
                m_method(method),
                m_url(url),
                m_headers(headers),
                m_get_parameters(get_parameters),
                m_body(body){}

            /* Deleted constructors */
            Request(const Request& r) = delete;
            Request(Request&& r) = default;

            /* Deleted assignment operators */
            Request& operator=(const Request&) = delete;
            Request& operator=(Request&& r) = delete;

            /* Destructor */
            ~Request() = default;

            /* Getters and Setters */
            /**
             * Getter for the request method.
             * @return the request method.
             */
            HttpMethods getMethod() const { return m_method; }

            /**
             * Getter for the request url.
             * @return the request url.
             */
            const std::string& getUrl() const { return m_url; }

            /**
             * Getter for the request headers.
             * @return the request headers.
             */
            const std::map<std::string,std::string>& getHeaders() const { return m_headers; }

            /**
             * Getter for the request get parameters.
             * @return the request get parameters.
             */
            const std::map<std::string,std::string>& getGetParameters() const { return m_get_parameters; }

            /**
             * Getter for the request body.
             * @return the request body.
             */
            const std::string& getBody() const { return m_body; }

        private:
            /* Members */
            /** The request method */
            HttpMethods m_method;

            /** The request url */
            std::string m_url;

            /** The request headers */
            std::map<std::string,std::string> m_headers;

            /** The request get parameters */
            std::map<std::string,std::string> m_get_parameters;

            /** The request body */
            std::string m_body;
    };
}

#endif // OWEBPP_REQUEST_HPP
