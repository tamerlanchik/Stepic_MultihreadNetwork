//	install libevent in Ubuntu: sudo apt-get install libevent-dev

//  original paste: https://pastebin.com/NZ9CSjAn
//	does not work - error in "setsockopt(6, SOL_SOCKET, SO_KEEPALIVE, [1], 4) = -1 EINVAL (Invalid argument)"
//	migrated to sockaddr_in - what is the fucking difference? but it works

#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static void echo_read_cb(struct bufferevent* bev, void* ctx) {
	struct evbuffer* input = bufferevent_get_input(bev);
	struct evbuffer* output = bufferevent_get_output(bev);

	size_t length = evbuffer_get_length(input);
	char* data = (char*) malloc(length);
	evbuffer_copyout(input, data, length);
	printf("data: %s\n", data);

	evbuffer_add_buffer(output, input);
	free(data);
}

static void echo_event_cb(struct bufferevent* bev, short events, void* ctx) {
	if (events & BEV_EVENT_ERROR) {
		perror("Error");
		bufferevent_free(bev);
	}

	if (events & BEV_EVENT_EOF) {
		bufferevent_free(bev);
	}
}

static void accept_conn_cb(struct evconnlistener* listener,
						   evutil_socket_t fd,
						   struct sockaddr* address,
						   int socklen,
						   void *ctx) {
	struct event_base* base = evconnlistener_get_base(listener);
	struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);
	bufferevent_enable(bev, EV_READ | EV_WRITE);
}

static void accept_error_cb(struct evconnlistener* listener,
							void *ctx) {
	struct event_base* base = evconnlistener_get_base(listener);

	int err = EVUTIL_SOCKET_ERROR();
	fprintf(stderr, "Error = %d = \"%s\"\n", err, evutil_socket_error_to_string(err));

	event_base_loopexit(base, NULL);
}

int main(int argc, char** argv) {
	event_base *base = event_base_new();
	if (!base) {
		perror("Cannot create base");
		return 1;
	}
	sockaddr_in sin = {0};
	sin.sin_port = htons(12345);
	sin.sin_family = AF_INET;

	evconnlistener* listener = evconnlistener_new_bind(base,
				accept_conn_cb, /* callback */
				NULL /* arg */,
//                (void*)base,
				LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, /* flags */
				-1, /* backlog */
				(sockaddr*)(&sin), sizeof(sin));

	if (!listener) {
		perror("Cannot create listener");
		return 1;
	}
	evconnlistener_set_error_cb(listener, accept_error_cb);
	event_base_dispatch(base);


	return 0;
}
