#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QPixmap>
#include <QLabel>

int main(int argc, char *argv[]){
    QApplication love(argc, argv);

    QWidget* window_main = new QWidget();
    window_main -> resize(426, 240);
    window_main -> setWindowTitle("Love");

    // 分辨率下拉框
    QComboBox *combo_resolution = new QComboBox(window_main);
    combo_resolution->addItem("426x240p");      // 像素画
    combo_resolution->addItem("854x480p");      // 鲜花心脏
    combo_resolution->addItem("1280x720p");     // 画的心脏
    combo_resolution->addItem("1920x1080p");    // 心脏
    combo_resolution->addItem("2560x1440p");    // 画 镰刀和榔头
    combo_resolution->addItem("3840x2160p");    // 镰刀和榔头
    
    QPixmap img_240p("img/love240p.jpg");           // 创建 QPixmap 对象，用于显示图片
    QLabel *label_image = new QLabel(window_main);  // 创建 QLabel 对象，用于显示图片
    label_image->setPixmap(img_240p);               // 设置图片
    
    QObject::connect(combo_resolution, &QComboBox::currentTextChanged, [=](){
        QString resolution = combo_resolution->currentText();
        if(resolution == "426x240p"){
            QPixmap img_240p("img/love240p.jpg");
            label_image->setPixmap(img_240p);
            label_image->resize(426, 240);
            window_main->resize(426, 240);
        }else if(resolution == "854x480p"){
            QPixmap img_480p("img/love480p.jpg");
            label_image->setPixmap(img_480p);
            label_image->resize(854, 480);
            window_main->resize(854, 480);
        }else if(resolution == "1280x720p"){
            QPixmap img_720p("img/love720p.jpg");
            label_image->setPixmap(img_720p);
            label_image->resize(1280, 720);
            window_main->resize(1280, 720);
        }else if(resolution == "1920x1080p"){
            QPixmap img_1080p("img/love1080p.jpg");
            label_image->setPixmap(img_1080p);
            label_image->resize(1920, 1080);
            window_main->resize(1920, 1080);
        }else if(resolution == "2560x1440p"){
            QPixmap img_1440p("img/love1440p.jpg");
            label_image->setPixmap(img_1440p);
            label_image->resize(2560, 1440);
            window_main->resize(2560, 1440);
        }else if(resolution == "3840x2160p"){
            QPixmap img_2160p("img/love2160p.jpg");
            label_image->setPixmap(img_2160p);
            label_image->resize(3840, 2160);
            window_main->resize(3840, 2160);
        }
    });

    combo_resolution->raise();  // 按钮置顶
    window_main->show();        // 显示窗口
    return love.exec();
}