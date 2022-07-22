////////////////////////////////////////////////////////////////////////////////
// ����trie��ͷ�ļ�
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
	int count;		// �Ըýڵ�������ַ�������
	string value;	// ��������
	map<string, trieNode*> child;	// keyΪ��ǰ���֣�valueΪ��Ӧ����һ�����ֽڵ�
};

class chTrie : Trie<trieNode> {
public:
	chTrie();
	chTrie(int lim, int wordsize);
	~chTrie();
	int			insert(string s, string trans);			// �����ַ���
	
	trieNode*	search(string s);						// ����"�ַ���"(�����壩
	int			del(string s);							// ɾ��
	trieNode*	modify(string s, string trans);			// �޸Ĵʵ�

	psvec		getPreStrings(string s, psvec& ret);	// ��ȡ��sΪǰ׺�������ַ���

	int			clear();								// ���

	int			setLimit(int lim);						// ������ʾ�����Ƹ���
	int			setWordSize(int wordsize);				// ����wordSize��һ������wordsize���ֽڣ�

	// �ʵ䵼�뵼��
	int			importDict(string path);				// ���ʵ䵼��
	int			exportDict(string path);				// ���ʵ䵼����Ĭ��en-zh,reverse = false
	int			exportItemNums;								// ʵ�ʵ���Item����

	void		_exportItem(string s, string trans, ofstream* out);						// ��s��trans��csvд��

public:
	void		dfsLow(trieNode* node, int layer, void(*fun)(string, string));			// ��³��dfs
	string		s;										// ���ѵ�tmp String

	void		dfs(trieNode* root, string pre, ofstream* out);		// ���ŵ�dfs



	// void		dfs(trieNode* node, int layer, void (*fun)(string, string));			// ����

public:
	trieNode*	root;										// root
private:
	trieNode*	_searchPre(string s);					// ����"��"
	int			_addStr(trieNode* root, string pre, psvec& ret);		// ����preΪǰ׺�������ַ�����ӵ�psvec��
private:
	int				limit;			// ��ʾ�ĸ�������
	int				wordSize;		// ÿ�����ʵĴ�С��Ӣ��Ϊ1��������win��Ϊ2��linuxΪ3
};
