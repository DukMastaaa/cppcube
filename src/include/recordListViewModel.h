#include <stddef.h>

#include "baseViewModel.h"
#include "recordList.h"
#include "myStructs.h"


class RecordListViewModel : public BaseViewModel {
    private:
        RecordList& records;
        int recordsShown;
        std::size_t selectedRecordRevIdx;  // bad name
    
    public:
        RecordListViewModel(RecordList& recordsRef);
        Pos2D calcHeightWidth();
        void draw(WINDOW* window);
};