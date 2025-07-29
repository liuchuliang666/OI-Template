#!/usr/bin/env bash

set -e

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

source "$DIRNAME"/install-python.sh

# Install dependencies
pip install -r "$DIRNAME"/requirements.txt