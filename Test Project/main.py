import ollama 
import os 

# Trigger Test Generation via Ollama API:
"""
- Utilize ollama Python library to interact with your local Ollama instance.
- Construct a prompt for Ollama requesting C++ test code for a specific scenario or function.
- Send this prompt to Ollama using the ollama.generate() or 
  ollama.chat() function, depending on whether a single response or a 
  conversational interaction is desired.
- Parse the response from Ollama to extract the generated C++ test code.
"""

def generate_cpp_test(prompt_text):
    try:
        response = ollama.generate(model='gemma3', prompt=prompt_text)
        return response['response']
    except Exception as e:
        print(f"Error geenrating test: {e}")
        return None 

# Write Generated Tests to C++ Files:
"""
- Create a dedicated directory for your generated C++ test files.
- Write the extracted C++ code into a .cpp file within this direectory. 
  Ensure a unique and descriptive filename for each generated test.
"""

def write_test_to_file(test_code, filename="drogon_test_integration_test.cpp"):
    test_dir = "generated_tests"
    os.makedirs(test_dir, exist_ok=True)
    filepath = os.path.join(test_dir, filename)
    with open(filepath, "W") as f:
        f.write(test_code)
        return filepath 
    
# Compile and Link the Test Executable:
"""
- Use Python's subprocess module to execute the C++ compiler (e.g., g++)
- Specify the input C++ test file(s) and any necessary compiler flags (e.g., include paths, libraries).
- Define an output executable name.
- handle potential compilation errors by checking the returncode of the subprcess call."""

import subprocess

def cmpile_cpp_test(filepath, executable_name="test_runner"):
    try:
        compile_command = ["g++", filepath, "-o", executable_name]
        result = subprocess.run(compile_command, capture_output=True, text=True, check=True)
        print("Compilation successful.")
        return executable_name 
    except subprocess.CalledProcessError as e:
        print(f"COmpilation failed: {e.stderr}")
        return None
    
# Run the Compiled Test Executable:
"""
- Again, use subprocess to execute the compiled test executable.
- Capture the output (stdout and stderr) to analyze test results.
- Implement logic to parse the output and determine test pass/fail status based 
  on your C++ test framework output format (e.g., Google test, Catch2)
"""

def run_compiled_test(executable_path): 
    try:
        run_command = [executable_path]
        result = subprocess.run(run_command, capture_output=True, text=True, check=True)
        print("Test execution ouput:")
        print(result.stdout)
        if result.stderr:
            print(f"Test execution errors: {result.stderr}")
        return result.stdout, result.stderr
    except subprocess.CalledProcessError as e:
        print(f"Test execution failed: {e.stderr}")
        return None, e.stderr


