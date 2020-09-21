#include <QtTest/QtTest>

#include "../src/diapasonedit.h"

class TestDiapasonEdit : public QObject {
    Q_OBJECT
private slots:
    void setBase_data();
    void setBase();
    void getNumbers_data();
    void getNumbers();
};


void TestDiapasonEdit::setBase_data()
{
    QTest::addColumn<DiapasonEdit::Base>("base");
    QTest::addColumn<QVector<uint> >("result");
    QTest::newRow("dec") << DiapasonEdit::Base::Dec << QVector<uint>{20};
    QTest::newRow("hex") << DiapasonEdit::Base::Hex << QVector<uint>{0x20};
}

void TestDiapasonEdit::setBase()
{
    QFETCH(DiapasonEdit::Base, base);
    QFETCH(QVector<uint>, result);
    DiapasonEdit diapasonEdit;
    diapasonEdit.setBase(base);
    diapasonEdit.setText("20");
    QCOMPARE(diapasonEdit.getNumbers(), result);
}


void TestDiapasonEdit::getNumbers_data()
{
    QTest::addColumn<DiapasonEdit::Base>("base");
    QTest::addColumn<QString>("text");
    QTest::addColumn<uint>("inc");
    QTest::addColumn<QVector<uint>>("result");
    QVector<uint> empty;
    QTest::newRow("dec_empty") << DiapasonEdit::Base::Dec << "" << 1U
                               << QVector<uint>();
    QTest::newRow("dec_inc_1") << DiapasonEdit::Base::Dec << "0-5,6,4294967294-4294967295" << 1U
                               << QVector<uint>{0, 1, 2, 3, 4, 5, 6, 4294967294, 4294967295};
    QTest::newRow("dec_inc_4") << DiapasonEdit::Base::Dec << "0-5,6,4294967294-4294967295" << 4U
                               << QVector<uint>{0, 4, 6, 4294967294};
    QTest::newRow("hex_empty") << DiapasonEdit::Base::Hex << "" << 1U
                               << QVector<uint>();
    QTest::newRow("hex_inc_1") << DiapasonEdit::Base::Hex << "0,1,FFFFFFFA-FFFFFFFF,FFFFFFFF" << 1U
                               << QVector<uint>{0, 1, 0xFFFFFFFA, 0xFFFFFFFB, 0xFFFFFFFC, 0xFFFFFFFD, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF};
    QTest::newRow("hex_inc_4") << DiapasonEdit::Base::Hex << "0,1,FFFFFFFA-FFFFFFFF,FFFFFFFF" << 4U
                               << QVector<uint>{0, 1, 0xFFFFFFFA, 0xFFFFFFFE, 0xFFFFFFFF};
}

void TestDiapasonEdit::getNumbers()
{
    QFETCH(DiapasonEdit::Base, base);
    QFETCH(QString, text);
    QFETCH(uint, inc);
    QFETCH(QVector<uint>, result);

    DiapasonEdit diapasonEdit;
    diapasonEdit.setBase(base);
    diapasonEdit.setText(text);
    QCOMPARE(diapasonEdit.getNumbers(inc), result);
}

QTEST_MAIN(TestDiapasonEdit)
#include "test_DiapasonEdit.moc"
