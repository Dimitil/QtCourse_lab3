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

    QLineEdit* createLineEdit(QWidget* parent = nullptr);
    QSlider*   createSlider(QWidget* parent = nullptr);
    QLabel*    createLabel(QWidget* parent = nullptr);
    QSpinBox*  createSpinBox(QWidget* parent = nullptr);
    QComboBox* createComboBox(QWidget* parent = nullptr);
    QHBoxLayout* createHBoxLayoutAndAddWidget(QWidget* parent = nullptr);
    QVBoxLayout* createVBoxLayoutAndAddWidget(QWidget* parent = nullptr);
    QGridLayout* createGridLayoutAndAddWidget(QWidget* parent = nullptr);
    QFrame* createFrame(QWidget* parent = nullptr);

    class Functor {
        Widget* m_widget;
    public:
        Functor(Widget* w) : m_widget(w) {}
        void operator()(const QString& str)
        {
            m_widget->mySlot(str);
        }
    };
};

#endif // WIDGET_H
