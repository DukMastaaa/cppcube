#include "recordListViewModel.h"

#include "recordList.h"
#include "myStructs.h"


RecordListViewModel::RecordListViewModel(RecordList& recordsRef) : records(recordsRef) {
    recordsShown = 10;  // this can be changed
}


Pos2D RecordListViewModel::calcHeightWidth() {
    return {recordsShown + 1, 14};
}