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
#ifndef AUTH_ROUTE_HPP
#define AUTH_ROUTE_HPP

#include <owebpp/HttpMethod.hpp>
#include <owebpp/HttpStatusCode.hpp>

class AuthRoute {
    public:
        /* Constructors */
        AuthRoute() = default;

        /* Deleted constructors */
        AuthRoute(const AuthRoute& o) = delete;
        AuthRoute(AuthRoute&& o) = delete;

        /* Deleted assignment operators */
        AuthRoute& operator=(const AuthRoute& o) = delete;
        AuthRoute& operator=(AuthRoute&& o) = delete;

        /* Destructor */
        ~AuthRoute() = default;

        /* Functions */
        /** This method is called when accessing url /auth_route.
         * If accessed with GET it will return a form to authenticate a user if done through POST it will try to authenticate a user.
         */
        std::shared_ptr<owebpp::Response> authFunction(const std::shared_ptr<owebpp::Request>& req) {
            std::shared_ptr<owebpp::Response> res = std::make_shared<owebpp::Response>();
            if(req->getMethod() == owebpp::HttpMethod::HTTP_POST) {
                if(BasicAuthenticator().authenticate(req)) {
                    res->setContent("admin authenticated");
                } else {
                    res->setContent("could not authenticate.");
                }
            } else {
                std::ifstream t("/usr/local/etc/owebpp-example-lib-nginx/index.html");
                std::stringstream buffer;
                buffer << t.rdbuf();

                res->setContent(buffer.str());
                res->setContentType("text/html");
                res->setSatusCode(owebpp::HttpStatusCode::OK);
            }
            return res;
        }

    private:
};

#endif // AUTH_ROUTE_HPP
