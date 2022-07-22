////////////////////////////////////////////////////////////////////////////////
// 英文trie树实现
////////////////////////////////////////////////////////////////////////////////

// enTrie standard Trie
#include "enTrie.h"

enTrieNode::enTrieNode() {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		children[i] = nullptr;
	}
	isEndOfWord = false;
};

enTrieNode::~enTrieNode() {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (children[i]) {
			children[i] = nullptr;
			delete children[i];
		}
	}
}
int enTrieNode::indexOf(char c)
{
	int index = -1;
	if (c == ' ') {
		index = 52;
	}
	else if (c == '-') {
		index = 53;
	}
	else if (c == '(') {
		index = 54;
	}
	else if (c == ')') {
		index = 55;
	}

	else if (c <= 'z' && c >= 'a') {
		index = c - 'a';
	}
	else if (c <= 'Z' && c >= 'A') {
		index = c - 'A' + 26;
	}

	return index;
}
char enTrieNode::valueOf(int index)
{
	if (index == 52) {
		return ' ';
	}
	else if (index == 53) {
		return '-';
	}
	else if (index == 54) {
		return '(';
	}
	else if (index == 55) {
		return ')';
	}
	else if (index <= 25 && index >= 0) {
		return 'a' + index;
	}
	else if (index <= 25+26 && index >= 0+26) {
		return index + 'A' - 26;
	}
	else if (index == -1) {
		return 0;
	}
};


enTrie::enTrie() {
	root = new enTrieNode();
	this->limit = 4;
};
enTrie::enTrie(int lim)
{
	root = new enTrieNode();
	this->limit = lim;
};
enTrie::~enTrie() {
	root = nullptr;
	delete root;
};



int	enTrie::insert(string s, string trans) {
	// 正常插入返回0， else -1
	if (root == nullptr || s == "")
		return -1;
	enTrieNode* cur = root;
	for (int i = 0; i < s.size(); i++) {
		// 要么是传index出来要么是用指针引用，但指针引用还要解引用，懒~
		int index = cur->indexOf(s[i]);
		// 如果index = -1 表明该字符无法读入 则函数返回-1
		if (index != -1) {
			if (cur->children[index] == nullptr) {
				cur->children[index] = new enTrieNode();
			}
			cur = cur->children[index];
		}
		else {
			return -1;
		}
	}
	cur->isEndOfWord = true;
	cur->value = trans;

	return 0;
};

enTrieNode* enTrie::_searchPre(string s)
{
	if (s == "")
		return root;
	if (nullptr == root)
		return nullptr;

	enTrieNode* cur = root;
	int i;
	for (i = 0; i < s.size() && cur != nullptr; i++) {
		cur = cur->children[cur->indexOf(s[i])];
	}
	
	return cur;
}

enTrieNode* enTrie::search(string s)
{
	// 搜索单词
	enTrieNode* preNode = _searchPre(s);
	if (preNode != nullptr) {
		if (preNode->isEndOfWord == false) {
			return nullptr;
		}
		else {
			// 搜索成功
			return preNode;
		}
	}
	return nullptr;
}

int enTrie::del(string s)
{
	// 返回0正常，-1则删除失败
	// 只能将对应标志去掉，但节点不能掉
	enTrieNode* node = search(s);
	if (node != nullptr) {
		node->isEndOfWord = false;
		return 0;
	}
	else {
		return -1;
	}
}

enTrieNode* enTrie::modify(string s, string trans)
{
	// 如果修改成功返回对应顶点指针，否则返回空指针
	enTrieNode* snode = search(s);
	if (snode) {
		snode->value = trans;
		return snode;
	}
	return nullptr;
}

int enTrie::_addStr(enTrieNode* root, string pre, psvec& ret)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != nullptr) {
			_addStr(root->children[i], pre + string(1, root->valueOf(i)), ret);
		}
	}
	if (root->isEndOfWord == true) {
		if (ret.size() < limit) {
			ret.push_back(pair<string, string>(pre, root->value));
		}
	}
	return 0;
}

psvec enTrie::getPreStrings(string s, psvec& ret)
{
	enTrieNode* prenode = _searchPre(s);   // 此处s为前缀
	if (prenode) {
		_addStr(prenode, s, ret);
	}
	return ret;
}

int enTrie::importDict(string path) {
	return Trie::importDict(path, false);
}

int enTrie::exportDict(string path)
{
	// return Trie::exportDict(path);
	// reverse: en-zh reverse
	// 导出格式：csv eg.(aas,我
	//					 bbs,你
	//					 ...,...)
	// 返回实际导出单词个数

	exportItemNums = 0;

	// 利用filestream读入
	ofstream* out = new ofstream(path);
	if (!out->is_open()) {
		printf("Error:[ %s ] opened error!\n", path.c_str());
		return -1;
	}

	dfs(root, "", out);

	out->close();

	return exportItemNums;
}


int enTrie::clear()
{
	vector<enTrieNode*> q;
	q.push_back(root);

	while (!q.empty()) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (root->children[i] != nullptr) {
				q.push_back(root->children[i]);
			}
		}
		enTrieNode* delNode = q.front();
		q.pop_back();

		delete delNode;
	}
	return 0;
}

int enTrie::setLimit(int lim)
{
	this->limit = lim;
	return 0;
}

void enTrie::dfs(enTrieNode* root, string pre, ofstream* out)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != nullptr) {
			dfs(root->children[i], pre + string(1, root->valueOf(i)), out);
		}
	}
	if (root->isEndOfWord == true) {
		_exportItem(pre, root->value, out);
		exportItemNums++;
	}
}

void enTrie::_exportItem(string s, string trans, ofstream* out)
{
	return Trie::_exportItem(s, trans, out);
}

void enTrie::dfsLow(enTrieNode* node, int layer, void (*fun)(string, string))
{
	// 递归版，用string做栈
	if (node == nullptr) {
		return;
	}
	if (node->isEndOfWord == true) {
		fun(s, node->value);
		// cout << s << " : " << node->value << endl;
	}
	// 按dfs遍历
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i] != nullptr) {
			int delLength = s.size() + 1 - layer;
			for (int j = 0; j < delLength; j++) {
				// 不要一边删str一边用size做判断条件！
				if (s.size() > 0) {
					s.pop_back();     // 当字符串长度和深度相等时pop掉最后一个再插入
				}
			}
			s.push_back(node->valueOf(i));
			dfsLow(node->children[i], layer+1, fun);
		}
	}
}

