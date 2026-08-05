#include "EnvLoader.hpp"
#define BOOST_JSON_HEADER_ONLY

// boost/asio
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

// boost/beast
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/json/src.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace json = boost::json;

using tcp = net::ip::tcp;

int main()
{
    std::string file_name{".env"};
    std::ifstream file(file_name);
    EnvLoader env_loader(std::move(file), std::move(file_name));
    if (!env_loader.load_env())
        return 1;
    else
        std::cout << "File is found" << std::endl;

    net::io_context io_context;

    // Holds certificates
    ssl::context ctx(ssl::context::tlsv12_client);

    // Set the certificate file
    ctx.set_default_verify_paths();

    tcp::resolver resolver{io_context};
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws{io_context, ctx};

    if (env_loader.get_env_var_value("TWITCH_WEBSOCKET_HOST") == nullptr ||
        env_loader.get_env_var_value("TWITCH_WEBSOCKET_PORT") == nullptr)
    {
        return 1;
    }

    // Get Twitch endpoints
    auto const results =
        resolver.resolve(env_loader.get_env_var_value("TWITCH_WEBSOCKET_HOST"),
                         env_loader.get_env_var_value("TWITCH_WEBSOCKET_PORT"));

    // Connect to the server
    beast::get_lowest_layer(ws).connect(results);

    SSL_set_tlsext_host_name(
        ws.next_layer().native_handle(),
        env_loader.get_env_var_value("TWITCH_WEBSOCKET_HOST"));

    // Perform the SSL handshake
    ws.next_layer().handshake(ssl::stream_base::client);

    // Set a decorator to change the User-Agent of the handshake
    ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type &req)
        {
            req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " twitch-bot-client");
        }));

    // Connect to Twitch's server
    ws.handshake(env_loader.get_env_var_value("TWITCH_WEBSOCKET_HOST"),
                 env_loader.get_env_var_value("TWITCH_WEBSOCKET_PATH"));

    // Store incoming bytes from Twitch
    beast::flat_buffer buffer;

    // Read a message into our buffer
    ws.read(buffer);

    // Get const_buffer
    auto data = buffer.data();

    // Convert buffer to string view and parse it as JSON
    // Cast data.data() from const void * to char const *
    std::string_view sv(static_cast<char const *>(data.data()), data.size());

    // Parse json
    json::value jv = json::parse(sv);

    std::string session_id =
        jv.at("payload").at("session").at("id").as_string().c_str();

    std::cout << "Session ID: " << session_id << std::endl;

    return 0;
}