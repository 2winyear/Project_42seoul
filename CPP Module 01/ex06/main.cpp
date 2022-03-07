#include "Karen.hpp"

int main(int argc, char *argv[])
{
    Karen k;

    if (argc != 2)
    {
        std::cout << "usage: ./karenFilter [ Level ]" << std::endl;
        return(1);
    }
    else
        k.complain(argv[1]);
    // k.complain("DEBUG");
    // k.complain("INFO");
    // k.complain("WARNING");
    // k.complain("ERROR");
    return(0);
}