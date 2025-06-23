// UI QML.
import QtQuick
import QtQuick.Layouts

import image
import "."

Window {
    id: window

    width: Style.windowWidth
    height: Style.windowHeight

    visible: true
    visibility: Window.Maximized
    color: Style.borderColor

    property int lastVisibility: visibility

    ColumnLayout {
        anchors.fill: parent
        spacing: Style.border

        GridLayout {
            id: grid

            Layout.fillWidth: true
            Layout.fillHeight: true
            rowSpacing: Style.border
            columnSpacing: Style.border

            rows: backend.rows
            columns: backend.cols

            property string set: "first"
            property bool fileNames: false

            Repeater {
                model: grid.rows * grid.columns

                StackLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    currentIndex: grid.set === "first" ? 0 : 1

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: Style.border

                        Image {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            padding: Style.padding
                            radius: Style.radius

                            source: backend.imgPairs[index].first
                            fillColor: Style.bgColor
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.panelHeight

                            visible: grid.fileNames
                            color: Style.bgColor

                            Text {
                                anchors.fill: parent

                                text: backend.imgPairs[index].first
                                font: Style.font
                                color: Style.fgColor
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: Style.border

                        Image {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            padding: Style.padding
                            radius: Style.radius

                            source: backend.imgPairs[index].second
                            fillColor: Style.bgColor
                        }

                        Rectangle {
                            Layout.fillWidth: true
                            Layout.preferredHeight: Style.panelHeight

                            visible: grid.fileNames
                            color: Style.bgColor

                            Text {
                                anchors.fill: parent

                                text: backend.imgPairs[index].second
                                font: Style.font
                                color: Style.fgColor
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            id: inputBar

            Layout.fillWidth: true
            Layout.preferredHeight: Style.panelHeight

            visible: false
            color: Style.bgColor

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Style.padding
                anchors.rightMargin: Style.padding

                Text {
                    Layout.fillHeight: true

                    text: "Go to image?"
                    font: Style.font
                    color: Style.fgColor
                    verticalAlignment: Text.AlignVCenter
                }

                TextInput {
                    id: input

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    font: Style.font
                    color: Style.fgColor
                    verticalAlignment: Text.AlignVCenter

                    onAccepted: {
                        backend.goTo(text);
                        clear();
                        inputBar.visible = false;
                        statusBar.visible = true;
                        keyHandler.focus = true;
                    }
                }
            }
        }

        Rectangle {
            id: statusBar

            Layout.fillWidth: true
            Layout.preferredHeight: Style.panelHeight

            color: Style.bgColor

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Style.padding
                anchors.rightMargin: Style.padding
                spacing: Style.keyHintSpacing

                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: backend.statusText
                    font: Style.font
                    color: Style.fgColor
                    verticalAlignment: Text.AlignVCenter
                }

                Repeater {
                    model: [
                        {
                            key: "⯇",
                            label: "Previous Set"
                        },
                        {
                            key: "⯈",
                            label: "Next Set"
                        },
                        {
                            key: "/",
                            label: "Go To"
                        },
                        {
                            key: "-",
                            label: "Add Row"
                        },
                        {
                            key: "_",
                            label: "Remove Row"
                        },
                        {
                            key: "=",
                            label: "Add Column"
                        },
                        {
                            key: "+",
                            label: "Remove Column"
                        },
                        {
                            key: "␣",
                            label: timer.running ? "Pause" : "Resume"
                        },
                        {
                            key: "I",
                            label: grid.fileNames ? "Hide File Names" : "Show File Names"
                        },
                        {
                            key: "S",
                            label: "Hide Statusbar"
                        },
                        {
                            key: "F",
                            label: window.visibility === Window.FullScreen ? "Restore" : "Fullscreen"
                        },
                        {
                            key: "Q",
                            label: "Quit"
                        }
                    ]

                    RowLayout {
                        Layout.fillHeight: true
                        spacing: 0

                        Rectangle {
                            Layout.fillHeight: true
                            Layout.preferredWidth: height
                            Layout.margins: Style.padding
                            radius: Style.radius

                            color: Style.fgColor

                            Text {
                                anchors.fill: parent

                                text: modelData.key
                                font: Style.font
                                color: Style.bgColor
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }

                        Text {
                            id: label

                            Layout.fillHeight: true

                            text: modelData.label
                            font: Style.font
                            color: Style.fgColor
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }

    Item {
        id: keyHandler

        focus: true

        Keys.onPressed: event => {
            switch (event.key) {
            case Qt.Key_Left:
                backend.prev();
                break;
            case Qt.Key_Right:
                backend.next();
                break;
            case Qt.Key_Slash:
                statusBar.visible = false;
                inputBar.visible = true;
                input.focus = true;
                break;
            case Qt.Key_Minus:
                backend.addRow();
                break;
            case Qt.Key_Underscore:
                backend.removeRow();
                break;
            case Qt.Key_Equal:
                backend.addCol();
                break;
            case Qt.Key_Plus:
                backend.removeCol();
                break;
            case Qt.Key_Space:
                timer.running = !timer.running;
                break;
            case Qt.Key_I:
                grid.fileNames = !grid.fileNames;
                break;
            case Qt.Key_S:
                statusBar.visible = !statusBar.visible;
                break;
            case Qt.Key_F:
                if (window.visibility === Window.FullScreen)
                    window.visibility = window.lastVisibility;
                else {
                    window.lastVisibility = window.visibility;
                    window.visibility = Window.FullScreen;
                }
                break;
            case Qt.Key_Q:
                Qt.quit();
                break;
            }
        }
    }

    Timer {
        id: timer

        interval: backend.timer
        running: true
        repeat: true

        onTriggered: grid.set = grid.set === "first" ? "second" : "first"
    }
}
