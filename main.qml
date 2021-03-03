import QtQuick 2.3
import QtQuick.Controls 2.5

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Integration World")


    //Connections{
    //    target: messageClass
    //    onMessageChanged:textId.text=value;
    //}

    //you can also change the property from qml:
    //Component.onCompleted: {
    //    messageClass.message="Changed from qml"
    //}
    //Message is a property, so I can just use my context property and set the message property directly


    Text{
        id:executingList
        x: 39
        y: 74
        height: 18
        text: executingClass.executing
        font.pointSize: 18
        //text: qsTr("Hello New World")
        //ask the c++ class for the message
        //this will get the message when program start and
        //because the notify signal, it will automatically know whenever a changes
        //that means, we don't need to connect to the connect changes derictly
    }

    //以下用于两种通信:在message.h文件中注册槽函数doMessageChange()
    //效果是console中出现"We are in c++. Hooray!"
    ScrollView {
        id: scrollView
        x: 35
        y: 201
        width: 570
        height: 241
        //availableHeight: 258
        hoverEnabled: false

        enabled: true

        TextArea {
            id: textArea
            x: -1
            y: -6
            width: 556
            height: 241
            text: waitingClass.waiting
            enabled: false
            font.pointSize: 15
        }
    }


    Text {
        id: waitingListTitle
        x: 34
        y: 177
        width: 493
        height: 18
        text: qsTr("进程号      进入时间      离开时间       等待时间   当前优先级")
        font.pixelSize: 18
    }

    Text {
        id: exeListTitle
        x: 34
        y: 44
        width: 493
        height: 18
        text: qsTr("进程号      进入时间       调用时间      作业时长     执行进度")
        font.pixelSize: 18
    }

    Text {
        id: seperator
        x: 8
        y: 125
        color: "#4a4646"
        text: qsTr("————————————————————————————————————————————————————")
        style: Text.Sunken
        font.pixelSize: 12
    }

    Text {
        id: executing
        x: 20
        y: 13
        width: 138
        height: 18
        color: "#f43f36"
        text: qsTr("正在执行作业：")
        font.capitalization: Font.MixedCase
        style: Text.Normal
        font.weight: Font.DemiBold
        font.family: "Courier"
        font.pixelSize: 18
    }

    Text {
        id: waiting
        x: 20
        y: 143
        width: 138
        height: 18
        color: "#f43f36"
        text: qsTr("等待作业列表：")
        font.family: "Courier"
        style: Text.Normal
        font.weight: Font.DemiBold
        font.pixelSize: 18
        font.capitalization: Font.MixedCase
    }

    Text {
        id: systemTimeTitle
        x: 458
        y: 451
        height: 18
        text: qsTr("当前时间：")
        font.pixelSize: 15
    }

    Text {
        id: systemTime
        x: 539
        y: 448
        height: 18
        text: messageClass.message
        font.pixelSize: 18
    }

    Button {
        id: button
        x: 24
        y: 448
        width: 77
        height: 24
        text: qsTr("停止运行")
        font.pointSize: 7
        onClicked: systemcontrolClass.doClose()
    }


}
