/* Copyright (C) Freeman - All Rights Reserved
 */

#pragma once

#include <QObject>
#include <QVariant>
#include <QSharedPointer>

namespace pipe
{
class PipeDispatcher;
class DataOcean;

/*!
    \class Pipe
    \brief The Pipe class is transfer class for events and data
    \since 1.0
*/
class Pipe : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Pipe)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString moduleName READ moduleName WRITE setModuleName NOTIFY moduleNameChanged)
    Q_PROPERTY(QStringList subscribes READ subscribes WRITE setSubscribes NOTIFY subscribesChanged)
    Q_PROPERTY(bool storaged READ storaged WRITE setStoraged NOTIFY storagedChanged)

public:
    /*!
        Constructs a pipe with parent object \a parent.
     */
    Pipe(QObject* parent = nullptr);

    /*!
     * \brief name of pipe, key for connect pipes
     * \property Pipe::name
     * \return name of pipe
     */
    QString const& name() const;

    /*!
     * \brief list names of pipes which send data fot this pipe
     * \property Pipe::subscribes
     * \return list subscribes
     */
    QStringList const& subscribes() const;

    /*!
     * \brief this value defines does data which sended from this pipe save to data ocean or not
     * \property Pipe::storaged
     * \return state of storaged
     */
    bool storaged() const;

    /*!
     * \brief get value from data ocean
     * \fn QVariant Pipe::get(QString const& name) const
     * \return value, if value not exists return invalid
     */
    Q_INVOKABLE QVariant get(QString const& name) const;

    QString moduleName() const
    {
        return m_moduleName;
    }

public slots:
    /*!
     * \brief set name of pipe
     * \fn void Pipe::setName(QString const& name)
     * \property Pipe::name
     * \details emit signal nameChanged
     * \warning this property can be assigned only once, next assignments will be ignored
     * \param name
     */
    void setName(QString const& name);

    /*!
     * \brief set subscribes of pipe
     * \fn void Pipe::setSubscribes(QStringList const& subscribes)
     * \property Pipe::subscribes
     * \details emit signal subscribesChanged, aslo emit signal initialValueExists when data with
     *          subcribe name exists in data ocean
     * \warning this property can be assigned only once, next assignments will be ignored
     * \param subscribes
     */
    void setSubscribes(QStringList const& subscribes);

    /*!
     * \brief set does data which sended from this pipe save to data ocean or not
     * \property Pipe::storaged
     * \details emit signal storagedChanged
     * \param storaged
     */
    void setStoraged(bool storaged);

    /*!
     * \internal
     * \brief slot on receive
     */
    void onReceive(QVariant const& data);

    void setModuleName(QString moduleName)
    {
        if (m_moduleName == moduleName)
            return;

        m_moduleName = moduleName;
        emit moduleNameChanged(m_moduleName);
    }

signals:
    void nameChanged(QString const& name);
    void subscribesChanged(QStringList const& subscribes);
    void storagedChanged(bool storaged);

    /*!
     * \brief send data from pipe
     * \param data
     */
    void send(QVariant const& data);

    /*!
     * \brief receive data from subscribes
     * \param source is name pipe which sends this data
     * \param data
     */
    void receive(QString const& moduleName,QString const& source, QVariant const& data);

    /*!
     * \brief get initail value from subscribes
     * \param source is name pipe which sends this data
     * \param data
     */
    void initialValueExists(QString const& source, QVariant const& data);

    void moduleNameChanged(QString moduleName);

private:
    static QSharedPointer<PipeDispatcher> pipeDispatcher;
    static QSharedPointer<DataOcean> dataOcean;

    QString m_name = {};
    QStringList m_subscribes = {};
    bool m_nameRegistered = false;
    bool m_subscribesRegistered = false;
    bool m_storaged = false;
    QString m_moduleName;
};
}
