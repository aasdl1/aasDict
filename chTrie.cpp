////////////////////////////////////////////////////////////////////////////////
// 中文trie树实现
////////////////////////////////////////////////////////////////////////////////

#include "chTrie.h"


chTrie::chTrie() {
    // 默认lim=4，wordsize=2 即zh-en - windows词典
    root = new trieNode();
    this->limit = 4;
    this->wordSize = 2;
}

chTrie::chTrie(int lim, int wordsize)
{
    root = new trieNode();
    this->limit = lim;
    this->wordSize = wordsize;
}

chTrie::~chTrie()
{
    root = nullptr;
    delete root;
}

int chTrie::insert(string s, string trans)
{
    if (root == nullptr || s == "")
        return -1;
    trieNode* cur = root;

    for (int i = 0; i < s.size(); i += wordSize) {
        string sub = s.substr(i, wordSize);
        map<string, trieNode*>::iterator it = cur->child.find(sub);
        
        if (it == cur->child.end()) {
            // 没有找到则插入
            trieNode* tmp = new trieNode();
            cur->child.insert(pair<string, trieNode*>(sub, tmp));
            cur = tmp;
        }
        else {
            // 如果找到了则指向下一个节点的指针
            cur = it->second;
        }
    }
    cur->count++;
    cur->value = trans;

    return 0;
}

void chTrie::dfs(trieNode* root, string pre, ofstream* out) {
    // 用时，dfsNeat(t.root, "", fun);
    for (map<string, trieNode*>::iterator it = root->child.begin(); it != root->child.end(); it++) {
        dfs(it->second, pre + it->first, out);
    }
    if (root->count != 0) {
        _exportItem(pre, root->value, out);
        exportItemNums++;
    }
}

void chTrie::_exportItem(string s, string trans, ofstream* out)
{
    return Trie::_exportItem(s, trans, out);
    /*out->write(s.c_str(), s.size());
    out->put(',');
    out->write(trans.c_str(), trans.size());
    out->put('\n');*/
}

void chTrie::dfsLow(trieNode* node, int layer, void (*fun)(string, string))
{
    //深搜实现
    if (nullptr == node) {
        return;
    }
    if (node->count != 0) {
        fun(s, node->value);
    }
    for (map<string, trieNode*>::iterator it = node->child.begin(); it != node->child.end(); it++) {
        int delChars = (s.size() / wordSize + 1 - layer);  //要删除的汉字个数
        for (int j = 0; j < delChars; j++) {
            if (s.size() / wordSize > 0) {
                // 删除单个汉字
                for (int k = 0; k < wordSize; k++) {
                    s.pop_back();
                }
            }
        }
        s += it->first;
        dfsLow(it->second, layer+1, fun);
    }
}

trieNode* chTrie::_searchPre(string s)
{
    if (s == "")    
        return root;
    if (nullptr == root)
        return nullptr;
    
    trieNode* cur = root;
    int i;
    for (i = 0; i < s.size(); i += wordSize) {
        string sub = s.substr(i, wordSize);
        map<string, trieNode*>::iterator it = cur->child.find(sub);

        if (it == cur->child.end()) {
            return nullptr;
        }
        else {
            cur = it->second;
        }
    }

    if (i == s.size()) {
        // 成功找到
        return cur;
    }
    else {
        return nullptr;
    }
}

trieNode* chTrie::search(string s)
{
    trieNode* preNode = _searchPre(s);
    if (preNode != nullptr) {
        if (preNode->count == 0) {
            return nullptr;
        }
        else {
            // 搜索成功
            return preNode;
        }
    }
    return nullptr;
}

int chTrie::del(string s)
{
    // 将对应节点count--
    trieNode* node = search(s);
    if (node != nullptr) {
        node->count--;
    }
    return 0;
}

trieNode* chTrie::modify(string s, string trans)
{
    // 如果修改成功返回对应顶点指针，否则返回空指针
    trieNode* snode = search(s);
    if (snode) {
        snode->value = trans;
        return snode;
    }
    return nullptr;
}

int chTrie::_addStr(trieNode* root, string pre, psvec& ret)
{

    for (map<string, trieNode*>::iterator it = root->child.begin(); it != root->child.end(); it++) {
        _addStr(it->second, pre + it->first, ret);
    }
    if (root->count != 0) {
        if (ret.size() < limit) {
            ret.push_back(pair<string, string>(pre, root->value));
        }
    }
    return 0;
}

psvec chTrie::getPreStrings(string s, psvec& ret)
{
    trieNode* prenode = _searchPre(s);   // 此处s为前缀
    if (prenode){
        _addStr(prenode, s, ret);
    }
    return ret;
}


int chTrie::importDict(string path) {
    return Trie::importDict(path, true);
    // return Trie::importDict(path, false);
}

int chTrie::exportDict(string path)
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


int chTrie::clear()
{
    vector<trieNode*> q;
    q.push_back(root);

    while (!q.empty()) {
        for (map<string, trieNode*>::iterator it = root->child.begin(); it != root->child.end(); it++) {
            q.push_back(it->second);
        }

        trieNode* delNode = q.front();
        q.pop_back();

        delete delNode;
    }
    return 0;
}

int chTrie::setLimit(int lim)
{
    this->limit = lim;
    return 0;
}

int chTrie::setWordSize(int wordsize)
{
    this->wordSize = wordsize;
    return 0;
}

