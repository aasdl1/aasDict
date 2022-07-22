////////////////////////////////////////////////////////////////////////////////
// aasDict���������
////////////////////////////////////////////////////////////////////////////////

#include "enTrie.h"
#include "chTrie.h"
#include "codeFormat.h"
//#include <string>

#include <windows.h> 

#define DEBUG

#ifdef _WIN32
#define WORD_SIZE 2     //GBK
#else
#define WORD_SIZE 3     //UTF-8
#endif

// ��ʾ��������
#define LIMIT 4

class promt {
public:
    // promt related
    int         width = 90;
    char        space = ' ';
    string      userInput;

    int         langu;
    string      dictFileName;

    // functions
    enTrie      ent;
    chTrie      cht;
    vector<pair<string, string>> ret;

    // some flag
    bool    modifiedFlag    = false;        // �ʵ��Ƿ��޸ı�־

    // Ŀǰ����������ܲ�̫�ȶ� - 2022-7-21
    int     deleteItemNum   = 0;            // ɾ������
    int     modifiedItemNum = 0;            // �޸ĸ���
    int     addItemNum      = 0;            // ��ӵĸ���

    void showNchar(char ch, int num) {
        for (int count = 1; count <= num; count++)
            putchar(ch);
    }

    void printPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "C���Թؼ���/��ͨ�ʵ� �����";
        const char* p2 = "1.EN-ZH";
        const char* p3 = "2.ZH-EN";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar(space, (width - strlen(p3)) / 2);
        printf("%s\n", p3);

