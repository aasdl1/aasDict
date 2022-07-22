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


// trie������
template <class T>
class Trie {
public:
	virtual int		insert(string s, string trans) = 0;			// �����ַ���
	virtual T*		search(string s) = 0;						// ����"�ַ���"(�����壩
	virtual int		del(string s) = 0;							// ɾ��
	virtual T*		modify(string s, string trans) = 0;			// �޸Ĵʵ�

	virtual psvec	getPreStrings(string s, psvec& ret) = 0;	// ��ȡ��sΪǰ׺�������ַ���
	virtual	int		clear() = 0;								// ���

	// ���뵼���ʵ�
	int				importDict(string path, bool reverse);		// ���ʵ䵼�룬Ĭ��en-zh,reverse = false
	int				exportDict(string path);					// ���ʵ䵼����Ĭ��en-zh,reverse = false

	// ���ı���csv����
	void			_exportItem(string s, string trans, ofstream* out);			// ��s��trans��csvд��

	// ����
	virtual void	dfs(T* node, string pre, ofstream* out) = 0;				// ����


	virtual T*		_searchPre(string s) = 0;					// ����"��"
	virtual int		_addStr(T* root, string pre, psvec& ret) = 0;		// ����preΪǰ׺�������ַ�����ӵ�psvec��

	// member
	T* root;			// root
};

template<class T>
int Trie<T>::importDict(string path, bool reverse)
{
	// reverse: en-zh reverse
	// �����ʽ��csv eg.(aas,��
	//					 bbs,��
	//					 ...,...)
	// ����ʵ�ʵ��뵥�ʸ���

	int succTotal = 0;

	// ����filestream����
	ifstream in(path);
	if (!in.is_open()) {
		printf("Error:[ %s ] opened error!\n", path.c_str());
		return -1;
	}

	//��ȡһ��for����
	string s, trans;
	char ctmp;
	bool isTrans = false;
	bool isend = false;
	while (!in.eof()) {
		in.get(ctmp);
		if (ctmp == ',' && isTrans == false && isend == false) {
			// ��һ������','
			isTrans = true;
			continue;
		}
		else if ((ctmp == ',' && isTrans == true) || (ctmp == '\n' && isTrans == true)) {
			// ������ĩ �� �ڶ�������','
			

			//// change utf8 to string
			//string gbS = UTF8_To_string(s);
			//string gbTrans = UTF8_To_string(trans);
			
			int insRes = -1;
			// ��reverse=true��Ϊzh-en
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
			// �ڷǸ��н���ʱ�����ַ���
			// �����ַ���
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
			// ������ĩ
			isend = false;
		}

	}

	return succTotal;
}


template<class T>
int Trie<T>::exportDict(string path)
{
	// reverse: en-zh reverse
	// ������ʽ��csv eg.(aas,��
	//					 bbs,��
	//					 ...,...)
	// ����ʵ�ʵ������ʸ���

	int succTotal = 0;

	// ����filestream����
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