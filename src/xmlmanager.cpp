#include <QDebug>

#include "xmlmanager.hpp"

#include <QDomDocument>
#include <QXmlStreamWriter>

void parseXML(QDomDocument &xml, ExperimentParameter &sp)
{
    QDomElement docElem = xml.documentElement();

    sp.setParallel(docElem.attribute("proc", "4").toLong());
    sp.setRuns(docElem.attribute("runs", "100").toLong());

    qDebug() << "Proc values:" << sp.getParallelization();
    qDebug() << "Runs values:" << sp.getRuns();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {

            if (e.tagName() == "period") {
                sp.setPeriod(e.text().toLong());
                qDebug() << "Trovato Period, che vale " << e.text(); // the node really is an element.
            }
        }
        n = n.nextSibling();
    }
/*
*/
    /*
    while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
             xml.name() == "simulation")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "runs") {
                xml.readNext();
                sp.setRuns(xml.text().toString().toLong());
                setRuns = true;
            } else if (xml.name() == "proc") {
                xml.readNext();
                sp.setParallilation(xml.text().toString().toLong());
                setParallelization = true;
            }/* else if (xml.name() == "deadline") {
                xml.readNext();
                sp.setDeadline(xml.text().toString().toLong());
                setDeadline = true;
                //} else if (xml.name() == "priority") {
                //  xml.readNext();
                //  sp.setPriority(xml.text().toString().toLong());
                //  setPriority = true;
            } else if (xml.name() == "path") {
                xml.readNext();
                sp.setPath(xml.text().toString());
                setPath = true;
            } else if (xml.name() == "args") {
                xml.readNext();
                sp.setArgs(xml.text().toString());
                setArgs = true;
            }
        }
        xml.readNext();
    }
    /*
    if (!setPeriod)
        sp.setPeriod(0);
    if (!setDeadline)
        sp.setDeadline(0);
    if (!setRunTime)
        sp.setRunTime(0);
    if (!setPath)
        sp.setPath("");
    if (!setArgs)
        sp.setArgs("");
*/
    sp.isValid(true);
}

ExperimentParameter parseXMLString(const QString &str)
{
    ExperimentParameter sp;
    QDomDocument xml;
    xml.setContent(str);

    parseXML(xml, sp);

    return sp;
}

QString constructXMLString(const ExperimentParameter &sp)
{
    QString xmlString;
    QXmlStreamWriter stream(&xmlString);

    stream.setAutoFormatting(true);

    stream.writeStartDocument();
    stream.writeStartElement("simulator");

    stream.writeAttribute("type", "FPGA");
    stream.writeAttribute("proc", QString::number(sp.getParallelization()));
    stream.writeAttribute("runs", QString::number(sp.getRuns()));

    stream.writeTextElement("period", QString::number(sp.getPeriod()));

    stream.writeEndElement();
    stream.writeEndDocument();

    return xmlString;
}
