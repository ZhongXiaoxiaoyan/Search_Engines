#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "cppjieba/Jieba.hpp"

//构建索引模块和搜索模块

namespace searcher {

struct DocInfo {
    uint64_t doc_id;
    std::string title;
    std::string content;
    std::string url;
};

//Weight 表示的含义是某个词在某个文档中出现过，
//以及该词的权重是多少
struct Weight {
    uint64_t doc_id;  // size_t
    int weight;         //权重，为了后面进行排序准备（采用词频计算权重）

    std::string key;
};

//类型重命名，创建一个“倒排拉链”类型
typedef std::vector<Weight> InvertedList;

//通过这个类来描述索引模块
class Index {
private:
    //知道id获取到对应的文档内容
    //使用vector的下表来表示文档id
    std::vector<DocInfo> forward_index_;

    //知道某个词，获取到对应的id列表
    std::unordered_map<std::string, InvertedList> inverted_index_;

    cppjieba::Jieba jieba_;
public:
    //读取 raw_input　文件，在内存中构建索引
    //input_path就是上面那个文件的路径
    bool Build(const std::string& input_path);
    
    //查正排，给定 id找到文档内容
    const DocInfo* GetDocInfo(uint64_t doc_id) const;

    //查倒排，给定词，找到这个词在哪些文档中出现过
    const InvertedList* GetInvertedList(const std::string& key) const;

    void CutWord(const std::string& input, 
                 std::vector<std::string>* output);
    Index();
private:
    const DocInfo* BuildForward(const std::string& line);
    void BuildInverted(const DocInfo* doc_info);
};

//搜索模块
    class Searcher {
        private:
            Index* index_;
        public:
            Searcher():index_(new Index())
            {}
            ~Searcher()
            {
                delete index_;
            }
            //加载索引
            bool Init(const std::string& input_path);
            //通过特定的格式再　result　字符串中表示搜索结果
            bool Search(const std::string& query, std::string* result);

        private:
            std::string GetDesc(const std::string& content,
                                const std::string& key);
    };

} //end searcher
