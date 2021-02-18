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
        static CubeController cubeController;
        static RecordListController recordListController;
        static ScramblerController scramblerController;
        static TimerController timerController;

        static std::vector<BaseController*> mainControllers;
        static std::vector<std::pair<PopupCallback, std::unique_ptr<PopupControllerInterface>>> popupControllers;
 
        static int dim;  // todo: only temporary
        static bool doAnUpdate;
        static bool appRunning;

        // helper
        static void refreshAllControllers();

        // handles keyboard inputs for main window (no popups)
        static void mainWindowKeyboardInput(int input);

        // app functionality
        static void handleTerminalResize();
        static void toggleTimer();
        static void togglePenalty(Penalty penalty, std::size_t recordNum);

        static void moveSelectedRecordUp();
        static void moveSelectedRecordDown();
        static void moveSelectedRecordTop();
        static void moveSelectedRecordBottom();

        static void jumpSelectedIndex(std::size_t index);
        static void generateNewScramble();

        // popup callbacks
        static void changeCubeDim(std::string popupReturnData);

    public:
        // App(int cubeDim);
        static void initialRefreshUpdate();
        static void keyboardInput(int input);
        static bool needUpdate();
        static void turnOffUpdate();
        static void forceUpdate();
        static bool appIsRunning();
        static WINDOW* getWindow();

        template<typename ViewModel, typename ModelClass, typename Window = CentredWindow>
        static void createPopup(PopupCallback callback, ModelClass& modelRef);

        template<typename ViewModel>
        static void createPopup(PopupCallback callback);

        static void sendDataToLatestPopup(std::string data);
};


#include "app.tpp"