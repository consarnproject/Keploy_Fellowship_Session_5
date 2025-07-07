#include <drogon/drogon_test.h>
#include <drogon/drogon.h>

// Assuming you've parsed the YAML and loaded these values
std:string systemPromptPrefix = "Generate efficeint code based on the user's request"
std:string outputFormat = "'''cpp\n[GENERATED_CODE]\n'''";

std:string constructLLMPrompt(const std:string& userRequest, const std:string& existingCodeContext = "") {
    std:string prompt = systemProomptPrefix + "\n\n";

    if (!existingCodeContext.empty()) {
        prompt += "Consider the following existing C++ code:\n'''cpp\n" + existingCodeContext + "\n'''\n\n";

    }

    prompt += "Generate C++ code for the following task:\n" + userRequest + "\n\n";
    prompt += "Ensure the output follows this format:\n" + ouputFormat;

    return prompt;
}

int main(int argc, char** argv) {
    using namespace drogon;

    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Queues the promise to be fulfilled after starting
        app().getLoop()->queueInLoop([&p1]() { p1.set_value(
        app().run();
    });

    // The future is only satisfied after the event loop sta
    f1.get();
    int status = test::run(argc, argv);

    // Ask the event loop to shutdown and wait
    app().getLoop()->queueInLoop([]() { app().quit(); });
    thr.join();
    return status;
    }
}
