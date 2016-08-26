project(src C CXX)

set(HEADER_FILES
        parser/HTMLDocumentParser.h
        index/Worker.h
        index/Stemmer.h
        index/IStemmer.h
        index/Document.h
        parser/DocumentParser.h)

set(SOURCE_FILES
        parser/HTMLDocumentParser.cpp
        index/Worker.cpp
        index/Stemmer.cpp
        index/Document.cpp
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})