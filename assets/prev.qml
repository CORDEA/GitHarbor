import bb.cascades 1.4

Page {
    Container {
        leftPadding: 30
        rightPadding: 30
        topPadding: 10
        bottomPadding: 10
        layout: StackLayout {
        }
        Label {
            textStyle.fontSize: FontSize.Large
            text: "title"
        }
        Label {
            textStyle.fontSize: FontSize.Medium
            text: "aaa"
            visible: false
        }
        Label {
            textStyle.fontSize: FontSize.Small
            text: "python"
        }
        
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Label {
                id: forks
                text: "0 forks"
            }
            Label {
                id: stars
                text: "0 stargazers"
            }
            Label {
                text: "0 watchers"
            }
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Right
            Label {
                textStyle.fontSize: FontSize.Small
                text: "private"
            }
        }
        Divider {
        }
    }
}
