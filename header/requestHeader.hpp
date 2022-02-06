#ifndef REQUESTHEADER_HPP
#define REQUESTHEADER_HPP

#include "httpHeader.hpp"

class RequestHeader : public httpHeader
{
    std::string Accept;
    std::string AcceptCharset;
    std::string AcceptEncoding;
    std::string Authorization;
    std::string Except;
    std::string From;
    std::string Host;
    std::string IfMatch;
    std::string IfNoneMatch;
    std::string IfRange;
    std::string IfUnmodifiedSince;
    std::string MaxForward;
    std::string ProxyAuthorization;
    std::string Range;
    std::string Referer;
    std::string TE;
    std::string UserAgent;
};

#endif