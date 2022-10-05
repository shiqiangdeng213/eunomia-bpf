/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
 *
 * Copyright (c) 2022, 郑昱笙，濮雯旭，张典典（牛校牛子队）
 * All rights reserved.
 */

#ifndef ECLI_EUNOMIA_RUNNER_H
#define ECLI_EUNOMIA_RUNNER_H

#include <memory>
#include <string>
#include <thread>

#include "config.h"
#include "eunomia/eunomia-bpf.hpp"

/// program
class eunomia_program
{
    eunomia::eunomia_ebpf_program program;
    program_config_data current_config;
    friend class eunomia_runner;

  public:
    eunomia_program(const program_config_data &config)
      : current_config(config){};
    void run_ebpf_program();
};

class eunomia_runner
{
  private:
    friend class tracker_manager;
    eunomia_program ep;

  public:
    std::thread thread;
    /// create a tracker with deafult config
    static std::unique_ptr<eunomia_runner> create_tracker_with_args(
        const program_config_data &config)
    {
        return std::make_unique<eunomia_runner>(config);
    }

    eunomia_runner(const program_config_data &config)
      : ep(config){};
    ~eunomia_runner() { stop_tracker(); }

    /// start process tracker
    void start_tracker() { ep.run_ebpf_program(); }
    const std::string get_name(void) const
    {
        return ep.program.get_program_name();
    }

    /// stop the tracker thread
    void stop_tracker()
    {
        ep.program.stop_and_clean();
        if (thread.joinable()) {
            thread.join();
        }
    }
};

#endif