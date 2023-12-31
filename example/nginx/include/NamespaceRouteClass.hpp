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
#ifndef NAMESPACE_ROUTE_CLASS_HPP
#define NAMESPACE_ROUTE_CLASS_HPP

#include <memory>
#include <owebpp/Request.hpp>
#include <owebpp/Response.hpp>

namespace example_namespace {
    class NamespaceRouteClass {
        public:
            /* Constructors */
            NamespaceRouteClass() = default;

            /* Deleted constructors */
            NamespaceRouteClass(const NamespaceRouteClass& o) = delete;
            NamespaceRouteClass(NamespaceRouteClass&& o) = delete;

            /* Deleted assignment operators */
            NamespaceRouteClass& operator=(const NamespaceRouteClass& o) = delete;
            NamespaceRouteClass& operator=(NamespaceRouteClass&& o) = delete;

            /* Destructor */
            virtual ~NamespaceRouteClass() = default;

            /* Functions */
            /** This method is called when accessing url /namespace_route via GET. Its purpose is to show the code generator can handle classes inside a namespace. */
            [[nodiscard]] std::shared_ptr<owebpp::Response> namespaceRouteFunction([[maybe_unused]] const std::shared_ptr<owebpp::Request>& req) {
                std::shared_ptr<owebpp::Response> res = std::make_shared<owebpp::Response>();
                res->setContent("Namespace content.");
                return res;
            }
    };
}

#endif // NAMESPACE_ROUTE_CLASS_HPP
