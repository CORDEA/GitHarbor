import bb.cascades 1.4
import Network.ApiRequest 1.0
import Util.Invoke 1.0

NavigationPane {
    id: nav
    property string mQuery
    Page {
        titleBar: TitleBar {
            id: titleBar
            kind: TitleBarKind.TextField
            visibility: ChromeVisibility.Hidden
            kindProperties: TextFieldTitleBarKindProperties {
                id: titleBarText
                textField.hintText: "Find repository"
            }
        }
        
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
                                text: ListItemData.name
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }
                                Label {
                                    textStyle.fontSize: FontSize.Small
                                    text: ListItemData.type
                                }
                                Label {
                                    textStyle.fontSize: FontSize.Small
                                    horizontalAlignment: HorizontalAlignment.Center
                                    text: new Date(ListItemData.updatedAt)
                                }
                            }
                            Divider {
                            }
                        }
                    }
                ]
                onTriggered: {
                    var choose = dataModel.data(indexPath)
                    invoke.openBrowser(choose.url);
                }
            }
        }
        actions: [
            ActionItem {
                title: "Search"
                ActionBar.placement: ActionBarPlacement.Signature
                imageSource: "asset:///images/ic_search.png"
                onTriggered: {
                    if (titleBar.visibility == ChromeVisibility.Default) {
                        titleBar.visibility = ChromeVisibility.Hidden
                        mQuery = titleBarText.textField.text
                        nav.push(searchResult.createObject())
                        return;
                    }
                    titleBar.visibility = ChromeVisibility.Default
                }
            }
        ]
        attachedObjects: [
            GroupDataModel {
                id: dataModel
                sortingKeys: ["updatedAt"]
                sortedAscending: false
                grouping: ItemGrouping.None
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
            },
            ComponentDefinition {
                id: searchResult
                source: "search_result.qml"
            },
            Invoke {
                id: invoke
            }
        ]
        onCreationCompleted: {
            if (apiRequest.alreadyAuthentication()) {
                indicator.start()
                apiRequest.getNotifications()
            }
        }
    }
}