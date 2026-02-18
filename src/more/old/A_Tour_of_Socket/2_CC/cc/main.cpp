#include "cc.h"

int main(int argc, char** argv){
    jiao::cc* c = new jiao::cc("0.0.0.0", atoi(argv[1]));
    c -> start();
    delete c;
    return 0;
}