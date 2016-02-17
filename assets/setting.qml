import bb.cascades 1.4

Page {
    Container {
        Button {
            text: "signin"
        }
    }
    onCreationCompleted: {
        if (!apiRequest.alreadyAuthentication()) {
            navPane.push(spl.createObject())
        }
    }
    attachedObjects: [
        ComponentDefinition {
            id: spl
            source: "main.qml"
        }
    ]
}