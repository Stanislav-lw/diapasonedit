#ifndef DIAPASONEDIT_H
#define DIAPASONEDIT_H

#include <QLineEdit>
#include <QVector>
#include <QRegExpValidator>

#include <memory>

class DiapasonEdit : public QLineEdit
{
    Q_OBJECT
public:
    enum class Base { Hex = 16, Dec = 10 };
    Q_ENUM(Base)
    explicit DiapasonEdit(QWidget *parent = nullptr);
    QVector<uint> getNumbers(uint increment = 1);
    void setBase(Base base);
private:
    int base_;
    std::unique_ptr<QRegExpValidator> validator_;
};

#endif // DIAPASONEDIT_H
