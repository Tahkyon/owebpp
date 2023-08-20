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
#ifndef OWEBPP_HTTP_METHODS_HPP
#define OWEBPP_HTTP_METHODS_HPP

#include <cstddef>

namespace owebpp {
    /** Lists all the HTTP methods that the framework supports. */
    enum class HttpMethod : size_t {
        HTTP_UNKNOWN=   0,
        HTTP_GET=       1,
        HTTP_HEAD=      2,
        HTTP_POST=      4,
        HTTP_PUT=       8,
        HTTP_DELETE=    16,
        HTTP_MKCOL=     32,
        HTTP_COPY=      64,
        HTTP_MOVE=      128,
        HTTP_OPTIONS=   256,
        HTTP_PROPFIND=  512,
        HTTP_PROPPATCH= 1024,
        HTTP_LOCK=      2048,
        HTTP_UNLOCK=    4096,
        HTTP_PATCH=     8192,
        HTTP_TRACE=     16384
    };

    /** Provides utility functions to convert to and from string. */
    class HttpMethodsUtils final {
        public:
            /* Deleted constructors */
            HttpMethodsUtils() = delete;
            HttpMethodsUtils(const HttpMethodsUtils& r) = delete;
            HttpMethodsUtils(HttpMethodsUtils&& r) = delete;

            /* Deleted assignment operators */
            HttpMethodsUtils& operator=(const HttpMethodsUtils& r) = delete;
            HttpMethodsUtils& operator=(HttpMethodsUtils&& r) = delete;

            /* Deleted destructor */
            ~HttpMethodsUtils() = delete;

            /* Functions */
            /**
             * Convert a string to an HttpMethod.
             * @param method_str The string to convert to an HttpMethod.
             * @return The HttpMethod corresponding to the given string.
             */
            static HttpMethod convertMethodStringToValue(const std::string& method_str) {
                HttpMethods method = HttpMethods::HTTP_UNKNOWN;
                if(method_str == "GET") {
                    method = HttpMethod::HTTP_GET;
                } else if(method_str == "HEAD") {
                    method = HttpMethod::HTTP_HEAD;
                } else if(method_str == "POST") {
                    method = HttpMethod::HTTP_POST;
                } else if(method_str == "PUT") {
                    method = HttpMethod::HTTP_PUT;
                } else if(method_str == "DELETE") {
                    method = HttpMethod::HTTP_DELETE;
                } else if(method_str == "MKCOL") {
                    method = HttpMethod::HTTP_MKCOL;
                } else if(method_str == "COPY") {
                    method = HttpMethod::HTTP_COPY;
                } else if(method_str == "MOVE") {
                    method = HttpMethod::HTTP_MOVE;
                } else if(method_str == "OPTIONS") {
                    method = HttpMethod::HTTP_OPTIONS;
                } else if(method_str == "PROPFIND") {
                    method = HttpMethod::HTTP_PROPFIND;
                } else if(method_str == "PROPPATCH") {
                    method = HttpMethod::HTTP_PROPPATCH;
                } else if(method_str == "LOCK") {
                    method = HttpMethod::HTTP_LOCK;
                } else if(method_str == "UNLOCK") {
                    method = HttpMethod::HTTP_UNLOCK;
                } else if(method_str == "PATCH") {
                    method = HttpMethod::HTTP_PATCH;
                } else if(method_str == "TRACE") {
                    method = HttpMethod::HTTP_TRACE;
                }
                return method;
            }

            /**
             * Convert an HttpMethod to a string.
             * @param method The HttpMethod to convert to a string.
             * @return The string corresponding to the given HttpMethod.
             */
            static std::string convertMethodToString(HttpMethod method) {
                std::string result;
                switch(method) {
                    case HttpMethods::HTTP_GET:
                        result = "GET";
                        break;
                    case HttpMethods::HTTP_HEAD:
                        result = "HEAD";
                        break;
                    case HttpMethods::HTTP_POST:
                        result = "POST";
                        break;
                    case HttpMethods::HTTP_PUT:
                        result = "PUT";
                        break;
                    case HttpMethods::HTTP_DELETE:
                        result = "DELETE";
                        break;
                    case HttpMethods::HTTP_MKCOL:
                        result = "MKCOL";
                        break;
                    case HttpMethods::HTTP_COPY:
                        result = "COPY";
                        break;
                    case HttpMethods::HTTP_MOVE:
                        result = "MOVE";
                        break;
                    case HttpMethods::HTTP_OPTIONS:
                        result = "OPTIONS";
                        break;
                    case HttpMethods::HTTP_PROPFIND:
                        result = "PROPFIND";
                        break;
                    case HttpMethods::HTTP_PROPPATCH:
                        result = "PROPPATCH";
                        break;
                    case HttpMethods::HTTP_LOCK:
                        result = "LOCK";
                        break;
                    case HttpMethods::HTTP_UNLOCK:
                        result = "UNLOCK";
                        break;
                    case HttpMethods::HTTP_PATCH:
                        result = "PATCH";
                        break;
                    case HttpMethods::HTTP_TRACE:
                        result = "TRACE";
                        break;
                    case HttpMethods::HTTP_UNKNOWN:
                        result="UNKNOWN";
                        break;
                    default:
                        result="";
                        break;
                }
                return result;
            }
    };
}
#endif //OWEBPP_HTTP_METHODS_HPP
