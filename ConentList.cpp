#include "ContentList.h"

ContentList::ContentList()
{

}

ContentList::ContentList(std::vector<Problem> arr)
{
    for(auto ele: arr)
    {
        ContentWidget* t = new ContentWidget();
        t->Setup(ele);
        addChildLayout(t);
    }
}
