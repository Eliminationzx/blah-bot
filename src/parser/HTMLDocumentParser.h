//
// Created by user on 7/25/16.
//

#ifndef CRAWLER_HTMLPARSER_H
#define CRAWLER_HTMLPARSER_H

#include <string>
#include <vector>

#include <gumbo.h>

#include "DocumentParser.h"

/*!
 * Operations on html code
 */
class HTMLDocumentParser : public DocumentParser {
public:
    HTMLDocumentParser ();
    ~HTMLDocumentParser ();

//    void parse (Document& page);

    /*!
     * \brief verifies if given string is a valid html document.
     * @param html string.
     * @return bool value.
     *
     * Checks html doctype tag.
     */
    bool isValid (const std::string& html) const override;

    /*!
     * \brief extract text of a page from html code
     * @param html source code of the page
     * @return plain text from the page
     *
     * Wrapper around gumbo library.
     * Uses internal dumpText method recursively to parse html code.
     */
    std::string extractText (const std::string& html) const override;

    /*!
     * \brief extract links from a page
     * @param html source code of the page
     * @return array of links from the page
     */
    std::vector<std::string> extractLinks (const std::string& html);

private:
    /*!
     * \brief dump text
     * @param html node
     * @param reference to a string that all text is concatenated to
     *
     * Recursively walks through an html tree and adds text from it to contents parameter.
     */
    void dumpText (const GumboNode* , std::string& ) const;

    void dumpLinks (const GumboNode*, std::vector<std::string>&);
};


#endif //CRAWLER_HTMLPARSER_H
