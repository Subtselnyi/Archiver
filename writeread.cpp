#include "WriteRead.h"

void writetoOutput(){//запис остовного дерева  у  файл  output.txt

    FILE *f;
    f=fopen("./newfileforsmth.txt","wt+");
    fputs("OKE",f);
    if (f)
        qInfo()<<f;
    fclose(f);

}
