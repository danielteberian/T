// lex.c
//
// A simple lexer.
// Copyright Daniel P. Teberian 2024


#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

using namespace std;

// Enum of different types of tokens
enum class TOKEN_TYPE
{
	KEYWORD,
	IDENTIFIER,
	INT_LITERAL,
	FLOAT_LITERAL,
	OPERATOR,
	PUNCTUATOR,
	UNKNOWN
};


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


	// Match leading whitespace
	std::regex whitespace_re("^\\s+");

	// Create line variable, which is a string
	std::string line;

	// Read each file, line by line
	while (std::getline(file, line))
	{
		// Process each line, where input refers to each line as it is read, respectively
		std::string input = line;

		// Remove leading whitespace
		// While input is not empty
		while (!input.empty())
		{
			// Use regex to search for leading whitespace, and, if it is found
			if (std::regex_search(input, whitespace_re))
			{
				// Set the value of input to the current line, without the leading whitespace.
				input = std::regex_replace(input, whitespace_re, "");
			}

			// Tokenization
			// if (std::regex_search(input, whatever_re))
			// {
			// 	
		}
	}
	file.close();
	return 0;
}
