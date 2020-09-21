#include "diapasonedit.h"

#include <QValidator>
#include <QStringList>
#include <QString>
#include <QSharedPointer>

DiapasonEdit::DiapasonEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setBase(Base::Dec);
}

QVector<uint> DiapasonEdit::getNumbers(uint increment)
{
    QVector<uint> numbers;
    if (!text().isEmpty()) {
    QStringList values = text().split(",");
        for (int i = 0; i < values.size(); i++) {
            if (values[i].contains("-")) {
                QStringList diapason = values[i].split("-");
                uint min = diapason[0].toUInt(nullptr, base_);
                uint max = diapason[1].toUInt(nullptr, base_);
                if (min > max) std::swap(min, max);
                for (quint64 j = min; j <= max; j += increment) {
                    numbers.push_back(j);
                }
            } else {
                numbers.push_back(values[i].toUInt(nullptr, base_));
            }
        }
    }
    return numbers;
}

void DiapasonEdit::setBase(Base base)
{
    QRegExp regexp;
    validator_.reset();
    if (base == Base::Hex) {
        regexp.setPattern("[0-9A-Fa-f]+(?:-[0-9A-Fa-f]+)?(?:,*[0-9A-Fa-f]+(?:-[0-9A-Fa-f]+)?)*$");
        validator_ = std::unique_ptr<QRegExpValidator>(new QRegExpValidator(regexp));
    } else {
        regexp.setPattern("\\d+(?:-\\d+)?(?:,*\\d+(?:-\\d+)?)*$");
        validator_ = std::unique_ptr<QRegExpValidator>(new QRegExpValidator(regexp));
    }
    setValidator(validator_.get());
    base_ = static_cast<int>(base);
}
