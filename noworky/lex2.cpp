// lex.cpp
//
// A simple lexer.
// Copyright Daniel P. Teberian 2024


#include <iostream>
#include <regex>
#include <string>
#include <fstream>


// The actual lexer
void lex(const std::string& input)
{
	// Create a string with the value of input
	std::string remaining_input = input;

	// Regex pattern definitions
	std::regex whitespace_re("^\\s+");
	std::regex identifier_re("[a-zA-Z_][a-zA-Z0-9_]*");
	std::regex const_re("[0-9]+\\b");
	std::regex int_re("\\bint\\b");
	std::regex return_re("\\breturn\\b");
	std::regex void_re("\\bvoid\\b");
	std::regex open_parenthesis_re("\\(");
	std::regex close_parenthesis_re("\\)");
	std::regex open_brace_re("\\{");
	std::regex close_brace_re("\\}");
	std::regex semicolon_re(";");

	// While there is remaining input
	while (!remaining_input.empty())
	{
		// Remove leading whitespace
		if (std::regex_search(remaining_input, whitespace_re))
		{
			// Replace the whitespace with ""
			remaining_input = std::regex_replace(remaining_input, whitespace_re, "");
			// Proceed to the next line
			continue;
		}

		// Match integers
		if (std::regex_search(remaining_input, int_re))
		{
			// Create an smatch variable, named match
			std::smatch match;
			std::regex_search(remaining_input, match, int_re);

			// Move beyond matched tokens
			remaining_input = remaining_input.substr(match.length(0));

			// Proceed to the next line
			continue;
		}

		// Match identifier
		if (std::regex_search(remaining_input, identifier_re))
		{
			// Create an smatch variable, named match
			std::smatch match;
			std::regex_search(remaining_input, match, identifier_re);

			// Move beyond matched tokens
			remaining_input = remaining_input.substr(match.length(0));

			// Proceed to the next line
			continue;
		}

		// Match return
		if (std::regex_search(remaining_input, return_re))
		{
			// Create an smatch variable, named match
			std::smatch match;
			std::regex_search(remaining_input, match, return_re);

			// Move beyond matched tokens
			remaining_input = remaining_input.substr(match.length(0));

			// Proceed to the next line
			continue;
		}


		// Match constant
		if (std::regex_search(remaining_input, const_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match void
	        if (std::regex_search(remaining_input, void_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match open parenthesis
	        if (std::regex_search(remaining_input, open_parenthesis_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match close parenthesis
		if (std::regex_search(remaining_input, close_parenthesis_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match open brace
	        if (std::regex_search(remaining_input, open_brace_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match close brace
           	if (std::regex_search(remaining_input, close_brace_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// Match semicolon
	        if (std::regex_search(remaining_input, semicolon_re))
                {
                        // Create an smatch variable, named match
                        std::smatch match;
                        std::regex_search(remaining_input, match, identifier_re);

                        // Move beyond matched tokens
                        remaining_input = remaining_input.substr(match.length(0));

                        // Proceed to the next line
                        continue;
                }

		// If unrecognized input is encountered
		std::cerr << "[ERR] Could not recognize character: " << remaining_input.substr(0, 1) << std::endl;
		// Break out of the loop
		break;
	}
}


// The main function
int main(int argc, char* argv[])
{
        // Ensure a file was specified

        // If fewer than two arguments are provided
        if (argc < 2)
        {
                // Return an error
                std::cerr << "[ERR] No input file specified." << std::endl;
                return 1;
        }

        // Use the command line argument as the filename
        std::string filename = argv[1];
        // Open file
        std::ifstream file(filename);


        // Check if the file has been opened
        // If file is not open
        if (!file.is_open())
        {
                // Return an error
                std::cerr << "[ERR] Could not open file: " << filename << std::endl;
                return 1;
        }

	std::string input((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	lex(input);
	return 0;
}
