#include "header/total.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    MyServer tmp(8080);
    tmp.start();

}
