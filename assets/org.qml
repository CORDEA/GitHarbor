import bb.cascades 1.4
import Network.ApiRequest 1.0

NavigationPane {
    id: nav
    Page {
        Container {
            layout: DockLayout {
            }
            ActivityIndicator {
                id: indicator
                preferredHeight: 150
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
            }
            ListView {
                id: list_view
                visible: false
                dataModel: dataModel
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        StandardListItem {
                            title: ListItemData.title
                            description: ListItemData.desc
                        }
                    }
                ]
            }
        }
        attachedObjects: [
            GroupDataModel {
                id: dataModel
            },
            ApiRequest {
                id: apiRequest
                onRequestCompleted: {
                    dataModel.clear()
                    dataModel.insertList(model)
                    list_view.visible = true
                    indicator.stop()
                }
                onRequestFailed: {
                    list_view.visible = true
                    indicator.stop()
                    failedToast.show()
                }
            }
        ]
        onCreationCompleted: {
            indicator.start()
            apiRequest.getOrganizations()
        }
    }
}

