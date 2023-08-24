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
#ifndef OWEBPP_RESPONSE_HPP
#define OWEBPP_RESPONSE_HPP

#include <owebpp/HttpStatusCode.hpp>
#include <string>
#include <vector>

namespace owebpp {
    /** Represents an HTTP response. */
    class Response {
        public:
            /* Constructors */
            /**
             * Construct a Response with default values.
             */
            Response():
                m_content(""),
                m_charset("utf-8"),
                m_content_type("text/plain"),
                m_status_code(HttpStatusCode::OK),
                m_headers() {}

            /* Deleted constructors */
            Response(const Response& o) = delete;
            Response(Response&& o) = delete;

            /* Deleted assignment operators */
            Response& operator=(const Response& o) = delete;
            Response& operator=(Response&& o) = delete;

            /* Destructor */
            ~Response() = default;

            /* Getters and Setters */
            /**
             * Getter for the response content.
             * @return The response content.
             */
            const std::string& getContent() const { return m_content; }

            /**
             * Setter for the response content.
             * @param content The content to use for the response.
             * @return The response.
             */
            inline Response& setContent(const std::string& content) {
                m_content = content;
                return *this;
            }

            /**
             * Getter for the response charset.
             * @return The response charset.
             */
            inline const std::string& getCharset() const { return m_charset; }

            /**
             * Setter for the response charset.
             * @param charset The charset to use for the response.
             * @return The response.
             */
            inline Response& setCharset(const std::string& charset) {
                m_charset = charset;
                return *this;
            }

            /**
             * Getter for the response content type.
             * @return The response content type.
             */
            inline const std::string& getContentType() const { return m_content_type; }

            /**
             * Setter for the response content type.
             * @param content_type The content type to use for the response.
             * @return The response.
             */
            inline Response& setContentType(const std::string& content_type) {
                m_content_type = content_type;
                return *this;
            }

            /**
             * Getter for the response status code.
             * @return The response status code.
             */
            inline HttpStatusCode getSatusCode() const { return m_status_code; }

            /**
             * Setter for the response status code.
             * @param status_code The status code to use for the response.
             * @return The response.
             */
            inline Response& setSatusCode(HttpStatusCode status_code) {
                m_status_code = status_code;
                return *this;
            }

            /**
             * Getter for the response headers.
             * @return The response headers.
             */
            inline std::vector<std::string>& getHeaders() { return m_headers; }

            /**
             * Setter for the response headers.
             * @param headers The headers to use for the response.
             * @return The response.
             */
            inline Response& setHeaders(const std::vector<std::string>& headers) {
                m_headers = headers;
                return *this;
            }

        protected:
            /* Members */
            /** The response content. */
            std::string m_content;

            /** The response charset. */
            std::string m_charset;

            /** The response content type. */
            std::string m_content_type;

            /** The response status code. */
            HttpStatusCode m_status_code;

            /** The response headers. */
            std::vector<std::string> m_headers;

    };
}
#endif //OWEBPP_RESPONSE_HPP
