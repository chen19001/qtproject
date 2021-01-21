#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include "qstring.h"
#include "qvector.h"

enum eCol
{
    eCol_datefrom = 1,
    eCol_dateto,
    eCol_channelname,
    eCol_channelstarttime,
    eCol_id,
    eCol_programmetitle,
    eCol_programmenumber,
    eCol_episodetitle,
    eCol_episodenumber,
    eCol_seriesnumber,
    eCol_yearofrelease,
    eCol_director,
    eCol_castname,
    eCol_scheduledate,
    eCol_schedulestarttime,
    eCol_scheduleendtime,
    eCol_classification,
    eCol_synopsis_1,
    eCol_synopsis_2,
    eCol_synopsis_3,
    eCol_genre,
    eCol_colour,
    eCol_country,
    eCol_language,
};

template <typename T>
void ClearPointerVector(QVector<T*>& ar)
{
    for (int i = 0; i < (int)ar.size(); i++)
    {
        if (ar[i] != NULL)
        {
            delete ar[i];
            ar[i] = NULL;
        }
    }
    ar.clear();
    ar.squeeze();
}

struct schedule
{
    //attribute
    QString m_id;

    //child
    QString m_programmetitle;
    QString m_programmenumber;
    QString m_episodetitle;
    QString m_episodenumber;
    QString m_seriesnumber;
    QString m_yearofrelease;
    QString m_director;
    QString m_castname;
    QString m_scheduledate;
    QString m_schedulestarttime;
    QString m_scheduleendtime;
    QString m_classification;
    QString m_synopsis_1;
    QString m_synopsis_2;
    QString m_synopsis_3;
    QString m_genre;
    QString m_colour;
    QString m_country;
    QString m_language;
};

typedef QVector<schedule*> ScheduleVector;

struct synergytoepg
{
    synergytoepg();
    ~synergytoepg();

    //attribute
    QString m_xmlns = QString("http://SourceSytem.Hostname.Interfaces/folder/1.0");
    QString m_xmlns_xsi = QString("http://www.w3.org/2001/XMLSchema-instance");

    //child
    QString m_datefrom;
    QString m_dateto;
    QString m_channelname;
    QString m_channelstarttime;

    ScheduleVector m_schedule;

    void clear();
    void readFromXlsx(const QString& strFile);
    bool writeToXML(const QString& strFile);
};


#endif // DATASTRUCT_H
