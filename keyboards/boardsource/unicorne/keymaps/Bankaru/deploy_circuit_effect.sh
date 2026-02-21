# ============================================================================
# CIRCUIT RGB EFFECT - FILE DEPLOYMENT SCRIPT
# ============================================================================
# Automated deployment script for circuit RGB effect implementation
# Version: 2.0 - Complete circuit effect deployment
# ============================================================================

#!/bin/bash

# Color codes for output formatting
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
KEYMAP_PATH="/home/phil/qmk_firmware/keyboards/boardsource/unicorne/keymaps/Bankaru"
BACKUP_DIR="${KEYMAP_PATH}/backup_$(date +%Y%m%d_%H%M%S)"

echo -e "${BLUE}============================================================================${NC}"
echo -e "${BLUE}    CIRCUIT RGB EFFECT - DEPLOYMENT SCRIPT${NC}"
echo -e "${BLUE}============================================================================${NC}"
echo

# Create backup directory
echo -e "${YELLOW}[INFO]${NC} Creating backup directory..."
mkdir -p "$BACKUP_DIR"
if [ $? -eq 0 ]; then
    echo -e "${GREEN}[SUCCESS]${NC} Backup directory created: $BACKUP_DIR"
else
    echo -e "${RED}[ERROR]${NC} Failed to create backup directory"
    exit 1
fi

# Backup existing files
echo -e "${YELLOW}[INFO]${NC} Backing up existing files..."
backup_files=(
    "rgb_matrix_user.inc"
    "config.h" 
    "keymap.c"
    "rules.mk"
    "rgb_matrix_user.h"
)

for file in "${backup_files[@]}"; do
    if [ -f "${KEYMAP_PATH}/${file}" ]; then
        cp "${KEYMAP_PATH}/${file}" "${BACKUP_DIR}/${file}"
        echo -e "${GREEN}[BACKUP]${NC} ${file} backed up"
    else
        echo -e "${YELLOW}[SKIP]${NC} ${file} not found, skipping backup"
    fi
done

echo

# Deploy simple version for testing
echo -e "${YELLOW}[INFO]${NC} Deploying SIMPLE VERSION for initial testing..."
deploy_files=(
    "rgb_matrix_user_simple.inc:rgb_matrix_user.inc"
    "config_circuit.h:config.h"
    "keymap_circuit.c:keymap.c"
    "rules_circuit.mk:rules.mk"
    "rgb_matrix_user.h:rgb_matrix_user.h"
)

echo -e "${BLUE}--- SIMPLE VERSION DEPLOYMENT ---${NC}"
for file_mapping in "${deploy_files[@]}"; do
    IFS=':' read -r source target <<< "$file_mapping"
    
    if [ -f "${KEYMAP_PATH}/${source}" ]; then
        cp "${KEYMAP_PATH}/${source}" "${KEYMAP_PATH}/${target}"
        echo -e "${GREEN}[DEPLOY]${NC} ${source} -> ${target}"
    else
        echo -e "${RED}[ERROR]${NC} Source file not found: ${source}"
    fi
done

echo

# Test compilation of simple version
echo -e "${YELLOW}[INFO]${NC} Testing SIMPLE VERSION compilation..."
echo -e "${BLUE}Command: make boardsource/unicorne:Bankaru-clean && make boardsource/unicorne:Bankaru${NC}"
echo -e "${YELLOW}[NOTE]${NC} This will test compilation but may fail without ARM toolchain"
echo

# Prompt user to proceed
read -p "Press Enter to continue with FULL VERSION deployment..."

# Deploy full version
echo -e "${YELLOW}[INFO]${NC} Deploying FULL VERSION with complete circuit effect..."
deploy_files_full=(
    "rgb_matrix_user_full.inc:rgb_matrix_user.inc"
    "config_circuit.h:config.h"
    "keymap_circuit.c:keymap.c"
    "rules_circuit.mk:rules.mk"
    "rgb_matrix_user.h:rgb_matrix_user.h"
)

echo -e "${BLUE}--- FULL VERSION DEPLOYMENT ---${NC}"
for file_mapping in "${deploy_files_full[@]}"; do
    IFS=':' read -r source target <<< "$file_mapping"
    
    if [ -f "${KEYMAP_PATH}/${source}" ]; then
        cp "${KEYMAP_PATH}/${source}" "${KEYMAP_PATH}/${target}"
        echo -e "${GREEN}[DEPLOY]${NC} ${source} -> ${target}"
    else
        echo -e "${RED}[ERROR]${NC} Source file not found: ${source}"
    fi
done

echo

# Test compilation of full version
echo -e "${YELLOW}[INFO]${NC} Testing FULL VERSION compilation..."
echo -e "${BLUE}Command: make boardsource/unicorne:Bankaru-clean && make boardsource/unicorne:Bankaru${NC}"
echo

# Summary
echo -e "${BLUE}============================================================================${NC}"
echo -e "${BLUE}    DEPLOYMENT SUMMARY${NC}"
echo -e "${BLUE}============================================================================${NC}"
echo -e "${GREEN}[SUCCESS]${NC} Backup created: ${BACKUP_DIR}"
echo -e "${GREEN}[SUCCESS]${NC} Simple version deployed: rgb_matrix_user_simple.inc"
echo -e "${GREEN}[SUCCESS]${NC} Full version deployed: rgb_matrix_user_full.inc"
echo -e "${GREEN}[SUCCESS]${NC} Configuration updated: config.h, rules.mk"
echo -e "${GREEN}[SUCCESS]${NC} Keymap updated: keymap.c"
echo
echo -e "${YELLOW}[NEXT STEPS]${NC}"
echo -e "1. Install ARM toolchain if not available:"
echo -e "   sudo apt install gcc-arm-none-eabi"
echo -e "2. Test simple version first:"
echo -e "   cd /home/phil/qmk_firmware"
echo -e "   make boardsource/unicorne:Bankaru"
echo -e "3. If simple works, test full version:"
echo -e "   cp rgb_matrix_user_full.inc rgb_matrix_user.inc"
echo -e "   make boardsource/unicorne:Bankaru"
echo -e "4. Flash firmware to your Unicorne keyboard"
echo
echo -e "${YELLOW}[DOCUMENTATION]${NC}"
echo -e "See CIRCUIT_EFFECT_GUIDE.md for complete documentation"
echo -e "See deployment files for detailed implementation"
echo
echo -e "${RED}[IMPORTANT]${NC} Always test SIMPLE version before FULL version!"
echo -e "${BLUE}============================================================================${NC}"