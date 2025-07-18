#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("缙云山打字通");
    this -> setFixedSize(800, 600);

    std::ifstream ifs("data.txt");
    std::string str;
    while(ifs >> str)
        _words.push_back(QString::fromStdString(str));
}

MainWindow::~MainWindow(){}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;
    // 设置等宽字体
    font.setFamily("Courier New");
    font.setPointSize(30);
    painter.setFont(font);
    painter.setPen(Qt::green);

    int x = 0, y = 100;
    for (int i = 0; i < _words.size(); i++) {
        QString word = _words[i];
        if (i >= cnt) painter.setPen(Qt::black);
        painter.drawText(x, y, word);
        x += 30;
        if (x > 750) {
            x = 0;
            y += 50;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event -> key() == Qt::Key_Backspace){
        if(cnt > 0) cnt--;
    }
    else if(event -> key() == Qt::Key_Space){
        cnt++;
    }
    else{
        QString str = event -> text();
        if(str == _words[cnt]) cnt++;
    }
    if(cnt == _words.size()){
        QMessageBox::information(this, "恭喜", "你已经完成了打字练习");
    }
}