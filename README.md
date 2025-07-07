# Keploy_Fellowship_Session_5:

APPROACH (Test Project Folder) ->

c++ prompt.cpp:

- Assuming you've parsed YAML and loaded values

catch2.hpp:

- Generate a catch2 unit test for the following c++ function within a Drogon application.
- Focus on testing various input values and potential error conditions.

cpprestsdk.cpp:
- Ollama API endpoint (default port)
- JSON payload for the request
- Make the POST / other request

main.py:
(Trigger Test Genration via Ollama API)
- Utilize llama Python library to interact with your local llama instance.
- Construct a prompt for llama requesting c++ test code for a specific scenario or function.
- Send this prompt to llama using the llama.generate() function.
- Parse the response from llama to extract the generated c++ test code.

(Write Generated Tests to c++ files)
- Create a dedicated directory for your generated c++ files.
- Write the extracted c++ code into a .cpp file within this directory
- Ensure a unique and descriptive filename for each generated test.

(Compile and Link the Test Executable)
- Use Python's subprocess module to execute the c++ compiler
- Specify the input c++ test files and any necessary compiler flags (e.g., include paths, libraries)
- Define an output executable name
- Handle potential compilation errors by checking the return code of the subprocess call.

(Run the compiled test executable)
- Again, use subprocesses to execute the compiled test executable.
- Capture the output (stdout and stderr) to analyze test results.
- Implement logic to parse the output and determine test pass/fail states based on your c++ test framework ouput format (e.g. catch2)

