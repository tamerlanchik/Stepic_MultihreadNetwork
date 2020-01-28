//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <boost/config.hpp>
//#include <cstdlib>
//#include <iostream>
//#include <memory>
//#include <string>
//#include <thread>
//
//namespace beast = boost::beast;
//namespace http = beast::http;
//namespace net = boost::asio;
//using tcp = net::ip::tcp;
//
////beast::string_view get_mime_type(beast::string_view path) {
////    auto const ext = [&path]{   // lambda-function, returns file extension
////        auto const pos = path.rfind(".");
////        if (pos == beast::string_view::npos)
////            return beast::string_view{};
////        return path.substr(pos);
////    }();
////    switch (true) {
////        case iequals(ext, ".htm")
////    }
////}
//
//std::string path_cat(beast::string_view base,
//					beast::string_view path) {
//	if (base.empty())
//		return std::string(path);
//	std::string result(base);
//
//	char constexpr path_separator = '/';
//	if (result.back() == path_separator) {
//		result.resize(result.size() - 1);
//	}
//	result.append(path.data(), path.size());
//	return result;
//}
//
//template<class Body, class Allocator, class Send>
//void handle_request(beast::string_view doc_root,
//					http::request<Body, http::basic_fields<Allocator>>&& req,
//					Send&& send) {
//	auto const bad_request = [&req](beast::string_view why) {
//		http::response<http::string_body> res{http::status::bad_request, req.version()};
//		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//		res.set(http::field::content_type, "text/html");
//		res.keep_alive(req.keep_alive());
//		res.body() = std::string(why);
//		res.prepare_payload();
//		return res;
//	};
//
//	auto const not_found = [&req](beast::string_view target) {
//		http::response<http::string_body> res{http::status::not_found, req.version()};
//		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//		res.set(http::field::content_type, "text/html");
//		res.keep_alive(req.keep_alive());
//		res.body() = "The resource '" + std::string(target) + "' was not found";
//		res.prepare_payload();
//		return res;
//	};
//
//	auto const server_error = [&req](beast::string_view what) {
//		http::response<http::string_body> res{http::status::internal_server_error, req.version()};
//		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//		res.set(http::field::content_type, "text/html");
//		res.keep_alive(req.keep_alive());
//		res.body() = "An error occurred: '" + std::string(what) + "'";
//		res.prepare_payload();
//		return res;
//	};
//
//	if (req.method() != http::verb::get &&
//		req.method() != http::verb::head) {
//		return send(bad_request("Unknown HTTP method"));
//	}
//
//	if (req.target().empty() ||
//		req.target()[0] != '/' ||
//		req.target().find("..") != beast::string_view::npos)
//		return send(bad_request("Illegal request target!"));
//
//	std::string path = path_cat(doc_root, req.target());
//	if (req.target().back() == '/') {
//		path.append("index.html");
//	}
//
//	beast::error_code ec;
//	http::file_body::value_type body;
//	body.open(path.c_str(), beast::file_mode::scan, ec);
//
//	if (ec == beast::errc::no_such_file_or_directory) {
//		return send(not_found(req.target()));
//	}
//	if (ec) {
//		return send(server_error(ec.message()));
//	}
//
//	auto const size = body.size();
//	if (req.method() == http::verb::head) {
//		http::response<http::empty_body> res{http::status::ok, req.version()};
//		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//		res.set(http::field::content_type, "text/html");	//TODO: mime_type()
//		res.content_length(size);
//		res.keep_alive(req.keep_alive());
//		return send(std::move(res));
//	};
//	http::response<http::file_body> res{
//		std::piecewise_construct,
//		std::make_tuple(std::move(body)),
//		std::make_tuple(http::status::ok, req.version())};
//	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//	res.set(http::field::content_type, "text/html");
//	res.content_length(size);
//	res.keep_alive(req.keep_alive());
//	return send(std::move(res));
//};
//
//template<class Stream>
//struct send_lambda {
//	Stream& _stream;
//	bool& _close;
//	beast::error_code & _ec;
//
//	explicit send_lambda(
//			Stream& stream,
//			bool& close,
//			beast::error_code & ec
//			) : _stream(stream), _close(close), _ec(ec) {};
//
//	template<bool isRequest, class Body, class Fields>
//	void operator() (http::message<isRequest, Body, Fields>&& msg) const {
//		_close = msg.need_eof();
//		http::serializer<isRequest, Body, Fields> sr{msg};
//		http::write(_stream, sr, _ec);
//	}
//};
//
//void fail(beast::error_code ec, char const* what) {
//	std::cerr << what << ": " << ec.message() << std::endl;
//}
//
//// Http connection handler
////void do_session(tcp::socket& socket, std::shared_ptr<std::string const> const& doc_root) {
////	std::cout << "New request: " << *doc_root << std::endl;
////	bool close = false;
////	beast::error_code ec;
////	beast::flat_buffer buffer;
////	send_lambda<tcp::socket> lambda{socket, close,  ec};
////	for(;;) {
////		http::request<http::string_body> req;
////		printf("Bytes read: %d\n", http::read(socket, buffer, req, ec));
////		if (ec == http::error::end_of_stream) {
////			break;
////		}
////		if (ec) {
////			return fail(ec, "read");
////		}
////		handle_request(*doc_root, std::move(req), lambda);
////		if (ec) {
////			return fail(ec, "write");
////		}
////		if (close) {
////			// "Connection close" state
////			break;
////		}
////	}
////
////	socket.shutdown(tcp::socket::shutdown_send, ec);
////}
////template<class Body, class Allocator, class Send>
//class Handler {
//public:
//	void operator() (){
//
//	};
//};
//
//class Router {
//public:
//	Router() {}
//
//	void AddHandler(const std::string& path, Handler& handler) {
//		_list.insert(std::pair<std::string, Handler&>(path, handler));
//	}
//	void Route(const std::string& path) {
//		_list.at(path)();
//	}
//private:
//	std::map<std::string, Handler&> _list;
//};
//
//class HTTPServer {
//public:
//	HTTPServer(const char* const address, const unsigned short port, const char* const doc_root) :
//			_address(net::ip::make_address(address)),
//			_port(port),
//			_doc_root(std::make_shared<std::string>(doc_root)){}
//private:
//	net::ip::address _address;
//	unsigned short _port;
//	std::shared_ptr<std::string> _doc_root;
//
//	static void do_session(tcp::socket& socket, std::shared_ptr<std::string const> const& doc_root) {
//		std::cout << "New request: " << *doc_root << std::endl;
//		bool close = false;
//		beast::error_code ec;
//		beast::flat_buffer buffer;
//		send_lambda<tcp::socket> lambda{socket, close,  ec};
//		for(;;) {
//			http::request<http::string_body> req;
//			printf("Bytes read: %d\n", http::read(socket, buffer, req, ec));
//			if (ec == http::error::end_of_stream) {
//				break;
//			}
//			if (ec) {
//				return fail(ec, "read");
//			}
//			handle_request(*doc_root, std::move(req), lambda);
//			if (ec) {
//				return fail(ec, "write");
//			}
//			if (close) {
//				// "Connection close" state
//				break;
//			}
//		}
//
//		socket.shutdown(tcp::socket::shutdown_send, ec);
//	}
//public:
//	int Run() {
//		try {
//			net::io_context ioc{1};
//			tcp::acceptor acceptor{ioc, {_address, _port}};
//
//			for (;;) {
//				tcp::socket socket{ioc};
//				acceptor.accept(socket);
//				std::thread{std::bind(
//						&do_session,
//						std::move(socket),
//						_doc_root
//				)}.detach();
//			}
//			return 0;
//		} catch (const std::exception& e) {
//			return EXIT_FAILURE;
//		}
//	}
//};
//
//int main(int argc, char* argv[]) {
//    std::cout << "Hello, World!" << std::endl;
//	if (argc != 4) {
//		std::cerr << "Not enough arguments.\n"
//				  << "Format: http-server-sync [address] [port] [root_dir]";
//		return EXIT_FAILURE;
//	}
//
//	HTTPServer server = HTTPServer(argv[1], std::atoi(argv[2]), argv[3]);
//	const int res = server.Run();
//	return res;
////    try {
////        if (argc != 4) {
////            std::cerr << "Not enough arguments.\n"
////            	<< "Format: http-server-sync [address] [port] [root_dir]";
////            return EXIT_FAILURE;
////        }
////        auto const address = net::ip::make_address(argv[1]);
////        auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
////        auto const doc_root = std::make_shared<std::string>(argv[3]);
////
////        net::io_context ioc{1};
////
////        tcp::acceptor acceptor{ioc, {address, port}};
////        for (;;) {
////            tcp::socket socket{ioc};
////            acceptor.accept(socket);
////            std::thread{std::bind(
////                    &do_session,
////                    std::move(socket),
////                    doc_root
////            )}.detach();
////        }
////    } catch (const std::exception& e) {
////        std::cerr << "Error: " << e.what() << std::endl;
////        return EXIT_FAILURE;
////    }
//
////    return 0;
//}