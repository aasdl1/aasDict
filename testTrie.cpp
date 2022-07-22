//////////////////////////////////////////////////////////////////////////////////
//// 测试demo
//////////////////////////////////////////////////////////////////////////////////
//
//
//#include "enTrie.h"
//#include "chTrie.h"
//#include "codeFormat.h"
////#include <string>
//
//#include <windows.h> 
//
//#define LIMIT 4
//
//#ifdef _WIN32
//#define WORD_SIZE 2     //GBK
//#else
//#define WORD_SIZE 3     //UTF-8
//#endif
//
//int main(void) {
//    //system("getch");
//    //return 0;
//
//    chTrie t(LIMIT, WORD_SIZE);
//
//    //enTrie t;
//
//    int n;
//    int total = 0;
//    string str;
//    string trans;
//    vector<pair<string, string>> ret(LIMIT);
//
//    // vs控制台的注册表在哪里？（可能用的是自带的cmd那边的，确认了codePage是65001）
//    // let console output with UTF8
//    // system("chcp 936"); //以gbk码运行
//    // SetConsoleOutputCP(CP_UTF8);
//    SetConsoleOutputCP(936);
//
//    // 导入字典并测试时间
//    clock_t start, end;     // 定义clock_t变量
//    
//
//    LARGE_INTEGER nFreq;
//    LARGE_INTEGER nBeginTime;
//    LARGE_INTEGER nEndTime;
//    double time;
//
//    QueryPerformanceFrequency(&nFreq);
//    QueryPerformanceCounter(&nBeginTime);
//
//    start = clock();        // 开始时间
//    //ecdict4-2000.csv / ecdict4-20000.csv /  ecdict2.csv / zhdict2.csv /cKeyWord.csv /cKeyWord-gbk.csv /test.csv
//    int totalItems = t.importDict("ecdict4-200.csv");
//
//
//    end = clock();          //结束时间
//    QueryPerformanceCounter(&nEndTime);
//
//    time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//    printf("%3.4f\n", time * 1000);
//    
//
//    
//
//    printf("---共读入%d个Item---\n", totalItems);
//
//    printf("construct dict time:%3.4g s\n", (double)(end - start) / CLOCKS_PER_SEC);
//
//    // t._addStr(t.root, "", ret);
//    //t.dfs(t.root, 1);
//    // return 0;
//    // string outputPath("OUT_CKEYWORD_EN.csv");
//    // t.dfs(t.root, "", (ofstream*) & cout);
//    // totalItems = t.exportDict(outputPath);
//    // printf("---共写入%d个Item---\n", totalItems);
//    // return 0;
//
//
//    cout << "please input the key word:" << endl;
//
//    while (getline(cin, str) && str.size() > 0) {
//
//        LARGE_INTEGER nFreq;
//        LARGE_INTEGER nBeginTime;
//        LARGE_INTEGER nEndTime;
//        double time;
//
//        QueryPerformanceFrequency(&nFreq);
//        QueryPerformanceCounter(&nBeginTime);
//
//        // --查询单个单词
//        // trieNode* res = t.search(str);
//        // string str2("类型");
//        auto res = t.search(str);
//
//        QueryPerformanceCounter(&nEndTime);
//
//        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//
//        if (res == NULL) {
//            //cout << "search failed\n" << endl;
//            //cout << "matched items:" << endl;
//
//            ret.clear();
//
//            ret = t.getPreStrings(str, ret);
//            for (psvec::iterator it = ret.begin(); it != ret.end(); it++) {
//                cout << it->first << endl;
//            }
//            cout << endl;
//        }
//        else {
//            cout << str << " : " << res->value << endl;
//        }
//        //printf("search time:%3.4f ms\n", time * 1000);
//        printf("%3.4f\n", time * 1000);
//
//        // --获取所有以该字符串为前缀的单词
//        // ret = t.get_str_pre(str);
//
//
//        cout << "please input the key word:" << endl;
//    }
//    return 0;
//}