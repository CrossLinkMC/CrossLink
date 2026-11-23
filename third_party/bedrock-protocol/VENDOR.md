# bedrock-protocol (vendored)

Upstream: https://github.com/EndstoneMC/bedrock-protocol
Commit:   ec394c9a437386448f60f33a7610ca3fb90fa089 (2026-10-30, v0.4.6)
License:  MIT (see ./LICENSE)
Targets:  protocol version 2225 (Minecraft Bedrock 1.26.60.30)

Layout mirrors an upstream *source release*:

  include/bedrock/protocol/**.hpp    runtime codec headers, copied verbatim
  generated/include/...              C++ emitted by `bpc`, committed so the build
                                     needs neither Python nor uv
  generated/include/bedrock/protocol/version.hpp
  generated/include/bedrock/protocol.hpp

Nothing here is edited by CrossLink. Regenerate after bumping the pinned commit with:

  python -m venv .venv && .venv/bin/pip install click griffe
  PYTHONPATH=<repo>/src <venv>/bin/python -m bedrock_protocol \
      --language cpp --out <out> --import-path <repo> <repo>/protocol/[!_]*.py

then reproduce `version.hpp` (PROJECT_VERSION + `__version__` from
`protocol/__init__.py`) and the umbrella `protocol.hpp` (one `#include` per
generated header), exactly as upstream's CMakeLists.txt does.
