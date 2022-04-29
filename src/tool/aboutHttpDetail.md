# aboutHttpDetail

* 1、如果是短连接，没有启用keepalive，则可以通过是否关闭了连接来判断是否传输结束，即在读取时可判断 read() != -1。

* 2、如果时长连接，那么一个socket（tcp）可能发送和接收多次请求，那么如何判断每次的响应已经接收?

* 3、先读请求头，一直到\r\n\r\n说明请求头结束，然后解析http头，如果Content-Length=x存在，则知道http响应的长度为x。直接读取x字节就是响应内容。

* 4、如果Content-Length=x不存在，那么头类型为Transfer-Encoding: chunked说明响应的长度不固定，则在响应头结束后标记第一段流的长度

* 5、然后客户端读取2000个字节，在接下来如果后续还有数据，那么会接着标记下一个段流的长度，

* 7、然后接着读，最后会用\r\n0\r\n\r\n表示结束。

```cpp
// \r\n0\r\n\r\n Transfer-Encoding = chunked
// bool check1 = receive_content[receive_contentsize() - 7] == '\r';
// bool check2 = receive_content[receive_contentsize() - 6] == '\n';
// bool check3 = receive_content[receive_contentsize() - 5] == '0'; chunksize 有多个chunk要接受
// bool check4 = receive_content[receive_contentsize() - 4] == '\r';
// bool check5 = receive_content[receive_contentsize() - 3] == '\n';
// bool check6 = receive_content[receive_contentsize() - 2] == '\r';
// bool check7 = receive_content[receive_contentsize() - 1] == '\n';
// bool check = check1 && check2 && check3 &&check4 && check5 && check6 && check7;
```
