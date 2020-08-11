/* Copyright (C) Freeman - All Rights Reserved
 */

#include "ctrlplugin_plugin.h"
#include "pipe.h"
#include "fakepipe.h"

#include <qqml.h>

namespace pipe
{
void CtrlPluginPlugin::registerTypes(char const* uri)
{
    // @uri tooling.Pipes
    qmlRegisterType<Pipe>(uri, 1, 0, "Pipe");
    qmlRegisterType<FakePipe>(uri, 1, 0, "FakePipe");
}
}
