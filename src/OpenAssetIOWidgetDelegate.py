# KatanaOpenAssetIO
# Copyright (c) 2024 The Foundry Visionmongers Ltd
# SPDX-License-Identifier: Apache-2.0

from Katana import UI4, AssetAPI, QT4FormWidgets, version

if version < (8,):
    from PyQt5 import QtCore, QtWidgets
else:
    from PySide6 import QtCore, QtWidgets


class OpenAssetIOBrowser(QtWidgets.QFrame):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        QtWidgets.QVBoxLayout(self)

        self.__textbox = QT4FormWidgets.InputWidgets.InputLineEdit(self)
        self.layout().addWidget(self.__textbox, QtCore.Qt.AlignCenter)

    def setLocation(self, assetId):
        self.__textbox.setText(assetId)

    def getResult(self):
        return self.__textbox.text()

    def selectionValid(self):
        """
        Required method for asset browsers.

        @rtype: C{bool}
        @return: C{True} if the currently selected path is a valid
        selection, otherwise C{False}.
        """
        return True


class OpenAssetIOWidgetDelegate(
    UI4.Util.AssetWidgetDelegatePlugins.DefaultAssetWidgetDelegate
):

    def configureAssetBrowser(self, browser):
        UI4.Util.AssetWidgetDelegatePlugins.BaseAssetWidgetDelegate.configureAssetBrowser(
            self, browser
        )
        index = browser.addBrowserTab(OpenAssetIOBrowser, "Asset")

        browser.getBrowser(index).setLocation(str(self.getValuePolicy().getValue()))


PluginRegistry = [
    ("AssetWidgetDelegate", 1, "KatanaOpenAssetIO", OpenAssetIOWidgetDelegate),
]
