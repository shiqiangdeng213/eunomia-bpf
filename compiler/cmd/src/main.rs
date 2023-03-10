//!  SPDX-License-Identifier: MIT
//!
//! Copyright (c) 2023, eunomia-bpf
//! All rights reserved.
//!
mod compile_bpf;
mod config;
mod document_parser;
mod export_types;
mod wasm;

use anyhow::Result;
use clap::Parser;
use compile_bpf::*;
use config::{CompileOptions, EunomiaWorkspace};

fn main() -> Result<()> {
    let args = CompileOptions::parse();
    let workspace = EunomiaWorkspace::init(args)?;

    compile_bpf(&workspace.options)?;

    Ok(())
}
