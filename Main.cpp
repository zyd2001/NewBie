#include "NewBie_Lang.hpp"

using namespace std;
int main(int argc, char **argv)
{
    zyd2001::NewBie::Interpreter inter;
    inter.setFile("test");
    inter.parse();
    inter.run();
}