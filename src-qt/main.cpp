#include "mainwindow.h"
#include "cfdg_highlighter.h"
#include <QApplication>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextEdit *editor = w.findChild<QTextEdit*>("code");
    cfdg_highlighter highlighter(editor->document());
    w.show();
    w.foobar();
    return a.exec();
}
