#include "./http_request.h"
http_request::http_request(std::map<std::string, std::string> header)
{
    this->header = header;
    this->method = string_trim(header["Method"]);
    this->url = string_trim(header["URL"]);
    this->version = string_trim(header["Version"]);
    this->content_type = string_trim(header["Content-Type"]);
    char *end_pos;
    this->content_length = std::strtoull(header["Content-Length"].c_str(), &end_pos, 10);
}
void http_request::print()
{
    std::cout << method << " " << url << " " << version << std::endl;
    std::cout << "Content-Length: " << content_length << std::endl;
}