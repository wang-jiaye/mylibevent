#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/http_struct.h>

void generic_handler(struct evhttp_request *req, void *arg) {
    struct evbuffer *returnbuffer = evbuffer_new();

    evbuffer_add_printf(returnbuffer, "Thanks for the request!");
    evhttp_send_reply(req, HTTP_OK, "Client", returnbuffer);
    evbuffer_free(returnbuffer);
    return;
}

int main() {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    base = event_base_new();
    if (!base) {
        fprintf(stderr, "Couldn't create an event_base: exiting\n");
        return 1;
    }

    http = evhttp_new(base);
    if (!http) {
        fprintf(stderr, "couldn't create evhttp. Exiting.\n");
        return 1;
    }

    evhttp_set_gencb(http, generic_handler, NULL);

    handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", 8080);
    if (!handle) {
        fprintf(stderr, "couldn't bind to port 8080. Exiting.\n");
        return 1;
    }

    event_base_dispatch(base);

    return 0;
}
