import bb.cascades 1.4
import bb.system 1.2
import Network.ApiRequest 1.0

TabbedPane {
    property NavigationPane navPane
    Tab {
        id: actTab
        title: "Activity"
        delegateActivationPolicy: TabDelegateActivationPolicy.Default
        delegate: Delegate {
            id: actDel
            source: "activity.qml"
        }
    }
    Tab {
        title: "Repositories"
        delegateActivationPolicy: TabDelegateActivationPolicy.Default
        delegate: Delegate {
            id: repDel
            source: "repository.qml"
        }
    }
    Tab {
        title: "Organizations"
        delegateActivationPolicy: TabDelegateActivationPolicy.Default
        delegate: Delegate {
            id: orgDel
            source: "org.qml"
        }
    }
    Tab {
        title: "Issues"
        delegateActivationPolicy: TabDelegateActivationPolicy.Default
        delegate: Delegate {
            id: issDel
            source: "issue.qml"
        }
    }
    Tab {
        title: "Gists"
        delegateActivationPolicy: TabDelegateActivationPolicy.Default
        delegate: Delegate {
            id: gisDel
            source: "gist.qml"
        }
    }
    onActiveTabChanged: {
        navPane = activeTab.content
    }
    onCreationCompleted: {
        actDel.active = true
        navPane = actTab.content
        if (!apiRequest.alreadyAuthentication()) {
            main.createObject().open()
        }
    }
    Menu.definition: MenuDefinition {
        actions: ActionItem {
            title: "Logout"
            onTriggered: {
                apiRequest.deleteToken()
                progress.show()
            }
        }
    }
    attachedObjects: [
        ComponentDefinition {
            id: setting
            source: "setting.qml"
        },
        ComponentDefinition {
            id: main
            source: "main.qml"
        },
        ApiRequest {
            id: apiRequest
            onAuthRequestCompleted: {
                progress.destroy()
                main.createObject().open()
            }
            onAuthRequestFailed: {
                progress.cancel()
            }
        },
        SystemToast {
            id: failedToast
            body: "Fetch of data has failed."
            position: SystemUiPosition.BottomCenter
        },
        SystemProgressDialog {
            id: progress
            title: "loading..."
            confirmButton.label: ""
        }
    ]
}