#Exemplo

# trivy image -q -f json -o security/report.json "$1"

# TODO "In production, you might want to run Trivy with the --quiet and --exit-code flags for CI/CD compatibility"
# TODO Sera preciso instalar Trivy antes de correr este comando?



#!/usr/bin/env bash
# security/scan.sh
set -euo pipefail

# --- Check Docker Installation (NEEDED) ---
if ! command -v docker >/dev/null 2>&1; then
  echo "[x] Docker not found. Install Docker before running this script."
  exit 1
fi
if ! docker info >/dev/null 2>&1; then
  echo "[x] Docker is installed but is not running or you don't have the permissions."
  echo "    Check if Docker service is active and if your user belongs to the 'docker' group."
  exit 1
fi

# --- Read args ---
# Usage:
#   ./scan.sh                  -> scans nginx:latest (no pull)
#   ./scan.sh --pull           -> scans nginx:latest (with pull)
#   ./scan.sh ubuntu:22.04     -> scans ubuntu:22.04 (no pull)
#   ./scan.sh ubuntu:22.04 --pull -> scans ubuntu:22.04 (with pull)
if [[ "${1:-}" == "--pull" ]]; then
  IMAGE="nginx:alpine"
  PULL=true
else
  IMAGE="${1:-nginx:alpine}"
  [[ "${2:-}" == "--pull" ]] && PULL=true || PULL=false
fi

# --- Paths ---
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$ROOT_DIR/scans" # TODO directorio com nome de IMAGE, mas resolvendo questao dos ":"
CACHE_DIR="$ROOT_DIR/.trivy-cache"
JSON_FILE="$OUT_DIR/result.json" # TODO result ou report?
mkdir -p "$OUT_DIR" "$CACHE_DIR"

# --- Optional pre-pull ---
if $PULL; then
  echo "[i] Trying to pull $IMAGE..."
  if docker pull "$IMAGE" >/dev/null 2>&1; then
    echo "[✓] Pulled: $IMAGE (saved locally). Proceeding to analysis…"
  else
    echo "[!] Could not pull $IMAGE. Proceeding anyway with existing/local version."
  fi
else
  echo "[i] Skipping image pull. Using local copy of $IMAGE (or Docker will fetch on the fly)."
fi

# --- Run Trivy locally if present; else Docker fallback ---
if command -v trivy >/dev/null 2>&1; then
  echo "[i] Using local Trivy"
  trivy image -q -f json -o "$JSON_FILE" "$IMAGE"
else
  echo "[i] Local Trivy not found — using Docker fallback"
  docker run --rm \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -v "$CACHE_DIR":/root/.cache/trivy \
    -v "$OUT_DIR":/out \
    aquasec/trivy:latest \
    image -q -f json -o "/out/$(basename "$JSON_FILE")" "$IMAGE"
fi

echo "[✓] Report saved to: $JSON_FILE"