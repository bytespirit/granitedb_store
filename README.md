# granitedb
A (maybe) enhancement of rocksdb.

Rocksdb is a very powerful database library, and is being widely used in production.

Granitedb is based on rocksdb and try to provide an `usage pattern` of rocksdb and a couple of functions that is frequently used.

## Principle

Granitedb is designed in the following principles:

* Read fast
* Optimize write throughput
* Column based data storage
* Support write acknowledgement
* Support the scale of petabyte dataset
* Support data sharding
* Support commonly used data structure and atomic operations
