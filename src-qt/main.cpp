#include "mainwindow.h"
#include "cfdg_highlighter.h"
#include <QApplication>
#include <QTextEdit>
#include <QtDebug>

int main(int argc, char *argv[])
{
    if (QIcon::themeName() == "") {
        QIcon::setThemeSearchPaths((QStringList){"/usr/share/icons"});
        QIcon::setThemeName("Tango");
    }
    QApplication a(argc, argv);
    MainWindow w;
    QTextEdit *editor = w.findChild<QTextEdit*>("code");
    cfdg_highlighter highlighter(editor->document());
    w.setWindowTitle("New Document - ContextFree");
    w.show();
    return a.exec();
}
