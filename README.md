# Search_Engines
Linux下基于C++实现类似百度搜索的搜索引擎


common文件夹： 是数据处理模块和搜索模块中相同代码的部分。

data： 是输入和输出的数据

http_server：是一个简易的http服务器

parser：数据处理模块

searcher：搜索模块。


1.前提
完备的搜索引擎：

    1)带有一个输入框
   
    2)点击搜索之后，得到了搜索界面
    
    3)搜索结果页中的每个结果都是和查询词有一定的关联关系的
    
    4)点击搜索的时候，会跳转到另外一个网站上
    

2实现原理：

2.1文件解剖器的中的详细过程。

  数据处理模块
  
  把boost文档中涉及到的html进行处理：
  
    １、去标签
    
    ２、把文件进行合并
    
          把文件中涉及到的N个HTML的内容合并成一个行文本文件。
          生成的结果是一个大文件，里面包含很多行，每一行对应boost文档中的一个html，
          这么做的目的是为了让后面的索引模块处理来更方便
          
    ３、对文档的结构进行分析，提取出文档的标题，正文，目标url

2.2索引以及搜索模块的实现

   ①正派索引：正排表是以文档的ID为关键字，表中记录文档中每个字的位置信息，查找时扫描表中每个文档中字的信息直到找出所有包含查询关键字的文档。
   
   ②倒排索引：倒排表以字或词为关键字进行索引，表中关键字所对应的记录表项记录了出现这个字或词的所有文档，一个表项就是一个字表段，它记录该文档的ID和字符在该文档中出现的位置情况。

搜索模块：

  根据用户输入的查询词，对索引进行查找，最终找出那些文档和这个词相关
  
    分词：对查询词进行分词
    
    匹配：针对每个分词结果查找倒排索引
    
    排序：按照词的出现频率进行降序排序
    
    构造返回结果：根据触发得到的id列表查正排索引得到搜索结果
    

其中用到了分词库是jieba分词，还有boost库，相关的下载地址在github上就有。
