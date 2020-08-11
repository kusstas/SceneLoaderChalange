/* Copyright (C) Freeman - All Rights Reserved
 */

#pragma once

#include <QQmlExtensionPlugin>

namespace pipe
{
class CtrlPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(char const* uri) override;
};
}
