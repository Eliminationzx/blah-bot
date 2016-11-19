CREATE TABLE IF NOT EXISTS index 
(
    token text,
    documentid integer,
    tf REAL,
    idf REAL,
    FOREIGN KEY (documentid) REFERENCES documents (id)
);

CREATE TABLE IF NOT EXISTS documents
(
    id SERIAL PRIMARY KEY,
    url text,
    termsNumber integer
);

CREATE TABLE IF NOT EXISTS crawlerQueue
(
    url text
);

CREATE TABLE IF NOT EXISTS indexQueue
(
    url text,
    sourceCode text
);

CREATE TABLE IF NOT EXISTS sites
(
    id SERIAL PRIMARY KEY,
    address text,
    isallblocked boolean,
    lastupdate date
);

CREATE TABLE IF NOT EXISTS disallowedPages 
(
    address text
);