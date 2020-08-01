import QtQuick 2.14
import QtQuick.Window 2.14
import tooling.Pipes 1.0


Item
{
    id: scene_loader

    Rectangle
    {
        color: "red"
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: qsTr("Dummpy scene")
        }
    }
    Loader
    {
        id:loader
        anchors.fill: parent
    }


    Timer {
        id: timer
        interval: 1500 ; running: true; repeat: true
        onTriggered:
        {    if(loop < 3 && loop >= 0)
            {
                console.log("event send")
                loader.sourceComponent = listOfComponnents[loop]
            }
            if(loop === 3)
                timer.stop()

            loop = loop + 1
        }

    }
    property var listOfComponnents: [first_event,second_event,third_event]
    property int loop: -1


    Component {
        id: first_event

        FakePipe {
            name: "text_event_listener"
            once: false
            interval: 100
            rawData: ["Hello test"]
        }


    }

    Component {
        id: third_event

        FakePipe {
            name: "smooth_action_from_scene"
            once: true
            interval: 100
            rawData: [0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1]
        }


    }

    Component {
        id: second_event

        FakePipe {
            name: "action_from_scene"
            once: true
            interval: 100
            rawData: [true]
        }



    }



}
