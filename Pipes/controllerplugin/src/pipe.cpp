/* Copyright (C) Freeman - All Rights Reserved
 */

#include "pipe.h"
#include "pipedispatcher.h"
#include "dataocean.h"

#include <QDebug>

namespace pipe
{
QSharedPointer<PipeDispatcher> Pipe::pipeDispatcher = nullptr;
QSharedPointer<DataOcean> Pipe::dataOcean = nullptr;

Pipe::Pipe(QObject* parent):
    QObject(parent)
{
    if (dataOcean == nullptr)
    {
        dataOcean.reset(new DataOcean());
    }

    if (pipeDispatcher == nullptr)
    {
        pipeDispatcher.reset(new PipeDispatcher(dataOcean.get()));
    }
}

QString const& Pipe::name() const
{
    return m_name;
}

QStringList const& Pipe::subscribes() const
{
    return m_subscribes;
}

bool Pipe::storaged() const
{
    return m_storaged;
}

QVariant Pipe::get(QString const& name) const
{
    return dataOcean->get(name);
}

void Pipe::setName(QString const& name)
{
    if (m_nameRegistered)
    {
        qWarning().nospace() << "Cannot reassign name of pipe. Current pipe name: " << m_name
                             << ", ordered name: " << name << ". Assigning new name will be ignored";
        return;
    }

    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
        pipeDispatcher->registerPipe(this);
        m_nameRegistered = true;
    }
}

void Pipe::setSubscribes(QStringList const& subscribes)
{
    if (m_subscribesRegistered)
    {
        qWarning().nospace() << "Cannot reassign subscribes of pipe. Pipe name: " << m_name
                             << ", subscribes: " << m_subscribes
                             << ", ordered subscribes: " << subscribes
                             << ". Assigning new subscribes will be ignored";
        return;
    }

    if (m_subscribes != subscribes)
    {
        m_subscribes = subscribes;
        emit subscribesChanged(m_subscribes);
        pipeDispatcher->subscribePipe(this);
        m_subscribesRegistered = true;
    }
}

void Pipe::setStoraged(bool storaged)
{
    if (m_storaged == storaged)
    {
        return;
    }

    m_storaged = storaged;
    emit storagedChanged(m_storaged);
}

void Pipe::onReceive(QVariant const& data)
{
    Pipe* source = qobject_cast<Pipe*>(sender());
    if (source)
    {
        emit receive(source->moduleName(),source->name(), data);
    }
}
}
