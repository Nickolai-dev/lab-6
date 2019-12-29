#include <iostream>
#include <fstream>
#include <map>
#include <complex>

using namespace std;

inline void run(std::istream &scin) {
    static float stk[80] = {0};
    static int i = 0;
    static map<string, float> assoc;
    do {
        string cmd;
        scin >> cmd;
        if(cmd[0] == '#') {
            while(true) {
                char t = scin.peek();
                if( (t=='\n' && cmd[cmd.length()-1]!='\\') || scin.eof() ) break;
                scin >> cmd;
            }
            continue;
        } //comment
        if(cmd == "PUSH") { // push number
            string item;
            scin >> item;
            auto it = assoc.find(item);
            if(it != assoc.end())
                stk[i++] = it->second;
            else {
                float num = atof(item.c_str());
                if(errno!=0) throw std::runtime_error("Syntax error");
                stk[i++] = num;
            }
        }
        if(cmd == "POP") { // pop item
            i--;
        }
        if(cmd == "PRINT") {
            cout << stk[i-1] << endl;
        }
        if(cmd == "DEFINE") {
            string param;
            float num;
            scin >> param >> num;
            assoc[param] = num;
        }
        if(cmd == "+") {
            stk[i-2]+=stk[i-1];
            i--;
        }
        if(cmd == "-") {
            stk[i-2]-=stk[i-1];
            i--;
        }
        if(cmd == "*") {
            stk[i-2]*=stk[i-1];
            i--;
        }
        if(cmd == "/") {
            stk[i-2]/=stk[i-1];
            i--;
        }
        if(cmd == "SQRT") {
            stk[i-1] = sqrtf(stk[i-1]);
        }
    } while(!scin.eof());
}

int main(int argc, char *argv[]) {
    if(argc > 1){
        std::ifstream in(argv[1]);
        run(in);
    }
    else
        run(std::cin);
    return 0;
}
