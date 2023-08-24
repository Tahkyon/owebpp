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
#ifndef THREE_PARAM_ROUTE_CLASS_HPP
#define THREE_PARAM_ROUTE_CLASS_HPP

#include <memory>
#include <owebpp/Request.hpp>
#include <owebpp/Response.hpp>

class ThreeParamRouteClass {
    public:
        /* Constructors */
        ThreeParamRouteClass() = default;

        /* Deleted constructors */
        ThreeParamRouteClass(const ThreeParamRouteClass& o) = delete;
        ThreeParamRouteClass(ThreeParamRouteClass&& o) = delete;

        /* Deleted assignment operators */
        ThreeParamRouteClass& operator=(const ThreeParamRouteClass& o) = delete;
        ThreeParamRouteClass& operator=(ThreeParamRouteClass&& o) = delete;

        /* Destructor */
        virtual ~ThreeParamRouteClass() = default;

        /**
         * This method is called when accessing url /three_param_route/:param1/:var2/:id via GET where :param1, :var2 and :id are parameters.
         * As you can see the function has three parameters in addition to the request object.
         */
        [[nodiscard]] std::shared_ptr<owebpp::Response> threeParamRouteFunction([[maybe_unused]] const std::shared_ptr<owebpp::Request>& req, const std::string& param1, const std::string& param2, const std::string& param3) {
            std::shared_ptr<owebpp::Response> res = std::make_shared<owebpp::Response>();
            res->setContent("three param content: " + param1 + " " + param2 + " " + param3);
            return res;
        }
};

#endif // THREE_PARAM_ROUTE_CLASS_HPP
