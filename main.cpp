#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w, b;

    // 取得主要螢幕可用區域（會自動避開工作列 / Dock）
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect area = screen->availableGeometry();

    // 想要左右並排，中間留 10 px 間距
    const int spacing = 10;

    // 將可用寬度平均分配給兩個視窗（也可以改成固定寬度）
    int winWidth = (area.width() - spacing) / 2;
    int winHeight = area.height(); // 或者指定成固定高度，例如 800

    // 設定視窗大小（可改用 resize 或 setGeometry）
    w.resize(winWidth, winHeight);
    b.resize(winWidth, winHeight);

    // 讓兩個視窗水平並排並垂直置中
    int leftX = area.x();
    int rightX = area.x() + winWidth + spacing;
    int y = area.y(); // 若要垂直置中，可改成: area.y() + (area.height() - winHeight)/2

    w.move(leftX, y);
    b.move(rightX, y);

    w.show();
    b.show();

    return a.exec();
}
