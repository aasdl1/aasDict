#include "trie.h"

string UTF8_To_string(const string& str)
{
	// change utf8 to string
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
};


string string_To_UTF8(const string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

bool is_str_utf8(const char* str)
{
    unsigned int nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�
    unsigned char chr = *str;
    bool bAllAscii = true;
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        //�ж��Ƿ�ASCII����,�������,˵���п�����UTF8,ASCII��7λ����,���λ���Ϊ0,0xxxxxxx
        if (nBytes == 0 && (chr & 0x80) != 0) {
            bAllAscii = false;
        }
        if (nBytes == 0) {
            //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���
            if (chr >= 0x80) {
                if (chr >= 0xFC && chr <= 0xFD) {
                    nBytes = 6;
                }
                else if (chr >= 0xF8) {
                    nBytes = 5;
                }
                else if (chr >= 0xF0) {
                    nBytes = 4;
                }
                else if (chr >= 0xE0) {
                    nBytes = 3;
                }
                else if (chr >= 0xC0) {
                    nBytes = 2;
                }
                else {
                    return false;
                }
                nBytes--;
            }
        }
        else {
            //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx
            if ((chr & 0xC0) != 0x80) {
                return false;
            }
            //����Ϊ��Ϊֹ
            nBytes--;
        }
    }
    //Υ��UTF8�������
    if (nBytes != 0) {
        return false;
    }
    if (bAllAscii) { //���ȫ������ASCII, Ҳ��UTF8
        return true;
    }
    return true;
}

bool is_str_gbk(const char* str)
{
    unsigned int nBytes = 0;//GBK����1-2���ֽڱ���,�������� ,Ӣ��һ��
    unsigned char chr = *str;
    bool bAllAscii = true; //���ȫ������ASCII,
    for (unsigned int i = 0; str[i] != '\0'; ++i) {
        chr = *(str + i);
        if ((chr & 0x80) != 0 && nBytes == 0) {// �ж��Ƿ�ASCII����,�������,˵���п�����GBK
            bAllAscii = false;
        }
        if (nBytes == 0) {
            if (chr >= 0x80) {
                if (chr >= 0x81 && chr <= 0xFE) {
                    nBytes = +2;
                }
                else {
                    return false;
                }
                nBytes--;
            }
        }
        else {
            if (chr < 0x40 || chr>0xFE) {
                return false;
            }
            nBytes--;
        }//else end
    }
    if (nBytes != 0) {   //Υ������
        return false;
    }
    if (bAllAscii) { //���ȫ������ASCII, Ҳ��GBK
        return true;
    }
    return true;
}
//