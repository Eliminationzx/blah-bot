project(src C CXX)

set(HEADER_FILES
        parser/HTMLDocumentParser.h
        index/Worker.h
        index/Stemmer.h
        index/IStemmer.h
        index/Document.h
        parser/DocumentParser.h
        db/IndexQueueDAO.h
        db/IndexQueueDAOImpl.h
        db/PageDAO.h
        db/Pagedb.h
        db/robotstxtDb.h
        crawler/crawler.h
        web/http.h
        web/Page.h
        web/robotscontroller.h)

set(SOURCE_FILES
        parser/HTMLDocumentParser.cpp
        index/Worker.cpp
        index/Stemmer.cpp
        index/Document.cpp
        db/DocumentDAO.cpp
        db/DocumentDAO.h
        db/IndexQueueDAOImpl.cpp
        db/Pagedb.cpp
        db/robotstxtDb.cpp
        crawler/crawler.cpp
        web/http.cpp
        web/robotscontroller.cpp Engine.cpp Engine.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})