import bb.cascades 1.4
import bb.data 1.0
import Network.ApiRequest 1.0

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
            id: listView
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
                            text: ListItemData.desc
                            visible: false
                            onTextChanged: {
                                var t = text.trim()
                                setVisible(t)
                            }
                        }
                        Label {
                            textStyle.fontSize: FontSize.Small
                            text: ListItemData.language
                        }
                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            Label {
                                id: forks
                                text: ListItemData.forksCount + " forks"
                            }
                            Label {
                                id: stars
                                text: ListItemData.stargazersCount + " stargazers"
                            }
                            Label {
                                text: ListItemData.watchersCount + " watchers"
                            }
                        }
                        Container {
                            horizontalAlignment: HorizontalAlignment.Right
                            Label {
                                textStyle.fontSize: FontSize.Small
                                text: ListItemData.score
                            }
                        }
                        Divider {
                        }
                    }
                }
            ]
        }
        attachedObjects: [
            GroupDataModel {
                id: dataModel
                sortingKeys: ["title"]
                grouping: ItemGrouping.ByFirstChar
            },
            ApiRequest {
                id: apiRequest
                onRequestCompleted: {
                    dataModel.clear()
                    dataModel.insertList(model)
                    listView.visible = true
                    indicator.stop()
                }
                onRequestFailed: {
                    listView.visible = true
                    indicator.stop()
                    failedToast.show()
                }
            }
        ]
        onCreationCompleted: {
            indicator.start()
            if (mQuery) {
                apiRequest.searchRepositories(mQuery)
            } else {
                listView.visible = true
                indicator.stop()
                failedToast.show()
            }
        }
    }
}
