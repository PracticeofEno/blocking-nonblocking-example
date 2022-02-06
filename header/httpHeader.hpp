#ifndef HTTPHEADER_HPP
#define HTTPHEADER_HPP

#include "../header/total.hpp"
class httpHeader
{
public:
    std::string CacheControl;
    std::string Connection;
    std::string Date;
    std::string Pragma;
    std::string Trailer;
    std::string TransferEnconding;
    std::string Upgrade;
    std::string Via;
    std::string Warning;

    httpHeader();
    ~httpHeader();

private:

};

#endif