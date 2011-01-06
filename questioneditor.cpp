#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "question.h"
#include "questioneditor.h"
#include "ui_questioneditor.h"

QuestionEditor::QuestionEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionEditor) {
    changed = false;
    ui->setupUi(this);
}

QuestionEditor::~QuestionEditor() {
    delete ui;
}

void QuestionEditor::on_actionWyjd_triggered() {
    if (changed) {
	QMessageBox msgBox;
	msgBox.setText("Dokument został zmodyfikowany");
	msgBox.setInformativeText("Czy chcesz zapisać zmiany?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();

	switch (ret) {
	case QMessageBox::Save:
	    on_actionZapisz_triggered();
	    this->close();
	    break;
	case QMessageBox::Discard:
	    this->close();
	    break;
	case QMessageBox::Cancel:
	    break;
	default:
	    break;
	}
    }
}

void QuestionEditor::on_actionZapisz_triggered() {
    if (file == 0) {
	on_actionNowy_triggered();
    }
    QTextStream ts(file);
    ts.device()->seek(0);
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
	Question *q = static_cast<Question*>(ui->stackedWidget->widget(i));

	QString questionText = q->getText();
	int correctAnswer = q->getCorrectAnswer() + 1;
	QString questionAnswer1 = q->getAnswerA();
	QString questionAnswer2 = q->getAnswerB();
	QString questionAnswer3 = q->getAnswerC();

	QString line = QString("%1|%2|%3|%4|%5\n")
		.arg(questionText)
		.arg(correctAnswer)
		.arg(questionAnswer1)
		.arg(questionAnswer2)
		.arg(questionAnswer3);
	ts << line;
    }
}

void QuestionEditor::on_actionNowy_triggered() {
    bool ok = false;
    QString filename = QFileDialog::getOpenFileName(this,
						    tr("Wybierz plik z pytaniami"),
						    QDir::currentPath(),
						    "Pytania (*.txt);;Wszystkie pliki (*)");
    if (filename.isEmpty()) {
	return;
    }
    if (!filename.endsWith(".txt", Qt::CaseInsensitive)) {
	filename.append(".txt");
    }
    QFileInfo info(filename);
    if (info.isFile()) {
	QMessageBox msgBox;
	msgBox.setText(trUtf8("Plik istnieje!"));
	msgBox.setInformativeText(trUtf8("Czy chcesz nadpisać ten plik?"));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();

	switch (ret) {
	case QMessageBox::Yes:
	    file = new QFile(filename);
	    if (!file->open(QFile::ReadWrite | QFile::Truncate)) {
		QMessageBox::critical(this, trUtf8("Błąd"), trUtf8("Nie można otworzyć pliku"));
		break;
	    }
	    ok = true;
	    break;
	case QMessageBox::No:
	    on_actionNowy_triggered();
	    ok = false;
	    break;
	case QMessageBox::Cancel:
	    return;
	    break;
	default:
	    ok = false;
	    break;
	}
    } else {
	file = new QFile(filename);
	if (!file->open(QFile::ReadWrite | QFile::Truncate)) {
	    QMessageBox::critical(this, trUtf8("Błąd"), trUtf8("Nie można otworzyć pliku"));
	    ok = false;
	}
    }
}


void QuestionEditor::on_newQuestion_clicked() {
    unsigned currentIndex = ui->stackedWidget->currentIndex();
    Question *q = new Question();
    ui->stackedWidget->insertWidget(currentIndex + 1, q);
    ui->stackedWidget->setCurrentWidget(q);
    updateOrder();
}

void QuestionEditor::on_nextQuestion_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    int nextIndex;
    if ((currentIndex + 1) < ui->stackedWidget->count()) {
	nextIndex = currentIndex + 1;
    } else {
	nextIndex = 0;
    }
    ui->stackedWidget->setCurrentIndex(nextIndex);
}

void QuestionEditor::on_prevQuestion_clicked() {
    int currentIndex = ui->stackedWidget->currentIndex();
    int nextIndex;
    if ((currentIndex - 1) >= 0) {
	nextIndex = currentIndex - 1;
    } else {
	nextIndex = ui->stackedWidget->count() - 1;
    }
    ui->stackedWidget->setCurrentIndex(nextIndex);
}

void QuestionEditor::updateOrder() {
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
	Question *q = static_cast<Question*>(ui->stackedWidget->widget(i));
	q->setIndex(i);
    }
}

void QuestionEditor::on_actionOtw_rz_triggered() {
    QString filename = QFileDialog::getOpenFileName(this,
						    tr("Wybierz plik z pytaniami"),
						    QDir::currentPath(),
						    "Pytania (*.txt);;Wszystkie pliki (*)");
    if (filename.isEmpty()) {
	return;
    }
    QFile questions(filename);

    QFileInfo info(questions);

    if (!info.isFile()) {
	qCritical() << trUtf8("Plik %1 jest niepoprawny").arg(filename);
	return;
    } else if (!info.isReadable()) {
	qCritical() << trUtf8("Plik %1 nie nadaje się do odczytu").arg(filename);
	return;
    } else if (!questions.open(QFile::Text | QFile::ReadOnly)) {
	qCritical() << trUtf8("Nie można otworzyć pliku %1 !").arg(filename);
	return;
    }

    QTextStream ts(&questions);

    while (ui->stackedWidget->count()) {
	Question *q = static_cast<Question*>(ui->stackedWidget->widget(0));
	ui->stackedWidget->removeWidget(q);
	delete q;
    }

    while (!ts.atEnd()) {
	QString line = ts.readLine();
	QStringList bum = line.split("|", QString::KeepEmptyParts);

	on_newQuestion_clicked();

	int index = ui->stackedWidget->count() - 1;
	Question *q = static_cast<Question*>(ui->stackedWidget->widget(index));
	q->setText(bum[0]);
	q->setCorrectAnswer(bum[1].toUInt());
	q->setAnswerA(bum[2]);
	q->setAnswerB(bum[3]);
	q->setAnswerC(bum[4]);
    }
}
