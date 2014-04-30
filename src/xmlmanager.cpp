#include "xmlmanager.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

void parseFeedback(QXmlStreamReader &xml, SchedParameter &sp)
{
  qDebug("Found QoS_Feedback Configuration");

  bool setResponseTime = false;

  sp.setType(QoS_Feedback);
  while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
           xml.name() == "SchedulingAlgorithm")) {
    if(xml.tokenType() == QXmlStreamReader::StartElement) {
      if (xml.name() == "responsetime") {
        xml.readNext();
        sp.setResponseTime(xml.text().toString().toLong());
        setResponseTime = true;
      }
    }
    xml.readNext();
  }

  if (!setResponseTime)
    sp.setResponseTime(0);

  sp.isValid(true);
}

void parseDL(QXmlStreamReader &xml, SchedParameter &sp)
{
  qDebug("Found SCHED_DEADLINE Configuration");

  bool setPeriod = false;
  bool setDeadline = false;
  bool setRunTime = false;
  bool setPriority = false;

  sp.setType(SCHED_DEADLINE);
  while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
           xml.name() == "SchedulingAlgorithm")) {
    if(xml.tokenType() == QXmlStreamReader::StartElement) {
      if (xml.name() == "period") {
        xml.readNext();
        sp.setPeriod(xml.text().toString().toLong());
        setPeriod = true;
      } else if (xml.name() == "runtime") {
        xml.readNext();
        sp.setRunTime(xml.text().toString().toLong());
        setRunTime = true;
      } else if (xml.name() == "deadline") {
        xml.readNext();
        sp.setDeadline(xml.text().toString().toLong());
        setDeadline = true;
      } else if (xml.name() == "priority") {
        xml.readNext();
        sp.setPriority(xml.text().toString().toLong());
        setPriority = true;
      }
    }
    xml.readNext();
  }

  if (!setPeriod)
    sp.setPeriod(0);
  if (!setDeadline)
    sp.setDeadline(0);
  if (!setRunTime)
    sp.setRunTime(0);
  if (!setPriority)
    sp.setPriority(0);

  sp.isValid(true);
}

SchedParameter parseXMLString(const QString &str)
{
  SchedParameter sp;
  QXmlStreamReader xml(str);

  while (!xml.atEnd()) {
    QXmlStreamReader::TokenType token = xml.readNext();

    if(token == QXmlStreamReader::StartDocument) {
      continue;
    }

    if(token == QXmlStreamReader::StartElement) {

      if(xml.name() == "SchedulingAlgorithm") {
        if (xml.attributes().value("name") == "SCHED_DEADLINE")
          parseDL(xml, sp);
        else if (xml.attributes().value("name") == "QoS_Feedback")
          parseFeedback(xml, sp);
      }
    }
  }
  if (xml.hasError()) {
    //if (xml.error() == QXmlStreamReader::NotWellFormedError)
    //    ui->statusbar->showMessage(tr("XML Document is not well-formed"));
    sp.isValid(false);
  } else {
    //ui->statusbar->showMessage(tr("XML Modifications updated"));
  }

  return sp;
}

QString constructXMLString(const SchedParameter &sp)
{
  QString xmlString;
  QXmlStreamWriter stream(&xmlString);

  stream.setAutoFormatting(true);

  stream.writeStartDocument();
  stream.writeStartElement("SchedulingAlgorithm");

  switch (sp.getType()) {
    case SCHED_DEADLINE:
      stream.writeAttribute("name", "SCHED_DEADLINE");
      stream.writeTextElement("period", QString::number(sp.getPeriod()));
      stream.writeTextElement("deadline", QString::number(sp.getDeadline()));
      stream.writeTextElement("runtime", QString::number(sp.getRunTime()));
      stream.writeTextElement("priority", QString::number(sp.getPriority()));
      break;
    case QoS_Feedback:
      stream.writeAttribute("name", "QoS_Feedback");
      stream.writeTextElement("responsetime", QString::number(sp.getResponseTime()));
      break;
    default: break;
  }

  stream.writeEndElement();
  stream.writeEndDocument();

  return xmlString;
}
