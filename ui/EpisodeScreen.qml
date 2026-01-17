import QtQuick

import EpisodeScreenControl 1.0

EpisodeScreenDesign {
    id: root

    enum State {
        Loading,
        FeedbackMessage,
        Characters
    }

    property int _currentState: EpisodeScreen.State.FeedbackMessage

    function _changeState(state) {
        root._currentState = state
    }

    function _handleConfirm() {
        control.doSearch(episodeIdField.text)
    }

    function _handleShowCharacters(characters) {
        root.charactersList.model = characters
        root._changeState(EpisodeScreen.State.Characters)
    }

    function _handleShowLoading(message) {
        root.loadingLabel.text = message
        root._changeState(EpisodeScreen.State.Loading)
    }

    function _handleMessageError(message) {
        root.feedbackLabel.text = message
        root._changeState(EpisodeScreen.State.FeedbackMessage)
    }

    confirmButton.onClicked: root._handleConfirm()

    charactersList.delegate: characterDelegateComponent

    EpisodeScreenControl {
        id: control

        onShowCharacters: function (characters) {
            root._handleShowCharacters(characters)
        }

        onShowLoading: function (message) {
            root._handleShowLoading(message)
        }

        onMessageError: function (message) {
            root._handleMessageError(message)
        }
    }

    // TODO A loader could be used to avoid storing all elements in memory.
    states: [
        State {
            name: "Loading"
            when: root._currentState === EpisodeScreen.State.Loading
            PropertyChanges {
                root {
                    loadingLabel {
                        visible: true
                    }

                    feedbackLabel {
                        visible: false
                    }

                    charactersList {
                        visible: false
                    }
                }
            }
        },
        State {
            name: "FeedbackMessage"
            when: root._currentState === EpisodeScreen.State.FeedbackMessage
            PropertyChanges {
                root {
                    loadingLabel {
                        visible: false
                    }

                    feedbackLabel {
                        visible: true
                    }

                    charactersList {
                        visible: false
                    }
                }
            }
        },
        State {
            name: "Characters"
            when: root._currentState === EpisodeScreen.State.Characters
            PropertyChanges {
                root {
                    loadingLabel {
                        visible: false
                    }

                    feedbackLabel {
                        visible: false
                    }

                    charactersList {
                        visible: true
                    }
                }
            }
        }
    ]
}
