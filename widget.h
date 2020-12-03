#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

class Widget : public QWidget
{



    Q_OBJECT
    QFrame* frame;
    QLineEdit *edit;
    QSlider *slider;
    QLabel *label;
    QSpinBox *spinBox;
    QLayout *frameLayout;
    QComboBox *comboBox;
    QPushButton *disableButton;
    QPushButton *styleSwitchButton;
    bool m_disable = false;

signals:

    void mySignal(int);

protected slots:
    void mySlot(QString);
    void slotChangeLayout(int index);
    void slotDisableButton();
public:

    Widget(QWidget *parent = nullptr);
    ~Widget();

    QLineEdit* createLineEdit(QWidget* parent = 0);
    QSlider*   createSlider(QWidget* parent = 0);
    QLabel*    createLabel(QWidget* parent = 0);
    QSpinBox*  createSpinBox(QWidget* parent = 0);

    QHBoxLayout* createHBoxLayout(QWidget* parent = 0);
    QVBoxLayout* createVBoxLayout(QWidget* parent = 0);
    QGridLayout* createGridLayout(QWidget* parent = 0);


};



#endif // WIDGET_H
