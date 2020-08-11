/* Copyright (C) Freeman - All Rights Reserved
 */

#pragma once

#include <QObject>
#include <QVariant>
#include <QHash>

namespace pipe
{
/*!
    \class DataOcean
    \brief The DataOcean class
    \since 1.0
 */
class DataOcean : public QObject
{
    Q_OBJECT

public:
    explicit DataOcean(QObject* parent = nullptr);

    /*!
     * \brief remove value from data by name
     * \param name is key
     */
    void remove(QString const& name);

    /*!
     * \brief get data be key from ocean
     * \param name is key
     * \return value, if key not exists, return invalid value
     */
    QVariant get(QString const& name) const;

public slots:
    /*!
     * \brief receive data from storaged pipe and save this
     * \param data
     */
    void onReceive(QVariant const& data);

private:
    QHash<QString, QVariant> m_data = {};
};
}
