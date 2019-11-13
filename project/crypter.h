#ifndef CRYPTER_H
#define CRYPTER_H

#include <QObject>

static const QString keycryption = QString("abcdefg12rewqrty789p");

class Cryption: public QObject {

    Q_OBJECT

private:

    static int keyIndex(int index){
        int len = keycryption.length();
        int multiple = index/len;
        if(index>= len){
            return index - (len*multiple);
        }
        return index;
    }

public:

    static QString cryptionpas(QString password){
        QString resultstring = "";
        for (int i=0 ; i< password.length(); i++){
            resultstring.append(QString(QChar(password[i]).unicode()^QChar(keycryption[keyIndex(i)]).unicode()));
        }
        return resultstring;
    }
};
#endif // CRYPTER_H
