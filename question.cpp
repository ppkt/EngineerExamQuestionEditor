#include "question.h"
#include "ui_question.h"

Question::Question(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Question) {
    ui->setupUi(this);
}

Question::~Question() {
    delete ui;
}

void Question::setIndex(int index) {
    this->ui->index->setText(trUtf8("Q: %1").arg(index));
}

QString Question::getText() {
    return ui->text->toPlainText();
}

QString Question::getAnswerA() {
    return ui->answerA->toPlainText();
}

QString Question::getAnswerB() {
    return ui->answerB->toPlainText();
}

QString Question::getAnswerC() {
    return ui->answerC->toPlainText();
}

quint16 Question::getCorrectAnswer() {
    if (ui->correctA->isChecked()) {
	return 0;
    } else if (ui->correctB->isChecked()) {
	return 1;
    } else if (ui->correctC->isChecked()) {
	return 2;
    }
    return 999;
}

quint32 Question::getQuestionNumber() {
    return ui->number->value();
}

void Question::setText(QString text) {
    ui->text->setPlainText(text);
}

void Question::setAnswerA(QString ans) {
    ui->answerA->setPlainText(ans);
}

void Question::setAnswerB(QString ans) {
    ui->answerB->setPlainText(ans);
}

void Question::setAnswerC(QString ans) {
    ui->answerC->setPlainText(ans);
}

void Question::setCorrectAnswer(quint16 correct) {
    if (correct == 1) {
	ui->correctA->setChecked(true);
    } else if (correct == 2) {
	ui->correctB->setChecked(true);
    } else if (correct == 3) {
	ui->correctC->setChecked(true);
    }
}

void Question::setQuestionNumber(quint32 number) {
    ui->number->setValue(number);
}
