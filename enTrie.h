#include "trie.h"

#include <iostream>
#include <string>
#include <vector>

#define ALPHABET_SIZE 26+26+2+2

typedef vector<pair<string, string>> psvec;

using namespace std;

class enTrieNode {
public:
	enTrieNode* children[ALPHABET_SIZE];  // 0-25 'a'-'z', 26-51Ϊ'A'-'Z', 52Ϊ' ', 53Ϊ'-', 54Ϊ'(', 55Ϊ')
	string value;
	bool isEndOfWord;

	enTrieNode();
	~enTrieNode();
	int			indexOf(char c);			// �����ַ�c��node�е�λ��
	char		valueOf(int index);			// ���ض�Ӧ������char
};

class enTrie :Trie <enTrieNode> {
public:
	enTrie();
	enTrie(int lim);
	~enTrie();
	int			insert(string s, string trans);			// �����ַ���
	enTrieNode* search(string s);						// ����"�ַ���"(�����壩
	int			del(string s);							// ɾ��
	enTrieNode* modify(string s, string trans);			// �޸Ĵʵ�

	psvec		getPreStrings(string s, psvec& ret);	// ��ȡ��sΪǰ׺�������ַ���
	
	int			clear();								// ���

	int			setLimit(int lim);						// ������ʾ�����Ƹ���

	// ���뵼��
	int			importDict(string path);				// ���ʵ䵼��
	int			exportDict(string path);				// ���ʵ䵼����Ĭ��en-zh,reverse = false
	int			exportItemNums;							// ʵ�ʵ���Item����

	void		_exportItem(string s, string trans, ofstream* out);						// ��s��trans��csvд��

public:
	// ����
	void		dfsLow(enTrieNode* node, int layer, void (*fun)(string, string));		// ��³��dfs
	string		s;																		// ���ѵ�tmp String

	void		dfs(enTrieNode* root, string pre, ofstream* out);		// ���ŵ�dfs

public:
	enTrieNode* root;			// root

private:
	enTrieNode* _searchPre(string s);					// ����"��"
	int			_addStr(enTrieNode* root, string pre, psvec& ret);		// ����preΪǰ׺�������ַ�����ӵ�psvec��
private:
	
	int				limit;			// ��ʾ�ĸ�������

};
