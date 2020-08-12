import QtQuick 2.14
import QtQuick.Window 2.14
import tooling.Pipes 1.0

import com.sipiex.sceneloader 1.0


Item
{
    id: scene_loader


    SceneLoader {
        anchors.fill: parent
        scenarioPath: ":/scenario.json"
        storagePath: "storage.json"

        provider: QtObject {
            id: provider
            signal doorsChangeState()

            property bool blockStatus: false

            onBlockStatusChanged: action_from_scene_sender.send(blockStatus)
        }
    }

    Pipe {
        subscribes: "action_to_scene"
        onReceive: {
            provider.doorsChangeState()
        }
    }

    Pipe
    {
        id: action_from_scene_sender
        name: "action_from_scene"
    }
}
