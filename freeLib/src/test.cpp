#include "common.h"
#include "test.h"

Test::Test(QObject* parent) :
    QObject(parent)
{
    // �������� ����� freeLib ������������� � �������� ����� ������������
    testFreeLidDir_ = QDir::toNativeSeparators(QDir::homePath() + QDir::separator() + "freeLib");
    mGenreFile_ = QDir::toNativeSeparators(testFreeLidDir_ + QDir::separator() + "mGenreFile.txt");
}

Test::~Test()
{
}

/*
    ������ � ���� ����������� mGenre
    ������ �������������: 
    1. � ������������� �����:       Test* test = new Test(this); test->print_mGenre();
    2. � ����������� � ����� �����: Test* test = new Test(this); test->print_mGenre(true);
*/
void Test::print_mGenre(bool append)
{
    QFile file(mGenreFile_);
    bool isFileOpen = false;
    if (!append) {
        file.remove();
        isFileOpen = file.open(QIODevice::NewOnly | QIODevice::Text);
    } else isFileOpen = file.open(QIODevice::Append | QIODevice::Text);
    
    if (isFileOpen) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out.setGenerateByteOrderMark(false);

        QMap <uint,SGenre>::const_iterator ciGenre = mGenre.constBegin();
        QString ParrentGenreName = "";
        while (ciGenre != mGenre.constEnd()) {
            if (ParrentGenreName != mGenre[ciGenre->idParrentGenre].sName) {
                if (ciGenre->idParrentGenre > 0) {
                    out << "id=" + QString::number(ciGenre->idParrentGenre) + ": " + mGenre[ciGenre->idParrentGenre].sName << endl;;
                    out << "    id=" + QString::number(ciGenre.key()) + ": " + ciGenre->sName + " (" + ciGenre->sCode + ")" << endl;;
                }
            } else {
                if (ciGenre->idParrentGenre > 0)
                    out << "    id=" + QString::number(ciGenre.key()) + ": " + ciGenre->sName + " (" + ciGenre->sCode + ")" << endl;;
            }
            ParrentGenreName = mGenre[ciGenre->idParrentGenre].sName;
            ++ciGenre;
        }
        out << "mGenre.size() = " + QString::number(mGenre.size());
        out << endl;
        out << "=============================";
    }
    file.close();
}
