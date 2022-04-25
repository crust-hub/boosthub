#include <string>
/**
 * @brief boosthub http protocol
 *
 */
class boosthub_http
{
public:
    boosthub_http();
    /**
     *
     * @brief 检测http请求报文头部是否接受完毕
     *
     * @param buffer socket接收内容缓存
     * @return std::size_t 报文头部大小
     */
    std::size_t header_check(std::string &buffer);
};
