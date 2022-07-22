#include "trie.h"

#include <iostream>
#include <string>
#include <vector>

#define ALPHABET_SIZE 26+26+2+2

typedef vector<pair<string, string>> psvec;

using namespace std;

class enTrieNode {
public:
	enTrieNode* children[ALPHABET_SIZE];  // 0-25 'a'-'z', 26-51为'A'-'Z', 52为' ', 53为'-', 54为'(', 55为')
	string value;
	bool isEndOfWord;

	enTrieNode();
	~enTrieNode();
	int			indexOf(char c);			// 索引字符c在node中的位置
	char		valueOf(int index);			// 返回对应索引的char
};

class enTrie :Trie <enTrieNode> {
public:
	enTrie();
	enTrie(int lim);
	~enTrie();
	int			insert(string s, string trans);			// 插入字符串
	enTrieNode* search(string s);						// 搜索"字符串"(有意义）
	int			del(string s);							// 删除
	enTrieNode* modify(string s, string trans);			// 修改词典

	psvec		getPreStrings(string s, psvec& ret);	// 获取以s为前缀的所有字符串
	
	int			clear();								// 清空

	int			setLimit(int lim);						// 设置提示的限制个数

	// 导入导出
	int			importDict(string path);				// 将词典导入
	int			exportDict(string path);				// 将词典导出，默认en-zh,reverse = false
	int			exportItemNums;							// 实际导出Item个数

	void		_exportItem(string s, string trans, ofstream* out);						// 将s和trans以csv写出

public:
	// 遍历
	void		dfsLow(enTrieNode* node, int layer, void (*fun)(string, string));		// 粗鲁的dfs
	string		s;																		// 深搜的tmp String

	void		dfs(enTrieNode* root, string pre, ofstream* out);		// 优雅的dfs

public:
	enTrieNode* root;			// root

private:
	enTrieNode* _searchPre(string s);					// 搜索"字"
	int			_addStr(enTrieNode* root, string pre, psvec& ret);		// 将以pre为前缀的所有字符串添加到psvec中
private:
	
	int				limit;			// 提示的个数限制

};
