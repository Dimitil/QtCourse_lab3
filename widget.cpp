#include "widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags f = Qt::Window;
    f |= Qt::CustomizeWindowHint;
    f |= Qt::WindowContextHelpButtonHint;
    setWindowFlags(f);

    QPushButton * buttonExit = new QPushButton(QObject::tr("Exit"),this);
    //buttonExit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    comboBox = new QComboBox(this);
    //comboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    disableButton = new QPushButton("dis/enable", this);
    //disableButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    styleSwitchButton = new QPushButton("style", this);
    //styleSwitchButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    connect(buttonExit, &QPushButton::clicked, this, &Widget::close);

    frame   = new QFrame(this);
    edit    = createLineEdit();
    slider  = createSlider();
    label   = createLabel();
    spinBox = createSpinBox();



    QHBoxLayout* mainLayout = createHBoxLayout(this);

    frameLayout = createVBoxLayout(frame);

    frameLayout -> addWidget(slider);
    frameLayout -> addWidget(label);
    frameLayout -> addWidget(spinBox);
    frameLayout -> addWidget(edit);
    frameLayout->setAlignment(edit, Qt::AlignHCenter | Qt::AlignVCenter);
    frameLayout->setAlignment(spinBox, Qt::AlignHCenter | Qt::AlignVCenter);
    frameLayout->setAlignment(slider, Qt::AlignHCenter | Qt::AlignVCenter);
    frameLayout->setAlignment(label, Qt::AlignHCenter | Qt::AlignVCenter);


    QLayout* buttonsLayout = createVBoxLayout();
    buttonsLayout -> addWidget(buttonExit);
    buttonsLayout -> addWidget(comboBox);
    buttonsLayout -> addWidget(disableButton);
    buttonsLayout -> addWidget(styleSwitchButton);

    mainLayout -> addWidget(frame);
    mainLayout -> addLayout(buttonsLayout);

    connect(spinBox,SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(mySlot(QString)));
    connect(this, SIGNAL(mySignal(int)), spinBox, SLOT(setValue(int)));
    //QObject::dumpObjectTree();
}

Widget::~Widget()
{
}

QLineEdit* Widget::createLineEdit(QWidget* parent)
{
    QLineEdit* edit = new QLineEdit(parent);
    QIntValidator qiv(0, 50);
    edit->setValidator(&qiv);
    edit->setMaxLength(2);
    edit->setMaximumWidth(25);
    //edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return edit;
}
QSlider*   Widget::createSlider(QWidget* parent)
{
    QSlider* slider = new QSlider(Qt::Horizontal, parent);
    slider->setRange(0, 50);
    slider->setSliderPosition(20);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(5);
    slider->setSingleStep(1);
    slider->setMinimumWidth(50);
    //slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return slider;

}
QLabel*    Widget::createLabel(QWidget* parent)
{
    QLabel* lbl = new QLabel("no set", parent);
    lbl->setFrameStyle(QFrame::Plain);
    lbl->setMinimumWidth(25);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    return lbl;
}
QSpinBox*  Widget::createSpinBox(QWidget* parent)
{
    QSpinBox* sb = new QSpinBox(parent);
    sb-> setMaximum(50);
    sb->setValue(25);
    sb->setFixedSize(sb->sizeHint());
    //slider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    return sb;
}

QHBoxLayout* Widget::createHBoxLayout(QWidget* parent)
{
    QHBoxLayout *hbl = new QHBoxLayout(parent);
    return hbl;
}

QVBoxLayout* Widget::createVBoxLayout(QWidget* parent)
{
    QVBoxLayout *hbl = new QVBoxLayout(parent);
    return hbl;
}

void Widget::mySlot(QString str)
{
    bool ok = false;
    int num = str.toInt(&ok);
   if (ok) {
        emit mySignal(num);
    }
}
