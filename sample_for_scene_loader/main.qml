import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

import tooling.Pipes 1.0

Window {
    visible: true
    width: 360
    height: 760
    Item {
        id: root
        anchors.fill: parent

        SceneLoader {
            id: scene_loader

            width: parent.width*0.8
            height: parent.height * 0.4

            anchors.left: parent.left
            anchors.top: parent.top

            anchors.topMargin: parent.height*0.1
            anchors.leftMargin: parent.width*0.1

        }

        Rectangle
        {
            width: parent.width
            height: parent.height * 0.4

            anchors.left: parent.left
            anchors.top: scene_loader.bottom

            anchors.topMargin: parent.height*0.1

            color: "grey"
            opacity: 0.5
        }

        Column {

            id: column
            width: parent.width*0.8
            height: parent.height * 0.3
            spacing: 30
            topPadding: 10
            leftPadding: 50

            anchors.left: parent.left
            anchors.top: scene_loader.bottom

            anchors.topMargin: parent.height*0.1
            anchors.leftMargin: parent.width*0.1

            Text {
                id: text_event_listener
                text: qsTr("Wait for text froom scene...")
                font.pixelSize: 12

                Pipe
                {
                    subscribes: "text_event_listener"
                    onReceive:
                    {
                        text_event_listener.text = data
                    }
                }
            }

            CheckBox {
                id: action_from_scene
                text: qsTr("action_from_scene")
                Pipe
                {
                    subscribes: "action_from_scene"
                    onReceive:
                    {
                        action_from_scene.checked = data
                    }
                }
            }

            Slider {
                id: smooth_action_from_scene
                value: 0.5
                Pipe
                {
                    subscribes: "smooth_action_from_scene"
                    onReceive:
                    {
                        smooth_action_from_scene.value = data
                    }
                }
            }

            Button {
                id: action_to_scene
                text: qsTr("action to scene")

                Pipe
                {
                    id : action_to_scene_sender
                    name: "action_to_scene"
                }
                onClicked:
                {
                    action_to_scene_sender.send("value")
                }
            }



        }

    }
}
