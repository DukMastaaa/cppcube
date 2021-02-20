#pragma once

#include <vector>
#include <utility>
#include <memory>

#include <ncurses.h>

#include "controllers/baseController.h"
#include "controllers/popupControllers.h"
#include "controllers/normal/cubeController.h"
#include "controllers/normal/recordListController.h"
#include "controllers/normal/scramblerController.h"
#include "controllers/normal/timerController.h"
#include "myStructs.h"


class App {
    private:
        CubeController cubeController;
        RecordListController recordListController;
        ScramblerController scramblerController;
        TimerController timerController;

        std::vector<BaseController*> mainControllers;
        std::vector<std::pair<PopupCallback, std::unique_ptr<PopupControllerInterface>>> popupControllers;

        int dim;  // todo: only temporary
        bool doAnUpdate;
        bool appRunning;

        // helper
        void refreshAllControllers() const;

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

        void jumpSelectedIndex(std::size_t index);
        void generateNewScramble();

        // popup callbacks
        void changeCubeDim(std::string popupReturnData);

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

        template<typename ViewModel>
        void createPopup(PopupCallback callback);

        void sendDataToLatestPopup(std::string data);
};


#include "app.tpp"