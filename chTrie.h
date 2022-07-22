////////////////////////////////////////////////////////////////////////////////
// 中文trie树头文件
////////////////////////////////////////////////////////////////////////////////


#include "trie.h"

#include <map>
#include <iostream>
#include <vector>
#include <fstream>

#include <windows.h> 

// #define CH_SIZE 2

using namespace std;

typedef vector<pair<string, string>> psvec;

class trieNode {
public:
	trieNode() { count = 0; };
	int count;		// 以该节点结束的字符串个数
	string value;	// 翻译内容
	map<string, trieNode*> child;	// key为当前汉字，value为对应的下一个汉字节点
};

class chTrie : Trie<trieNode> {
public:
	chTrie();
	chTrie(int lim, int wordsize);
	~chTrie();
	int			insert(string s, string trans);			// 插入字符串
	
	trieNode*	search(string s);						// 搜索"字符串"(有意义）
	int			del(string s);							// 删除
	trieNode*	modify(string s, string trans);			// 修改词典

	psvec		getPreStrings(string s, psvec& ret);	// 获取以s为前缀的所有字符串

	int			clear();								// 清空

	int			setLimit(int lim);						// 设置提示的限制个数
	int			setWordSize(int wordsize);				// 设置wordSize（一个汉字wordsize个字节）

	// 词典导入导出
	int			importDict(string path);				// 将词典导入
	int			exportDict(string path);				// 将词典导出，默认en-zh,reverse = false
	int			exportItemNums;								// 实际导出Item个数

	void		_exportItem(string s, string trans, ofstream* out);						// 将s和trans以csv写出

public:
	void		dfsLow(trieNode* node, int layer, void(*fun)(string, string));			// 粗鲁的dfs
	string		s;										// 深搜的tmp String

	void		dfs(trieNode* root, string pre, ofstream* out);		// 优雅的dfs



	// void		dfs(trieNode* node, int layer, void (*fun)(string, string));			// 深搜

public:
	trieNode*	root;										// root
private:
	trieNode*	_searchPre(string s);					// 搜索"字"
	int			_addStr(trieNode* root, string pre, psvec& ret);		// 将以pre为前缀的所有字符串添加到psvec中
private:
	int				limit;			// 提示的个数限制
	int				wordSize;		// 每个单词的大小，英文为1，中文在win下为2，linux为3
};
