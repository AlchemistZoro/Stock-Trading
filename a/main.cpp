#include "query.h"
#include "ViewerContent.h"
#include "buy.h"
#include <QApplication>
const QString testURL = "http://hq.sinajs.cn/list=sh600519";
//**********************************
//name:main
//
//input:
//
//output:void
//
//description:程序入口
//**********************************
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ViewerContent vct;
    vct.SetFromSinaAPI(testURL);

    Query w;
    w.updateViewer(vct);

    w.show();
    return a.exec();
}
