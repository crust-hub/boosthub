#include <string>
#include <vector>
#include <iostream>
#include <map>
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
     * @brief 检测http请求报文头部是否接受完毕,当缓存超过一定长度后后清理缓存
     *
     * @param buffer socket接收内容缓存
     * @param max_length 最大缓存长度,当超过max_length时会将buffer清理
     * @return std::size_t 报文头部大小 为零0则没有找到合法头部
     */
    std::size_t header_check(std::string &buffer, std::size_t max_length);

    /**
     * @brief HTTP 头部分析
     *
     * @param buffer 接收缓冲
     */
    std::map<std::string, std::string> header_analysis(std::string &buffer, std::size_t header_end_index);

    /**
     * @brief 将字符串根据指定字符进行split
     *
     * @param str 要处理的字符串
     * @param ch 根据ch进行split
     * @param count 只处理前count个ch，当count为0时处理所有ch
     * @return std::vector<std::string>
     */
    static std::vector<std::string> string_split(std::string &str, const char ch, const std::size_t count)
    {
        std::vector<std::string> result;
        std::size_t last_index = 0;
        std::size_t index = 0;
        std::size_t process_count = 0;
        //探测字符串
        for (auto now_ch : str)
        {
            if (count != 0 && process_count == count) //处理了count后，则直接将后面的处理掉
            {
                result.push_back(str.substr(last_index, str.size() - last_index));
                return result;
            }
            if (now_ch == ch || index == str.size() - 1)
            {
                result.push_back(str.substr(last_index, index - last_index));
                last_index = index + 1;
                process_count++;
            }
            ++index;
        }
        return result;
    }
};
