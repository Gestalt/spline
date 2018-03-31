#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    std::ifstream inn;
    std::ofstream out;

    inn.open("input.txt", std::ifstream::in);
    out.open("output.txt", std::ofstream::out);

    int n = 0;
    inn >> n;

    std::cout << "n=" << n << std::endl;

    //std::vector

    while(!inn.eof()) {
        float x;
        float y ;
        inn >> x >> y;

        std::cout << "x=" << x << " y=" << y << std::endl;
        out << x << " " << y << std::endl;
    }

    inn.close();
    out.close();

    std::cout << std::endl;

	return 0;
}
