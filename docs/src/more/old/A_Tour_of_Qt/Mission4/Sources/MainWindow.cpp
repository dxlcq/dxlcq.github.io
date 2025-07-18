#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString title = "QQ - " + QString::number(c.getid());
    this -> setWindowTitle(title);
    this -> setCentralWidget(&centralWidget);
    this -> resize(800, 600);
    centralWidget.setLayout(&centralLayout);
    
    centralLayout.addWidget(&_friendList);
    centralLayout.addLayout(&_rightLayout);
    _rightLayout.addWidget(&_sw);
    _rightLayout.addLayout(&_inputLayout);
    _inputLayout.addWidget(&_input);
    _inputLayout.addWidget(&_send);

    _friendList.setFixedWidth(100);
    _input.setFixedHeight(100);
    _send.setFixedHeight(100);

    _send.setText("发\n送");
    _send.setStyleSheet("background-color: rgb(255, 0, 0);");

    // test
    /*
    _friendList.addItem("5");           // 假设有一个好友 5
    _chatRecord[5] = new QTextEdit();
    _chatRecord[5] -> setReadOnly(true);
    _sw.addWidget(_chatRecord[5]);
    
    _friendList.addItem("4");           // 假设有一个好友 4
    _chatRecord[4] = new QTextEdit();
    _chatRecord[4] -> setReadOnly(true);
    _sw.addWidget(_chatRecord[4]);
    */

    _friendList.addItem("0");           // 与服务器通话的界面
    _chatRecord[0] = new QTextEdit();
    _chatRecord[0] -> setReadOnly(true);
    _sw.addWidget(_chatRecord[0]);

    // 当点击好友时
    connect(&_friendList, &QListWidget::itemClicked, this, [&](QListWidgetItem* item){ 
        _sw.setCurrentWidget(_chatRecord[item -> text().toInt()]);
    });

    // 当点击发送按钮时
    connect(&_send, &QPushButton::clicked, this, [&](){
        QString msg = _input.toPlainText(); // 获取输入框内容
        _input.clear();                     // 清空输入框
        _chatRecord[_friendList.currentItem() -> text().toInt()] -> append("我：" + msg);
        c.sendMsg( (_friendList.currentItem() -> text() + msg).toStdString() );
    });


    QTimer *t = new QTimer(this);
    t -> start(10);   // 每隔 0.01 秒
    // 当定时器超时时
    connect(t, &QTimer::timeout, this, [&](){
        // 接收消息
        std::string msg = c.recvMsg();
        if(msg == "") return ;  // 如果没有消息，直接返回
        int id = msg[0] - '0';  // 获取好友 id
        
        if(id == 0){    // 更新好友列表
            int i=0;    // 从第一个字符开始
            int one=0;  // 一个好友的 id
            qDebug() << QString::fromStdString(msg);
            while(++i < (int)msg.size()){
                if(msg[i] == ' '){
                    if(_chatRecord.count(one) == 0 && one != c.getid()){    // 如果没有这个好友
                        _friendList.addItem(QString::number(one));  // 添加好友
                        _chatRecord[one] = new QTextEdit();         // 添加聊天记录
                        _chatRecord[one] -> setReadOnly(true);
                        _sw.addWidget(_chatRecord[one]);
                    }
                    one = 0;
                }else{
                    one *= 10;
                    one += msg[i] - '0';
                }
            }

            return ;
        }

        _chatRecord[id] -> append(QString::number(id) + "：" + QString::fromStdString(msg.substr(1)));
    });
}

MainWindow::~MainWindow(){}

    