#include "datastruct.h"
#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include <QFile>
#include <QtXml\QtXml>
#include <QtXml\QDomDocument>

synergytoepg::synergytoepg()
{
    clear();
}

synergytoepg::~synergytoepg()
{
    clear();
}

void synergytoepg::clear()
{
    ClearPointerVector(m_schedule);
}

void synergytoepg::readFromXlsx(const QString &strFile)
{
    QXlsx::Document xlsx(strFile);
    QXlsx::Workbook *workBook = xlsx.workbook();
    if(workBook != nullptr)
    {
        QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(0));

        int firstRow = workSheet->dimension().firstRow();
        int lastRow = workSheet->dimension().lastRow();
        int firstColumn = workSheet->dimension().firstColumn();
        int lastColumn = workSheet->dimension().lastColumn();

        for (int i = firstRow; i <= lastRow; i++)
        {
            if(i == 1)
            {
                for (int j = firstColumn; j <= lastColumn; j++)
                {
                    QXlsx::Cell *cell = workSheet->cellAt(i, j);
                    if (cell==nullptr)
                        continue;

                    eCol col = (eCol)j;
                    switch (col)
                    {
                    case eCol_datefrom:
                        m_datefrom = cell->value().toString();
                    break;
                    case eCol_dateto:
                        m_dateto = cell->value().toString();
                    break;
                    case eCol_channelname:
                        m_channelname = cell->value().toString();
                    break;
                    case eCol_channelstarttime:
                        m_channelstarttime = cell->value().toString();
                    break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                schedule* p = new schedule;
                m_schedule.append(p);

                for (int j = firstColumn; j <= lastColumn; j++)
                {
                    QXlsx::Cell *cell = workSheet->cellAt(i, j);
                    if (cell==nullptr)
                        continue;

                    eCol col = (eCol)j;
                    switch (col)
                    {
                    case eCol_id:
                        p->m_id = cell->value().toString();
                    break;
                    case eCol_programmetitle:
                        p->m_programmetitle = cell->value().toString();
                    break;
                    case eCol_programmenumber:
                        p->m_programmenumber = cell->value().toString();
                    break;
                    case eCol_episodetitle:
                        p->m_episodetitle = cell->value().toString();
                    break;
                    case eCol_episodenumber:
                        p->m_episodenumber = cell->value().toString();
                    break;
                    case eCol_seriesnumber:
                        p->m_seriesnumber = cell->value().toString();
                    break;
                    case eCol_yearofrelease:
                        p->m_yearofrelease = cell->value().toString();
                    break;
                    case eCol_director:
                        p->m_director = cell->value().toString();
                    break;
                    case eCol_castname:
                        p->m_castname = cell->value().toString();
                    break;
                    case eCol_scheduledate:
                        p->m_scheduledate = cell->value().toString();
                    break;
                    case eCol_schedulestarttime:
                        p->m_schedulestarttime = cell->value().toString();
                    break;
                    case eCol_scheduleendtime:
                        p->m_scheduleendtime = cell->value().toString();
                    break;
                    case eCol_classification:
                        p->m_classification = cell->value().toString();
                    break;
                    case eCol_synopsis_1:
                        p->m_synopsis_1 = cell->value().toString();
                    break;
                    case eCol_synopsis_2:
                        p->m_synopsis_2 = cell->value().toString();
                    break;
                    case eCol_synopsis_3:
                        p->m_synopsis_3 = cell->value().toString();
                    break;
                    case eCol_genre:
                        p->m_genre = cell->value().toString();
                    break;
                    case eCol_colour:
                        p->m_colour = cell->value().toString();
                    break;
                    case eCol_country:
                        p->m_country = cell->value().toString();
                    break;
                    case eCol_language:
                        p->m_language = cell->value().toString();
                    break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void addChildElement(QDomDocument& doc, QDomElement& parent, const QString& name, const QString& value)
{
    QDomElement element = doc.createElement(name);
    parent.appendChild(element);
    QDomText text = doc.createTextNode(value);
    element.appendChild(text);
}

bool synergytoepg::writeToXML(const QString &strFile)
{
    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("synergytoepg");
    doc.appendChild(root);
    root.setAttribute(QString("xmlns"), m_xmlns);
    root.setAttribute(QString("xmlns:xsi"), m_xmlns_xsi);

    addChildElement(doc, root, QString("datefrom"), m_datefrom);
    addChildElement(doc, root, QString("dateto"), m_dateto);
    addChildElement(doc, root, QString("channelname"), m_channelname);
    addChildElement(doc, root, QString("channelstarttime"), m_channelstarttime);

    for(auto item : m_schedule)
    {
        if (item != nullptr)
        {
            QDomElement schedule = doc.createElement("schedule");
            root.appendChild(schedule);
            schedule.setAttribute(QString("id"), item->m_id);

            addChildElement(doc, schedule, QString("programmetitle"), item->m_programmetitle);
            addChildElement(doc, schedule, QString("programmenumber"), item->m_programmenumber);
            addChildElement(doc, schedule, QString("episodetitle"), item->m_episodetitle);
            addChildElement(doc, schedule, QString("episodenumber"), item->m_episodenumber);
            addChildElement(doc, schedule, QString("seriesnumber"), item->m_seriesnumber);
            addChildElement(doc, schedule, QString("yearofrelease"), item->m_yearofrelease);
            addChildElement(doc, schedule, QString("directorname"), item->m_director);
            addChildElement(doc, schedule, QString("castname"), item->m_castname);
            addChildElement(doc, schedule, QString("scheduledate"), item->m_scheduledate);
            addChildElement(doc, schedule, QString("schedulestarttime"), item->m_schedulestarttime);
            addChildElement(doc, schedule, QString("scheduleendtime"), item->m_scheduleendtime);
            addChildElement(doc, schedule, QString("classification"), item->m_classification);
            addChildElement(doc, schedule, QString("synopsis1"), item->m_synopsis_1);
            addChildElement(doc, schedule, QString("synopsis2"), item->m_synopsis_2);
            addChildElement(doc, schedule, QString("synopsis3"), item->m_synopsis_3);
            addChildElement(doc, schedule, QString("genre"), item->m_genre);
            addChildElement(doc, schedule, QString("colour"), item->m_colour);
            addChildElement(doc, schedule, QString("country"), item->m_country);
            addChildElement(doc, schedule, QString("language"), item->m_language);
        }
    }

    QFile file(strFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    doc.normalize();
    doc.save(out, 4, QDomNode::EncodingFromTextStream);
    file.close();
    return true;
}
