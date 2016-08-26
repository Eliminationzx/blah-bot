//
// Created by user on 8/21/16.
//

#ifndef INDEXER_DOCUMENTPARSER_H
#define INDEXER_DOCUMENTPARSER_H

#include <string>

/*!
 * \brief Abstract interface for document parsers
 */
class DocumentParser {
public:
    virtual ~DocumentParser () = default;

    /*!
     * \brief Verifies if given code is valid document of it's type.
     * @param Source code.
     * @return Boolean value.
     */
    virtual bool isValid (const std::string& ) const = 0;

    /*!
     * \brief Extracts text from the document's source code.
     * @param Source code.
     * @return Extracted text.
     */
    virtual std::string extractText (const std::string& ) const = 0;
};

#endif //INDEXER_DOCUMENTPARSER_H
