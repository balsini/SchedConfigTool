#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlmanager.hpp"

#include <QDebug>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  about.hide();

  ui->lineEditParallelization->setValidator(new QIntValidator(this));
  ui->lineEditRuns->setValidator(new QIntValidator(this));
  //ui->lineEditPriority->setValidator(new QIntValidator(this));

  ui->plainEditorTab->setCurrentIndex(0);

  filename = "";
  updateTitle();

  changedParameter();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::changedParameter()
{
    qDebug() << "changedParameter()";

  ExperimentParameter sp;

  sp.setParallel(ui->lineEditParallelization->text().toLong());
  sp.setRuns(ui->lineEditRuns->text().toLong());
  sp.setPeriod(ui->lineEditPeriod->text().toLong());

  /*
      sp.setParam(ui->lineEditParallelization->text().toLong(),
                  ui->lineEditRuns->text().toLong());
                  */
  ui->plainXMLEditor->setPlainText(constructXMLString(sp));
}

void MainWindow::updateGUIParameters(const ExperimentParameter &sp)
{
  qDebug() << "Updating GUI parameters";

  if (sp.isValid()) {
        ui->lineEditParallelization->setText(QString::number(sp.getParallelization()));
        ui->lineEditRuns->setText(QString::number(sp.getRuns()));
        ui->lineEditPeriod->setText(QString::number(sp.getPeriod()));
  }
}

void MainWindow::changedXML()
{
  qDebug() << "changedXML()";
  //if (validXML())
  updateGUIParameters(parseXMLString(ui->plainXMLEditor->toPlainText()));
}

void MainWindow::on_actionQuit_triggered()
{
  this->close();
}

void MainWindow::on_actionAbout_triggered()
{
  about.show();
}

bool MainWindow::validJSON()
{
  /////////////////////
  /// TODO
  /////////////////////

  return true;
}

/*
bool MainWindow::validXML()
{
  QFile schemaFile(":/xsd/schema.xsd");
  if (!schemaFile.open(QIODevice::ReadOnly)) {
    qDebug() << "Error while opening XML Schema";
    exit(1);
  }

  const QByteArray schemaData = schemaFile.readAll();
  const QByteArray instanceData = ui->plainXMLEditor->toPlainText().toUtf8();

  //QString str;
  //str.append(schemaData);
  //qDebug() << str;

  MessageHandler messageHandler;

  QXmlSchema schema;
  schema.setMessageHandler(&messageHandler);

  schema.load(schemaData);

  bool errorOccurred = false;
  if (!schema.isValid()) {
    errorOccurred = true;
  } else {
    QXmlSchemaValidator validator(schema);
    if (!validator.validate(instanceData))
      errorOccurred = true;
  }

  if (errorOccurred) {
    ui->validationStatus->setText(messageHandler.statusMessage());
    moveCursor(messageHandler.line(), messageHandler.column());
  } else {
    ui->validationStatus->setText(tr("Validation successful"));
    QList<QTextEdit::ExtraSelection> extraSelections;
    ui->plainXMLEditor->setExtraSelections(extraSelections);
  }

  return !errorOccurred;
}
*/

void MainWindow::moveCursor(int line, int column)
{
  QPlainTextEdit * instanceEdit = ui->plainXMLEditor;
  QColor lineColor = QColor(Qt::red).lighter(160);

  instanceEdit->moveCursor(QTextCursor::Start);
  for (int i=1; i<line; ++i)
    instanceEdit->moveCursor(QTextCursor::Down);
  for (int i=1; i<column; ++i)
    instanceEdit->moveCursor(QTextCursor::Right);

  QList<QTextEdit::ExtraSelection> extraSelections;
  QTextEdit::ExtraSelection selection;

  selection.format.setBackground(lineColor);
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = instanceEdit->textCursor();
  selection.cursor.clearSelection();
  extraSelections.append(selection);

  instanceEdit->extraSelections().clear();
  instanceEdit->setExtraSelections(extraSelections);

  instanceEdit->setFocus();
}

void MainWindow::updateTitle()
{
  QString t = "Sched Config Tool";
  if (filename.length() > 0) {
    t.append(" - ");
    t.append(filename);
  }
  this->setWindowTitle(t);
}

void MainWindow::on_actionOpen_triggered()
{
  QString tmpfilename = QFileDialog::getOpenFileName(
                          this,
                          tr("Open File"),
                          "./",
                          "XML File (*.xml);;JSON File (*.json);;Text File (*.txt)"
                          );

  QFile openFile(tmpfilename);
  if (openFile.open(QIODevice::ReadOnly)) {
    filename = tmpfilename;
    ui->statusbar->showMessage("Opened: " + filename);
    ui->plainXMLEditor->setPlainText(openFile.readAll());
    updateTitle();
    openFile.close();
  } else {
    qDebug() << "Error while opening file";
  }
}

void MainWindow::saveTo(const QString &tmpfilename) {
  QFile openFile(tmpfilename);
  if (openFile.open(QIODevice::WriteOnly)) {
    filename = tmpfilename;
    ui->statusbar->showMessage("Saved: " + filename);

    if (tmpfilename.right(4) == ".xml")
      openFile.write(ui->plainXMLEditor->toPlainText().toUtf8());

    updateTitle();
    openFile.close();
  } else {
    qDebug() << "Error while opening file";
  }
}

void MainWindow::on_actionSave_As_triggered()
{
  QString tmpfilename = QFileDialog::getSaveFileName(
                          this,
                          tr("Save File"),
                          "./",
                          "XML File (*.xml);;JSON File (*.json);;Text File (*.txt)"
                          );
  saveTo(tmpfilename);
}

void MainWindow::on_actionSave_triggered()
{
  QString tmpfilename = filename;
  if (filename.length() == 0) {
    tmpfilename = QFileDialog::getSaveFileName(
                    this,
                    tr("Save File"),
                    "./",
                    "XML File (*.xml);;JSON File (*.json);;Text File (*.txt)"
                    );
  }
  saveTo(tmpfilename);
}
