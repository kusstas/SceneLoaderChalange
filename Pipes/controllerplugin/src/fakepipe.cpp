/* Copyright (C) Freeman - All Rights Reserved
 */

#include "fakepipe.h"

namespace pipe
{
FakePipe::FakePipe(QObject* parent)
    : Pipe(parent)
{
}

int FakePipe::interval() const
{
    return m_interval;
}

QVariantList const& FakePipe::rawData() const
{
    return m_rawData;
}

bool FakePipe::once() const
{
    return m_once;
}

bool FakePipe::running() const
{
    return m_running;
}

void FakePipe::setInterval(int interval)
{
    if (m_interval == interval)
    {
        return;
    }

    m_interval = interval;
    emit intervalChanged(m_interval);

    if (m_timer_id != 0)
    {
        // kill old timer
        killTimer(m_timer_id);
    }
    if (running())
    {
        m_timer_id = startTimer(m_interval);
    }
}

void FakePipe::setRawData(QVariantList const& rawData)
{
    if (m_rawData == rawData)
    {
        return;
    }

    m_rawData = rawData;
    m_iterator = m_rawData.begin();

    if (running())
    {
        // send begin data
        timerEvent(nullptr);
    }

    emit rawDataChanged(m_rawData);
}

void FakePipe::setRunning(bool running)
{
    if (m_running == running)
    {
        return;
    }

    if (m_timer_id != 0)
    {
        killTimer(m_timer_id);
        m_timer_id = 0;
    }

    if (running)
    {
        m_timer_id = startTimer(m_interval);
        // send first data
        timerEvent(nullptr);
    }

    m_running = running;
    emit runningChanged(m_running);
}

void FakePipe::setOnce(bool once)
{
    if (m_once == once)
    {
        return;
    }

    m_once = once;
    emit onceChanged(m_once);
}

void FakePipe::defaultOnceValue()
{
    m_once = false;
}

void FakePipe::defaultRuningValue()
{
    m_running = true;
}

void FakePipe::timerEvent(QTimerEvent*)
{
    if (m_iterator == m_rawData.end())
    {
        return;
    }

    emit send(*m_iterator);

    ++m_iterator;
    if (m_iterator == m_rawData.end())
    {
        m_iterator = m_rawData.begin();
        if(m_once)
        {
            killTimer(m_timer_id);
            m_timer_id = 0;
        }
    }
}
}
