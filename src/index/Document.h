//
// Created by user on 8/19/16.
//

#ifndef CRAWLER_DOCUMENT_H
#define CRAWLER_DOCUMENT_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "parser/HTMLDocumentParser.h"
#include "Token.h"

/*!
 * \brief Encapsualtes a document.
 *
 * Stores all the document's data such as it's source code, text, list of tokens etc.
 * Contains methods for parsing itself and verifying documents validity
 * using underlying abstract parser.
 * Works with any document format given respective parser for this format.
 */
class Document {
    std::shared_ptr<DocumentParser> parser;

    unsigned long id = 0;
    std::string address;
    std::string html;
    std::string text;
    std::vector<Token> tokens;
    bool valid = false;

public:
    Document () = delete;
    Document (std::shared_ptr<DocumentParser> );
    ~Document ();
    Document (const Document& ) = default;
    Document (Document&& ) = default;

    /*!
     * \brief parse document's code.
     *
     * Tries to parse the document. If the html code is invalid, returns false.
     */
    bool parse ();

    unsigned long getId () const;
    void setId (unsigned long id);

    const std::string &getHtml () const;

    /*!
     * \brief Set html code
     * @param html string
     * @returns whether the html code is valid or not
     */
    bool setHtml (const std::string &html);
    bool setHtml (std::string&& html);

    const std::string& getText () const;
    void setText (const std::string &text);

    const std::vector<Token> getTokens () const;
    void setTokens (const std::vector<Token> &tokens);
    void setTokens (std::vector <std::string> tokens);

    const std::string &getAddress () const {
        return address;
    }

    void setAddress (std::string address) {
        Document::address = address;
    }

    bool isValid () const;

private:
    /*!
     * \brief Checks if given html code is valid.
     * @returns valid value.
     *
     * Changes the valid flag respectively.
     */
    bool checkHtml ();
};


#endif //CRAWLER_DOCUMENT_H
