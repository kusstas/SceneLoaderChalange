/* Copyright (C) Freeman - All Rights Reserved
 */

#include "dataocean.h"
#include "pipe.h"

namespace pipe
{
DataOcean::DataOcean(QObject* parent)
    : QObject(parent)
{
}

void DataOcean::remove(QString const& name)
{
    m_data.remove(name);
}

QVariant DataOcean::get(QString const& name) const
{
    return m_data.value(name, QVariant());
}

void DataOcean::onReceive(QVariant const& data)
{
    Pipe* source = qobject_cast<Pipe*>(sender());
    m_data[source->name()] = data;
}
}
