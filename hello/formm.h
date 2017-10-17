#ifndef FORMM_H
#define FORMM_H

#include <QWidget>

namespace Ui {
class Formm;
}

class Formm : public QWidget
{
    Q_OBJECT

public:
    explicit Formm(QWidget *parent = 0);
    ~Formm();

private:
    Ui::Formm *ui;
};

#endif // FORMM_H
