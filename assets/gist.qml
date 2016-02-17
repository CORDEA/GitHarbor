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
                            description: ListItemData.date
                            onTitleChanged: {
                                if (!ListItemData.title) {
                                    setTitle("no name")
                                }
                            }
                        }
                    }
                ]
                onTriggered: {
                    var choose = dataModel.data(indexPath)
                    invoke.query.setUri(choose.url)
                    invoke.trigger()
                }
            }
        }
        attachedObjects: [
            GroupDataModel {
                id: dataModel
                sortingKeys: ["title"]
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
            },
            Invocation {
                id: invoke
                query: InvokeQuery {
                    mimeType: "text/html"
                    invokeActionId: "bb.action.OPEN"
                }
            }
        ]
        onCreationCompleted: {
            indicator.start()
            apiRequest.getGists()
        }
    }
}
