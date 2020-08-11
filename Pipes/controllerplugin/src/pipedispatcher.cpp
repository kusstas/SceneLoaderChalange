/* Copyright (C) Freeman - All Rights Reserved
 */

#include "pipedispatcher.h"
#include "dataocean.h"
#include "pipe.h"

#include <QDebug>
#include <cassert>

namespace pipe
{
PipeDispatcher::PipeDispatcher(DataOcean* ocean, QObject* parent)
    : QObject(parent)
    , m_ocean(ocean)
{
    assert(m_ocean);
}

void PipeDispatcher::registerPipe(Pipe* pipe)
{
    if (!m_pipes.contains(pipe->name()))
    {
        m_pipes.insert(pipe->name(), {});
    }

    m_pipes[pipe->name()].append(pipe);
    connect(pipe, &QObject::destroyed, this, &PipeDispatcher::deleteFromPipes);
    connect(pipe, &Pipe::storagedChanged, this, &PipeDispatcher::storagedPipeChanged);

    if (pipe->storaged())
    {
        storagePipe(pipe);
    }

    for (auto const& subscriber : m_subscribes.value(pipe->name()))
    {
        qDebug().nospace() << "Connect sender: " << pipe << " " << pipe->name()
                           << " with subscriber: " << subscriber << " " << subscriber->name();
        connect(pipe, &Pipe::send, subscriber, &Pipe::onReceive);
    }
}

void PipeDispatcher::subscribePipe(Pipe* pipe)
{
    if (pipe->subscribes().isEmpty())
    {
        return;
    }

    connect(pipe, &QObject::destroyed, this, &PipeDispatcher::deleteFromSubscribes);

    for (auto const& subcribeName : pipe->subscribes())
    {
        if (!m_subscribes.contains(subcribeName))
        {
            m_subscribes.insert(subcribeName, {});
        }

        m_subscribes[subcribeName].append(pipe);

        auto initialValue = pipe->get(subcribeName);
        if (initialValue.isValid())
        {
            qDebug() << "Receive initial value for:" << pipe << pipe->name()
                     << "source:" << subcribeName << "value:" << initialValue;
            emit pipe->initialValueExists(subcribeName, initialValue);
        }

        for (auto const& subcribe : m_pipes.value(subcribeName))
        {
            qDebug().nospace() << "Connect subscriber: " << pipe << " " << pipe->name()
                               << " with sender: " << subcribe << " " << subcribe->name();
            connect(subcribe, &Pipe::send, pipe, &Pipe::onReceive);
        }
    }
}

void PipeDispatcher::storagePipe(Pipe* pipe)
{
    qDebug() << "Connect:" << pipe << pipe->name() << "with data ocean";
    connect(pipe, &Pipe::send, m_ocean, &DataOcean::onReceive);
}

void PipeDispatcher::unstoragePipe(Pipe* pipe)
{
    qDebug() << "Disconnect:" << pipe << pipe->name() << "from data ocean";
    disconnect(pipe, &Pipe::send, m_ocean, &DataOcean::onReceive);
}

void PipeDispatcher::storagedPipeChanged(bool storaged)
{
    Pipe* pipe = qobject_cast<Pipe*>(sender());

    if (pipe)
    {
        if (storaged)
        {
            storagePipe(pipe);
        }
        else
        {
            unstoragePipe(pipe);
        }
    }
}

void PipeDispatcher::deleteFromPipes(QObject* obj)
{
    Pipe* pipe = qobject_cast<Pipe*>(obj);

    if (pipe)
    {
        if (m_pipes.contains(pipe->name()))
        {
            auto& pipes = m_pipes[pipe->name()];

            pipes.removeAll(pipe);

            if (pipes.isEmpty())
            {
                m_pipes.remove(pipe->name());
            }
        }
    }
}

void PipeDispatcher::deleteFromSubscribes(QObject* obj)
{
    Pipe* pipe = qobject_cast<Pipe*>(obj);

    if (pipe)
    {
        for (auto const& subscribeName : pipe->subscribes())
        {
            if (m_subscribes.contains(subscribeName))
            {
                auto& subscribes = m_subscribes[subscribeName];

                subscribes.removeAll(pipe);

                if (subscribes.isEmpty())
                {
                    m_subscribes.remove(subscribeName);
                }
            }
        }
    }
}
}
