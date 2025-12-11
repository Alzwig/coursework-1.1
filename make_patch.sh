#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Путь до папки с кодом относительно скрипта(МЕНЯЕМ ТУТ ПУТЬ)!!!!!
SRC_DIR="$SCRIPT_DIR/src"

first_hash=$(git rev-list --max-parents=0 HEAD)

if git diff --quiet --exit-code "$SRC_DIR" && git diff --cached --quiet --exit-code "$SRC_DIR"; then
    echo "No changes in $SRC_DIR to commit. Skipping commit..."
    last_hash=$(git rev-parse HEAD)
else
    last_commit=$(git log --pretty=format:"%s" | grep -E "^comm:[0-9]+" | head -1)
    if [ -z "$last_commit" ]; then
        next_number=1
    else
        number=$(echo $last_commit | grep -oE "[0-9]+")
        next_number=$((number + 1))
    fi

    git add "$SRC_DIR"
    git commit -m "comm:$next_number"

    last_hash=$(git rev-parse HEAD)
    echo "Created commit: comm:$next_number ($last_hash)"
fi

PATCH_FILE="$SCRIPT_DIR/src.patch"
git diff --no-prefix "$first_hash" "$last_hash" -- "$SRC_DIR" > "$PATCH_FILE"
echo "Patch created: $PATCH_FILE"
