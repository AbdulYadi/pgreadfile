# pgqr
PostgreSQL extension to read binary file

This project has been compiled successfully in Linux against PostgreSQL version 11.<br />
$ make clean<br />
$ make<br />
$ make install<br />

On successful compilation, install this extension in PostgreSQL environment<br />
$ create extension pgreadfile<br />

Let us read a file<br />
$ select pgreadfile('/tmp/myfile.dat');<br />
The output is binary data in bytea.<br />