import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import com.imooc.myplayer 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id:demoNum
        x:236
        y:144
        text:qsTr("Click Me")
        onClicked: {
            MainApp.testFunc()
        }
    }

    Text {
        id:text
        x:400
        y:400
        text:""+MainApp.demoNum
        color: "#ff0000"
        font.pointSize: 50
    }

}

