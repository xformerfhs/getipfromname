# getipfromname

A simple program to get the ip addresses for a host name on Linux systems.

[![License](https://img.shields.io/github/license/xformerfhs/getipfromname)](https://github.com/xformerfhs/getipfromname/blob/main/LICENSE)

## Introduction

This is a simple program that returns all ip addresses that a given host name resolves to when querying the [DNS](https://en.wikipedia.org/wiki/Domain_Name_System).

I wrote it, because I needed a lightweight program that checks, if the DNS client is working.
It can also give a compact overview of the returned IP addresses.

It shows [IPv4](https://en.wikipedia.org/wiki/IPv4) and [IPV6](https://en.wikipedia.org/wiki/IPv6) addresses.

When I wrote the program I searched quite a few places for examples and all of them very simply plain wrong or overly complicated.
The documentation I found was also quite terse and difficult to understand, at least for me.

So this little utility may serve as an example of how to do DNS address lookups on Linux.

## Usage

Just call it with a list of host names.

## Return codes

When all look-ups were successful, the return code is `0`; otherwise, it is `1`.

## Example

Get the ip addresses of `changelogs.ubuntu.com`:

```bash
./getipfromname changelogs.ubuntu.com
```

The result will be something like this:

```
changelogs.ubuntu.com => (91.189.91.48, 91.189.91.49, 185.125.190.17, 185.125.190.18, 2620:2d:4000:1::2b, 2001:67c:1562::23, 2001:67c:1562::24, 2620:2d:4000:1::2a)
```

## Contact

Frank Schwab ([Mail](mailto:github.sfdhi@slmails.com "Mail"))

## License

This source code is published under the [Apache License V2](https://www.apache.org/licenses/LICENSE-2.0.txt).

