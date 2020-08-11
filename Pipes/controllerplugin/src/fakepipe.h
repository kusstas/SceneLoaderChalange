/* Copyright (C) Freeman - All Rights Reserved
 */

#pragma once

#include "pipe.h"

namespace pipe
{
/*!
    \class FakePipe
    \brief The FakePipe class is pipe which sends cycled raw data with interval
    \since 1.0
 */
class FakePipe : public Pipe
{
    Q_OBJECT
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(QVariantList rawData READ rawData WRITE setRawData NOTIFY rawDataChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged RESET defaultRuningValue)
    Q_PROPERTY(bool once READ once WRITE setOnce NOTIFY onceChanged RESET defaultOnceValue)

public:
    /*!
        Constructs a pipe with parent object \a parent.
     */
    explicit FakePipe(QObject* parent = nullptr);

    /*!
     * \brief interval sending of data
     * \property FakePipe::interval
     * \return inverval
     */
    int interval() const;

    /*!
     * \brief raw data for sending
     * \property FakePipe::rowData
     * \return raw data
     */
    QVariantList const& rawData() const;

    /*!
     * \brief running state of pipe
     * \return running
     */
    bool running() const;

    /*!
     * \brief if true sending data will be stopped at end of array
     * \return once
     */
    bool once() const;

signals:
    void intervalChanged(int interval);
    void rawDataChanged(QVariantList const& rawData);
    void runningChanged(bool running);
    void onceChanged(bool once);

public slots:
    /*!
     * \brief set interval sending of data
     * \property FakePipe::interval
     * \details emit intervalChanged
     * \param interval
     */
    void setInterval(int interval);

    /*!
     * \brief set raw data for sending
     * \property FakePipe::rowData
     * \details emit rowDataChanged
     * \param raw data
     */
    void setRawData(QVariantList const& rawData);

    /*!
     * \brief set state sending of data
     * \param running
     */
    void setRunning(bool running);

    /*!
     * \brief set loop of sending data
     * \param once
     */
    void setOnce(bool once);

    /*!
     * \brief reset property "once"
     */
    void defaultOnceValue();

    /*!
     *  \brief reset property "running"
     */
    void defaultRuningValue();

protected:
    void timerEvent(QTimerEvent*) override;

private:
    int m_timer_id = 0;
    int m_interval = 1000;
    QVariantList m_rawData = {};
    QVariantList::const_iterator m_iterator = m_rawData.begin();
    bool m_running = true;
    bool m_once = false;
};
}
