-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pgreadfile" to load this file. \quit

CREATE OR REPLACE FUNCTION pgreadfile(path text)
RETURNS bytea
AS 'MODULE_PATHNAME' LANGUAGE C IMMUTABLE;

