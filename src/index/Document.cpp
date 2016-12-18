//
// Created by user on 8/19/16.
//

#include <utility>

#include "Document.h"

using namespace std;

Document::Document (shared_ptr<DocumentParser> Parser)
    : parser (Parser)
{}

Document::~Document () {}

Document& Document::operator = (Document const& other)
{
    this->id = other.id;
    this->address = other.address;
    this->html = other.html;
    this->parser = other.parser;
    this->text = other.text;
    this->tokens = other.tokens;
    this->valid = other.valid;

    return *this;
}

Document& Document::operator = (Document&& other)
{
    this->id = move (other.id);
    this->address = move (other.address);
    this->html = move (other.html);
    this->parser = move (other.parser);
    this->text = move (other.text);
    this->tokens = move (other.tokens);
    this->valid = move (other.valid);

    return *this;
}

bool Document::parse () {
    if (!valid)
        return false;

    setText (parser->extractText (html));

    return true;
}

bool Document::checkHtml () {
    valid = parser->isValid (html);

    return valid;
}

unsigned long Document::getId () const {
    return id;
}

void Document::setId (unsigned long id) {
    Document::id = id;
}

std::string Document::getHtml () {
    return html;
}

bool Document::setHtml (const std::string &html) {
    Document::html = html;
    text.clear ();

    checkHtml ();

    if (!valid)
        this->html.clear ();

    return valid;
}

bool Document::setHtml (std::string&& html) {
    Document::html = move (html);

    checkHtml ();

    if (!valid)
        this->html.clear ();

    return valid;
}

std::string Document::getText () {
    return text;
}

void Document::setText (const std::string &text) {
    Document::text = text;
}

std::vector<Token> Document::getTokens () {
    return tokens;
}

void Document::setTokens (const std::vector<Token> &tokens) {
    Document::tokens = tokens;
}

void Document::setTokens (vector <string> tokens) {
    for (const auto& token : tokens) {
        this->tokens.emplace_back (token);
    }
}

bool Document::isValid () const {
    return valid;
}
