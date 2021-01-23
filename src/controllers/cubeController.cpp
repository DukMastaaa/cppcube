#include "controllers/cubeController.h"

#include "controllers/baseController.h"

CubeController::CubeController(int cubeDim) : 
        BaseController(), 
        dim(cubeDim), 
        cubeModel(dim), 
        cubeViewModel(cubeModel), 
        cubeWindow(cubeViewModel) {}

// todo: implement other methods

