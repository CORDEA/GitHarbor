/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.4
import bb.system 1.0
import Network.ApiRequest 1.0

Sheet {
    property string mUser
    property string mPass
Page {
    titleBar: TitleBar {
        title: "Login"
        acceptAction: ActionItem {
            title: "Go"
            onTriggered: {
                mUser = username.text
                mPass = password.text
                progress.show()
                if (twoFactor.enabled) {
                    apiRequest.twoFactorAuthentication(mUser, mPass, twoFactor.text);
                } else {
                    apiRequest.authentication(mUser, mPass)
                }
            }
        }
        dismissAction: ActionItem {
            title: "Cancel"
            onTriggered: {
                close()
            }
        }
    }
    Container {
        topPadding: 40
        rightPadding: 20
        leftPadding: 20
        
        layout: StackLayout {
        }
        TextField {
            id: username
            hintText: "Username"
        }
        TextField {
            id: password
            topMargin: 40
            hintText: "Password"
        }
        TextField {
            id: twoFactor
            topMargin: 40
            hintText: "Two Factor"
            enabled: false
        }
    }
    attachedObjects: [
        ApiRequest {
            id: apiRequest
            onAuthRequestCompleted: {
                progress.destroy()
                close()
                main.loginComplete()
            }
            onAuthRequestFailed: {
                progress.cancel()
            }
            onTwoFactorAuthenticationRequest: {
                progress.cancel()
                twoFactor.enabled = true
                username.enabled = false
                password.enabled = false
            }
        },
        SystemProgressDialog {
            id: progress
            title: "loading..."
            confirmButton.label: ""
        }
    ]
}
}