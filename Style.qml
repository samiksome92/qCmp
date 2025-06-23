// Single object which provides a set of constant style values to be used.
pragma Singleton
import QtQuick

QtObject {
    readonly property int windowWidth: 1280
    readonly property int windowHeight: 720
    readonly property int panelHeight: 30
    readonly property int border: 1
    readonly property int padding: 5
    readonly property int radius: 1
    readonly property int keyHintSpacing: 10

    readonly property font font: ({
            family: "IBM Plex Sans",
            pointSize: 10
        })

    readonly property color fgColor: "#f9f9f9"
    readonly property color bgColor: "#000000"
    readonly property color borderColor: "#303030"
}
