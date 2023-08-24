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
#include <cstdio>
#include <cstring>
#include <owebpp/Config.hpp>
#include <owebpp/Logger.hpp>
#include <owebpp/Request.hpp>
#include <owebpp/Response.hpp>
#include <owebpp/Router.hpp>
#include <sstream>
#include <string>

#include "include/_owebpp_generated_code.hpp"

// Mandatory logger initialization
OWEBPP_STATIC_INIT_LOGGER

extern "C" {
    /* These are c files without an extern "C" guard so we include them here. */
    #include <ngx_http.h>
    #include <ngx_link_func_module.h>

    /**
     * This method is called when the library is loaded.
     */
    [[maybe_unused]] void OWEBPP_LIB_EXPORT ngx_link_func_init_cycle(ngx_link_func_cycle_t* cycle);

    /**
     * This method is called when the library is unloaded.
     */
    [[maybe_unused]] void OWEBPP_LIB_EXPORT ngx_link_func_exit_cycle(ngx_link_func_cycle_t* cycle);

    /**
     * This method is called when a request is issued to nginx maching the url.
     */
    [[maybe_unused]] void OWEBPP_LIB_EXPORT entryPoint(ngx_link_func_ctx_t *ctx);

    /**
     * This method builds an owebpp::Request object from nginx data.
     */
    static std::shared_ptr<owebpp::Request> buildRequest(ngx_link_func_ctx_t *ctx);

    void ngx_link_func_init_cycle([[maybe_unused]] ngx_link_func_cycle_t* cycle) {
        std::shared_ptr<std::ofstream> output = std::make_shared<std::ofstream>("/var/log/libnginx.log", std::ios::trunc | std::ios::out);
        std::shared_ptr<owebpp::Logger> logger = std::make_shared<owebpp::Logger>(owebpp::LogLevel::LOG_DEBUG, output, DEFAULT_DATE_TIME_FORMAT);
        owebpp::Logger::setLogger(logger);
        OWEBPP_LOG_INFO("Starting application.");
    }

    static std::shared_ptr<owebpp::Request> buildRequest(ngx_link_func_ctx_t *ctx) {
        ngx_http_request_t* req = (ngx_http_request_t*)ctx->__r__;
        owebpp::HttpMethod method(owebpp::HttpMethod::HTTP_UNKNOWN);
        switch(req->method) {
            case NGX_HTTP_UNKNOWN:
                OWEBPP_LOG_WARNING("Method [UNKNOWN] provided.");
                method = owebpp::HttpMethod::HTTP_UNKNOWN;
                break;
            case NGX_HTTP_GET:
                method = owebpp::HttpMethod::HTTP_GET;
                break;
            case NGX_HTTP_HEAD:
                method = owebpp::HttpMethod::HTTP_HEAD;
                break;
            case NGX_HTTP_POST:
                method = owebpp::HttpMethod::HTTP_POST;
                break;
            case NGX_HTTP_PUT:
                method = owebpp::HttpMethod::HTTP_PUT;
                break;
            case NGX_HTTP_DELETE:
                method = owebpp::HttpMethod::HTTP_DELETE;
                break;
            case NGX_HTTP_MKCOL:
                method = owebpp::HttpMethod::HTTP_MKCOL;
                break;
            case NGX_HTTP_COPY:
                method = owebpp::HttpMethod::HTTP_COPY;
                break;
            case NGX_HTTP_MOVE:
                method = owebpp::HttpMethod::HTTP_MOVE;
                break;
            case NGX_HTTP_OPTIONS:
                method = owebpp::HttpMethod::HTTP_OPTIONS;
                break;
            case NGX_HTTP_PROPFIND:
                method = owebpp::HttpMethod::HTTP_PROPFIND;
                break;
            case NGX_HTTP_PROPPATCH:
                method = owebpp::HttpMethod::HTTP_PROPPATCH;
                break;
            case NGX_HTTP_LOCK:
                method = owebpp::HttpMethod::HTTP_LOCK;
                break;
            case NGX_HTTP_UNLOCK:
                method = owebpp::HttpMethod::HTTP_UNLOCK;
                break;
            case NGX_HTTP_PATCH:
                method = owebpp::HttpMethod::HTTP_PATCH;
                break;
            case NGX_HTTP_TRACE:
                method = owebpp::HttpMethod::HTTP_TRACE;
                break;
            default:
                OWEBPP_LOG_WARNING("Unknown method provided: " + std::to_string(req->method));
                break;
        }
        std::string url((const char*)req->uri.data, req->uri.len);
        ngx_list_part_t* current_header = &(req->headers_in.headers.part);
        ngx_table_elt_t* elem = (ngx_table_elt_t*)(current_header->elts);
        std::map<std::string, std::string> headers_map;
        for(size_t i = 0; i < current_header->nelts; i++) {
            std::string key((char*)(elem[i].key.data), elem[i].key.len);
            std::string value((char*)(elem[i].value.data), elem[i].value.len);
            headers_map[key] = value;
        }
        std::map<std::string, std::string> get_args_map;
        std::string get_args((char*)(req->args.data), req->args.len);
        std::istringstream get_args_stream(get_args);
        std::string get_parameter;
        while (std::getline(get_args_stream, get_parameter, '&')) {
            int pos = get_parameter.find_first_of('=');
            std::string key = get_parameter.substr(0, pos);
            std::string value = get_parameter.substr(pos+1);
            get_args_map[key] = value;
        }
        std::string body((char*)ctx->req_body, ctx->req_body_len);
        OWEBPP_LOG_INFO("Processing request: " + owebpp::HttpMethodUtils::convertMethodToString(method) + " " + url + '?'+ get_args);
        return std::make_shared<owebpp::Request>(method, url, headers_map, get_args_map, body);
    }

    void entryPoint(ngx_link_func_ctx_t *ctx) {
        std::shared_ptr<owebpp::Request> request(buildRequest(ctx));
        std::shared_ptr<owebpp::Response> response = owebpp::Router::getInstance().searchAndExecuteRoute(request);

        ngx_link_func_write_resp(
            ctx,
            (int)response->getSatusCode(),
            std::to_string((int)response->getSatusCode()).data(),
            (response->getContentType() + "; " + response->getCharset()).data(),
            response->getContent().data(),
            response->getContent().size()
        );
    }

    void ngx_link_func_exit_cycle([[maybe_unused]] ngx_link_func_cycle_t* cycle) {
        OWEBPP_LOG_INFO("Exiting application.");
    }
}
