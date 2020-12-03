#include "widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags f = Qt::Window;
    f |= Qt::CustomizeWindowHint;
    f |= Qt::WindowContextHelpButtonHint;
    setWindowFlags(f);

    QPushButton * buttonExit = new QPushButton("Exit",this);
    //buttonExit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    comboBox = createComboBox(this);
    connect(comboBox, qOverload<int>(&QComboBox::activated), this, &Widget::slotChangeLayout);

    disableButton = new QPushButton("Disable", this);
    //disableButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(disableButton, &QPushButton::clicked, this, &Widget::slotDisableButton);

    styleSwitchButton = new QPushButton("style", this);
    //styleSwitchButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(buttonExit, &QPushButton::clicked, this, &Widget::close);

    frame   = createFrame(this);
    edit    = createLineEdit();
    slider  = createSlider();
    label   = createLabel();
    spinBox = createSpinBox();

    frameLayout = createVBoxLayoutAndAddWidget(frame);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout -> addWidget(buttonExit);
    buttonsLayout -> addWidget(comboBox);
    buttonsLayout -> addWidget(disableButton);
    buttonsLayout -> addWidget(styleSwitchButton);

    mainLayout -> addWidget(frame);
    mainLayout -> addLayout(buttonsLayout);

    connect(spinBox, qOverload<int>(&QSpinBox::valueChanged),
            slider, &QSlider::setValue);
    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(spinBox, qOverload<int>(&QSpinBox::valueChanged),
            label, qOverload<int>(&QLabel::setNum));
    connect(edit, &QLineEdit::textChanged, Functor(this));
    connect(this, &Widget::mySignal, spinBox, &QSpinBox::setValue);
    connect(spinBox, &QSpinBox::textChanged, edit, &QLineEdit::setText);

    mySignal(20);

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
    slider->setMinimumWidth(300);
    //slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return slider;
}

QComboBox* Widget::createComboBox(QWidget* parent) {
    QComboBox* comboBox = new QComboBox(parent);
    //comboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    comboBox->addItem("Vertical");
    comboBox->addItem("Horizon");
    comboBox->addItem("Grid");
    comboBox->setStyleSheet("padding-left: 20px;");//нет нормального решения на Qt 5.12
    return comboBox;
}

QLabel*    Widget::createLabel(QWidget* parent)
{
    QLabel* lbl = new QLabel("no set", parent);
    lbl->setFrameStyle(QFrame::Plain);
    lbl->setAlignment(Qt::AlignCenter);
    //lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    return lbl;
}
QSpinBox*  Widget::createSpinBox(QWidget* parent)
{
    QSpinBox* sb = new QSpinBox(parent);
    sb-> setMaximum(50);
    sb->setValue(25);
    sb->setAlignment(Qt::AlignCenter);
    sb->setFixedSize(sb->sizeHint());
    return sb;
}

QHBoxLayout* Widget::createHBoxLayoutAndAddWidget(QWidget* parent)
{
    QHBoxLayout *hbl = new QHBoxLayout(parent);
    hbl -> addWidget(slider);
    hbl -> addWidget(label);
    hbl -> addWidget(spinBox);
    hbl -> addWidget(edit);
   // hbl->setAlignment(edit, Qt::AlignCenter);
   // hbl->setAlignment(spinBox, Qt::AlignCenter);
    return hbl;
}

QVBoxLayout* Widget::createVBoxLayoutAndAddWidget(QWidget* parent)
{
    QVBoxLayout *vbl = new QVBoxLayout(parent);
    vbl -> addWidget(slider);
    vbl -> addWidget(label);
    vbl -> addWidget(spinBox);
    vbl -> addWidget(edit);
    vbl->setAlignment(edit, Qt::AlignCenter);
    vbl->setAlignment(spinBox, Qt::AlignCenter);
    return vbl;
}

QGridLayout* Widget::createGridLayoutAndAddWidget(QWidget* parent)
{
    QGridLayout *gl = new QGridLayout(parent);
    gl -> addWidget(slider, 0, 0);
    gl -> addWidget(label, 0, 1);
    gl -> addWidget(spinBox, 1, 1);
    gl -> addWidget(edit, 1, 0, Qt::AlignCenter);
    return gl;
}

QFrame* Widget::createFrame(QWidget* parent) {
    QFrame* frame = new QFrame(parent);
    frame -> setFrameStyle(QFrame::Panel);
    return frame;
}

void Widget::mySlot(QString str)
{
    bool ok = false;
    int num = str.toInt(&ok);
    if (ok) {
        emit mySignal(num);
    }
}

void Widget::slotChangeLayout(int index)
{
    delete frameLayout;
    switch (index) {
    case 0:
        frameLayout = createVBoxLayoutAndAddWidget(frame);
        break;
    case 1:
        frameLayout = createHBoxLayoutAndAddWidget(frame);
        break;
    case 2:
        frameLayout = createGridLayoutAndAddWidget(frame);
        break;
    default:
        return;
    }
    repaint();
}

void Widget::slotDisableButton()
{
    m_disable = !m_disable;
    frame->setDisabled(m_disable);
    if (m_disable) {
        disableButton -> setText("Enable");
    }
    else {
        disableButton -> setText("Disable");
    }
}
