import bb.cascades 1.4
import Network.ApiRequest 1.0

Sheet {
    id: main
    peekEnabled: false
    signal loginComplete
    
    Page {
        Container {
            layout: DockLayout {
            }
            
            Container {
                layout: StackLayout {
                }
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                Label {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: "Git Harbor"
                    textStyle {
                        base: SystemDefaults.TextStyles.BigText
                    }
                }
                Button {
                    text: "Login"
                    topMargin: 100
                    onClicked: {
                        login.createObject().open()
                    }
                }
            }
        }
        attachedObjects: [
            ComponentDefinition {
                id: login
                source: "login.qml"
            },
            ApiRequest {
                id: apiRequest
            }
        ]
    }
    onLoginComplete: {
        close()
    }
}