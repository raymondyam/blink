#QMAKE_CC = gocache gcc
#QMAKE_CXX = gocache g++

TEMPLATE    = app
#CONFIG += release

QT += widgets xml network
RC_FILE = Resources/Icons/appIcons.rc
RESOURCES   = Resources/app.qrc
#RESOURCES   += Resources/webview.qrc 

INCLUDEPATH += "Utils"

FORMS       = Resources/Forms/mainWindow.ui \
              Resources/Forms/profileDialog.ui \
              Resources/Forms/groupDialog.ui \ 
              Resources/Forms/aboutDialog.ui \
              Resources/Forms/configDialog.ui

SOURCES     += main.cpp \
               Utils/CUtils.cpp \
               Display/CMainWindow.cpp \
               Display/CProfileDlg.cpp \
               Display/CGroupDlg.cpp \ 
               Display/CAboutDlg.cpp \
               Display/CProfileListWidget.cpp \
               Display/CGroupListWidget.cpp \ 
               Display/COutputListWidget.cpp \
               Display/CConfigDlg.cpp \
               Display/CEventFilterObj.cpp \
               Display/CSearchTextBrowser.cpp \
               Model/qTagger/CTagResultItem.cpp \
               Model/qTagger/qTagger.cpp \
               Model/qTagger/CSourceFileList.cpp \ 
               Model/CProfileListModel.cpp \
               Model/CGroupListModel.cpp \ 
               Model/COutputListModel.cpp \
               Model/CProfileManager.cpp \
               Model/CProfileUpdateThread.cpp \
               Model/CProfileLoadThread.cpp \
               Model/CGroupLoadThread.cpp \
               Model/CConfigManager.cpp \
               Model/CGroupItem.cpp \ 
               Model/CProfileItem.cpp \
               Model/COutputItem.cpp \
               Model/CRunCommand.cpp \ 
               Storage/CXmlStorageHandler.cpp \


HEADERS     += Utils/commonType.h \
               Utils/CUtils.h \
               Display/CMainWindow.h \
               Display/CProfileDlg.h \
               Display/CGroupDlg.h \ 
               Display/CAboutDlg.h \
               Display/CProfileListWidget.h \
               Display/CGroupListWidget.h \
               Display/COutputListWidget.h \
               Display/CConfigDlg.h \
               Display/CEventFilterObj.h \  
               Display/CSearchTextBrowser.h \
               Model/qTagger/CTagResultItem.h \
               Model/qTagger/qTagger.h \ 
               Model/qTagger/CSourceFileList.h \
               Model/CProfileListModel.h \ 
               Model/CGroupListModel.h \
               Model/COutputListModel.h \
               Model/CProfileManager.h \
               Model/CProfileUpdateThread.h \
               Model/CProfileLoadThread.h \
               Model/CGroupLoadThread.h \
               Model/CConfigManager.h \
               Model/CProfileItem.h \ 
               Model/CGroupItem.h \
               Model/COutputItem.h \
               Model/CRunCommand.h \
               Storage/CXmlStorageHandler.h \
               Storage/IStorageHandler.h \




