#ifndef RESPONSEHEADER_HPP
#define RESPONSEHEADER_HPP

#include "httpHeader.hpp"

class ResponseHeader : public httpHeader
{
    std::string AcceptRanges;
    std::string Age;
    std::string Etag;
    std::string Location;
    std::string ProxyAuthenticate;
    std::string RetryAfter;
    std::string Server;
    std::string Vary;
};
#endif