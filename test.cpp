////////////////////////////////////////////////////////////////////////////////
// aasDict运行主入口
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

// 提示个数限制
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
    bool    modifiedFlag    = false;        // 词典是否修改标志

    // 目前这个计数功能不太稳定 - 2022-7-21
    int     deleteItemNum   = 0;            // 删除个数
    int     modifiedItemNum = 0;            // 修改个数
    int     addItemNum      = 0;            // 添加的个数

    void showNchar(char ch, int num) {
        for (int count = 1; count <= num; count++)
            putchar(ch);
    }

    void printPromt(void) {
        const char* header = "aasDict";
        const char* p1 = "C语言关键字/普通词典 翻译机";
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
        const char* p1 = "请导入词典";
        const char* p2 = "1.C语言关键字（32）";
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
        const char* p1 = "请导入词典";
        const char* p2 = "1.C语言关键字（32）";
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
        const char* p1 = "选择功能(select function)";
        const char* p2 = "1.查询(search)";
        const char* p3 = "2.增加(add)";
        const char* p4 = "3.修改(modify)";
        const char* p5 = "4.删除(delete)";


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
        const char* p1 = "查询/添加（Search/Add）";

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
        const char* p1 = "增加（Add）";

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
        const char* p1 = "修改（Modify）";

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
        const char* p1 = "删除（Delete）";

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
        const char* p1 = "选择功能(select function)";
        const char* p2 = "1.查询(search)";
        const char* p3 = "2.增加(add)";
        const char* p4 = "3.修改(modify)";
        const char* p5 = "4.删除(delete)";
        const char* p6 = "5.导出(export)";


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
        const char* p1 = "导出词典（export）";
        const char* p2 = "词典已被修改(modified)";
        const char* p3 = "词典未被修改(unmodified)";
        string tmp1, tmp2, tmp3;
        tmp1 = (string("添加(add)单词个数：") + to_string(addItemNum));
        tmp2 = (string("修改(modified)单词个数：") + to_string(modifiedItemNum));
        tmp3 = (string("删除(delete)单词个数：") + to_string(deleteItemNum));
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
            // 计数功能 仅debug时用
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
        const char* p1 = "欢迎使用 :)";
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
        // 获取中/英文词典，1为en-zh（默认），2为zh-en，其余返回-1
        _getUserInput("please input the dictionary Type：");
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
        // 获取读入词典的名称，1为c语言词典（默认），2为ecdict，其余返回-1
        _getUserInput("please input the dictionary number：");
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
        // 获取读入词典的名称，1为查询（默认），2为增加，3为修改，4为删除
        _getUserInput("please input the functions：");
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
                // 导出
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
        // 添加单词到Dict中（与用户交互）
        string addFlag = _getUserInput("add to the dictionary?");
        if (addFlag.compare("y") == 0 || addFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?");
            if (wordTrans.size() > 0) {
                // 插入
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
        // 修改单词到enDict中（与用户交互）
        string modifyedFlag = _getUserInput("modify?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?:");
            if (wordTrans.size() > 0) {
                // 插入
                node->value = wordTrans;
                return 0;
            }
        }
        return -1;
    }

    int modifyWordToCHDict(trieNode* node) {
        // 修改单词到chDict中（与用户交互）
        string modifyedFlag = _getUserInput("modify?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            string wordTrans = _getUserInput("the translation is?:");
            if (wordTrans.size() > 0) {
                // 插入
                node->value = wordTrans;
                return 0;
            }
        }
        return -1;
    }

    int deleteWordToENDict(string word) {
        // 删除单词到enDict中（与用户交互）
        string modifyedFlag = _getUserInput("delete?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            return ent.del(word);
        }
        return -1;
    }

    int deleteWordToCHDict(string word) {
        // 删除单词到chDict中（与用户交互）
        string modifyedFlag = _getUserInput("delete?:");
        if (modifyedFlag.compare("y") == 0 || modifyedFlag.compare("yes") == 0) {
            return cht.del(word);
        }
        return -1;
    }

    void dictSelectLanguage() {
        system("cls");
        printPromt();
        // 选择词典语言
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
        // 跳转到导入词典界面
        dictImportDict();
    }

    void dictImportDict() {
        // 导入词典界面
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


        // ***导入词典***
        if (langu == 1) {
            // en
            ent.setLimit(LIMIT);
            totalItems = ent.importDict(dictFileName);
            cout << "---共导入" << totalItems << "个Items---" << endl;
            _getUserInput("press any key to next...");
        }
        else if (langu == 2) {
            // zh
            cht.setLimit(LIMIT);
            cht.setWordSize(WORD_SIZE);
            totalItems = cht.importDict(dictFileName);
            cout << "---共导入" << totalItems << "个Items---" << endl;
            _getUserInput("press any key to next...");
        }

        // ***跳转到功能选择界面***
        dictSelectFunction();
    }

    void dictSelectFunction() {
        // 功能选择界面
        int func;
        system("cls");
        printFunctionPromt();
        while (true) {
            func = getFunctionInput();
            if (func == 1) {
                // 查询
                break;
            }
            else if (func == 2) {
                // 增加
                break;
            }
            else if (func == 3) {
                // 修改
                break;
            }
            else if (func == 4) {
                // 删除
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
            // 查询
            dictFuncSearch();
        }
        else if (func == 2) {
            // 增加
            dictFuncAdd();
        }
        else if (func == 3) {
            // 修改
            dictFuncModify();
        }
        else if (func == 4) {
            // 删除
            dictFuncDelete();
        }
    }

    void _dictFuncCombined(int type){
        // 集大成函数
        // type =1 搜索，type=2 添加， type=3 修改， type = 4 删除
        system("cls");

        // 打印promt
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
        // 单词查询
        while (true) {
            string word = getSearchWord(); //到userInput中
            if (word.compare("") == 0) {
                // 输入为空则退出
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
                        // 尝试添加到目录中
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

                    // 修改
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
                        // 尝试添加到目录中
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

                    // 修改
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
            string funcAndExFlag = _getUserInput("please input the functions：");
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
                // 默认导出
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
        // 当有修改过标志时确认是否导出
        system("cls");
        printExportDictPromt();
        int totalItems = _endExportDict();
        cout << "---共导出" << totalItems << "个Items---" << endl;
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
        // 不好的实现
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