#!/bin/bash
set -e

# Holt den aktuellen Branchnamen zuverlässig einzeilig
BRANCH=$(git branch --show-current 2>/dev/null | tr -d '\r\n')
if [ -z "$BRANCH" ] || [ "$BRANCH" = "HEAD" ]; then
    BRANCH="main"
fi

MSG="${1:-Auto-Sync Update}"

echo "=========================================="
echo "  Universal Sync: $(basename "$PWD")"
echo "  Branch:         $BRANCH"
echo "=========================================="

git add .

if ! git diff-index --quiet HEAD -- 2>/dev/null; then
    git commit -m "$MSG"
else
    echo "Keine neuen lokalen Änderungen zum Committen."
fi

echo "Synchronisiere mit remote ($BRANCH)..."
if ! git pull --rebase origin "$BRANCH"; then
    echo "KONFLIKT oder Rebase-Fehler! Breche ab..."
    git rebase --abort 2>/dev/null || true
    echo "FEHLER: Bitte manuell prüfen!"
    exit 1
fi

echo "Pushe zu origin/$BRANCH..."
git push origin "$BRANCH"

echo "=========================================="
echo "  Erfolgreich synchronisiert!"
echo "=========================================="