#include "./cpp-httplib/httplib.h"
#include <iostream>
#include "../searcher/searcher.hpp"


int main()
{
    //1.创建searcher对象，并初始化
    searcher::Searcher s;
    bool ret = s.Init("../data/tmp/raw_input");
    if (!ret)
    {
        std::cout << "Searcher Init failed" << std::endl;
        return 1;
    }
    //2.创建http服务器
    using namespace httplib;
    Server server;
    server.Get("/search", [&s](const Request& req, Response& res){
                std::string query = req.get_param_value("query");
                std::string result;
                s.Search(query, &result);
                res.set_content(result, "text/plain");
                // std::cout << req.path << std::endl;
                // res.set_content("<html>hello</html>", "text/html");
               });
    server.listen("0.0.0.0", 8080);
    return 0;
}
