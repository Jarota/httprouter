/* This is a managed file. Do not delete this comment. */

#include <corto/httprouter/httprouter.h>
int16_t httprouter_Router_construct(
    httprouter_Router this)
{
    if (!corto_interface(this)->base) {
        corto_ptr_setref(&corto_interface(this)->base, httprouter_Service_o);
    }

    return corto_super_construct(this);
}

int32_t httprouter_Router_matchRoute(
    httprouter_Router this,
    corto_route route,
    corto_stringseq pattern,
    corto_any param,
    corto_any *routerData)
{
    corto_assert(
      corto_instanceofType(httpserver_HTTP_Request_o, param.type),
      "web/server/Router parameter is not HTTP/Request");

    corto_int32 result = -1;
    httpserver_HTTP_Request *r = param.value;
    corto_bool match = FALSE;

    if ((r->method == Httpserver_Get) && (corto_instanceof(httprouter_GET_o, route))) {
        match = TRUE;
    } else if ((r->method == Httpserver_Post) && (corto_instanceof(httprouter_POST_o, route))) {
        match = TRUE;
    } else if ((r->method == Httpserver_Put) && (corto_instanceof(httprouter_PUT_o, route))) {
        match = TRUE;
    } else if ((r->method == Httpserver_Delete) && (corto_instanceof(httprouter_DELETE_o, route))) {
        match = TRUE;
    }

    if (match) {
        result = x_parser_matchRoute_v(this, route, pattern, param, routerData);
    }

    return result;
}

