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
                        Container {
                            leftPadding: 30
                            rightPadding: 30
                            topPadding: 10
                            bottomPadding: 10
                            layout: StackLayout {
                            }
                            Label {
                                textStyle.fontSize: FontSize.Large
                                text: ListItemData.title
                            }
                            Label {
                                textStyle.fontSize: FontSize.Medium
                                text: ListItemData.body
                            }
                            Container {
                                Label {
                                    id: user
                                    visible: false
                                    textStyle.fontSize: FontSize.Small
                                    text: "created by " + ListItemData.user
                                    onTextChanged: {
                                        if (ListItemData.user) {
                                            setVisible(true)
                                        }
                                    }
                                }
                            }
                            Container {
                                Label {
                                    id: assign
                                    visible: false
                                    textStyle.fontSize: FontSize.Small
                                    text: "assignee " + ListItemData.assign_user
                                    onTextChanged: {
                                        if (ListItemData.assign_user) {
                                            setVisible(true)
                                        }
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Right
                                Label {
                                    textStyle.fontSize: FontSize.Small
                                    text: ListItemData.comments + " comments"
                                }
                            }
                            Divider {
                            }
                        }
                    }
                ]
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
            }
        ]
        onCreationCompleted: {
            indicator.start()
            apiRequest.getIssues()
        }
    }
}
