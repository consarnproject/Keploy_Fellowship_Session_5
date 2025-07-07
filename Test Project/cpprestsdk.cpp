#include <iostream>
# include <cpprest/http_client.h>
# include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    // Ollama API endpoint (default port)
    uri_builder builder(U("http://localhost:3000/api/generate"));
    http_client client(builder.to_uri());

    // JSON payload for the request
    json::value request_body;
    request_body[U("model")] = json::value::string(U("Gemma3")); 
    request_body[U("prompt")] = json::value::string(U("Generate a Catch2 unit test for the following C++ function within a Drogon application.
                                                        Focus on testing various input values and potential error conditions."))
    request_body[U("prompt")] = json::value::boolean(false);

    // make the POST request
    client.request(methods::POST, U("http://localhost:3000/api/generate"), request_body.serialize(), U("application/json"))
        .then([](http_response response) {
            // Check the respones status code
            if (response.status_code() == status_codes::OK) {
                // Extract and process the JSON response body
                return response.extract_json();

            } else {
                throw std::runtime_error("Request failed with status code: " + std::to_string(response.status_code()));

            }
        }) 
        .then([](json::value json_response) {
            // Print the generated response
            if (json_reponse.has_field(U("response"))) {
                std::cout << "Ollama Response: " << json_response[U("response")].as_string() << std::endl;
            } else {
                std::cout << "Unexpected JSON response format." << std::endl;
            }
        })
        .execpt([](const std::Exception& e) {
            // Handle exceptions 
            std::cerr << "Error: " << e.what() << std::endl;
        })
        .wait(); // Wait for the asynchronous operation to complete

    return 0;
}