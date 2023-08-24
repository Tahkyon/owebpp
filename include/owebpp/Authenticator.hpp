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
#ifndef OWEBPP_AUTHENTICATOR_HPP
#define OWEBPP_AUTHENTICATOR_HPP

#include <memory>

namespace owebpp {
    /** This class is used to perform user authentication. */
    class Authenticator {
        public:
            /* Constructors */
            /** Construct a default authenticator. */
            Authenticator() = default;

            /* Deleted constructors */
            Authenticator(const Authenticator& o) = delete;
            Authenticator(Authenticator&& o) = delete;

            /* Deleted assignment operators */
            Authenticator& operator=(const Authenticator& o) = delete;
            Authenticator& operator=(Authenticator&& o) = delete;

            /* Destructor */
            virtual ~Authenticator() = default;

            /* Functions */
            /**
             * Try to authenticate a user based on request data.
             * @param req The request to use to authenticate a user.
             * @return true if the user was authenticated, false otherwise.
             */
            virtual bool authenticate(const std::shared_ptr<Request>& req) = 0;
    };
}

#endif // OWEBPP_AUTHENTICATOR_HPP

