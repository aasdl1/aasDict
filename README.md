# aasDict
a dictionary implemented by trie, support en-zh and zh-en, and auto complete<br>
支持中英互译，采用trie树实现，支持自动补全<br>
<br>
**学校的暑期实习，中英互译词典，搜索时间与词典大小无关，在10微秒级<br>**
## 两种方法食用方法
- 进行学习，使用testTrie.cpp，这是一个demo
- 使用test.cpp，调用promt类进行界面引用

## demo版展示
![demo测试.PNG](https://s2.loli.net/2022/07/22/sMaE48Fb5mpCDlk.png)<br>
首先会提示构建trie树的时间，其次会展示真实导入的Item个数<br>
默认使用的是enTrie树，即en-zh词典，输入为空时退出查询<br>
界面如下<br>
**首先是主界面，让用户选择中文词典或英文词典**
<img src="https://i.imgur.com/R5ZyNVF.png">
**接着导入词典，1对应cKeyWord.csv，2对应ecdict**
<img src="[https://imgur.com/ZGEExC7](https://i.imgur.com/ZGEExC7.png)">
