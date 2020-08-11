/* Copyright (C) Freeman - All Rights Reserved
 */

#pragma once

#include <QObject>
#include <QHash>

namespace pipe
{
class Pipe;
class DataOcean;

/*!
   \class PipeDispatcher
   \brief The PipeDispatcher class is mediator class for pipes and data ocean
   \since 1.0
 */
class PipeDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit PipeDispatcher(DataOcean* ocean, QObject* parent = nullptr);

    /*!
     * \brief register pipe which can send data(has name)
     * \param pipe
     */
    void registerPipe(Pipe* pipe);

    /*!
     * \brief subcribe pipe on other pipes
     * \param pipe
     */
    void subscribePipe(Pipe* pipe);

    /*!
     * \brief connect data ocean with storaged pipe
     * \param pipe
     */
    void storagePipe(Pipe* pipe);

    /*!
     * \brief disconnect data ocean from pipe
     * \param pipe
     */
    void unstoragePipe(Pipe* pipe);

private slots:
    void storagedPipeChanged(bool storaged);
    void deleteFromPipes(QObject* obj);
    void deleteFromSubscribes(QObject* obj);

private:
    QHash<QString, QList<Pipe*>> m_pipes = {};
    QHash<QString, QList<Pipe*>> m_subscribes = {};

    DataOcean* m_ocean = nullptr;
};
}
