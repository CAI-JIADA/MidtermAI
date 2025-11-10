#include "mainwindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <algorithm>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w, b;

    // 設定視窗標題以區分兩個視窗
    w.setWindowTitle("主視窗 (Main Window)");
    b.setWindowTitle("副視窗 (Secondary Window)");

    // 取得主要螢幕可用區域（會自動避開工作列 / Dock）
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect area = screen->availableGeometry();

    // 視窗配置參數
    const int spacing = 20;              // 視窗間距（增加到 20px 以獲得更好的視覺效果）
    const int minWindowWidth = 600;      // 最小視窗寬度
    const int minWindowHeight = 500;     // 最小視窗高度
    const int maxWindowWidth = 1200;     // 最大視窗寬度
    const int maxWindowHeight = 900;     // 最大視窗高度
    const int verticalMargin = 50;       // 上下邊距

    // 計算視窗寬度（平均分配可用寬度，但考慮最小和最大限制）
    int winWidth = (area.width() - spacing) / 2;
    winWidth = std::max(minWindowWidth, std::min(maxWindowWidth, winWidth));

    // 計算視窗高度（使用可用高度減去邊距，但考慮最小和最大限制）
    int winHeight = area.height() - (verticalMargin * 2);
    winHeight = std::max(minWindowHeight, std::min(maxWindowHeight, winHeight));

    // 設定視窗最小尺寸
    w.setMinimumSize(minWindowWidth, minWindowHeight);
    b.setMinimumSize(minWindowWidth, minWindowHeight);

    // 設定視窗大小
    w.resize(winWidth, winHeight);
    b.resize(winWidth, winHeight);

    // 計算視窗位置以實現水平並排和垂直置中
    // 如果兩個視窗的總寬度超過可用寬度，則從左邊開始排列
    int totalWidth = winWidth * 2 + spacing;
    int leftX = area.x();
    if (totalWidth < area.width()) {
        // 如果有額外空間，將視窗組水平置中
        leftX = area.x() + (area.width() - totalWidth) / 2;
    }
    int rightX = leftX + winWidth + spacing;

    // 垂直置中
    int y = area.y() + (area.height() - winHeight) / 2;

    // 移動視窗到計算的位置
    w.move(leftX, y);
    b.move(rightX, y);

    // 顯示視窗
    w.show();
    b.show();

    return a.exec();
}
