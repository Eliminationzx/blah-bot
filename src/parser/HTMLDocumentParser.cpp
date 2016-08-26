//
// Created by user on 7/25/16.
//

#include <gumbo.h>
#include "HTMLDocumentParser.h"

using namespace std;

HTMLDocumentParser::HTMLDocumentParser () {

}

HTMLDocumentParser::~HTMLDocumentParser () {

}

bool HTMLDocumentParser::isValid (const std::string &html) const {
    if (html.substr (0, 9) == "<!DOCTYPE" || html.substr (0, 9) == "<!doctype")
        return true;

    return false;
}

string HTMLDocumentParser::extractText (const std::string& html) const {
    auto output = gumbo_parse (html.data ());

    string text;
    this->dumpText (output->root, text);

    gumbo_destroy_output (&kGumboDefaultOptions, output);

    return text.substr (0, text.size () - 1);
}

void HTMLDocumentParser::dumpText (const GumboNode* node, string& contents) const {
    if (node->type == GUMBO_NODE_TEXT) {
        contents.append (node->v.text.text);
    } else if (node->type == GUMBO_NODE_ELEMENT &&
            node->v.element.tag != GUMBO_TAG_SCRIPT &&
            node->v.element.tag != GUMBO_TAG_STYLE
    ) {
        auto children = &node->v.element.children;

        for (size_t i = 0; i < children->length; ++i) {
            if (contents.back () != ' ' && contents.length () > 0)
                contents.append (" ");

            this->dumpText (static_cast<GumboNode*> (children->data[i]), contents);
        }
    }
}

vector<string> HTMLDocumentParser::extractLinks (const std::string& html) {
    auto gumboOutput = gumbo_parse (html.data ());
    vector<string> links;

    this->dumpLinks (gumboOutput->root, links);

    gumbo_destroy_output (&kGumboDefaultOptions, gumboOutput);

    return links;
}

void HTMLDocumentParser::dumpLinks (const GumboNode* node, std::vector<std::string>& links) {
    if (node->type == GUMBO_NODE_ELEMENT) {
        GumboAttribute* href;

        if (node->v.element.tag == GUMBO_TAG_A &&
                (href = gumbo_get_attribute (&node->v.element.attributes, "href"))
        )
            links.push_back (href->value);

        const GumboVector* children = &node->v.element.children;

        for (size_t i = 0; i < children->length; ++i) {
            dumpLinks ((GumboNode*) children->data[i], links);
        }
    }
}

//void HTMLDocumentParser::parse (Document& page) {
//    page.setText (this->extractText (page.getHtml ()));
//}
