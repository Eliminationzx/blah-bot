//
// Created by user on 12/15/16.
//

#include <math.h>
#include <map>

#include "IndexWriter.h"

using namespace std;
using namespace pqxx;

IndexWriter::IndexWriter (shared_ptr <connection> Conn)
    : conn (Conn)
{
    initQueries ();
}

void IndexWriter::initQueries ()
{
    conn->prepare (
            "findDocument",
            "SELECT * FROM documents WHERE id=$1;"
    );

    this->conn->prepare (
            "insertToken",
            "INSERT INTO index (token, documentid, tf, idf) VALUES ($1, $2, $3, $4);"
    );

    this->conn->prepare (
            "countDocuments",
            "SELECT count (id) FROM documents;"
    );

    this->conn->prepare (
            "countDocumentFrequency",
            "SELECT count (documentid) FROM index WHERE token=$1;"
    );
}

void IndexWriter::write (Document& doc)
{
    bool documentInDb;
    long numberOfDocuments = 0;
    long documentFrequency = 0;
    double df;
    map <string, long> counts;

    // check if the document is already in the index
    work w0 (*conn);

    auto res = w0.prepared ("findDocument")
            (doc.getId ())
            .exec ();

    w0.commit ();

    // TODO:: problem with concurrent access
    documentInDb = res.size () == 1;

    numberOfDocuments = this->countDocuments ();

    if (!documentInDb)
    {
        numberOfDocuments++;

        for (auto const& token : doc.getTokens ())
            counts[token.getData ()] = 1;
    }

    for (auto& token : doc.getTokens ())
    {
        df = this->countDocuments (token.getData ());

        token.setIdf (log10 (numberOfDocuments / df));
        counts[token.getData ()]++;
    }

    work w (*conn);

    for (auto& token : doc.getTokens ()) {
        w.prepared ("insertToken")
            (token.getData ())
            (doc.getId ())
            (counts[token.getData ()])
            (token.getIdf ())
            .exec ();
    }

    w.commit ();
}

long IndexWriter::countDocuments () {
    work w (*conn);

    auto res = w.prepared ("countDocuments").exec ();

    return res.front ()[0].as<long> ();
}

long IndexWriter::countDocuments (string token) {
    work w (*conn);

    auto res = w.prepared ("countDocumentFrequency").exec ();

    return res.front ()[0].as<long> ();
}
