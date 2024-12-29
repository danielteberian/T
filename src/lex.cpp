/*
	lex.cpp

	A simple lexer.

	Copyright Daniel P. Teberian 2024
*/


//	IMPORTS
#include <iostream>	// I/O stuff
#include <fstream>	// File stuff
#include <string>	// Stringy stuff
#include <cctype>	// CC type (idk)
#include <vector>	// Vector stuff
#include <unordered_map>	// Unordered map stuff


// Token types
enum class TOKEN_TYPE
{
	KEYWORD,
	IDENTIFIER,
	NUMBER,
	OPERATOR,
	PUNCTUATION,
	STRING_LITERAL,
	END_OF_FILE,
	UNKNOWN,
	ERROR,
};


// Token struct
struct TOKEN
{
	TOKEN_TYPE type;
	std::string value;

	// Tokens contain a token type and a string, making up a keypair (I think)

	TOKEN(TOKEN_TYPE t, const std::string &v) : type(t), value(v) {}
};


// C keywords, stored in an unordered map
std::unordered_map<std::string, TOKEN_TYPE> keywords = {
	{"int", TOKEN_TYPE::KEYWORD},
	{"return", TOKEN_TYPE::KEYWORD},
	{"if", TOKEN_TYPE::KEYWORD},
	{"else", TOKEN_TYPE::KEYWORD},
	{"while", TOKEN_TYPE::KEYWORD},
	{"for", TOKEN_TYPE::KEYWORD}
};


// C operators, stored in an unordered map
std::unordered_map<std::string, TOKEN_TYPE> operators = {
	{"+", TOKEN_TYPE::OPERATOR},
	{"-", TOKEN_TYPE::OPERATOR},
	{"*", TOKEN_TYPE::OPERATOR},
	{"/", TOKEN_TYPE::OPERATOR},
	{"=", TOKEN_TYPE::OPERATOR},
	{"==", TOKEN_TYPE::OPERATOR},
	{"<", TOKEN_TYPE::OPERATOR},
	{">", TOKEN_TYPE::OPERATOR}
};

TOKEN_TYPE check_keyword(const std::string &str);


// Function that checks if a string is a keyword
TOKEN_TYPE check_keyword(const std::string &str)
{
	if (keywords.find(str) != keywords.end())
	{
		return keywords[str];
	}

	return TOKEN_TYPE::IDENTIFIER;
}


// Lexer function
std::vector<TOKEN> lex(const std::string &source)
{
	std::vector<TOKEN> tokens;
	size_t i = 0;
	size_t length = source.length();

	while (i < length)
	{
		// Skip whitespace (I hope)
		if (isspace(source[i]))
		{
			++i;
			continue;
		}

		// Number literals
		if (isdigit(source[i]))
		{
			std::string number;

			while (i < length && isdigit(source[i]))
			{
				number += source[i++];
			}

			// Detect invalid tokens, such as input with a leading number
			if (i < length && (isalpha(source[i]) || source[i]== '_'))
			{
				tokens.push_back(TOKEN(TOKEN_TYPE::ERROR, "[ERR] Invalid token: " + number + source[i]));
				exit(1);
			}
			else
			{
				// If valid
				tokens.push_back(TOKEN(TOKEN_TYPE::NUMBER, number));
			}

			continue;
		}

		// Identifier/keyword
		if (isalpha(source[i]) || source[i] == '_')
		{
			std::string identifier;

			while (i < length && (isalnum(source[i]) || source[i] == '_'))
			{
				identifier += source[i++];
			}

			TOKEN_TYPE type = check_keyword(identifier);

			// Return an error if keyword is misspelled
			if (type == TOKEN_TYPE::IDENTIFIER)
			{
				tokens.push_back(TOKEN(TOKEN_TYPE::ERROR, "[ERR] Misspelled keyword: " + identifier));
				exit(1);
			}
			else
			{
				tokens.push_back(TOKEN(type, identifier));
			}

			continue;
		}

		// String literal
		if (source[i] == '"')
		{
			std::string str;

			// Skip opening quotation mark
			++i;

			while (i < length && source[i] != '"')
			{
				str += source[i++];
			}

			// Skip closing quotation mark
			if (i < length && source[i] == '"')
			{
				tokens.push_back(TOKEN(TOKEN_TYPE::STRING_LITERAL, str));
			}
			else
			{
				tokens.push_back(TOKEN(TOKEN_TYPE::UNKNOWN, "Unterminated string literal"));
				exit(1);
			}

			continue;
		}

		// Single character operators
		if (operators.find(std::string(1, source[i])) != operators.end())
		{
			tokens.push_back(TOKEN(TOKEN_TYPE::OPERATOR, std::string(1, source[i++])));
			continue;
		}

		// Punctuation
		if (source[i] == ';' || source[i] == ',' || source[i] == '(' || source[i] == ')')
		{
			tokens.push_back(TOKEN(TOKEN_TYPE::PUNCTUATION, std::string(1, source[i++])));
			continue;
		}

		// Unknown/invalid character
		tokens.push_back(TOKEN(TOKEN_TYPE::UNKNOWN, std::string(1, source[i++])));
		exit(1);
	}

	// EOF
	tokens.push_back(TOKEN(TOKEN_TYPE::END_OF_FILE, ""));
	return tokens;
}


// Main function
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "[ERR] Could not open file." << std::endl;
		return 1;
	}


	// Open file
	std::string filepath = argv[1];
	std::ifstream file(filepath);

	if (!file.is_open())
	{
		std::cerr << "[ERR] Could not open file." << std::endl;
		return 1;
	}

	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::vector<TOKEN> tokens = lex(source);

	return 0;
}