        showNchar('*', width);
        putchar('\n');
    }

    void _printImportDictPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "�뵼��ʵ�";
        const char* p2 = "1.C���Թؼ��֣�32��";
        const char* p3 = "2.ecdict-0.2k";
        const char* p4 = "3.ecdict-2k";
        const char* p5 = "4.ecdict-20k";
        const char* p6 = "5.ecdict-200k";
        const char* p7 = "6.ecdict-770k";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar(space, (width - strlen(p3)) / 2);
        printf("%s\n", p3);

        showNchar(space, (width - strlen(p4)) / 2);
        printf("%s\n", p4);

        showNchar(space, (width - strlen(p5)) / 2);
        printf("%s\n", p5);

        showNchar(space, (width - strlen(p6)) / 2);
        printf("%s\n", p6);

        showNchar(space, (width - strlen(p7)) / 2);
        printf("%s\n", p7);

        showNchar('*', width);
        putchar('\n');
    }

    void printImportDictPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "�뵼��ʵ�";
        const char* p2 = "1.C���Թؼ��֣�32��";
        const char* p3 = "2.ecdict";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar(space, (width - strlen(p3)) / 2);
        printf("%s\n", p3);

        showNchar('*', width);
        putchar('\n');
    }

    void printFunctionPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "ѡ����(select function)";
        const char* p2 = "1.��ѯ(search)";
        const char* p3 = "2.����(add)";
        const char* p4 = "3.�޸�(modify)";
        const char* p5 = "4.ɾ��(delete)";


        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar(space, (width - strlen(p3)) / 2);
        printf("%s\n", p3);

        showNchar(space, (width - strlen(p4)) / 2);
        printf("%s\n", p4);

        showNchar(space, (width - strlen(p5)) / 2);
        printf("%s\n", p5);

        showNchar('*', width);
        putchar('\n');
    }

    void printFuncSearchAddPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "��ѯ/��ӣ�Search/Add��";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar('*', width);
        putchar('\n');
    }

    void printFuncAddPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "���ӣ�Add��";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar('*', width);
        putchar('\n');
    }

    void printFuncModifyPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "�޸ģ�Modify��";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar('*', width);
        putchar('\n');
    }

    void printFuncDeletePromt(void) {
        const char* header = "aasDict";
        const char* p1 = "ɾ����Delete��";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar('*', width);
        putchar('\n');
    }

    void printFunctionAndExportPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "ѡ����(select function)";
        const char* p2 = "1.��ѯ(search)";
        const char* p3 = "2.����(add)";
        const char* p4 = "3.�޸�(modify)";
        const char* p5 = "4.ɾ��(delete)";
        const char* p6 = "5.����(export)";


        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar(space, (width - strlen(p3)) / 2);
        printf("%s\n", p3);

        showNchar(space, (width - strlen(p4)) / 2);
        printf("%s\n", p4);

        showNchar(space, (width - strlen(p5)) / 2);
        printf("%s\n", p5);

        showNchar(space, (width - strlen(p5)) / 2);
        printf("%s\n", p6);

        showNchar('*', width);
        putchar('\n');
    }


    void printExportDictPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "�����ʵ䣨export��";
        const char* p2 = "�ʵ��ѱ��޸�(modified)";
        const char* p3 = "�ʵ�δ���޸�(unmodified)";
        string tmp1, tmp2, tmp3;
        tmp1 = (string("���(add)���ʸ�����") + to_string(addItemNum));
        tmp2 = (string("�޸�(modified)���ʸ�����") + to_string(modifiedItemNum));
        tmp3 = (string("ɾ��(delete)���ʸ�����") + to_string(deleteItemNum));
        const char* p4 = tmp1.c_str();
        const char* p5 = tmp2.c_str();
        const char* p6 = tmp3.c_str();

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        if (modifiedFlag == true) {
            showNchar(space, (width - strlen(p2)) / 2);
            printf("%s\n", p2);

#ifdef DEBUG
            // �������� ��debugʱ��
            showNchar(space, (width - strlen(p2)) / 2);
            printf("%s\n", p4);

            showNchar(space, (width - strlen(p2)) / 2);
            printf("%s\n", p5);

            showNchar(space, (width - strlen(p2)) / 2);
            printf("%s\n", p6);
#endif // DEBUG
        }
        else {
            showNchar(space, (width - strlen(p3)) / 2);
            printf("%s\n", p3);
        }

        showNchar('*', width);
        putchar('\n');
    }

    void printEndPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "��ӭʹ�� :)";
        const char* p2 = "Good Bye!";

        showNchar('*', width);
        putchar('\n');

        showNchar(space, (width - strlen(header)) / 2);
        printf("%s\n", header);

        showNchar(space, (width - strlen(p1)) / 2);
        printf("%s\n", p1);

        showNchar(space, (width - strlen(p2)) / 2);
        printf("%s\n", p2);

        showNchar('*', width);
        putchar('\n');
    }

    void showUserArea() {
        const char* userPromt = "  User Area  ";
        printf("\n");
        showNchar('*', (width - strlen(userPromt)) / 2);
        printf("%s", userPromt);
        showNchar('*', (width - strlen(userPromt)) / 2);
        printf("\n");
    }

    int getLanguInput() {
        // ��ȡ��/Ӣ�Ĵʵ䣬1Ϊen-zh��Ĭ�ϣ���2Ϊzh-en�����෵��-1
        _getUserInput("please input the dictionary Type��");
        if (userInput.compare("1") == 0 || userInput.compare("") == 0) {
            return 1;
        }
        else if (userInput.compare("2") == 0) {
            return 2;
        }
        else {
            return -1;
            printf("%s\n", "Error:Illegal Input!");
        }
    }

    int getDictInput() {
        // ��ȡ����ʵ�����ƣ�1Ϊc���Դʵ䣨Ĭ�ϣ���2Ϊecdict�����෵��-1
        _getUserInput("please input the dictionary number��");
        if (userInput.compare("1") == 0 || userInput.compare("") == 0) {
            return 1;
        }
        else if (userInput.compare("2") == 0) {
            return 2;
        }
        else {
            return -1;
            printf("%s\n", "Error:Illegal Input!");
        }
    }

    int getFunctionInput() {
        // ��ȡ����ʵ�����ƣ�1Ϊ��ѯ��Ĭ�ϣ���2Ϊ���ӣ�3Ϊ�޸ģ�4Ϊɾ��
        _getUserInput("please input the functions��");
        if (userInput.compare("1") == 0 || userInput.compare("") == 0) {
            return 1;
        }
        else if (userInput.compare("2") == 0) {
            return 2;
        }
        else if (userInput.compare("3") == 0) {
            return 3;
        }
        else if (userInput.compare("4") == 0) {
            return 4;
        }
        else {
            return -1;
            printf("%s\n", "Error:Illegal Input!");
        }
    }

    string getSearchWord() {
        return _getUserInput("please input the word");
    }

    int _endExportDict() {
        if (modifiedFlag == false) {
            return 0;
        }
        int totalItems = 0;
        string exportFlag = _getUserInput("export the dict?");
        if (exportFlag.compare("y") == 0 || exportFlag.compare("yes") == 0) {
            string path = _getUserInput("the path(relative) is?");
            if (path.size() > 0) {
                // ����
                if (langu == 1) {
                    totalItems = ent.exportDict(path);
                }
                else if (langu == 2) {
                    totalItems = cht.exportDict(path);
                }
            }
        }
        return totalItems;
    }

    int addWordToDict(string word) {
        // ��ӵ��ʵ�Dict�У����û�������
        string addFlag = _getUserInput("add to the dictionary?");
        if (addFlag.compare("y") == 0 || addFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?");
            if (wordTrans.size() > 0) {
                // ����
                if (langu == 1) {
                    ent.insert(word, wordTrans);
                    return 0;
                }
                else if (langu == 2) {
                    cht.insert(word, wordTrans);
                    return 1;
                }
            }
        }
        return -1;
    }

    int modifyWordToENDict(enTrieNode* node) {
        // �޸ĵ��ʵ�enDict�У����û�������
        string modifyedFlag = _getUserInput("modify?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?:");
            if (wordTrans.size() > 0) {
                // ����
                node->value = wordTrans;
                return 0;
            }
        }
        return -1;
    }

    int modifyWordToCHDict(trieNode* node) {
        // �޸ĵ��ʵ�chDict�У����û�������
        string modifyedFlag = _getUserInput("modify?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?:");
            if (wordTrans.size() > 0) {
                // ����
                node->value = wordTrans;
                return 0;
            }
        }
        return -1;
    }

    int deleteWordToENDict(string word) {
        // ɾ�����ʵ�enDict�У����û�������
        string modifyedFlag = _getUserInput("delete?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            return ent.del(word);
        }
        return -1;
    }

    int deleteWordToCHDict(string word) {
        // ɾ�����ʵ�chDict�У����û�������
        string modifyedFlag = _getUserInput("delete?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            return cht.del(word);
        }
        return -1;
    }

    void dictSelectLanguage() {
        system("cls");
        printPromt();
        // ѡ��ʵ�����
        while (true) {
            langu = getLanguInput();
            if (langu == 1) {
                break;
            }
            else if (langu == 2) {
                break;
            }
            else if (langu == -1) {
                printf("%s\n", "Error:Illegal Input!");
                continue;
            }
        }
        // ��ת������ʵ����
        dictImportDict();
    }

    void dictImportDict() {
        // ����ʵ����
        system("cls");
        printImportDictPromt();
        int totalItems = 0;
        while (true) {
            int dictName = getDictInput();
            if (dictName == 1) {
                dictFileName = string("cKeyWord.csv");
                break;
            }
            else if (dictName == 2) {
                dictFileName = string("ecdict4-20000.csv");
                break;
            }
            else if (dictName == 0) {
                ;
            }
            else if (dictName == -1) {
                printf("%s\n", "Error:Illegal Input!");
                continue;
            }
        }


        // ***����ʵ�***
        if (langu == 1) {
            // en
            ent.setLimit(LIMIT);
            totalItems = ent.importDict(dictFileName);
            cout << "---������" << totalItems << "��Items---" << endl;
            _getUserInput("press any key to next...");
        }
        else if (langu == 2) {
            // zh
            cht.setLimit(LIMIT);
            cht.setWordSize(WORD_SIZE);
            totalItems = cht.importDict(dictFileName);
            cout << "---������" << totalItems << "��Items---" << endl;
            _getUserInput("press any key to next...");
        }

        // ***��ת������ѡ�����***
        dictSelectFunction();
    }

    void dictSelectFunction() {
        // ����ѡ�����
        int func;
        system("cls");
        printFunctionPromt();
        while (true) {
            func = getFunctionInput();
            if (func == 1) {
                // ��ѯ
                break;
            }
            else if (func == 2) {
                // ����
                break;
            }
            else if (func == 3) {
                // �޸�
                break;
            }
            else if (func == 4) {
                // ɾ��
                break;
            }
            else if (func == 0) {
                break;
            }
            else if (func == -1) {
                printf("%s\n", "Error:Illegal Input!");
                continue;
            }
        }

        if (func == 1) {
            // ��ѯ
            dictFuncSearch();
        }
        else if (func == 2) {
            // ����
            dictFuncAdd();
        }
        else if (func == 3) {
            // �޸�
            dictFuncModify();
        }
        else if (func == 4) {
            // ɾ��
            dictFuncDelete();
        }
    }

    void _dictFuncCombined(int type){
        // ����ɺ���
        // type =1 ������type=2 ��ӣ� type=3 �޸ģ� type = 4 ɾ��
        system("cls");

        // ��ӡpromt
        if (type == 1 || type == 2) {
            printFuncSearchAddPromt();
        }
        else if (type == 3) {
            printFuncModifyPromt();
        }
        else if (type == 4) {
            printFuncDeletePromt();
        }

        LARGE_INTEGER nFreq;
        LARGE_INTEGER nBeginTime;
        LARGE_INTEGER nEndTime;
        double time;
        // ���ʲ�ѯ
        while (true) {
            string word = getSearchWord(); //��userInput��
            if (word.compare("") == 0) {
                // ����Ϊ�����˳�
                break;
            }
            if (langu == 1) {

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime);

                auto res = ent.search(word);

                QueryPerformanceCounter(&nEndTime);

                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
                printf("search time:%3.4f ms\n", time * 1000);

                if (res == NULL) {
                    cout << "search failed\n" << endl;

                    cout << "matched items:" << endl;

                    ret.clear();

                    ret = ent.getPreStrings(word, ret);
                    for (psvec::iterator it = ret.begin(); it != ret.end(); it++) {
                        cout << it->first << endl;
                    }
                    cout << endl;

                    if (type == 2) {
                        // ������ӵ�Ŀ¼��
                        int addSuccess = addWordToDict(word);
                        if (addSuccess != -1) {
                            modifiedFlag = true;
                            addItemNum++;
                            printf("add successfully!\n");
                        }
                        else {
                            printf("add Unsuccessfully!\n");
                        }
                    }
                }
                else {
                    cout << word << " : " << res->value << endl;

                    // �޸�
                    if (type == 3) {
                        int modifiedRes= modifyWordToENDict(res);
                        if (modifiedRes != -1) {
                            modifiedFlag = true;
                            modifiedItemNum++;
                            cout << "modified Successfully!" << endl;
                        }
                        else {
                            cout << "modified Unsuccessfully!" << endl;
                        }
                    }
                    else if (type == 4) {
                        int deleteRes = deleteWordToENDict(word);
                        if (deleteRes != -1) {
                            modifiedFlag = true;
                            deleteItemNum++;
                            cout << "delete Successfully!" << endl;
                        }
                        else {
                            cout << "delete Unsuccessfully!" << endl;
                        }
                    }

                }
            }
            else if (langu == 2) {

                QueryPerformanceFrequency(&nFreq);
                QueryPerformanceCounter(&nBeginTime);

                auto res = cht.search(word);

                QueryPerformanceCounter(&nEndTime);

                time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
                printf("search time:%3.4f ms\n", time * 1000);

                if (res == NULL) {
                    cout << "search failed\n" << endl;
                    cout << "matched items:" << endl;

                    ret.clear();

                    ret = cht.getPreStrings(word, ret);
                    for (psvec::iterator it = ret.begin(); it != ret.end(); it++) {
                        cout << it->first << endl;
                    }
                    cout << endl;

                    if (type == 2) {
                        // ������ӵ�Ŀ¼��
                        int addSuccess = addWordToDict(word);
                        if (addSuccess != -1) {
                            modifiedFlag = true;
                            addItemNum++;
                            printf("add successfully!\n");
                        }
                        else {
                            printf("add Unsuccessfully!\n");
                        }
                    }
                }
                else {
                    cout << word << " : " << res->value << endl;

                    // �޸�
                    if (type == 3) {
                        int modifiedRes = modifyWordToCHDict(res);
                        if (modifiedRes != -1) {
                            modifiedFlag = true;
                            modifiedItemNum++;
                            cout << "modified Successfully!" << endl;
                        }
                        else {
                            cout << "modified Unsuccessfully!" << endl;
                        }
                    }
                    else if (type == 4) {
                        int deleteRes = deleteWordToCHDict(word);
                        if (deleteRes != -1) {
                            modifiedFlag = true;
                            deleteItemNum++;
                            cout << "delete Successfully!" << endl;
                        }
                        else {
                            cout << "delete Unsuccessfully!" << endl;
                        }
                    }
                }
            }
            

        }

        dictFunctionAndExport();
    }

    void dictFuncSearch() {
        _dictFuncCombined(1);
    }

    void dictFuncAdd() {
        _dictFuncCombined(2);
    }

    void dictFuncModify() {
        _dictFuncCombined(3);
    }

    void dictFuncDelete() {
        _dictFuncCombined(4);
    }

    void dictFunctionAndExport() {
        system("cls");
        printFunctionAndExportPromt();
        while (true) {
            string funcAndExFlag = _getUserInput("please input the functions��");
            if (funcAndExFlag.compare("1") == 0) {
                dictFuncSearch();
                break;
            }
            else if (funcAndExFlag.compare("2") == 0) {
                dictFuncAdd();
                break;
            }
            else if (funcAndExFlag.compare("3") == 0) {
                dictFuncModify();
                break;
            }
            else if (funcAndExFlag.compare("4") == 0) {
                dictFuncDelete();
                break;
            }
            else if (funcAndExFlag.compare("5") == 0 || funcAndExFlag.compare("") == 0) {
                // Ĭ�ϵ���
                dictExport();
                break;
            }
            else if (funcAndExFlag.compare("0") == 0) {
                ;
            }
            else {
                printf("%s\n", "Error:Illegal Input!");
                continue;
            }
        }
    }
    

    void dictExport() {
        // �����޸Ĺ���־ʱȷ���Ƿ񵼳�
        system("cls");
        printExportDictPromt();
        int totalItems = _endExportDict();
        cout << "---������" << totalItems << "��Items---" << endl;
        _getUserInput("press any key to end...");
        
        dictEnd();
    }

    void dictEnd() {
        system("cls");
        printEndPromt();
        _getUserInput("press any key to end...");
    }

    void dictStart() {
        dictSelectLanguage();
    }

    string _getUserInput(const char* promt) {
        showUserArea();
        printf("%s:", promt);
        getline(cin, userInput);

#ifdef DEBUG
        // ���õ�ʵ��
        if (userInput.compare("bye") == 0) {
            dictEnd();
            exit(0);
        }
#endif // DEBUG

        return userInput;
    }
};





int main(void) {
    promt pboard;
    pboard.dictStart();

}