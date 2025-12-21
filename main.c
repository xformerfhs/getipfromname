//
// SPDX-FileCopyrightText: Copyright 2025 Frank Schwab
//
// SPDX-License-Identifier: Apache-2.0
//
// SPDX-FileType: SOURCE
//
// Licensed under the Apache License, Version 2.0 (the "License");
// You may not use this file except in compliance with the License.
//
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Purpose: Main program for crypto benchmark.
//
// Author: Frank Schwab
//
// Version: 1.0.0
//
// Change history:
//    2025-10-31: V1.0.0: Created.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>


// ******** Private constants ********

/// Return code, when there was no error.
#define RC_OK 0

/// Return code, when there was an error.
#define RC_ERROR 1


// ******** Private variables ********

/// String representation of IP address.
char ipaddr_text[INET6_ADDRSTRLEN];  // Is allocated only once and has the largest possible length.


// ******** Private functions ********

/// @brief Prints all ip addresses (4 and 6) of the given host name.
/// @param hostname Host name.
/// @param hints The hints to be used for address lookup.
/// @return RC_OK, if there was no error; otherwise, RC_ERROR.
int printHostAddresses(const char * const hostname, const struct addrinfo * const hints) {
   // 1. Get address information with the supplied hints.
   struct addrinfo * results;
   const int rc = getaddrinfo(hostname, NULL, hints, &results);
   if (rc != 0) {
      fprintf(stderr, "Error getting address of host \"%s\": %s\n", hostname, gai_strerror(rc));
      return RC_ERROR;
   }

   fputs(hostname, stdout);
   fputs(" => (", stdout);

   // 2. Loop through all returned address information records.
   char withSeparator = 0;
   void* ipaddr;
   socklen_t ipaddr_len;

   for (
      const struct addrinfo* res = results;
      res != NULL;
      res = res->ai_next
      ) {
      if (withSeparator != 0)
         fputs(", ", stdout);
      else
         withSeparator = 0x7f;

      // The ip address starts on different boundaries, depending on the family.
      if (res->ai_family == AF_INET) {
         ipaddr = (void*) &((struct sockaddr_in *)res->ai_addr)->sin_addr;
         ipaddr_len = INET_ADDRSTRLEN;
      } else {
         ipaddr = (void*) &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
         ipaddr_len = INET6_ADDRSTRLEN;
      }

      // There can be no error, so we do not test for one.
      inet_ntop(res->ai_family, ipaddr, ipaddr_text, ipaddr_len);

      fputs(ipaddr_text, stdout);
   }

   // 3. Clean up.
   freeaddrinfo(results);

   puts(")");

   return RC_OK;
}

// ******** Main function ********

int main(const int argc, const char ** argv) {
   if (argc > 1) {
      // 1. Set hints for the getaddrinfo function.
      //    They need to be initialized only once and can be reused for each call.
      struct addrinfo hints = {0};

      hints.ai_family = AF_UNSPEC;      // We want V4 and V6 addresses.
      hints.ai_socktype = SOCK_STREAM;  // We are interested in streams, not datagrams.
      hints.ai_protocol = IPPROTO_TCP;  // We want only addresses suitable for a TCP connection.
      hints.ai_flags = AI_ADDRCONFIG;   // Only return address families that this system is configured to use.

      // 2. Loop through all given arguments.
      //    If any lookup fails, the program return code is RC_ERROR.
      //    Otherwise, it is RC_OK.
      int rc = RC_OK;
      for (int i = 1; i < argc; i++)
         rc |= printHostAddresses(argv[i], &hints);

      return rc;
   } else {
      fputs("No hostnames supplied\n", stderr);
      return RC_ERROR;
   }
}
