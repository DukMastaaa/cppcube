#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <functional>

#include <ncurses.h>

#include "controllers/baseController.h"
#include "controllers/popupControllers.h"
#include "controllers/normal/cubeController.h"
#include "controllers/normal/recordListController.h"
#include "controllers/normal/scramblerController.h"
#include "controllers/normal/timerController.h"
#include "models/summaryStatsModel.h"
#include "models/fileManager.h"
#include "myStructs.h"


class App {
    private:
        struct PopupPair {
            PopupCallback callback;
            std::unique_ptr<PopupControllerInterface> controller;
        };

        CubeController cubeController;
        RecordListController recordListController;
        ScramblerController scramblerController;
        TimerController timerController;

        SummaryStatsModel summaryStatsModel;
        FileManager fileManager;

        std::vector<BaseController*> mainControllers;
        std::vector<PopupPair> popupControllers;

        int dim;
        bool doAnUpdate;
        bool appRunning;

        // helper
        void refreshAllControllers() const;
        void createInfoPopup(std::string description);

        // handles keyboard inputs for main window (no popups)
        void mainWindowKeyboardInput(int input);

        // app functionality
        void handleTerminalResize();
        void toggleTimer();
        void togglePenalty(Penalty penalty, std::size_t recordNum);

        void moveSelectedRecordUp();
        void moveSelectedRecordDown();
        void moveSelectedRecordTop();
        void moveSelectedRecordBottom();

        void generateNewScramble();

        void deleteLatestRecord();
        void deleteSelectedRecord();
        void displayRecordInfoPopup();

        void exportTimes();
        void importTimes();

        // popup callbacks
        void changeCubeDim(std::string popupReturnData);
        void confirmRecordDeletion(std::string popupReturnData, unsigned int recordIndex);
        void jumpToSelectedIndex(std::string popupReturnData);
        void exportToFilename(std::string popupReturnData);
        void importFromFilename(std::string popupReturnData);
        void closeProgram(std::string popupReturnData);

    public:
        App(int cubeDim);
        void initialRefreshUpdate();
        void keyboardInput(int input);
        bool needUpdate() const;
        void turnOffUpdate();
        void forceUpdate();
        bool appIsRunning() const;
        WINDOW* getWindow() const;

        template<typename ViewModel, typename ModelClass, typename Window = CentredWindow>
        void createPopup(PopupCallback callback, ModelClass& modelRef);

        // specific overload for const&
        template<typename ViewModel, typename ModelClass, typename Window = CentredWindow>
        void createPopup(PopupCallback callback, const ModelClass& constModelRef);

        template<typename ViewModel>
        void createPopup(PopupCallback callback);

        void sendDataToLatestPopup(std::string data);
        void makeTitleForLatestPopup(std::string title);
        void closeLatestPopup();  // this is very dangerous
};


#include "app.tpp"