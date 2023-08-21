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
#ifndef OWEBPP_ROUTER_HPP
#define OWEBPP_ROUTER_HPP

#include <fstream>
#include <memory>

#include <owebpp/AbstractRoute.hpp>

namespace owebpp {
    /**
     * This class is a lazy loading singleton since the routes are added at program launch so we need to make sure the Router is loaded as soon as we need it
     */
    class Router final {

        /* allow Router shared_ptr without making the constructor public */
        friend std::shared_ptr<Router>;

        public:
            /* Constructors */
            /** Construct a Router object, simply load routes. */
            Router() : m_routes() { loadRoutes(); }

            /* Deleted constructors */
            Router(const Router& r) = delete;
            Router(Router&& r) = default;

            /* Deleted assignment operators */
            Router& operator=(const Router&) = delete;
            Router& operator=(Router&& r) = delete;

            /* Destructor */
            ~Router() = default;

            /* Singleton call method */
            /**
             * Get the router instance.
             * @return The logger instance.
             */
            static Router& getInstance() {
                if(s_router==nullptr){
                    s_router = std::make_shared<Router>();
                }
                return *s_router;
            }

            /* Functions */
            /**
             * Run the code associated to a route given the request.
             * @param The request.
             * @return The response to the request.
             */
            [[nodiscard]] std::shared_ptr<Response> searchAndExecuteRoute(const std::shared_ptr<Request>& req) {
                for(size_t i = 0; i < m_routes.size(); i++) {
                    int allowed_methods = m_routes[i]->getAllowedMethods();
                    int request_method = (int) req->getMethod();
                    if(allowed_methods & request_method ) {
                        std::smatch sm;
                        if (regex_search(req->getUrl(), sm, m_routes[i]->getRegex())) {
                            if((sm.size() - 1) == m_routes[i]->getParametersNumber()) {
                                return m_routes[i]->execute(req, sm);
                            }
                        }
                    }
                }
                std::shared_ptr<Response> response = std::make_shared<Response>();
                response->setSatusCode(HttpStatusCodes::NOT_FOUND);
                return response;
            }

        private:

            /* Methods */
            /**
             * This method is used to create an AbstractRoute child class std::shared_ptr object and cast it to a std::shared_ptr<AbstractRoute>.
             * This allows to insert the object into the m_routes container without a type error.
             * @param The request.
             * @return The AbstractRoute child class object shared_ptr cast to std::shared_ptr<AbstractRoute>.
             */
            template <class T> requires std::is_base_of_v<owebpp::AbstractRoute, T>
            [[nodiscard]] std::shared_ptr<owebpp::AbstractRoute> createRoute(const std::string& reg) {
                return std::make_shared<T>(reg);
            }

            /** this methods content is generated automaticaly */
            void loadRoutes();

            /* Members */
            /** Contains all the route that are available in the program */
            std::vector<std::shared_ptr<owebpp::AbstractRoute>> m_routes;

            /** Singleton object */
            static std::shared_ptr<Router> s_router;
    };

}

#endif // ROUTER_HPP
