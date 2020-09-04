#include "gamemodelplugin_plugin.h"
#include "gamemodel.h"

#include <qqml.h>

void GameModelPluginPlugin::registerTypes(const char *uri)
{
    // @uri GameModel
    qmlRegisterType<GameModel>(uri, 1, 0, "GameModel");
}

