#ifndef QUESTION_H
#define QUESTION_H

#include <QtGui/QWidget>

namespace Ui {
    class Question;
}

class Question : public QWidget {
    Q_OBJECT

public:
    explicit Question(QWidget *parent = 0);
    ~Question();
    void setIndex(int index);

    QString getText();
    QString getAnswerA();
    QString getAnswerB();
    QString getAnswerC();
    quint16 getCorrectAnswer();
    quint32 getQuestionNumber();

    void setText(QString text);
    void setAnswerA(QString ans);
    void setAnswerB(QString ans);
    void setAnswerC(QString ans);
    void setCorrectAnswer(quint16 correct);
    void setQuestionNumber(quint32 number);
private:
    Ui::Question *ui;
};

#endif // QUESTION_H
