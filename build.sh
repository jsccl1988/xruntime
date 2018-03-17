#!/bin/sh
gn --root=src args out/debug
ninja -C out/debug
