// Copyright (c) 2023 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ============================================================================
#pragma once
#ifndef VERBOSE_H
#define VERBOSE_H

#include <cinttypes>
#include <mutex>
#include <stdio.h>
#include <sys/time.h>

class Printer {
public:
    static void gemm(const char* api_func, int M, int K, int N, double ms) {
        printf("xft_verbose,exec,cpu,api,%s,m%dk%dn%d,%g\n", api_func, M, K, N, ms);
    }
};

class Env {
private:
    static int verbose_value;

public:
    static void xft_set_verbose() {
        char* xft_verbose_value = getenv("XFT_VERBOSE");
        if (xft_verbose_value != NULL) {
            verbose_value = atoi(xft_verbose_value);
        } else {
            verbose_value = 0;
        }
    }

    static int xft_get_verbose() {
        return verbose_value;
    }
};

int Env::verbose_value = 0;

#define Verbose_GE1(api_func, compute_func) \
    if (Env::xft_get_verbose() >= 1) { \
        TimeLine t(api_func); \
        auto tag_0 = std::chrono::high_resolution_clock::now(); \
        decltype(tag_0) tag_1; \
        static std::chrono::duration ms = tag_0 - tag_0; \
        compute_func; \
        tag_1 = std::chrono::high_resolution_clock::now(); \
        ms += tag_1 - tag_0; \
        Printer::gemm(api_func, M, K, N, ms.count()); \
        fflush(stdout); \
    } else { \
        TimeLine t(api_func); \
        compute_func; \
    }

#endif





// Printer::gemm(api_func, M, K, N, ms.count()); 
