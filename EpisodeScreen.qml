import QtQuick

import EpisodeScreenControl 1.0

EpisodeScreenDesign {
    id: root

    function _handleConfirm() {
        control.doSearch(episodeIdField.text)
    }

    function _handleShowCharacters(characters) {
        root.charactersList.model = characters
    }

    confirmButton.onClicked: root._handleConfirm()

    EpisodeScreenControl {
        id: control

        onShowCharacters: function (characters) {
            root._handleShowCharacters(characters)
        }
    }
}
