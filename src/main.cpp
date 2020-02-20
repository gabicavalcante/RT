#include "RTParser.h"

int main(int argc, char const *argv[])
{
    std::cout << "Creating Parser...\n";
    auto parser = RTParser::instance();
    parser->read_file(argv[1]);
}