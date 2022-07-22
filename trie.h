#ifndef _TRIE_H_
#define _TRIE_H_

#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

#include <Windows.h>
#include <wchar.h>

using namespace std;

typedef vector<pair<string, string>> psvec;

string UTF8_To_string(const string& str);
string string_To_UTF8(const string& str);


// trie树基类
template <class T>
class Trie {
public:
	virtual int		insert(string s, string trans) = 0;			// 插入字符串
	virtual T*		search(string s) = 0;						// 搜索"字符串"(有意义）
	virtual int		del(string s) = 0;							// 删除
	virtual T*		modify(string s, string trans) = 0;			// 修改词典

	virtual psvec	getPreStrings(string s, psvec& ret) = 0;	// 获取以s为前缀的所有字符串
	virtual	int		clear() = 0;								// 清空

	// 导入导出词典
	int				importDict(string path, bool reverse);		// 将词典导入，默认en-zh,reverse = false
	int				exportDict(string path);					// 将词典导出，默认en-zh,reverse = false

	// 将文本以csv导出
	void			_exportItem(string s, string trans, ofstream* out);			// 将s和trans以csv写出

	// 搜索
	virtual void	dfs(T* node, string pre, ofstream* out) = 0;				// 深搜


	virtual T*		_searchPre(string s) = 0;					// 搜索"字"
	virtual int		_addStr(T* root, string pre, psvec& ret) = 0;		// 将以pre为前缀的所有字符串添加到psvec中

	// member
	T* root;			// root
};

template<class T>
int Trie<T>::importDict(string path, bool reverse)
{
	// reverse: en-zh reverse
	// 导入格式：csv eg.(aas,我
	//					 bbs,你
	//					 ...,...)
	// 返回实际导入单词个数

	int succTotal = 0;

	// 利用filestream读入
	ifstream in(path);
	if (!in.is_open()) {
		printf("Error:[ %s ] opened error!\n", path.c_str());
		return -1;
	}

	//争取一个for跑完
	string s, trans;
	char ctmp;
	bool isTrans = false;
	bool isend = false;
	while (!in.eof()) {
		in.get(ctmp);
		if (ctmp == ',' && isTrans == false && isend == false) {
			// 第一次遇到','
			isTrans = true;
			continue;
		}
		else if ((ctmp == ',' && isTrans == true) || (ctmp == '\n' && isTrans == true)) {
			// 到达行末 或 第二次遇到','
			

			//// change utf8 to string
			//string gbS = UTF8_To_string(s);
			//string gbTrans = UTF8_To_string(trans);
			
			int insRes = -1;
			// 若reverse=true则为zh-en
			if (!reverse) {
				insRes = insert(s, trans);
			}
			else {
				insRes = insert(trans, s);
			}
			if (insRes == 0) {
				succTotal++;
			}
			// cout << "s:" << s << ",trans:" << trans << endl;
			//printf("s:%s,trans:%s\n", s, trans);

			s.clear();
			trans.clear();

			isTrans = false;
			isend = true;
			continue;
		}

		if (!isend) {
			// 在非该行结束时处理字符串
			// 处理字符串
			if (!isTrans) {
				// key
				s += ctmp;
			}
			else {
				trans += ctmp;
			}
			continue;
		}

		if ((ctmp == '\n' && isend == true)) {
			// 到达行末
			isend = false;
		}

	}

	return succTotal;
}


template<class T>
int Trie<T>::exportDict(string path)
{
	// reverse: en-zh reverse
	// 导出格式：csv eg.(aas,我
	//					 bbs,你
	//					 ...,...)
	// 返回实际导出单词个数

	int succTotal = 0;

	// 利用filestream读入
	ofstream* out = new ofstream(path);
	if (!out->is_open()) {
		printf("Error:[ %s ] opened error!\n", path.c_str());
		return -1;
	}

	dfs(root, "", out);
	
	out->close();

	return 0;
}
template<class T>
void Trie<T>::_exportItem(string s, string trans, ofstream* out)
{
	out->write(s.c_str(), s.size());
	out->put(',');
	out->write(trans.c_str(), trans.size());
	out->put('\n');
};



#endif // !_TRIE_H_