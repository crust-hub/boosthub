#include "./http_request.h"
http_request::http_request(std::map<std::string, std::string> header)
{
    this->header = header;
    this->method = header["Method"];
    this->url = header["URL"];
    this->version = header["Version"];
    char *end_pos;
    this->content_length = std::strtoull(header["Content-Length"].c_str(), &end_pos, 10);
}
void http_request::print()
{
    std::cout << method << " " << url << " " << version << std::endl;
    std::cout << "Content-Length: " << content_length << std::endl;
}