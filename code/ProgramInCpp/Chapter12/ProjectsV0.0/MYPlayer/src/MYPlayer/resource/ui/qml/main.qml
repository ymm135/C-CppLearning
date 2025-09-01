import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import com.imooc.myplayer 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600
    title: qsTr("MuYing Player")
    property bool fullscreen: false
    property string language:
    {
        root.title = qsTr("MuYing Player")
        chooseSkin.title = qsTr("Choose the picture.")
        chooseSkin.nameFilters = [qsTr("Image files(*.png *.jpg *.bmp)"),qsTr("All files(*)")]
    }
    property int controlAreaButtonWidth: 48
    property int controlAreaButtonHeight: 48
    property color controlAreaButtonPressedColor: "#265F99"
    property color controlAreaButtonUnpressedColor: "#00000000"

    // 
    Image{
        id:backGround
        x:0
        y:7
        width: parent.width
        height:parent.height
        source:myplay.backGround?"file:///"+myplay.backGround:""
        smooth:true
    }

    //
     Button{
         x:10
         y:10
         id:changeSkinBtn
         width:root.controlAreaButtonWidth
         height:root.controlAreaButtonHeight
         contentItem: Image{
             width:parent.width
             height: parent.height
             source: "qrc:///image/changeSkin.png"
             fillMode: Image.PreserveAspectFit
         }
         background: Rectangle{
             implicitWidth: parent.width
             implicitHeight: parent.height
             color:changeSkinBtn.down?root.controlAreaButtonPressedColor:controlAreaButtonUnpressedColor
             radius:6
         }
         onClicked: {
             chooseSkin.open()
         }

     }

     // 
     FileDialog {
         id: chooseSkin
         title: qsTr("Choose the picture.")
         folder: myplay.backGroundChoose?"file:///"+myplay.backGroundChoose:shortcuts.desktop
         nameFilters: [qsTr("Image files(*.png*.jpg*.nmp)"),qsTr("All files(*)")]
         onAccepted: {
             console.log(backGround.source)
             backGround.source=chooseSkin.fileUrl
             myplay.changeBackground(chooseSkin.fileUrl.toString().substring(8, chooseSkin.fileUrl.length))
             console.log("You choose"+chooseSkin.fileUrl)
         }
         onRejected: {
             console.log("Canceled")
         }

     }


    MYPlay{
        id:myplay
    }

}
