//
// Created by ololosh on 12/15/16.
//

#ifndef INDEXER_TOKEN_H
#define INDEXER_TOKEN_H

#include <string>

/*!
 * \brief stores all the information about a token
 */
class Token
{
    std::string data;               // the token itself
    double idf;
    double tf;

public:
    Token () = default;
    Token (std::string );
    Token (std::string, double, double);
    ~Token () = default;
    Token (const Token& ) = default;
    Token (Token&& ) noexcept;

    std::string getData ();
    const std::string getData () const;
    void setData (const std::string&);
    void setData (std::string&&);

    double getIdf ();
    const double getIdf () const;
    void setIdf (double);

    double getTf ();
    const double getTf () const;
    void setTf (double);
};


#endif //INDEXER_TOKEN_H
