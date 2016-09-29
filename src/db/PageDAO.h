//
// Created by user on 8/17/16.
//

#ifndef CRAWLER_PAGEDAO_H
#define CRAWLER_PAGEDAO_H

#include <web/Page.h>

class PageDAO {
public:
    virtual ~PageDAO () = default;
    virtual void saveURL (Page& ) = 0;
};


#endif //CRAWLER_PAGEDAO_H
