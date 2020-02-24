#include "RTParser.h"

int main(int argc, char const *argv[])
{
	std::cout << "creating parser to read: ";
	std::cout << argv[1] << "\n";

	auto parser = RTParser::create(argv[1]);
	parser->read_file();
}
