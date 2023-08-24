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
#ifndef BASIC_AUTHENTICATOR_HPP
#define BASIC_AUTHENTICATOR_HPP

#include <owebpp/Authenticator.hpp>
#include <owebpp/Logger.hpp>

#include "include/BasicUrlEncodedDataParser.hpp"

/** This class is an example to perform user authentication. */
class BasicAuthenticator : public owebpp::Authenticator {
    public:
        /* Constructors */
        /** Construct a default parser. */
        BasicAuthenticator() = default;

        /* Deleted constructors */
        BasicAuthenticator(const BasicAuthenticator& o) = delete;
        BasicAuthenticator(BasicAuthenticator&& o) = delete;

        /* Deleted assignment operators */
        BasicAuthenticator& operator=(const BasicAuthenticator& o) = delete;
        BasicAuthenticator& operator=(BasicAuthenticator&& o) = delete;

        /* Destructor */
        virtual ~BasicAuthenticator() = default;

        /* Functions */
        /**
         * This function is an example of user authentication.
         * @param req The request containing the data to use to authenticate a user.
         * @return true if the user was authenticated, false otherwise.
         */
        bool authenticate(const std::shared_ptr<owebpp::Request>& req) override {
            bool ret(false);
            std::shared_ptr<std::map<std::string,std::string>> result = BasicUrlEncodedDataParser().parse(req->getBody());
            OWEBPP_LOG_DEBUG(req->getBody());
            if(result->contains("username") && result->contains("password")) {
                OWEBPP_LOG_DEBUG(result->at("username"));
                OWEBPP_LOG_DEBUG(result->at("password"));
                if((result->at("username") == "admin") && ((result->at("password")) == "adminpassword")) {
                    OWEBPP_LOG_DEBUG("check succesfull");
                    ret = true;
                }
            }
            return ret;
        }
};

#endif // BASIC_AUTHENTICATOR_HPP
