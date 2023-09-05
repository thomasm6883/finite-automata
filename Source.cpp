#include <iostream>
#include <string>
#include <stack>
#include <regex>
enum tokens {
	PLUS_TOKEN = 0, MIN_TOKEN = 1, MULT_TOKEN = 2, DIV_TOKEN = 3, LP_TOKEN
	= 4, RP_TOKEN = 5, DOUBLE_TOKEN = 6, EOF_TOKEN = 7,
	T_NT = 0, t_NT = 1, R_NT = 2, r_NT = 3, V_NT = 4
};
int main() {
	// ll(1) look-up table for arithemtic with parenthesis
	std::string ll_table[5][8] = {
		//+ - * / ( ) double $
		{"" ,"" ,"" ,"" ,"Rt" ,"" ,"Rt" ,""}, // T->
		{"+Rt" ,"-Rt" ,"" ,"" ,"" ,"e" ,"" ,"e"}, // t->
		{"" ,"" ,"" ,"" ,"Vr" ,"" ,"Vr" ,""}, // R->
		{"e" ,"e" ,"*Vr" ,"/Vr" ,"" ,"e" ,"" ,"e"}, // r->
		{"" ,"" ,"" ,"" ,"(T)" ,"" ,"d" ,""} // V->
	};
	std::string math_exp = ""; // input string
	std::stack<char> stack_machine; // stack for stack machine
		std::regex double_pattern("(\\d+\\.?\\d*|\\.\\d+)"); // regex for doubles, excludes scientific notation
		// get input from user
		std::cout << "Enter a mathematical expression: ";
	std::cin >> math_exp;
	// eliminate all doubles and replace them with d token
	math_exp = std::regex_replace(math_exp, double_pattern, "d");
	// append end of string character $
	math_exp.append("$");
	// push t and $ onto the stack as the start symbols
	stack_machine.push('$');
	stack_machine.push('T');
	// loop over the input string
	for (long unsigned i = 0; i < math_exp.length(); i++) {
		if (stack_machine.empty()) {
			std::cout << "String is not a valid arithmetic expression.\n";
			std::cout << math_exp.substr(0, i) << " ^ " << math_exp.substr(i);
			return 0;
		}
		std::string push_string = "";
		int next_token;
		int current_nonterminal;
		char string_char = math_exp.at(i);
		char stack_char = stack_machine.top();
		stack_machine.pop();

		switch (string_char) {
			case '+': next_token = PLUS_TOKEN; break;
			case '-': next_token = MIN_TOKEN; break;
			case '*': next_token = MULT_TOKEN; break;
			case '/': next_token = DIV_TOKEN; break;
			case '(': next_token = LP_TOKEN; break;
			case ')': next_token = RP_TOKEN; break;
			case 'd': next_token = DOUBLE_TOKEN; break;
			case '$': next_token = EOF_TOKEN; break;
			default:
				std::cout << "Error in input string. Unidentified input character:" << string_char << "\n";
					return 0;
			}
		// use the ll(1) table to push characters onto the stack until we match the current string character
			while (string_char != stack_char) {
				switch (stack_char) {
				case 'T': current_nonterminal = T_NT; break;
				case 't': current_nonterminal = t_NT; break;
				case 'R': current_nonterminal = R_NT; break;
				case 'r': current_nonterminal = r_NT; break;
				case 'V': current_nonterminal = V_NT; break;
				default:
					std::cout << "String is not a valid arithmetic expression.\n";
					std::cout << math_exp.substr(0, i) << " ^ " <<
						math_exp.substr(i);
					return 0;
				}
				// use ll(1) table to lookup push string
				push_string = ll_table[current_nonterminal][next_token];
				// if the push string is empty, then the input string is not in the language
					if (push_string.length() == 0) {
						std::cout << "String is not a valid arithmetic expression.\n";
						std::cout << math_exp.substr(0, i) << " ^ " << math_exp.substr(i);
						return 0;
					}
				// if the characters to push are not the empty string, then push them in reverse order
					if (push_string.at(0) != 'e') {
						for (int j = push_string.length() - 1; j >= 0; j--) {
							stack_machine.push(push_string.at(j));
						}
					}
				// stack is empty before the string has been fully processed
				if (stack_machine.empty()) {
					std::cout << "String is not a valid arithmetic expression.\n";
					std::cout << math_exp.substr(0, i) << " ^ " << math_exp.substr(i);
					return 0;
				}
				stack_char = stack_machine.top();
				stack_machine.pop();
			}
	}
	if (stack_machine.empty()) {
		std::cout << "The entered string is a valid arithmetic expression.\n";
	}
	else {
		std::cout << "The entered string is not a valid arithmetic expression.\n";
	}
	return 0;
}