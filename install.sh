#!/bin/bash

# CHILLAR - Quick Setup Script
# This script installs all required dependencies

echo "╔════════════════════════════════════════╗"
echo "║  CHILLAR - Dependency Installation    ║"
echo "╚════════════════════════════════════════╝"
echo ""

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Check if Ubuntu/Debian or Fedora
    if [ -f /etc/debian_version ]; then
        echo "🐧 Detected: Ubuntu/Debian"
        echo "📦 Installing dependencies..."
        sudo apt-get update
        sudo apt-get install -y build-essential curl libcurl4-openssl-dev nlohmann-json3-dev
        echo "✓ Dependencies installed successfully!"
        
    elif [ -f /etc/fedora-release ]; then
        echo "🐧 Detected: Fedora/RedHat"
        echo "📦 Installing dependencies..."
        sudo dnf install -y gcc-c++ libcurl-devel nlohmann_json-devel
        echo "✓ Dependencies installed successfully!"
    fi

elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "🍎 Detected: macOS"
    echo "📦 Installing dependencies..."
    
    # Check if Homebrew is installed
    if ! command -v brew &> /dev/null; then
        echo "⚠️  Homebrew not found. Installing Homebrew first..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    
    brew install cmake curl nlohmann-json
    echo "✓ Dependencies installed successfully!"

elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "🪟 Detected: Windows"
    echo "⚠️  Manual installation required"
    echo "Please install:"
    echo "  1. MinGW-w64 or Visual Studio Build Tools"
    echo "  2. vcpkg (https://github.com/Microsoft/vcpkg)"
    echo "  3. Then run: vcpkg install curl nlohmann-json"
    exit 1
else
    echo "❓ Unknown OS: $OSTYPE"
    exit 1
fi

echo ""
echo "🔨 Building CHILLAR..."
make clean
make

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Build successful!"
    echo ""
    echo "🚀 To run the application:"
    echo "   ./chillar"
    echo ""
    echo "Or use: make run"
else
    echo "❌ Build failed!"
    exit 1
fi