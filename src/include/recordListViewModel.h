#include "baseViewModel.h"
#include "recordList.h"


class RecordListViewModel : public BaseViewModel {
    private:
        RecordList& records;
    
    public:
        RecordListViewModel(RecordList& recordsRef);
};