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
#ifndef NO_PARAM_ROUTE_CLASS_HPP
#define NO_PARAM_ROUTE_CLASS_HPP

#include <memory>
#include <owebpp/Request.hpp>
#include <owebpp/Response.hpp>

class NoParamRouteClass {
    public:
        /* Constructors */
        NoParamRouteClass() = default;

        /* Deleted constructors */
        NoParamRouteClass(const NoParamRouteClass& r) = delete;
        NoParamRouteClass(NoParamRouteClass&& r) = delete;

        /* Deleted assignment operators */
        NoParamRouteClass& operator=(const NoParamRouteClass&) = delete;
        NoParamRouteClass& operator=(NoParamRouteClass&& r) = delete;

        /* Destructor */
        virtual ~NoParamRouteClass() = default;

        /** This method is called when accessing url /no_param_route via GET. This is a basic example on how to use the framework. */
        [[nodiscard]] std::shared_ptr<owebpp::Response> noParamRouteFunction([[maybe_unused]] const std::shared_ptr<owebpp::Request>& req) {
            std::shared_ptr<owebpp::Response> res = std::make_shared<owebpp::Response>();
            res->setContent("no param content.");
            return res;
        }
};

#endif // NO_PARAM_ROUTE_CLASS_HPP
