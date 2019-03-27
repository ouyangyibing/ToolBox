#include "regexp.h"
#include "ui_regexp.h"
#include "myassistant.h"

#include <QDir>
#include <QDebug>
#include <QClipboard>
#include <QFileDialog>
#include <QRegularExpression>

namespace  {

const QString configPath = "./Configuration/RegExp/";

QString patternToCode(QString pattern)
{
    pattern.replace(QStringLiteral("\\"), QStringLiteral("\\\\"));
    pattern.replace(QStringLiteral("\""), QStringLiteral("\\\""));
    return pattern;
}

void writeConfigFile(QString txt,QString name)
{
    if(!QFile::exists(configPath)) {
        QDir().mkpath(configPath);
    }

    QFile file(configPath + name);
    if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        file.write(txt.toLocal8Bit());
    }
    file.close();
}

QString readConfigFile(QString name)
{
    QString buf;
    QString path = QString("%1%2").arg(configPath, name);
    if(!my::readFile(path, buf)) {
        qDebug()<< "该文件打开失败: " << path << endl;
        return "";
    }
    return buf;
}

}
//namespace end
RegExp* RegExp::self = nullptr;

RegExp::RegExp(QWidget *parent) :
    PluginWidget(parent),
    ui(new Ui::RegExp)
{
    ui->setupUi(this);

    self = this;

    connect(ui->refresh, &QToolButton::clicked, this, &RegExp::slot_regExp);
    connect(ui->patternLineEdit, &QLineEdit::textChanged, this, &RegExp::slot_regExp);
    connect(ui->subjectPlainTextEdit, &QPlainTextEdit::textChanged, this, &RegExp::slot_regExp);
    connect(ui->clearSubjectBtn, &QToolButton::clicked, ui->subjectPlainTextEdit, &QPlainTextEdit::clear);

    connect(ui->cpPatternBtn, &QToolButton::clicked, [&]{
        QGuiApplication::clipboard()->setText(ui->patternLineEdit->text());
    });

    connect(ui->cpEscapedPatternBtn, &QToolButton::clicked, [&]{
        QGuiApplication::clipboard()->setText(ui->escapedPatternLabel->text());
    });

    ui->patternLineEdit->setText(readConfigFile("pattern.txt"));
    ui->subjectPlainTextEdit->setPlainText(readConfigFile("subject.txt"));
}

RegExp::~RegExp()
{
    writeConfigFile(ui->patternLineEdit->text(),"pattern.txt");
    writeConfigFile(ui->subjectPlainTextEdit->toPlainText(),"subject.txt");

    delete ui;
}

RegExp *RegExp::newObj()
{
    return staticNewObj();
}


RegExp *RegExp::staticNewObj()
{
    static bool flag = false;

    if(flag) {
        return new RegExp();

    } else {
        flag = true;
        return self;
    }
}


void RegExp::slot_regExp()
{
    QString sourceData = ui->subjectPlainTextEdit->toPlainText();
    QString pattern  = ui->patternLineEdit->text();

    ui->matchResult->clear();
    ui->countLab->setText(QString("%1").arg(0));
    ui->escapedPatternLabel->setText(patternToCode(pattern));

    if(sourceData.isEmpty() || pattern.isEmpty()) {
        return;
    }

    QRegularExpression rx(pattern);
    QStringList texts = rx.match(sourceData).capturedTexts();

    if(texts.isEmpty()) {
        ui->patternLineEdit->setStyleSheet("color: rgb(255, 0, 0);");
        return ;

    } else {
        ui->patternLineEdit->setStyleSheet("color: rgb(0, 0, 0);");
    }

    int count = 0;
    for(QString text : texts) {
        ui->matchResult->appendPlainText(QString("第 %1 个匹配:").arg(count));
        ui->matchResult->appendPlainText(text);
        ui->matchResult->appendPlainText("");
        count++;
    }
    ui->countLab->setText(QString("%1").arg(count));
}

void RegExp::on_openFile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        ui->subjectPlainTextEdit->setPlainText(file.readAll());
    }
    file.close();
}
